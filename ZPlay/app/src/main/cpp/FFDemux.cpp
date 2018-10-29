//
// Created by bigfish on 2018/10/11.
//


#include "FFDemux.h"
#include "ZLog.h"

extern "C"{
#include <libavformat/avformat.h>
}

//分数转为浮点数
static  double  r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ? 0.:(double)r.num/(double)r.den;
}


void FFDemux::Close()
{
    mux.lock();
    if(ic)
    {
        avformat_close_input(&ic);
    }
    mux.unlock();
}
//打开文件或者流媒体 rtmp http rtsp
bool FFDemux::Open(const char *url)
{
    ZLOGI("Open file %s begin",url);
    Close();
    mux.lock();
    int re = avformat_open_input(&ic,url,0,0);
    if(re != 0 )
    {
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re,buf,sizeof(buf));
        ZLOGE("FFDemux open %s failed!",url);
        return false;
    }
   ZLOGI("FFDemux open %s success!",url);

    //读取文件信息
    re = avformat_find_stream_info(ic,0);
    if(re != 0 )
    {
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re,buf,sizeof(buf));
        ZLOGE("avformat_find_stream_info %s failed!",url);
        return false;
    }

    this->totalMs = ic->duration/(AV_TIME_BASE/1000);

    mux.unlock();
    ZLOGI("total ms = %d!",totalMs);

    GetVPara();
    GetAPara();
    return true;
}

//读取视频参数
ZParameter FFDemux::GetVPara()
{
    mux.lock();
    if (!ic) {
        mux.unlock();
        ZLOGE("GetVPara failed! ic is NULL！");
        return ZParameter();
    }
    //获取了视频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (re < 0) {
        mux.unlock();
        ZLOGE("av_find_best_stream failed!");
        return ZParameter();
    }
    videoStream = re;
    ZParameter para;
    para.para = ic->streams[re]->codecpar;
    mux.unlock();
    return para;
}

 ZParameter FFDemux::GetAPara(){
     mux.lock();
     if (!ic) {
         mux.unlock();
         ZLOGE("GetVPara failed! ic is NULL！");
         return ZParameter();
     }
     //获取了音频流索引
     int re = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
     if (re < 0) {
         mux.unlock();
         ZLOGE("av_find_best_stream failed!");
         return ZParameter();
     }
     audioStream = re;
     ZParameter para;
     para.para = ic->streams[re]->codecpar;
     para.channels = ic->streams[re]->codecpar->channels;
     para.sample_rate = ic->streams[re]->codecpar->sample_rate;
     mux.unlock();
     return para;

 }



//读取一帧数据，数据由调用者清理
ZData FFDemux::Read()
{
    mux.lock();
    if(!ic)
    {
        mux.unlock();
        return ZData();
    }

    ZData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic,pkt);
    if(re != 0)
    {
        mux.unlock();
        av_packet_free(&pkt);
        return ZData();
    }
    //XLOGI("pack size is %d ptss %lld",pkt->size,pkt->pts);
    d.data = (unsigned char*)pkt;
    d.size = pkt->size;
    if(pkt->stream_index == audioStream)
    {
        d.isAudio = true;
    }
    else if(pkt->stream_index == videoStream)
    {
        d.isAudio = false;
    }
    else
    {
        mux.unlock();
        av_packet_free(&pkt);
        return ZData();
    }

    //转换pts
    pkt->pts = pkt->pts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    pkt->dts = pkt->dts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    d.pts = (int)pkt->pts;
    //XLOGE("demux pts %d",d.pts);
    mux.unlock();
    return d;

}

//初始化
FFDemux::FFDemux()
{
    static bool isFirst = true;
    if(isFirst)
    {
        isFirst = false;
        //注册所有封装器
        av_register_all();

        //注册所有的解码器
        avcodec_register_all();

        //初始化网络
        avformat_network_init();
        ZLOGI("register ffmpeg!");
    }

}
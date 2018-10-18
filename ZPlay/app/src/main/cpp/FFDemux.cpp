//
// Created by bigfish on 2018/10/11.
//


#include "FFDemux.h"
#include "ZLog.h"

extern "C"{
#include <libavformat/avformat.h>
}


//打开文件或者流媒体 rtmp http rtsp
bool FFDemux::Open(const char *url)
{
    ZLOGI("Open file %s begin",url);
    //打开文件
    int re = avformat_open_input(&ic,url,0,0);
    if (re != 0 )
    {
        char buf[1024] = {0};
        av_strerror(re,buf,sizeof(buf));
        ZLOGE("FFDemux open %s failed!",url);
        return false;
    }

    ZLOGI("FFDemux open %s success!",url);

    //读取文件信息
    re = avformat_find_stream_info(ic,0);
    if (re != 0 )
    {
        char buf[1024] = {0};
        av_strerror(re,buf, sizeof(buf));
        ZLOGE("avformat_find_stream_info %s failed!",url);
        return false;
    }
    this->totalMs =  ic->duration/(AV_TIME_BASE/1000);//不一定有
    ZLOGI("total ms =  %d !",totalMs);

    GetVPara();
    GetAPara();
    return true;
}

//读取视频参数
ZParameter FFDemux::GetVPara()
{
    if (!ic)
    {
        ZLOGE("GetVPara  failed! ic is NULL!");
        return ZParameter();
    }
    //获取视频流索引
    int re =  av_find_best_stream(ic,AVMEDIA_TYPE_VIDEO,-1,-1,0,0);
    if (re < 0)
    {
        ZLOGE("av_find_best_stream failed!");
        return ZParameter();
    }
    videoStream = re;
    ZParameter para;
    para.para = ic->streams[re]->codecpar;

    return  para;
}

 ZParameter FFDemux::GetAPara(){
     if (!ic)
     {
         ZLOGE("GetVPara  failed! ic is NULL!");
         return ZParameter();
     }
     //获取音频流索引
     int re =  av_find_best_stream(ic,AVMEDIA_TYPE_AUDIO,-1,-1,0,0);
     if (re < 0)
     {
         ZLOGE("av_find_best_stream failed!");
         return ZParameter();
     }
     audioStream = re;
     ZParameter para;
     para.para = ic->streams[re]->codecpar;
     para.channels = ic->streams[re]->codecpar->channels;
     para.sample_rate = ic->streams[re]->codecpar->sample_rate;
     return  para;

 }



//读取一帧数据，数据由调用者清理
ZData FFDemux::Read()
{
    if(!ic)return ZData();

    ZData d;
    AVPacket *pkt = av_packet_alloc();

    //读取
    int re = av_read_frame(ic,pkt);
    if(re != 0)
    {
        av_packet_free(&pkt);//释放空间
        return ZData();
    }

   // ZLOGI("packet size=%d pts= %lld",pkt->size,pkt->pts);
    d.data = (unsigned char*)pkt;
    d.size = pkt->size;

    if (pkt->stream_index == audioStream)
    {
        d.isAudio = true;
    }
    else if (pkt->stream_index == videoStream)
    {
        d.isAudio = false;
    }
    else
    {
        av_packet_free(&pkt);//释放空间
        return ZData();
    }

    return  d;

}

//初始化
FFDemux::FFDemux()
{
    static bool isFirst = true;//非线程安全
    if (isFirst)
    {
        isFirst = false;//初始化
        //注册所有封装器
        av_register_all();
        //注册所有解码器
        avcodec_register_all();
        //初始化网络
        avformat_network_init();

        ZLOGI("register FFmpeg ");

    }




}
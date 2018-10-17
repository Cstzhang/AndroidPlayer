//
// Created by bigfish on 2018/10/12.
//
extern "C"
{

#include <libavcodec/avcodec.h>

}



#include "FFDecode.h"
#include "ZLog.h"

bool FFDecode::Open(ZParameter para)
{
    if(!para.para) return false;

    AVCodecParameters *p = para.para;

    //1 查找解码器
    AVCodec *cd = avcodec_find_decoder(p->codec_id);
    if (!cd)
    {
        ZLOGE("avcodec_find_encoder %d failed!",p->codec_id);
        return  false;
    }
    ZLOGI("avcodec_find_encoder success!");

    //2 创建解码上下文，并复制参数
    codec = avcodec_alloc_context3(cd);//创建
    avcodec_parameters_to_context(codec,p);//复制参数
    codec->thread_count = 8;//多线程解码

    //3 打开解码器
    int re = avcodec_open2(codec,0,0);
    if (re != 0)
    {
        char buf[1024] = {0};
        av_strerror(re,buf, sizeof(buf)-1);
        ZLOGE("avcodec_open2 failed !%s %d",buf,re);
        return false;
    }
    ZLOGI("avcodec_open2 success!");

    if(codec->codec_type == AVMEDIA_TYPE_VIDEO)
    {
        this->isAudio = false;

    }
    else
    {  //有字幕解码的时候不能这么写
        this->isAudio = this;
    }

    return true;
}


bool FFDecode::SendPacket(ZData pkt)
{
    if ( pkt.size <=0 || !pkt.data) return false;
    if (!codec)
    {
        ZLOGE("codec 失效 ");
        return false;
    }
    int re = avcodec_send_packet(codec,(AVPacket*)pkt.data);
    if (re != 0)
    {
        ZLOGE("avcodec_send_packet failed ");
        return false;
    }

    return true;
}

//从线程中获取解码结果
ZData FFDecode::RecvFrame()
{

    if (!codec)
    {
        ZLOGE("codec 失效 ");
        return ZData();
    }
    if(!frame)
    {
        frame = av_frame_alloc();
    }

    int re = avcodec_receive_frame(codec,frame);
    if(re != 0)
    {
        return  ZData();
    }
    ZData d;
    d.data = (unsigned char *)frame;
    if(codec->codec_type == AVMEDIA_TYPE_VIDEO)
    {
        d.size   = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
        d.width  = frame->width;
        d.height = frame->height;

    }
    else
    {
        //样本字节数 * 单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat)frame->format) * frame->nb_samples *2;
    }
    //复制数据
    memcpy(d.datas,frame->data, sizeof(d.datas));

    return d;
}
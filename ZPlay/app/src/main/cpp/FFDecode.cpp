//
// Created by bigfish on 2018/10/12.
//
extern "C"
{

#include <libavcodec/avcodec.h>
#include <libavcodec/jni.h>
}



#include "FFDecode.h"
#include "ZLog.h"


void FFDecode::InitHard(void *vm)
{
    av_jni_set_java_vm(vm,0);
}

bool FFDecode::Open(ZParameter para , bool isHard)
{
    if(!para.para) return false;
    AVCodecParameters *p = para.para;
    //1 查找解码器
    AVCodec *cd = avcodec_find_decoder(p->codec_id);
    if(isHard)
    {
        cd = avcodec_find_decoder_by_name("h264_mediacodec");
    }

    if(!cd)
    {
        ZLOGE("avcodec_find_decoder %d failed!  %d",p->codec_id,isHard);
        return false;
    }
    ZLOGI("avcodec_find_decoder success %d!",isHard);
    //2 创建解码上下文，并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec,p);

    codec->thread_count = 8;
    //3 打开解码器
    int re = avcodec_open2(codec,0,0);
    if(re != 0)
    {
        char buf[1024] = {0};
        av_strerror(re,buf,sizeof(buf)-1);
        ZLOGE("%s",buf);
        return false;
    }

    if(codec->codec_type == AVMEDIA_TYPE_VIDEO)
    {
        this->isAudio = false;
    }
    else
    {
        this->isAudio = true;
    }

    ZLOGI("avcodec_open2 success!");
    return true;
}


bool FFDecode::SendPacket(ZData pkt)
{
    if(pkt.size<=0 || !pkt.data)return false;
    if(!codec)
    {
        return false;
    }
    int re = avcodec_send_packet(codec,(AVPacket*)pkt.data);
    if(re != 0)
    {
        return false;
    }

    return true;
}

//从线程中获取解码结果
ZData FFDecode::RecvFrame()
{

    if(!codec)
    {
        return ZData();
    }
    if(!frame)
    {
        frame = av_frame_alloc();
    }
    int re = avcodec_receive_frame(codec,frame);
    if(re != 0)
    {
        return ZData();
    }
    ZData d;
    d.data = (unsigned char *)frame;
    if(codec->codec_type == AVMEDIA_TYPE_VIDEO)
    {
//        ZLOGI("===== AVMEDIA_TYPE_VIDEO ======");
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2])*frame->height;
        d.width = frame->width;
        d.height = frame->height;
    }
    else
    {
//        ZLOGI("===== AVMEDIA_TYPE_AUDIO ======");
        //样本字节数 * 单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat)frame->format)*frame->nb_samples*2;
    }
    d.format = frame->format;
    if(!isAudio)
        ZLOGE("data format is %d",frame->format);
    memcpy(d.datas,frame->data,sizeof(d.datas));

    return d;
}
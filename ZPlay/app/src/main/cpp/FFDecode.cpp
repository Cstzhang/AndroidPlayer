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


    return true;
}
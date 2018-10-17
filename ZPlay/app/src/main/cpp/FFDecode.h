//
// Created by bigfish on 2018/10/12.
//

#ifndef ZPLAY_FFDECODE_H
#define ZPLAY_FFDECODE_H


#include "ZParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;
class FFDecode:public IDecode

{
public:
    //打开文件
    virtual bool Open(ZParameter para);

    //future模型 多线程并发处理 发送数据到线程解码

    virtual bool SendPacket(ZData pkt);

    //从线程中获取解码结果 再次调用会复用上次空间，线程不安全
    virtual ZData RecvFrame();

protected:
    AVCodecContext *codec = 0;

    AVFrame *frame = 0;
};


#endif //ZPLAY_FFDECODE_H
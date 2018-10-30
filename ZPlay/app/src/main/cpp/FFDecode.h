//
// Created by bigfish on 2018/10/12.
//

#ifndef ZPLAY_FFDECODE_H
#define ZPLAY_FFDECODE_H


#include "ZParameter.h"
#include "IDecode.h"
#include <mutex>
struct AVCodecContext;
struct AVFrame;
class FFDecode:public IDecode

{
public:
    static void InitHard(void *vm);

    virtual bool Open(ZParameter para,bool isHard=false);
    virtual void Close();
    //future模型 发送数据到线程解码
    virtual bool SendPacket(ZData pkt);

    //从线程中获取解码结果，再次调用会复用上次空间，线程不安全
    virtual ZData RecvFrame();
    virtual  void  Clear();
protected:
    AVCodecContext *codec = 0;
    AVFrame *frame = 0;
    std::mutex mux;
};


#endif //ZPLAY_FFDECODE_H

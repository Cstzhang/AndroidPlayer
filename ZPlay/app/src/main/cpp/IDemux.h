//
// Created by bigfish on 2018/10/11.
//

#ifndef ZPLAY_IDEMUX_H
#define ZPLAY_IDEMUX_H

#include "ZData.h"
#include "IObserver.h"

//解封装接口
class IDemux: public IObserver
{

public:
    //打开文件或者流媒体 rtmp http rtsp
    virtual bool Open(const char *url) = 0;  //纯虚函数

    //读取一帧数据，数据由调用者清理
    virtual ZData Read() = 0;

    //总时长（毫秒）
    int totalMs = 0;

protected:
    virtual void Main();

};


#endif //ZPLAY_IDEMUX_H

//
// Created by bigfish on 2018/10/11.
//

#ifndef ZPLAY_FFDEMUX_H
#define ZPLAY_FFDEMUX_H



#include "IDemux.h"

struct AVFormatContext;

class FFDemux: public IDemux
{

public:
    //打开文件或者流媒体 rtmp http rtsp
    virtual bool Open(const char *url);
    //读取一帧数据，数据由调用者清理
    virtual ZData Read();
    //构造函数
    FFDemux();

private:
    AVFormatContext *ic = 0; //初始值无参数构造函数才生效 c++11

};


#endif //ZPLAY_FFDEMUX_H

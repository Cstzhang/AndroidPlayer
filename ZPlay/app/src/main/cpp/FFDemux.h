//
// Created by bigfish on 2018/10/11.
//

#ifndef ZPLAY_FFDEMUX_H
#define ZPLAY_FFDEMUX_H



#include "IDemux.h"
#include <mutex>
struct AVFormatContext;

class FFDemux: public IDemux
{

public:
    //打开文件或者流媒体 rtmp http rtsp
    virtual bool Open(const char *url);
    //seek pos = 0.0 ~ 1.0
    virtual bool Seek(double pos);
    virtual void Close();
    //读取视频参数
    virtual ZParameter GetVPara();
    //读取音频参数
    virtual ZParameter GetAPara();

    //读取一帧数据，数据由调用者清理
    virtual ZData Read();
    //构造函数
    FFDemux();

private:
    AVFormatContext *ic = 0; //初始值无参数构造函数才生效 c++11
    std::mutex mux;
    int audioStream = 1;
    int videoStream = 0;
};


#endif //ZPLAY_FFDEMUX_H

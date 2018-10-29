//
// Created by bigfish on 2018/10/19.
//

#ifndef ZPLAY_IPLAYER_H
#define ZPLAY_IPLAYER_H


#include <mutex>
#include "ZThread.h"
#include "ZParameter.h"

class  IDemux;
class  IDecode;
class  IResample;
class  IVideoView;
class  IAudioPlay;

class IPlayer: public ZThread
{
public:
    static IPlayer *Get(unsigned char index=0);
    virtual bool Open(const char *path);
    virtual void Close();
    virtual bool Start();
    virtual void InitView(void *win);

    //是否硬解码
    bool isHardDecode = false;//默认不打开
    IDemux     *demux     = 0;
    IDecode    *vdecode   = 0;
    IDecode    *adecode   = 0;
    IResample  *resample  = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;
    //音频输出参数
    ZParameter outPara;

protected:

    void Main(); //用作音视频同步
    std::mutex mux;
    IPlayer();

};


#endif //ZPLAY_IPLAYER_H

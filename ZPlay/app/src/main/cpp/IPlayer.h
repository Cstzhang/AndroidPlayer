//
// Created by bigfish on 2018/10/19.
//

#ifndef ZPLAY_IPLAYER_H
#define ZPLAY_IPLAYER_H


#include "ZThread.h"

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
    virtual bool Start();
    //是否硬解码
    bool isHardDecode = true;
    IDemux     *demux     = 0;
    IDecode    *vdecode   = 0;
    IDecode    *adecode   = 0;
    IResample  *resample  = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;

protected:

    IPlayer();

};


#endif //ZPLAY_IPLAYER_H

//
// Created by bigfish on 2018/10/19.
//

#include "IPlayer.h"

#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "ZLog.h"
IPlayer *IPlayer::Get(unsigned char index)
{
    static IPlayer p[256];
    return  &p[index];
}

bool IPlayer::Open(const char *path)
{
    //解封装
    if(!demux || !demux->Open(path))
    {
        ZLOGE("demux->Open failed! %s",path);
        return false;
    }
    //解码 解码可能不需要 解封装后就是原始数据
    if(!vdecode || !vdecode->Open(demux->GetVPara(),isHardDecode))
    {
        ZLOGE("vdecode->Open failed! %s",path);
        //return false;
    }

    if(!adecode || !adecode->Open(demux->GetAPara()))
    {
        ZLOGE("vdecode->Open failed! %s",path);
        //return false;
    }
    //重采样 有可能不需要 解码后或者解封装后可之别播放
    ZParameter outPara = demux->GetAPara();
    if(!resample || resample->Open(demux->GetAPara(),outPara))
    {
        ZLOGE("resample->Open failed! %s",path);
    }

    return true;
}


bool IPlayer::Start()
{
    return true;
}

IPlayer::IPlayer()
{

}
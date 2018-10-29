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

//用作音视频同步
void IPlayer::Main()
{

    while (!isExit)
    {
        mux.lock();
        if(!audioPlay || !vdecode)
        {
            mux.unlock();
            ZSleep(2);
            continue;

        }
        //同步
        //获取音频的pts 告诉视频
        int apts = audioPlay->pts;
        ZLOGE(" apts %d",apts);
        vdecode->synPts = apts;

        mux.unlock();
        ZSleep(200);
    }

}
void IPlayer::Close()
{
    mux.lock();
    //1 先关闭主体线程 再清理观察者

    //同步线程
    ZThread::Stop();
    //解封装
    if(demux)
    {
        demux->Stop();
    }

    //解码
    if(vdecode)
    {
        vdecode->Stop();
    }

    if(adecode)
    {
        adecode->Stop();
    }


    //2 清理缓冲队列
    if(vdecode)
    {
        vdecode->Clear();
    }

    if(adecode)
    {
        adecode->Clear();
    }

    if(audioPlay)
    {
        audioPlay->Clear();
    }


    //3 清理资源
    if(audioPlay)
    {
        audioPlay->Close();
    }

    if(videoView)
    {
        videoView->Close();
    }

    if(vdecode)
    {
        vdecode->Close();
    }

    if(adecode)
    {
        adecode->Close();
    }

    if(demux)
    {
        demux->Close();
    }

    mux.unlock();
}


bool IPlayer::Open(const char *path)
{
    Close();
    mux.lock();
    //解封装
    if(!demux || !demux->Open(path))
    {
        mux.unlock();
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
    if(outPara.sample_rate <=0)
    {
        outPara = demux->GetAPara();
    }
    if(!resample || !resample->Open(demux->GetAPara(),outPara))
    {
        ZLOGE("resample->Open failed! %s",path);
    }
    mux.unlock();
    return true;
}


bool IPlayer::Start()
{
    mux.lock();

    if(audioPlay)
    {
        audioPlay->StartPlay(outPara);
    }
    if(vdecode)
    {
        vdecode->Start();
    }
    if (adecode)
    {
        adecode->Start();
    }



    if(!demux || !demux->Start())
    {
        mux.unlock();
        ZLOGE("demux->Start failed! ");
        return false;
    }




    ZThread::Start();

    mux.unlock();
    return true;
}

void IPlayer::InitView(void *win)
{
    if(videoView)
    {
        videoView->SetRender(win);
    }

}



IPlayer::IPlayer()
{

}
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
       // ZLOGE(" apts %d",apts);
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

    if(audioPlay)
    {
        audioPlay->Stop();
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

double IPlayer::PlayPos()
{

    double pos = 0.0;
    mux.lock();
    int total = 0;
    if(demux)
        total = demux->totalMs;
    if(total>0)
    {
        if(vdecode)
        {
            pos = (double)vdecode->pts/(double)total;
        }
    }
    mux.unlock();
//    ZLOGE("pos   %lld",vdecode->pts/total);
    return pos;
}

void IPlayer::SetPause(bool isP)
{
    mux.lock();
     ZThread::SetPause(isP);
    if(demux)
    {
        demux->SetPause(isP);
    }
    if(vdecode)
    {
        vdecode->SetPause(isP);
    }
    if(adecode)
    {
        adecode->SetPause(isP);
    }
    if(audioPlay)
    {
        audioPlay->SetPause(isP);
    }
    mux.unlock();

}

bool IPlayer::Seek(double pos)
{
    bool re = false;
    if(!demux) return false;

    //暂停所有线程
    SetPause(true);
    mux.lock();
    //清理缓冲
    //2 清理缓冲队列
    if(vdecode)
        vdecode->Clear(); //清理缓冲队列，清理ffmpeg的缓冲
    if(adecode)
        adecode->Clear();
    if(audioPlay)
        audioPlay->Clear();


    re = demux->Seek(pos); //seek跳转到关键帧
    if(!vdecode)
    {
        mux.unlock();
        SetPause(false);
        return re;
    }
    //解码到实际需要显示的帧
    int seekPts = pos*demux->totalMs;
    while(!isExit)
    {
        ZData pkt = demux->Read();
        if(pkt.size<=0)break;
        if(pkt.isAudio)
        {
            if(pkt.pts < seekPts)
            {
                pkt.Drop();
                continue;
            }
            //写入缓冲队列
            demux->Notify(pkt);
            continue;
        }

        //解码需要显示的帧之前的数据
        vdecode->SendPacket(pkt);
        pkt.Drop();
        ZData data = vdecode->RecvFrame();
        if(data.size <=0)
        {
            continue;
        }
        if(data.pts >= seekPts)
        {
            //vdecode->Notify(data);
            break;
        }
    }
    mux.unlock();

    SetPause(false);
    return re;

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
    outPara = demux->GetAPara();
//    if(outPara.sample_rate <=0)
//    {

//    }
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
//
//    if(vdecode)
//        vdecode->Start();
//
//
//
//    if(!demux || !demux->Start())
//    {
//        mux.unlock();
//        ZLOGE("demux->Start failed!");
//        return false;
//    }
//    if(adecode)
//        adecode->Start();
//    if(audioPlay)
//        audioPlay->StartPlay(outPara);


    ZThread::Start();

    mux.unlock();
    return true;
}

void IPlayer::InitView(void *win)
{
    if(videoView)
    {
        videoView->Close();
        videoView->SetRender(win);
    }

}




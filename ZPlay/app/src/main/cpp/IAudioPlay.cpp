//
// Created by bigfish on 2018/10/18.
//

#include "IAudioPlay.h"
#include "ZLog.h"


void IAudioPlay::Clear()
{
    framesMutes.lock();

    while (!frames.empty())
    {
        frames.front().Drop();
        frames.pop_front();

    }
    framesMutes.unlock();
}
ZData IAudioPlay::GetData()
{
    ZData d;
    isRunning = true;
    while(!isExit)
    {
        if(IsPause())
        {
            ZSleep(2);
            continue;
        }
        framesMutes.lock();
        if(!frames.empty())
        {
            //有数据返回
            d = frames.front();
            frames.pop_front();
            framesMutes.unlock();
            pts = d.pts;
            return  d;
        }

        framesMutes.unlock();
        ZSleep(1);
    }

    isRunning = false;
    //未获取数据
    return d;
}



void IAudioPlay::Update(ZData data)
{
   // ZLOGI("IAudioPlay::Update %d",data.size);
    //压入缓冲队列
    if(data.size <= 0 || !data.data)return;
    while(!isExit)
    {
        framesMutes.lock();
        if (frames.size() > maxFrame)
        {
            framesMutes.unlock();
            ZSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutes.unlock();
        break;
    }


}
//
// Created by bigfish on 2018/10/18.
//

#include "IAudioPlay.h"
#include "ZLog.h"

ZData IAudioPlay::GetData()
{
    ZData d;
    while(!isExit)
    {
        framesMutes.lock();
        if(!frames.empty())
        {
            d = frames.front();
            frames.pop_front();
            framesMutes.unlock();
            return  d;
        }

        framesMutes.unlock();
        ZSleep(1);
    }

    return d;
}



void IAudioPlay::Update(ZData data)
{
    ZLOGI("IAudioPlay::Update %d",data.size);
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
//
// Created by bigfish on 2018/10/18.
//

#ifndef ZPLAY_IAUDIOPLAY_H
#define ZPLAY_IAUDIOPLAY_H

#include "IObserver.h"
#include "ZParameter.h"
#include <list>
class IAudioPlay: public IObserver
{
public:
    //接收重采样数据 缓冲满后阻塞
    virtual void Update(ZData data);
    //获取缓冲数据，如果没有则阻塞
    virtual ZData GetData();
    virtual bool StartPlay(ZParameter out) = 0;
    virtual void Close() =  0;
    virtual void Clear();
    //最大缓冲
    int maxFrame = 100; //100帧
    int pts = 0;
protected:
    std::list<ZData> frames;//音频队列
    std::mutex framesMutes;

};


#endif //ZPLAY_IAUDIOPLAY_H

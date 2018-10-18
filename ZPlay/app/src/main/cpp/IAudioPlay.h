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
    virtual bool StartPlay(ZParameter out) = 0;
    //最大缓冲
    int maxFrame = 100; //100帧
protected:
    std::list<ZData> frames;//音频队列
    std::mutex framesMutes;

};


#endif //ZPLAY_IAUDIOPLAY_H

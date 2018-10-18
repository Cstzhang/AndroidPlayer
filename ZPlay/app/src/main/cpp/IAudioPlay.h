//
// Created by bigfish on 2018/10/18.
//

#ifndef ZPLAY_IAUDIOPLAY_H
#define ZPLAY_IAUDIOPLAY_H

#include "IObserver.h"
#include "ZParameter.h"
class IAudioPlay: public IObserver
{
public:
    //接收重采样数据
    virtual void Update(ZData data);
    virtual bool StartPlay(ZParameter out) = 0;

};


#endif //ZPLAY_IAUDIOPLAY_H

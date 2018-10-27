//
// Created by bigfish on 2018/10/17.
//

#ifndef ZPLAY_IRESAMPLE_H
#define ZPLAY_IRESAMPLE_H


#include "IObserver.h"
#include "ZParameter.h"
class IResample: public IObserver
{
public:
    virtual bool Open(ZParameter in,ZParameter out=ZParameter()) = 0;
    virtual ZData Resample(ZData indata) = 0;
    virtual void Close() = 0;
    virtual void Update(ZData data);
    int outChannels = 2;
    int outFormat = 1;
};


#endif //ZPLAY_IRESAMPLE_H

//
// Created by bigfish on 2018/10/17.
//

#ifndef ZPLAY_FFRESAMPLE_H
#define ZPLAY_FFRESAMPLE_H


#include "IResample.h"
struct SwrContext;
class FFResample: public IResample
{
public:
    virtual bool Open(ZParameter in,ZParameter out=ZParameter());
    virtual ZData Resample(ZData indata);
protected:
    SwrContext *actx = 0;

};


#endif //ZPLAY_FFRESAMPLE_H

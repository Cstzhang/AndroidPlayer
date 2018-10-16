//
// Created by bigfish on 2018/10/12.
//

#ifndef ZPLAY_IDECODE_H
#define ZPLAY_IDECODE_H


//解码接口，支持硬解码

#include "ZParameter.h"
#include "IObserver.h"

class IDecode:public IObserver
{
public:
    //打开解码器
    virtual bool Open(ZParameter para) = 0;


};


#endif //ZPLAY_IDECODE_H

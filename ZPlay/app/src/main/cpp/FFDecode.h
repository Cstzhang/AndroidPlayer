//
// Created by bigfish on 2018/10/12.
//

#ifndef ZPLAY_FFDECODE_H
#define ZPLAY_FFDECODE_H


#include "ZParameter.h"
#include "IDecode.h"

struct AVCodecContext;
class FFDecode:public IDecode

{
public:
    virtual bool Open(ZParameter para);

protected:
    AVCodecContext *codec = 0;


};


#endif //ZPLAY_FFDECODE_H

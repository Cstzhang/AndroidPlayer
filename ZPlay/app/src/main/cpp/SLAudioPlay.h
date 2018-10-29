//
// Created by bigfish on 2018/10/18.
//

#ifndef ZPLAY_SLAUDIOPLAY_H
#define ZPLAY_SLAUDIOPLAY_H

#include "IAudioPlay.h"

class SLAudioPlay:public IAudioPlay
{
public:
    virtual bool StartPlay(ZParameter out);
    virtual void Close();
    void PlayCall(void *bufq);

    SLAudioPlay();
    virtual ~SLAudioPlay();

protected:
    unsigned char *buf = 0;
    std::mutex mux;

};


#endif //ZPLAY_SLAUDIOPLAY_H

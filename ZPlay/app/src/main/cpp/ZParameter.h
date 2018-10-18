//
// Created by bigfish on 2018/10/12.
//

#ifndef ZPLAY_ZPARAMETER_H
#define ZPLAY_ZPARAMETER_H

struct  AVCodecParameters;

class ZParameter
{
public:
    AVCodecParameters *para = 0;
    int channels = 2; //样本数
    int sample_rate = 44100;//样本率

};


#endif //ZPLAY_ZPARAMETER_H

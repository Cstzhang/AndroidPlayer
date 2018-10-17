//
// Created by bigfish on 2018/10/16.
//

#ifndef ZPLAY_ZSHADER_H
#define ZPLAY_ZSHADER_H


class ZShader
{
public:
    //初始化
    virtual bool Init();

    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
};


#endif //ZPLAY_ZSHADER_H

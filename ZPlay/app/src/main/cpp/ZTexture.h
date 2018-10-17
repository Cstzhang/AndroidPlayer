//
// Created by bigfish on 2018/10/16.
//

#ifndef ZPLAY_ZTEXTURE_H
#define ZPLAY_ZTEXTURE_H


class ZTexture
{
public:
    static ZTexture *Create();

    virtual bool Init(void *win) = 0;

    virtual void Draw(unsigned char *data[],int width,int height) = 0;

};


#endif //ZPLAY_ZTEXTURE_H

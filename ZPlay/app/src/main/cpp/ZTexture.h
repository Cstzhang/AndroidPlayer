//
// Created by bigfish on 2018/10/16.
//

#ifndef ZPLAY_ZTEXTURE_H
#define ZPLAY_ZTEXTURE_H

enum ZTextureType
{
    ZTEXTURE_YUV420P = 0,    // Y4  U1  V1
    ZTEXTURE_NV12    = 25,   // Y4  UV1
    ZTEXTURE_NV21    = 26    // Y4  VU1
};


class ZTexture
{
public:
    static ZTexture *Create();
    virtual bool Init(void *win,ZTextureType type=ZTEXTURE_YUV420P) = 0;
    virtual void Draw(unsigned char *data[],int width,int height) = 0;

};


#endif //ZPLAY_ZTEXTURE_H

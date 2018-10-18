//
// Created by bigfish on 2018/10/16.
//

#include "ZTexture.h"
#include "ZLog.h"
#include "ZEGL.h"
#include "ZShader.h"

class CZTexture:public ZTexture
{
public:
    ZShader sh;
    ZTextureType type;
    virtual bool Init(void *win,ZTextureType type)
    {
        if(!win)
        {
            ZLOGE("ZTexture init failed win is NULL");
            return false;
        }
        //初始化EGL
        if(!ZEGL::Get()->Init(win))return false;

        //初始化shader
        sh.Init((ZShaderType)type);
        return true;
    }
    virtual void Draw(unsigned char *data[],int width,int height)
    {
        sh.GetTexture(0,width,height,data[0]);  // Y

        if(type == ZTEXTURE_YUV420P)
        {
            sh.GetTexture(1,width/2,height/2,data[1]);  // U
            sh.GetTexture(2,width/2,height/2,data[2]);  // V
        }
        else
        {
            sh.GetTexture(1,width/2,height/2,data[1], true);  // UV
        }
        sh.Draw();
        ZEGL::Get()->Draw();
    }

};


ZTexture *ZTexture::Create()
{
    return new CZTexture();
}
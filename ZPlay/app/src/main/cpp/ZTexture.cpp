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
    virtual bool Init(void *win)
    {
        if(!win)
        {
            ZLOGE("ZTexture init failed win is NULL");
            return false;
        }
        //初始化EGL
        if(!ZEGL::Get()->Init(win))
        {
            return false;
        }
        //初始化shader
        sh.Init();

        return true;
    }
};


ZTexture *ZTexture::Create()
{
    return new CZTexture();
}
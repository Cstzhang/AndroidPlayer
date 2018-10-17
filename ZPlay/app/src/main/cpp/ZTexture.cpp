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
        if(!ZEGL::Get()->Init(win))return false;

        //初始化shader
        sh.Init();

        return true;
    }
    virtual void Draw(unsigned char *data[],int width,int height)
    {
        sh.GetTexture(0,width,height,data[0]);      // Y
        sh.GetTexture(1,width/2,height/2,data[1]);  // U
        sh.GetTexture(2,width/2,height/2,data[2]);  // V
        sh.Draw();//显示
        ZEGL::Get()->Draw();

    }

};


ZTexture *ZTexture::Create()
{
    return new CZTexture();
}
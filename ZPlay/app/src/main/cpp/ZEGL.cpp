//
// Created by bigfish on 2018/10/16.
//

#include <android/native_window.h>
#include "ZEGL.h"
#include <EGL/egl.h>
#include "ZLog.h"

class CZEGL:public ZEGL
{
public:
    EGLDisplay display = EGL_NO_DISPLAY; //用于检测设备是否打开正常
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;
    virtual void Draw()
    {
        if(display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE)
        {
            return;
        }

        eglSwapBuffers(display,surface);

    }

    virtual bool Init(void *win)
    {
        ANativeWindow *nwin = (ANativeWindow *)win;

        //初始化EGL

        //1 获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if(display == EGL_NO_DISPLAY)
        {
            ZLOGE("eglGetDisplay failed!");
            return false;
        }
        ZLOGI("eglGetDisplay success!");
        //2 初始化Display
        if(EGL_TRUE != eglInitialize(display,0,0))
        {
            ZLOGI("eglInitialize failed!");
            return false;
        }
        ZLOGI("eglInitialize success!");

        //3 获取配置并创建surface
        EGLint configSpec [] = {
                EGL_RED_SIZE,8,
                EGL_GREEN_SIZE,8,
                EGL_BLUE_SIZE,8,
                EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = 0;
        EGLint numConfigs = 0;
        if(EGL_TRUE != eglChooseConfig(display,configSpec,&config,1,&numConfigs))
        {
            ZLOGE("eglChooseConfig failed!");
            return false;
        }
        ZLOGI("eglChooseConfig success!");
        surface = eglCreateWindowSurface(display,config,nwin,NULL);


        //4 创建并打开EGL上下文
        const EGLint ctxAttr[] = { EGL_CONTEXT_CLIENT_VERSION ,2, EGL_NONE};
        context = eglCreateContext(display,config,EGL_NO_CONTEXT,ctxAttr);
        if(context == EGL_NO_CONTEXT)
        {
            ZLOGE("eglCreateContext failed!");
            return false;
        }
        ZLOGI("eglCreateContext success!");

        if(EGL_TRUE != eglMakeCurrent(display,surface,surface,context))
        {
            ZLOGI("eglMakeCurrent failed!");
            return false;
        }
        ZLOGI("eglMakeCurrent success!");

        return true;
    }


};


ZEGL *ZEGL::Get()
{
    static CZEGL egl;
    return &egl;
}
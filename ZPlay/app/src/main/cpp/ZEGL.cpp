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

        //初始化egl
        //1 获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY)
        {
            ZLOGE("eglGetDisplay failed!");
            return false;
        }
        ZLOGI("eglGetDisplay success!");
        //2初始化display
        if (EGL_TRUE != eglInitialize(display,0,0))
        {
            ZLOGE("eglInitialize failed!");
            return false;
        }
        ZLOGI("eglInitialize success!");
        //3配置并创建surface 显示缓冲
        EGLint configSpec [] = {
                EGL_RED_SIZE,8,
                EGL_GREEN_SIZE,8,
                EGL_BLUE_SIZE,8,
                EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = 0;
        EGLint numConfig = 0;//config数量
        if (EGL_TRUE != eglChooseConfig(display,configSpec,&config,1,&numConfig))
        {
            ZLOGE("eglChooseConfig failed!");
            return false;
        }
        ZLOGI("eglChooseConfig success!");
        // 创建具体的surface 关联窗口和egl
        surface = eglCreateWindowSurface(display,config,nwin,NULL);

        //4 创建上下文 打开  关联opengl
        const EGLint ctxAttr [] = {
                EGL_CONTEXT_CLIENT_VERSION,2,
                EGL_NONE
        };
        context =  eglCreateContext(display,config,EGL_NO_CONTEXT,ctxAttr);
        if (context == EGL_NO_CONTEXT)
        {
                ZLOGE("eglCreateContext failed!");
                return false;
        }
        ZLOGI("eglCreateContext success!");

        //上下文切换
        if (EGL_TRUE != eglMakeCurrent(display,surface,surface,context))
        {
            ZLOGE("eglMakeCurrent failed!");
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
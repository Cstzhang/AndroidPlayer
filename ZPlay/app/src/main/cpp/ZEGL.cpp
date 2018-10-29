//
// Created by bigfish on 2018/10/16.
//

#include <android/native_window.h>
#include "ZEGL.h"
#include <EGL/egl.h>
#include <mutex>
#include "ZLog.h"

class CZEGL:public ZEGL
{
public:
    EGLDisplay display = EGL_NO_DISPLAY; //用于检测设备是否打开正常
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;
    std::mutex mux;
    virtual void Draw()
    {
        mux.lock();

        if(display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE)
        {
            mux.unlock();
            return;
        }

        eglSwapBuffers(display,surface);
        mux.unlock();
    }
    virtual void Close()
    {
        mux.lock();
        if(display == EGL_NO_DISPLAY)
        {
            mux.unlock();
            return;;
        }

        eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);//去除绑定
        if(surface != EGL_NO_SURFACE)
        {  eglDestroySurface(display,surface);//清理surface
        }
        if(context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(display,context);//清理context
        }

        eglTerminate(display);

        display = EGL_NO_DISPLAY;
        surface = EGL_NO_SURFACE;
        context = EGL_NO_CONTEXT;
        mux.unlock();
    }

    virtual bool Init(void *win)
    {
        ANativeWindow *nwin = (ANativeWindow *)win;
        Close();
        //初始化EGL
        mux.lock();
        //1 获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if(display == EGL_NO_DISPLAY)
        {
            mux.unlock();
            ZLOGE("eglGetDisplay failed!");
            return false;
        }
        ZLOGI("eglGetDisplay success!");
        //2 初始化Display
        if(EGL_TRUE != eglInitialize(display,0,0))
        {
            mux.unlock();
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
            mux.unlock();
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
            mux.unlock();
            ZLOGE("eglCreateContext failed!");
            return false;
        }
        ZLOGI("eglCreateContext success!");

        if(EGL_TRUE != eglMakeCurrent(display,surface,surface,context))
        {
            mux.unlock();
            ZLOGI("eglMakeCurrent failed!");
            return false;
        }
        ZLOGI("eglMakeCurrent success!");
        mux.unlock();
        return true;
    }


};


ZEGL *ZEGL::Get()
{
    static CZEGL egl;
    return &egl;
}
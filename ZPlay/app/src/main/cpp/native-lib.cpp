#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
//#include "FFPlayerBuilder.h"

//#include "FFDemux.h"
//#include "ZLog.h"
//#include "IDecode.h"
//#include "FFDecode.h"
//#include "ZEGL.h"
//#include "ZShader.h"
//#include "IVideoView.h"
//#include "GLVideoView.h"
//#include "FFResample.h"
//#include "IAudioPlay.h"
//#include "SLAudioPlay.h"
//
//#include "IPlayer.h"

#include "IPlayerProxy.h"



//IVideoView *view = NULL;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm ,void *res)
{

    IPlayerProxy::Get()->Init(vm);
    IPlayerProxy::Get()->Open("/sdcard/1080.mp4");
    IPlayerProxy::Get()->Start();


    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_zplay_zplay_ZPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);//获取到窗口对象

    IPlayerProxy::Get()->InitView(win);

}


extern "C" JNIEXPORT jstring

JNICALL
Java_zplay_zplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    return env->NewStringUTF(hello.c_str());
}

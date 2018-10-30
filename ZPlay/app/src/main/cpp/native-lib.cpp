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
//#include "ZLog.h"



//IVideoView *view = NULL;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm ,void *res)
{

    IPlayerProxy::Get()->Init(vm);

//    IPlayerProxy::Get()->Open("/sdcard/1080.mp4");
//    IPlayerProxy::Get()->Start();
//    ZSleep(500);
//    IPlayerProxy::Get()->Close();
//    IPlayerProxy::Get()->Open("/sdcard/1080v.mp4");
//    IPlayerProxy::Get()->Start();

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_zplay_zplay_ZPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);//获取到窗口对象

    IPlayerProxy::Get()->InitView(win);

}


extern "C"
JNIEXPORT void JNICALL
Java_zplay_zplay_OpenUrl_Open(JNIEnv *env, jobject instance, jstring url_) {

    const char *url = env->GetStringUTFChars(url_, 0);

    // TODO
//    ZLOGI("OPEN URL %s",url);
    IPlayerProxy::Get()->Open(url);
    IPlayerProxy::Get()->Start();

    env->ReleaseStringUTFChars(url_, url);
}extern "C"
JNIEXPORT jdouble JNICALL
Java_zplay_zplay_MainActivity_PlayPos(JNIEnv *env, jobject instance) {

    // TODO
    return IPlayerProxy::Get()->PlayPos();

}extern "C"
JNIEXPORT void JNICALL
Java_zplay_zplay_MainActivity_Seek(JNIEnv *env, jobject instance, jdouble pos) {

    // TODO

    IPlayerProxy::Get()->Seek(pos);
}extern "C"
JNIEXPORT void JNICALL
Java_zplay_zplay_ZPlay_playOrPause(JNIEnv *env, jobject instance) {

    IPlayerProxy::Get()->SetPause(!IPlayerProxy::Get()->IsPause());

}
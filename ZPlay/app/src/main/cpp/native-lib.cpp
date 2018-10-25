#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "ZLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "ZEGL.h"
#include "ZShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include <android/native_window_jni.h>
#include "IPlayer.h"


IVideoView *view = NULL;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm ,void *res)
{
    FFDecode::InitHard(vm);

    ///////////////////////////////////
    ///测试用代码

    IDemux *de = new FFDemux();
    //de->AddObs(tobs);
//    de->Open("/sdcard/1080.mp4");


    IDecode *vdecode = new FFDecode();
    //vdecode->Open(de->GetVPara(), true);
//    vdecode->Open(de->GetVPara(), false);

    IDecode *adecode = new FFDecode();
//    adecode->Open(de->GetAPara());
    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample *resample = new FFResample();
//    ZParameter outPara = de->GetAPara();

//    resample->Open(de->GetAPara(),outPara);
    adecode->AddObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();

//    audioPlay->StartPlay(outPara);
    resample->AddObs(audioPlay);

    IPlayer::Get()->demux = de;
    IPlayer::Get()->adecode = adecode;
    IPlayer::Get()->vdecode = vdecode;
    IPlayer::Get()->videoView = view;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->audioPlay = audioPlay;



    IPlayer::Get()->Open("/sdcard/1080.mp4");
    IPlayer::Get()->Start();

    //vdecode->Open();
//    de->Start();
//    vdecode->Start();
//    adecode->Start();


    return JNI_VERSION_1_4;
}


extern "C" JNIEXPORT jstring

JNICALL
Java_zplay_zplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_zplay_zplay_ZPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);//获取到窗口对象
    IPlayer::Get()->InitView(win);
//    view->SetRender(win);



}
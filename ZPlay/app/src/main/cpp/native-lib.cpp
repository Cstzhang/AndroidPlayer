#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "ZLog.h"

extern "C" JNIEXPORT jstring

JNICALL
Java_zplay_zplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    IDemux *de = new FFDemux();
    de->Open("/sdcard/cat.mp4");
    de->Start();
    ZSleep(3000);
    de->Stop();
//    for (; ; ) {
//        ZData d = de->Read();
//        ZLOGI("read data size %d",d.size);
//    }


    return env->NewStringUTF(hello.c_str());
}

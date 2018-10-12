#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "ZLog.h"


class TestObs:public IObserver
{
public:
    void Update(ZData d)
    {
        ZLOGI("TestObs update data size is %d ",d.size);
    }

};



extern "C" JNIEXPORT jstring

JNICALL
Java_zplay_zplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    TestObs *tobs = new TestObs();

    IDemux *de = new FFDemux();
    de->AddObs(tobs);
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

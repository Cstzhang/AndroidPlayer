//
// Created by bigfish on 2018/10/11.
//

#ifndef ZPLAY_ZLOG_H
#define ZPLAY_ZLOG_H


class ZLog {

};
#ifdef ANDROID
#include <android/log.h>
#define ZLOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"ZPlay",__VA_ARGS__)
#define ZLOGI(...) __android_log_print(ANDROID_LOG_INFO,"ZPlay",__VA_ARGS__)
#define ZLOGE(...) __android_log_print(ANDROID_LOG_ERROR,"ZPlay",__VA_ARGS__)
#else
//其他平台

#endif


#endif //ZPLAY_ZLOG_H

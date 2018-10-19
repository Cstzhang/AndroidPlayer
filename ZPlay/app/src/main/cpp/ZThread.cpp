//
// Created by bigfish on 2018/10/12.
//

#include "ZThread.h"
#include <thread>
#include "ZLog.h"
using namespace std;

void ZSleep(int mis)
{
    chrono::milliseconds du(mis);//毫秒
    this_thread::sleep_for(du);
}


//启动线程
void ZThread::Start()
{

    isExit = false;

    thread th(&ZThread::ThreadMain,this);

    th.detach();//放弃对线程的控制

}

void ZThread::ThreadMain()
{

    isRunning = true;
//    ZLOGI("线程函数进入");
    Main();
//    ZLOGI("线程函数退出");
    isRunning = false;
}


//通过控制isExit安全停止线程（不一定成功）
void ZThread::Stop()
{
    isExit = true;
    for (int i = 0; i < 200; ++i) {//200毫秒
        if(!isRunning){
            ZLOGI("停止线程成功");
            return;
        }
        ZSleep(1);
    }
    ZLOGI("停止线程超时");

}



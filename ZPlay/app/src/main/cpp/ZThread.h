//
// Created by bigfish on 2018/10/12.
//

#ifndef ZPLAY_ZTHREAD_H
#define ZPLAY_ZTHREAD_H

//sleep 毫秒
void ZSleep(int mis);


//c++11 线程库
class ZThread
{
public:
    //启动线程
    virtual bool Start();

    //通过控制isExit安全停止线程（不一定成功）
    virtual void Stop();

    //入口主函数
    virtual void Main(){}

protected:
    bool isExit = false;
    bool isRunning = false;


private:
    void ThreadMain();


};


#endif //ZPLAY_ZTHREAD_H

//
// Created by bigfish on 2018/10/12.
//

#ifndef ZPLAY_IOBSERVER_H
#define ZPLAY_IOBSERVER_H


#include "ZData.h"
#include "ZThread.h"
#include <vector>
#include <mutex>
//观察者 和 主体
class IObserver:public ZThread
{

public:
    //观察者接收数据函数
    virtual void Update(ZData data) {}

    //主体函数 添加观察者（线程安全）
    void AddObs(IObserver *obs);

    //通知所有观察者
    void Notify(ZData data);

protected:
    std::vector<IObserver *>obss;
    std::mutex mux;

};


#endif //ZPLAY_IOBSERVER_H

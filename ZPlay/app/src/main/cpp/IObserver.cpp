//
// Created by bigfish on 2018/10/12.
//

#include "IObserver.h"


//主体函数
void IObserver::AddObs(IObserver *obs)
{
    if(!obs)return;

    mux.lock();
    obss.push_back(obs);
    mux.unlock();

}


//通知所有观察者
void IObserver::Notify(ZData data)
{
    mux.lock();
    for (int i = 0; i < obss.size(); ++i) {// obss.size()效率比较低 数据大的时候不要使用
        obss[i]->Update(data);
    }
    mux.unlock();


}
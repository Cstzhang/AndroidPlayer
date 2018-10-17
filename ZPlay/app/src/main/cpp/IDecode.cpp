//
// Created by bigfish on 2018/10/12.
//

#include "IDecode.h"
#include "ZLog.h"


//由主体notify的数据
void IDecode::Update(ZData pkt)
{
    if(pkt.isAudio != isAudio)
    {
        return;
    }

    while (!isExit)
    {

        packsMutex.lock();

        //阻塞
        if (packs.size() < maxList)
        {
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        ZSleep(1);
    }



}

void IDecode::Main()
{
    while (!isExit)
    {

        packsMutex.lock();
        if (packs.empty())
        {
            packsMutex.unlock();
            ZSleep(1);//释放当前占用的cpu
            continue;
        }
        //取出packet
        ZData pack = packs.front();//取出最早的数据
        packs.pop_front();//取出后在 链表中删除数据
        //发数据到解码线程
        if(this->SendPacket(pack))
        {
            while (!isExit)//可能一次send 多次recv 音频的时候会出现
            {
                //获取解码数据
                ZData frame = RecvFrame();
                if (!frame.data) break;
//                ZLOGI("RecvFrame %d",frame.size);
                //发送数据给观察者
                this->Notify(frame);
            }

        }

        pack.Drop();//清理数据


        packsMutex.unlock();


    }


}


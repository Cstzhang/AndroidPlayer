//
// Created by bigfish on 2018/10/11.
//

#include "IDemux.h"
#include "ZLog.h"


void IDemux::Main()
{
    while (!isExit)
    {
        if(IsPause())
        {
            ZSleep(2);
            continue;
        }
        ZData d = Read();
        if (d.size > 0){
            Notify(d); //没有人接收的时候要进行处理
        } else
        {
            ZSleep(2);
        }
    }

}

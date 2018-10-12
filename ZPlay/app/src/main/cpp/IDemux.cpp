//
// Created by bigfish on 2018/10/11.
//

#include "IDemux.h"
#include "ZLog.h"


void IDemux::Main()
{
    while (!isExit)
    {
        ZData d = Read();
        if (d.size > 0){
            Notify(d);
        }
      //  ZLOGI("IDemux Read %d",d.size);
        //if (d.size <=0) break;
    }

}

//
// Created by bigfish on 2018/10/17.
//

#include "IResample.h"
#include "ZLog.h"

void IResample::Update(ZData data)
{
    ZData d = this->Resample(data);
//    ZLOGI("IResample::Update %d",d.size);
    if (d.size > 0)
    {
        this->Notify(d);
    }
}
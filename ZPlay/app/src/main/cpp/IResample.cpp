//
// Created by bigfish on 2018/10/17.
//

#include "IResample.h"
void IResample::Update(ZData data)
{
    ZData d = this->Resample(data);
    if (d.size > 0)
    {
        this->Notify(d);
    }
}
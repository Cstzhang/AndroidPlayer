//
// Created by bigfish on 2018/10/11.
//

#include "ZData.h"
extern "C"{
#include <libavformat/avformat.h>
}
void ZData::Drop()
{
    if(!data)return;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}
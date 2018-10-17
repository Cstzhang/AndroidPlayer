//
// Created by bigfish on 2018/10/11.
//

#ifndef ZPLAY_ZDATA_H
#define ZPLAY_ZDATA_H


struct ZData {
    unsigned char *data = 0;
    unsigned char *datas[8] = {0};//解码后数据
    int size = 0;
    bool isAudio = false;
    int width = 0;
    int height = 0;
    //清理
    void Drop();

};


#endif //ZPLAY_ZDATA_H

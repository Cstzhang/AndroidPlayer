//
// Created by bigfish on 2018/10/11.
//

#ifndef ZPLAY_ZDATA_H
#define ZPLAY_ZDATA_H


struct ZData {
    unsigned char *data = 0;
    int size = 0;

    //清理
    void Drop();

};


#endif //ZPLAY_ZDATA_H

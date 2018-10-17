//
// Created by bigfish on 2018/10/16.
//

#ifndef ZPLAY_ZEGL_H
#define ZPLAY_ZEGL_H


class ZEGL
{
public:
    virtual bool Init(void *win) = 0;
    static ZEGL *Get();

protected:
    ZEGL(){}

};


#endif //ZPLAY_ZEGL_H

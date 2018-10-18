//
// Created by bigfish on 2018/10/16.
//

#ifndef ZPLAY_GLVIDEOVIEW_H
#define ZPLAY_GLVIDEOVIEW_H

#include "ZData.h"
#include "IVideoView.h"

class ZTexture;


class GLVideoView:public IVideoView
{
public:
    virtual void SetRender(void *win);
    virtual void Render(ZData data);

protected:
    //显示窗体
    void *view = 0;
    ZTexture *txt = 0;
};


#endif //ZPLAY_GLVIDEOVIEW_H

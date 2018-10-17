//
// Created by bigfish on 2018/10/16.
//

#include "GLVideoView.h"
#include "ZTexture.h"

void  GLVideoView::SetRender(void *win)
{
    view = win;
}
void  GLVideoView::Render(ZData data)
{
    if(!view)return;
    if(!txt)
    {
        //创建 texture
        txt  = ZTexture::Create();
        txt->Init(view);
    }




}
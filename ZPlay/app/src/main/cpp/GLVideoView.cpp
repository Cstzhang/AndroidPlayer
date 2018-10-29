//
// Created by bigfish on 2018/10/16.
//

#include "GLVideoView.h"
#include "ZTexture.h"

void  GLVideoView::SetRender(void *win)
{
    view = win;
}
void  GLVideoView::Close()
{
    mux.lock();

    if(txt)
    {
        txt->Drop();
        txt = 0;
    }

    mux.unlock();
}

void  GLVideoView::Render(ZData data)
{
    if(!view)return;
    if(!txt)
    {
        //创建 texture
        txt = ZTexture::Create();
        txt->Init(view,(ZTextureType)data.format);
    }
    txt->Draw(data.datas,data.width,data.height);

}
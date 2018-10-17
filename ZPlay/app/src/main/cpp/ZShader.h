//
// Created by bigfish on 2018/10/16.
//

#ifndef ZPLAY_ZSHADER_H
#define ZPLAY_ZSHADER_H


class ZShader
{
public:
    //初始化
    virtual bool Init();
    //获取材质并映射到内存
    /*
     *index 材质第几层索引
     * */
    virtual void GetTexture(unsigned int index,int width,int height, unsigned char *buf);
    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};

};


#endif //ZPLAY_ZSHADER_H

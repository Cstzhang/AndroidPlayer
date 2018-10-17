//
// Created by bigfish on 2018/10/16.
//

#include "ZShader.h"
#include "ZLog.h"
#include <GLES2/gl2.h>


//顶点着色器glsl
#define GET_STR(x) #x
static const  char *vertexShader = GET_STR(
        attribute vec4 aPosition;//顶点坐标
        attribute vec2 aTexCoord;//材质顶点坐标
        varying   vec2 vTexCoord;//输出的材质坐标 输出给片元着色器
        void main()
        {
            vTexCoord   = vec2(aTexCoord.x,1.0 - aTexCoord.y);
            gl_Position = aPosition;//显示顶点
        }
);

//片元着色器 软解码和部分x86硬解码 YUV420P
static const char *fragYUV420P = GET_STR(
        precision mediump float;//精度
        varying  vec2 vTexCoord;//顶点着色器传递的坐标
        uniform  sampler2D yTexture;//输入材质参数（不透明灰度,单像素）
        uniform  sampler2D uTexture;//输入材质参数
        uniform  sampler2D vTexture;//输入材质参数
        void main()
        {
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture,vTexCoord).r;
            yuv.g = texture2D(uTexture,vTexCoord).r - 0.5;
            yuv.b = texture2D(vTexture,vTexCoord).r - 0.5;
            rgb   = mat3(1.0,1.0,1.0,
                         0.0,-0.39425,2.03211,
                         1.13983,-0.5806,0.0)*yuv;
            //输出像素颜色
            gl_FragColor = vec4(rgb,1.0);
        }


);


//初始化着色器
static GLuint InitShader(const char *code,GLint type)
{
    //创建shader
    GLuint sh =  glCreateShader(type);
    if (sh == 0 ){
        ZLOGE(" glCreateShader  %d failed ! ",type);
        return 0;
    }
    //加载shader
    glShaderSource(
            sh,
            1,//shader数量
            &code,//shader代码
            0);//代码长度 传0自动查找计算

    //编译shader 显卡
    glCompileShader(sh);

    //获取编译情况
    GLint status;
    glGetShaderiv(sh,GL_COMPILE_STATUS,&status);
    if (status == 0){
        ZLOGE(" GL_COMPILE_STATUS   failed ! ");
        return 0;
    }
    ZLOGI(" init shader   success ! ");
    return sh;
}



bool ZShader::Init()
{
    //顶点和片元shader初始化
    //顶点
    vsh = InitShader(vertexShader,GL_VERTEX_SHADER);
    if (vsh == 0)
    {
        ZLOGE("InitShader vsh failed! ");
        return false;
    }
    ZLOGI("InitShader vsh success! ");
    //片元yuv420
    fsh = InitShader(fragYUV420P,GL_FRAGMENT_SHADER);
    if (fsh == 0)
    {
        ZLOGE("InitShader fsh failed! ");
        return false;
    }
    ZLOGI("InitShader fsh success! ");

    //////////////////////////////////////////////////////////
    //创建渲染程序
    program = glCreateProgram();
    if (program == 0){
        ZLOGE("glCreateProgram failed!");
        return false;
    }
    //向渲染程序中加入着色器
    glAttachShader(program,vsh);
    glAttachShader(program,fsh);
    //链接程序
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program,GL_LINK_STATUS,&status);
    if (status != GL_TRUE) {
        ZLOGE("glLinkProgram failed!");
        return false;
    }
    //激活渲染程序
    glUseProgram(program);
    ZLOGI("glLinkProgram success!");
    //////////////////////////////////////////////////////////
    //加入三维顶点数据 两个三角形组成正方形
    static float vers[] = {
            1.0f,-1.0f,0.0f,
            -1.0f,-1.0f,0.0f,
            1.0f,1.0f,0.0f,
            -1.0f,1.0f,0.0f,
    };
    //获取shader中的顶点变量
    GLuint apos = (GLuint)glGetAttribLocation(program,"aPosition");
    glEnableVertexAttribArray(apos);
    //传递顶点
    /*
     * apos 传到哪
     * 每一个点有多少个数据
     * 格式
     * 是否有法线向量
     * 一个数据的偏移量
     * 12 顶点有三个值（x,y，z）float存储 每个有4个字节 每一个值的间隔是 3*4 =12
     * ver 顶点数据
     * */
    glVertexAttribPointer(apos,3,GL_FLOAT,GL_FALSE,12,vers);

    //加入材质坐标数据
    static float txts[] = {
            1.0f,0.0f,//右下
            0.0f,0.0f,
            1.0f,1.0f,
            0.0f,1.0f
    };
    GLuint atex = (GLuint)glGetAttribLocation(program,"aTexCoord");
    glEnableVertexAttribArray(atex);
    glVertexAttribPointer(atex,2,GL_FLOAT,GL_FLOAT,8,txts);


    //设置纹理层 //需要处理 yuv420p nv12
    //TODO
    glUniform1i(glGetUniformLocation(program,"yTexture"),0);//对于纹理第1层
    glUniform1i(glGetUniformLocation(program,"uTexture"),1);//对于纹理第2层
    glUniform1i(glGetUniformLocation(program,"vTexture"),2);//对于纹理第3层

    ZLOGI("初始化ZShader success!");

    return true;

}
//
//  ball.hpp
//  macForC++
//
//  Created by aa on 2019/11/20.
//  Copyright © 2019 aa. All rights reserved.
//  用于渲染小球图像

#ifndef ball_hpp
#define ball_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "public.hpp"

class ball
{
public:
    //初始化球的 速度， 位置
    ball(vector2 oldPosition, SDL_Renderer * ballRender);
    ~ball(void);
    
public:
    //绘制小球
//    float x,float y, int width,int height
    void drowBall();
    //球的运动方向被改变
    
    void presentBall();
    //设置小球的位置
//    void setBallPossition(float x,float y);
    
    void setBallPossition(vector2  position) {this->ballposion = position;};
    //获取球的位置
    vector2 getBallPosition()const {return ballposion;}
    
private:
    //私有属性
    //小球的矢量速度
//    vector2 ballvector;
    
    float ball_X;
    float ball_Y;
    //小球的坐标
    vector2 ballposion;
    
    SDL_Renderer * ballrender;
};

#endif

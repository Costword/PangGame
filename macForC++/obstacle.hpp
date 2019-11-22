//
//  obstacle.hpp
//  macForC++
//
//  Created by aa on 2019/11/20.
//  Copyright © 2019 aa. All rights reserved.
//  障碍物

#ifndef obstacle_hpp
#define obstacle_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "public.hpp"

class obstacle
{
public:
    //初始化每个方块的位置
    obstacle(vector2 oldPosition, SDL_Renderer * ballRender);
    ~obstacle(void);
    
public:
    //绘制每个方块
    void drowObstacle();
    
   //获取每个方块的位置
    vector2 getObstaclePosition()const{return  positon;}
    
private:
    //方块的位置
    vector2 positon;
    //填充
    SDL_Renderer * render;
};

#endif 

//
//  ball.cpp
//  macForC++
//
//  Created by aa on 2019/11/20.
//  Copyright © 2019 aa. All rights reserved.
//

#include "ball.hpp"

//初始化球的位置及速度
ball::ball(vector2 oldPosition,SDL_Renderer*ballRender):
ballposion(oldPosition),ballrender(ballRender)
{
//   ball_X = oldPosition.x;
//   ball_Y = oldPosition.y;
}


//绘制小球
void ball::drowBall()
{
//    ball_X = x;
//    ball_Y = y;
    SDL_Rect ball = {
        static_cast<int>(ballposion.x),
        static_cast<int>(ballposion.y),
        kThickness*2,
        kThickness*2,
    };
    SDL_RenderFillRect(ballrender, &ball);
    
}



//
//void ball::setBallPossition(float x, float y)
//{
//    this->ball_X = x;
//    this->ball_Y = y;
//}
//
//
//vector2 ball::getBallPosition()
//{
//    this->ballposion.x = this->ball_X;
//    this->ballposion.y = this->ball_Y;
//    return this->ballposion;
//}

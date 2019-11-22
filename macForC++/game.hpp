//
//  game.hpp
//  macForC++
//
//  Created by aa on 2019/11/11.
//  Copyright © 2019 aa. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <vector>
#include "public.hpp"
#include "ball.hpp"
#include "obstacle.hpp"

class game
{
public:
    //初始化游戏
    game(SDL_Window * gameWindow,SDL_Renderer*gameRender,bool isrunning);
    void Intialize();
    //运行游戏循环直到结束
    void RunLoop();
    //关闭游戏
    void ShutDown();
private:
    //处理进程输入
    void ProcessInput();
    //更新游戏
    void UpdateGame();
    //生成输出
    void GenerateOutput();
    //通过sdl创建窗口
    SDL_Window * mygameWindow;
    //渲染器
    SDL_Renderer * mygameRenderer;
    //游戏继续运行
    bool gameIsRunning;
 
    //球拍 和 球 坐标
    vector2 mpadpos;
    vector2 mballpos;
    //球的初始运动方向
    vector2 mballVel;
    
    //记录运行时间
    uint32_t mTicksCount;
    ball * gameBall;
    //球拍方向
    int mPadDir;
    
    //设置障碍物数组
    std::vector<obstacle*>ObstacleArr;
};
#endif /* game_hpp */

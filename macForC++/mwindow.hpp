//
//  mwindow.hpp
//  macForC++
//
//  Created by aa on 2019/11/20.
//  Copyright © 2019 aa. All rights reserved.
//

#ifndef mwindow_hpp
#define mwindow_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "public.hpp"
#include "game.hpp"

class mwindow
{
public:
    //初始化窗口
    mwindow(void);
    ~mwindow(void);
public:
    //
    
    bool initWindow();
    
    void startGame();
    
    void updateGame();

    //通过sdl创建窗口
    SDL_Window * myWindow;
    //渲染器
    SDL_Renderer * mRenderer;
    //游戏继续运行
    bool mIsRunning;
    
    //创建游戏管理类
    game * myGame;
};

#endif /* mwindow_hpp */

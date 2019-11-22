//
//  mwindow.cpp
//  macForC++
//
//  Created by aa on 2019/11/20.
//  Copyright © 2019 aa. All rights reserved.
//

#include "mwindow.hpp"

mwindow::mwindow()
{
    
}


bool mwindow::initWindow()
{
    //返回值为0的时候证明初始化成功
      int sdlResult = SDL_Init(SDL_INIT_VIDEO);
      if (sdlResult != 0) {
          SDL_Log("不能初始化:%s",SDL_GetError());
          return false;
      }
      //创建游戏窗口
      myWindow = SDL_CreateWindow("我的乒乓球",//游戏标题
                                  100,//x
                                  100,//y
                                  kwindowW,//宽
                                  kwindowH,//高
                                  0);//默认标志位
      
      if (!myWindow) {
          SDL_Log("创建窗口失败%s",SDL_GetError());
          return false;
      }
      
      //创建渲染器
      mRenderer  = SDL_CreateRenderer(myWindow,//渲染窗口
                                      -1,//驱动程序索引（默认-1）
                                      SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);//采用硬件加速和保持刷新率一致
      if (!mRenderer) {
          SDL_Log("创建渲染器失败%s",SDL_GetError());
          return false;
      }
      return true;
}

void mwindow::startGame()
{
    myGame = new game(myWindow,mRenderer,true);
    myGame->Intialize();
    myGame->RunLoop();
}


mwindow::~mwindow(void)
{
    //销毁
}

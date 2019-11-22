//
//  game.cpp
//  macForC++
//
//  Created by aa on 2019/11/11.
//  Copyright © 2019 aa. All rights reserved.
//

#include "game.hpp"

////墙壁宽度 球拍厚度，球大小
//const int kThickness = 5;
//const int kpadW = 80;
//const int kwindowW = 500;
//const int kwindowH = 600;
//const float padSpeed = 500.f;



game::game(SDL_Window * gameWindow,SDL_Renderer*gameRender,bool isrunning):
mygameWindow(gameWindow),mygameRenderer(gameRender),gameIsRunning(isrunning),gameBall(nullptr)
{
    
}

//初始化球和墙的位置
void game::Intialize(){
    //初始化随机数种子
    srand((int)time(0));
    //初始化球拍和球的位置
    mpadpos.x = kwindowW/2.f;
    mpadpos.y = kwindowH;
    
    int ballx = 10 + rand()%480;
    mballpos.x = ballx/1.f;
    mballpos.y = kwindowH/4.f;
    
    //球的初始运动方向
    mballVel.x = -50.f;
    mballVel.y = 50.f;
    
    //初始化绘制球和球拍
    gameBall = new ball(mballpos,mygameRenderer);
    
    vector2 obsposition;
    for (int i = 0; i<5; i++) {
        
        for (int j = 0; j<98; j++) {
            obsposition.x = kThickness+ j*kThickness*2;
            obsposition.y = kThickness+ i*kThickness*2;
            obstacle * obs = new obstacle(obsposition,mygameRenderer);
            ObstacleArr.push_back(obs);
        }
    }
    
}

//关闭游戏
void game:: ShutDown()
{
    //销毁渲染器，窗口
    SDL_DestroyRenderer(mygameRenderer);
    SDL_DestroyWindow(mygameWindow);
    SDL_Quit();
}

//游戏循环
void game:: RunLoop()
{
    while (gameIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

//进程输入
/**
 *任何一个桌面操作系统用户都可以在窗口上执行操作，如拖动，最小，最大化等，这些不同的操作用不同的events进行表示
 用户执行不同的操作时，程序从操作系统接收事件，并根据事件作出响应
 *SDL维护了一个内部队列来接收保存传入操作系统的事件，并不需要我们处理所有的事件，对于用户的一些无理请求，我们可以选择忽略
 *控制游戏的位置通过键盘输入
 */
void game:: ProcessInput()
{
    //有event在队列就一直循环
    mPadDir = 0;
    SDL_Event event;
    //SDL_PollEvent 将在访问 SDL 内部事件队列，如果队列存在事件，将返回 true
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
                //退出循环程序
            case SDL_QUIT:
                gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                    {
                        //左移动
                        mPadDir -= 1;
                    }
                        break;
                    case SDLK_RIGHT:
                    {
                        //右移动
                        mPadDir += 1;
                    }
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    
}

//更新游戏
/**
 *游戏循环的时候有一点非常值得注意，时间。游戏循环不是连续的，是刷新率带来的错觉，游戏中的时间和现实中的时间也未必一样
 *例如在8MHz的处理器下运行和在16MHz的处理器下运行相同的代码 ;刷新率会快一倍，游戏速度也直接翻了一倍为了解决这个问题我们在游戏中使用  增量时间(deltaTime)  上一帧到现在的时间流逝长度
 *为了计算增量时间 SDL 提供了 SDL_GetTicks 函数返回从 SDL_Init 调用以来的毫秒数。通过存储上一帧的 SDL_GetTicks 的结果在成员变量里，就可以使用现在的值来计算增量时间。
 *声明一个时间变量 mTicksCount 初始化为0
 *有一些依赖物理的游戏，行为会根据帧速率不同而不同，最简单的解决方案就是限速，强制游戏循环需要等一个增量时间，例如目标帧数60fps 一帧完成时间仅15ms ，则强制附加1.6ms
 *SDL 已经为我们提供了限制帧速的方法 SDL_TICKS_PASSED
 *除了最短时间间隔我们还需要关注最长时间间隔，例如在调试的时候中断了游戏，过一段时间恢复运行，游戏将产生一个突跃，为了解决这个问题需设置一个增量时间最大值
 *球拍位置改变 在游戏中我们可以通过键盘使球拍左右移动-1表示向左 1表示向右 定义mPadDir表示方向
 *更新球的位置 球撞到墙壁和球拍会反弹 我们需要使用球的速度和对他进行速度检测，对速度的表示采用矢量分解 定义成员变量mballVel 初始化（-200.f , 235)代表球一开始向x轴负方向以200像素每秒y轴235像素每秒移动即向左下方移动
 *球撞击墙面和球拍的回弹 如果球撞击后需要向反方向回弹，即如果撞击右侧墙壁则需要在x乘以-1向左侧移动，撞击上下墙壁则在y方向乘以-1
 */
void game:: UpdateGame()
{
    //等到上一帧间隔16ms
    while (!SDL_TICKS_PASSED(SDL_GetTicks(),mTicksCount + 16));
    
    //此处多此一举，但是对于属性比较复杂的游戏类型还是建议分类创建
    mballpos = gameBall->getBallPosition();
    
    //增量时间就是上一帧到这一帧的时差
    float deltaTime = (SDL_GetTicks() - mTicksCount)/1000.f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    //更新运行时间为这一帧的时间
    mTicksCount = SDL_GetTicks();
    //根据方向更新球拍的位置 方向*速度*时间
    if (mPadDir != 0) {
        mpadpos.x += mPadDir*padSpeed*deltaTime;
        if (mpadpos.x<(kThickness+kpadW/2.f)) {
            mpadpos.x = kThickness+kpadW/2.f;
        }else if ((mpadpos.x+kpadW)>(kwindowW-kThickness))
        {
            mpadpos.x = kwindowW-kThickness-kpadW;
        }
    }
    //检查球是否与墙壁碰撞
    if ((mballpos.x+kThickness) >= (kwindowW-kThickness)) {
        //球与左右侧墙壁碰撞
        mballVel.x *= -1;
    }else if (mballpos.y <= kThickness){
        //球与上面墙壁碰撞
        mballVel.y *= -1;
    }else if (mballpos.x< kThickness)
    {
        mballVel.x *= -1;
    }
    
    //检查j球是否碰到障碍物
    if (ObstacleArr.size()==0) {
        std::cout << "YOU WIN" << std::endl;
    }else
    {
        for (int i =0;i<ObstacleArr.size(); i++) {
            vector2 tempVec = ObstacleArr[i]->getObstaclePosition();
            if (abs(mballpos.x-tempVec.x)>=0 && abs(mballpos.x-tempVec.x)<=10 && abs(mballpos.y-tempVec.y)>=0 && abs(mballpos.y-tempVec.y)<=10) {
                
                //左右的速度可以给一个随机值，不至于游戏过于单调
                int j = rand()%2;
                std::cout << "%d" << j<< std::endl;
                if (j==0) {
                    mballVel.x *= -1;
                }
                //掉头，销毁障碍
                mballVel.y *= -1;
                delete ObstacleArr[i];
                ObstacleArr.erase(ObstacleArr.begin()+i);
                break;
            }
        }
    }
    
    //检查球是否与球拍碰撞
    float balldiff = mballpos.x - (mpadpos.x-kpadW/2.f-0.2) ;
    
    //如果球落在球拍上且速度向下
    if (balldiff >= 0 && balldiff<= kpadW && (mballpos.y+kThickness*2)>=(kwindowH - kThickness) && mballVel.y>0) {
        //球回弹
        mballVel.y *= -1;
    }else if ((mballpos.y+kThickness*2)>(kwindowH - kThickness))
    {
        //球没进入球拍 游戏结束
        std::cout << "GAME OVER" << std::endl;
        gameIsRunning = false;
    }
    mballpos.x = mballpos.x + mballVel.x *deltaTime;
    mballpos.y = mballpos.y + mballVel.y * deltaTime;
    
    gameBall ->setBallPossition(mballpos);
}




//输出游戏
/**
 *后缓冲区：游戏写入的缓冲区。前缓冲区：显示器读取的缓冲区 （读取速度过快后缓冲区没写入完成就读取可能会造成画面撕裂）
 *任何游戏绘制图形的时候都包含三个步骤：
 *清空后缓冲区颜色
 *写入游戏场景
 *交换前后缓冲区
 *创建障碍物，障碍物有位置，当某个障碍物被撞击后消失，空余的位置可被小球穿过
 */
void game:: GenerateOutput(){
    
    //设置背景颜色，Tiffany蓝
       SDL_SetRenderDrawColor(mygameRenderer,
                              129,//R
                              216,//G
                              209,//B
                              255);//Alpha(0-255)
       //清空后缓冲区
       SDL_RenderClear(mygameRenderer);
       
       SDL_SetRenderDrawColor(mygameRenderer,
                                 0,//R
                                 0,//G
                                 255,//B
                                 255);//Alpha(0-255)
       //绘制“顶部墙”
       SDL_Rect wall{
           0,
           0,
           kwindowW,
           kThickness
       };
       //SDL_RenderFillRect 绘制矩形，传入SDL_Rect指针
       SDL_RenderFillRect(mygameRenderer, &wall);
       
       //绘制“左侧墙”
       wall = {
           0,
           0,
           kThickness,
           kwindowH
       };
       SDL_RenderFillRect(mygameRenderer, &wall);
       
       //绘制“右侧墙”
       wall = {
           kwindowW-kThickness+1,
           0,
           kThickness-1,
           kwindowH
       };
           
       SDL_RenderFillRect(mygameRenderer, &wall);
    
    //绘制障碍物
    
    for (int i = 0; i<ObstacleArr.size(); i++) {
        ObstacleArr[i]->drowObstacle();
    }

    
    //绘制球拍和球 球拍也可以分类封装（vector2中的xy指的是中心坐标，不符合SDL_Rect要求，需转化成左上角上的点）
       SDL_Rect pad {
           static_cast<int>(mpadpos.x - kpadW/2),
           static_cast<int>(mpadpos.y-kThickness),
           kpadW,
           kThickness
       };
       SDL_RenderFillRect(mygameRenderer, &pad);
    
        gameBall ->drowBall();
    
    //交换前后缓冲区
    SDL_RenderPresent(mygameRenderer);
    
}

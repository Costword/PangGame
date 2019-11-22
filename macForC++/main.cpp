//
//  main.cpp
//  macForC++
//
//  Created by aa on 2019/11/11.
//  Copyright © 2019 aa. All rights reserved.
//

#include <iostream>
#include "mwindow.hpp"
#include "game.hpp"

int main(int argc, const char * argv[]) {
    
    mwindow mwindow;
    //窗口初始化成功
    bool success = mwindow.initWindow();
    if (success) {
       //初始化成功
        mwindow.startGame();
    }
    return 0;
}

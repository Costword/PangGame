//
//  obstacle.cpp
//  macForC++
//
//  Created by aa on 2019/11/20.
//  Copyright © 2019 aa. All rights reserved.
//

#include "obstacle.hpp"

obstacle::obstacle(vector2 oldPosition, SDL_Renderer * ballRender):
positon(oldPosition),render(ballRender)
{
    
}


void obstacle::drowObstacle()
{
    SDL_Rect obstacle = {
           static_cast<int>(positon.x+1),
           static_cast<int>(positon.y+1),
           kThickness*2-1,
           kThickness*2-1,
       };
       SDL_RenderFillRect(render, &obstacle);
}


obstacle::~obstacle(void)
{
    
}

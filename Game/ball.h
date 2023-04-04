#include <bits/stdc++.h>
#include <raylib.h>
#include "data.h"
#pragma once

class Ball{

    public:
    float centre_x,centre_y;
    int speed_x, speed_y;
    int radius, directionx,directiony;
    bool hack;
    Ball(int r,int centrex, int centrey, Data &objd)
    {
        radius = r;
        centre_x=centrex/2;
        centre_y=centrey/2;
        speed_x=8+objd.diff*2;
        speed_y=8+ objd.diff*2;
        directionx=1;
        directiony=1;
    }
    void update(Data &objd)
    {
       
        if(hack==true)
        {       
            hack=false;
            directionx=-1*directionx;
        }
        else if(centre_y+radius>=objd.screen_height || centre_y-radius<=0)
        {
            directiony=-1*directiony;
        }
        else if(centre_x+radius >=objd.screen_width || centre_x-radius<=0)
        {
            if(centre_x+radius>=objd.screen_width)
                objd.score[0]++;
            else
                objd.score[1]++;
            if(objd.score[0]==10 || objd.score[1]==10)
                objd.win=true;
            centre_x=objd.screen_width/2;
            centre_y=objd.screen_height/2;
            directionx=-1*directionx;
            directiony=-1*directiony;
            speed_x=8 + 2*objd.diff;
            speed_y=8 +2 *objd.diff;

        }
        centre_x=centre_x+ (directionx*speed_x);
        centre_y=centre_y+ (directiony*speed_y);
    }

};

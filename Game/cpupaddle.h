#include <bits/stdc++.h>
#include <raylib.h>
#include "paddle.h"
#include "data.h"
#pragma once

class CPUPaddle: public Paddle{
    
    public:
    CPUPaddle(int x, int  y, int l, int b):Paddle(x,  y, l, b){
    }
    //easy diffculty
    void update(Ball obj , Data &objd)
    {
        if( obj.centre_x < (0.30 + objd.diff*0.1 )*objd.screen_width && centre_y>0 &&((centre_y + length/2 )>= obj.centre_y))
            centre_y-=speed_y-4+ objd.diff;
        if( obj.centre_x< (0.30 + objd.diff*0.1) *objd.screen_width && centre_y+120<objd.screen_height &&((centre_y + length/2 )<= obj.centre_y))
            centre_y+=speed_y-4+ objd.diff;
    }
};

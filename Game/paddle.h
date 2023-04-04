#include <bits/stdc++.h>
#include <raylib.h>
#include "data.h"
#pragma once

class Paddle{
    public:
    int centre_x, centre_y;
    int speed_x, speed_y;
    int length, breadth;

    Paddle(int x, int  y, int l, int b)
    {
        centre_x=x;
        centre_y=y;
        length=l;
        breadth=b;
        speed_x=9;
        speed_y=9;
    }
    void update(int h, bool r)
    {
        if( r==true and IsKeyDown(KEY_UP) && centre_y>0)
        {
            centre_y-=speed_x;
        }
        if(r==true and IsKeyDown(KEY_DOWN) && centre_y+length<=h)
        {
            centre_y+=speed_x;
        }
        if( r==false and IsKeyDown(KEY_W) && centre_y>0)
        {
            centre_y-=speed_x;
        }
        if(r==false and IsKeyDown(KEY_S) && centre_y+length<=h)
        {
            centre_y+=speed_x;
        }
    }
};

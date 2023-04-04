#include <raylib.h>
#pragma once
class Data{
    public:
    int screen_width;
    int screen_height;
    int score[2];
    bool win, menu, is_q, is_t, is_s, mm;
    int diff;
    
    Data()
    {
        screen_height=800;
        screen_width=1280;
        score[0]=0;
        score[1]=0;
        win=false;
        menu=true;
        is_q=true;
        is_s=false;
        is_t=false;
        mm=true;
        diff=0;
    }
};
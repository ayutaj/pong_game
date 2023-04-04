#include <bits/stdc++.h>
#include <raylib.h>
#include "./Game/ball.h"
#include "./Game/cpupaddle.h"
#include "./Game/paddle.h"
#include "./Game/data.h"
#include "./Game/funcclass.h"
using namespace std;

int main(){

    //declaring objects
    Data objd;
    Ball obj_ball(15,objd.screen_width,objd.screen_height,objd);
    Paddle person(objd.screen_width-30,objd.screen_height/2-60,120,10);
    Paddle person2(30,objd.screen_height/2-60,120,10);
    CPUPaddle pc(30,objd.screen_height/2-60,120,10);
    Func objf;

    //initating window
    InitWindow(objd.screen_width, objd.screen_height, "PONG!! Game");
    SetTargetFPS(60);

    //Game LOOP
    while (WindowShouldClose() == false and !IsKeyDown(KEY_Q))
    {
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        if(!objd.is_s and !objd.is_t and objd.is_q and objd.mm)
            objf.printmenu(objd);

        if(objd.mm==false and objd.is_s)
            objf.single_player(obj_ball,  person,  person2,pc,objd);
        
        if(objd.mm ==false and objd.is_t)
            objf.two_player(obj_ball,  person, person2,pc,objd);
       
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
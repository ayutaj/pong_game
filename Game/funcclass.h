#include <bits/stdc++.h>
#include <raylib.h>
#include "ball.h"
#include "cpupaddle.h"
#include "paddle.h"
#include "data.h"

class Func{
    public:

        
void checking_collisionabyme(Ball &obj_ball, Paddle person, CPUPaddle cp,Paddle person2, Data &objd)
{
        if(person.centre_y+person.length>obj_ball.centre_y-obj_ball.radius and person.centre_y<obj_ball.centre_y+obj_ball.radius
            and person.centre_x<=obj_ball.centre_x+obj_ball.radius and person.centre_x+person.breadth>=obj_ball.centre_x-obj_ball.radius)
        {
            obj_ball.hack=true;
            obj_ball.update(objd);
        }
        if(objd.is_s)
        {
            if(cp.centre_y+cp.length>obj_ball.centre_y-obj_ball.radius and cp.centre_y<obj_ball.centre_y+obj_ball.radius
                and cp.centre_x<=obj_ball.centre_x+obj_ball.radius and cp.centre_x+cp.breadth>obj_ball.centre_x-obj_ball.radius)
            {
                obj_ball.hack=true;
                obj_ball.update(objd);
            }
        }
        else
        {
            if(person2.centre_y+person2.length>obj_ball.centre_y-obj_ball.radius and person2.centre_y<obj_ball.centre_y+obj_ball.radius
                and person2.centre_x<=obj_ball.centre_x+obj_ball.radius and person2.centre_x+person2.breadth>obj_ball.centre_x-obj_ball.radius)
            {
                obj_ball.hack=true;
                obj_ball.update(objd);
            }

        }
}


void on_win(Data &objd)
{
    DrawLine(objd.screen_width/2,0,objd.screen_width/2,objd.screen_height,WHITE);
    if(objd.score[0]==10)
    {
        DrawRectangle(objd.screen_width/2-400,objd.screen_height/2-110,200,50,GREEN);
        DrawText("WINNER!!!",objd.screen_width/2-350,objd.screen_height/2-95,20,BLACK);
    }
    else 
    {
        DrawRectangle(objd.screen_width/2+200,objd.screen_height/2-110,200,50,GREEN);
        DrawText("WINNER!!!",objd.screen_width/2+250,objd.screen_height/2-95,20,BLACK);
    }
        DrawRectangle(objd.screen_width/2-150,objd.screen_height/2,320,50,WHITE);
        DrawText("Press SPACE to Continue",objd.screen_width/2-120,objd.screen_height/2+20,20,BLACK);
    if(IsKeyDown(KEY_SPACE))
    {
        objd.mm=true;
        objd.win=false;
        objd.is_s=false;
        objd.is_t=false;
        objd.score[0]=0;
        objd.score[1]=0;
        return ;
    }

}


void single_player(Ball &obj_ball, Paddle &person, Paddle &person2, CPUPaddle &pc, Data & objd)
{
    if(objd.menu==true)
    {
        DrawRectangle(objd.screen_width/2-150,objd.screen_height/2-110,300,50,WHITE);
        DrawText("EASY (PRESS E)",objd.screen_width/2-90,objd.screen_height/2-95,20,BLACK);
        DrawRectangle(objd.screen_width/2-150,objd.screen_height/2,300,50,WHITE);
        DrawText("MEDIUM (PRESS M)",objd.screen_width/2-90,objd.screen_height/2+20,20,BLACK);
        DrawRectangle(objd.screen_width/2-150,objd.screen_height/2+110,300,50,WHITE);
        DrawText("HARD (PRESS H)",objd.screen_width/2-90,objd.screen_height/2+125,20,BLACK);
        if(IsKeyDown(KEY_E))
        {
            objd.diff=0;
            objd.menu=false;
        }
        if(IsKeyDown(KEY_M))
        {
            objd.diff=1;
            obj_ball.update(objd);
            objd.menu=false;
        }
        if(IsKeyDown(KEY_H))
        {
            objd.diff=2;
            obj_ball.update(objd);
            objd.menu=false;
        }
    }
    else if(objd.win==false)
    {
        //Draobjd.wing task
        
        DrawCircle(obj_ball.centre_x,obj_ball.centre_y,obj_ball.radius, WHITE);
        DrawRectangle(person.centre_x,person.centre_y,person.breadth,person.length,WHITE);
        DrawRectangle(pc.centre_x,pc.centre_y,pc.breadth,pc.length,WHITE);
        DrawLine(objd.screen_width/2,0,objd.screen_width/2,objd.screen_height,WHITE);

        //Updating ball and paddle
        obj_ball.update(objd);
        person.update(objd.screen_height,true);
        pc.update(obj_ball,objd);

        //Checking collision
        checking_collisionabyme(obj_ball,person,pc,person2,objd);

        DrawText(TextFormat("%i",objd.score[0]),objd.screen_width/4-20,20,80,WHITE);
        DrawText(TextFormat("%i",objd.score[1]),3*objd.screen_width/4-20,20,80,WHITE);
    }
    else if(objd.win ==true)
            {
               on_win(objd);  
            }
        
}

void two_player(Ball &obj_ball, Paddle &person, Paddle &person2, CPUPaddle &pc, Data &objd)
{
       if(objd.win==false)
            {
                //Drawing task
                DrawCircle(obj_ball.centre_x,obj_ball.centre_y,obj_ball.radius, WHITE);
                DrawRectangle(person.centre_x,person.centre_y,person.breadth,person.length,WHITE);
                DrawRectangle(person2.centre_x,person2.centre_y,person2.breadth,person2.length,WHITE);
                DrawLine(objd.screen_width/2,0,objd.screen_width/2,objd.screen_height,WHITE);

                //Updating ball and paddle
                obj_ball.update(objd);
                person.update(objd.screen_height,true);
                person2.update(objd.screen_height,false);


                //Checking collision
                checking_collisionabyme(obj_ball,person,pc,person2,objd);

                DrawText(TextFormat("%i",objd.score[0]),objd.screen_width/4-20,20,80,WHITE);
                DrawText(TextFormat("%i",objd.score[1]),3*objd.screen_width/4-20,20,80,WHITE);
            }
            else if(objd.win ==true)
            {
                on_win(objd);
            }
}

void printmenu(Data &objd)
{
    objd.menu=true;
    objd.diff=0;
    DrawRectangle(objd.screen_width/2-250,objd.screen_height/2-110,400,50,WHITE);
    DrawText("SINGLE PLAYER (PRESS S)",objd.screen_width/2-200,objd.screen_height/2-95,20,BLUE);
    DrawRectangle(objd.screen_width/2-250,objd.screen_height/2,400,50,WHITE);
    DrawText("TWO PLAYER (PRESS T)",objd.screen_width/2-200,objd.screen_height/2+20,20,BLUE);
    DrawRectangle(objd.screen_width/2-250,objd.screen_height/2+110,400,50,WHITE);
    DrawText("QUIT (PRESS Q)",objd.screen_width/2-200,objd.screen_height/2+125,20,BLUE);
    if(IsKeyDown(KEY_Q))
    {
        objd.is_q=false;
        objd.mm=false;
    }
    if(IsKeyDown(KEY_S))
    {
        objd.is_s=true;
        objd.mm=false;
    }
    if(IsKeyDown(KEY_T))
    {
        objd.is_t=true;
        objd.mm=false;
    }
}

};
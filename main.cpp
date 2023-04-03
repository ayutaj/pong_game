#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;
int diff=0;
class Ball{

    public:
    float centre_x,centre_y;
    int speed_x, speed_y;
    int radius, directionx,directiony;
     bool hack;
    Ball(int r,int centrex, int centrey )
    {
        radius = r;
        centre_x=centrex/2;
        centre_y=centrey/2;
        speed_x=8+diff*2;
        speed_y=8+ diff*2;
        directionx=1;
        directiony=1;
    }
    void update(int height, int width, vector<int> &score, bool &win)
    {
       
        if(hack==true)
        {       
            hack=false;
            directionx=-1*directionx;
        }
        else if(centre_y+radius>=height || centre_y-radius<=0)
        {
            directiony=-1*directiony;
        }
        else if(centre_x+radius >=width || centre_x-radius<=0)
        {
            if(centre_x+radius>=width)
                score[0]++;
            else
                score[1]++;
            if(score[0]==2 || score[1]==2)
                win=true;
            centre_x=width/2;
            centre_y=height/2;
            directionx=-1*directionx;
            directiony=-1*directiony;
            speed_x=8 + 2*diff;
            speed_y=8 +2 *diff;

        }
        centre_x=centre_x+ (directionx*speed_x);
        centre_y=centre_y+ (directiony*speed_y);
    }

};

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

class CPUPaddle: public Paddle{
    
    public:
    CPUPaddle(int x, int  y, int l, int b):Paddle(x,  y, l, b){
    }
    //easy diffculty
    void update(int h,int w, Ball obj)
    {
        if( obj.centre_x < (0.30 + diff*0.1 )*w && centre_y>0 &&((centre_y + length/2 )>= obj.centre_y))
            centre_y-=speed_y-4+ diff;
        if( obj.centre_x< (0.30 + diff*0.1) *w && centre_y+120<h &&((centre_y + length/2 )<= obj.centre_y))
            centre_y+=speed_y-4+ diff;
    }
};

void checking_collisionabyme(Ball &obj_ball, Paddle person, CPUPaddle cp,Paddle person2, vector<int> &score, bool &win, bool is_s)
{
        if(person.centre_y+person.length>obj_ball.centre_y-obj_ball.radius and person.centre_y<obj_ball.centre_y+obj_ball.radius
            and person.centre_x<=obj_ball.centre_x+obj_ball.radius and person.centre_x+person.breadth>=obj_ball.centre_x-obj_ball.radius)
        {
            obj_ball.hack=true;
            obj_ball.update(800,1200,score, win);
        }
        if(is_s)
        {
            if(cp.centre_y+cp.length>obj_ball.centre_y-obj_ball.radius and cp.centre_y<obj_ball.centre_y+obj_ball.radius
                and cp.centre_x<=obj_ball.centre_x+obj_ball.radius and cp.centre_x+cp.breadth>obj_ball.centre_x-obj_ball.radius)
            {
                obj_ball.hack=true;
                obj_ball.update(800,1200,score, win);
            }
        }
        else
        {
            if(person2.centre_y+person2.length>obj_ball.centre_y-obj_ball.radius and person2.centre_y<obj_ball.centre_y+obj_ball.radius
                and person2.centre_x<=obj_ball.centre_x+obj_ball.radius and person2.centre_x+person2.breadth>obj_ball.centre_x-obj_ball.radius)
            {
                obj_ball.hack=true;
                obj_ball.update(800,1200,score, win);
            }

        }
}


void on_win(bool &mm, vector<int> &score, bool &win, bool &is_s, bool &is_t)
{
    int screen_width = 1280;
    int screen_height = 800;
   DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);
    if(score[0]==2)
    {
        DrawRectangle(screen_width/2-400,screen_height/2-110,200,50,GREEN);
        DrawText("WINNER!!!",screen_width/2-350,screen_height/2-95,20,BLACK);
    }
    else 
    {
        DrawRectangle(screen_width/2+200,screen_height/2-110,200,50,GREEN);
        DrawText("WINNER!!!",screen_width/2+250,screen_height/2-95,20,BLACK);
    }
        DrawRectangle(screen_width/2-150,screen_height/2,320,50,WHITE);
        DrawText("Press SPACE to Continue",screen_width/2-120,screen_height/2+20,20,BLACK);
    if(IsKeyDown(KEY_SPACE))
    {
        mm=true;
        win=false;
        is_s=false;
        is_t=false;
        score[0]=0;
        score[1]=0;
        return ;
    }

}


void single_player(Ball &obj_ball, Paddle &person, Paddle &person2, CPUPaddle &pc,bool &mm, bool &win, bool &is_s, bool &is_t,vector<int> &score,bool &menu)
{
    const int screen_width = 1280;
    const int screen_height = 800;
    if(menu==true)
    {
        DrawRectangle(screen_width/2-150,screen_height/2-110,300,50,WHITE);
        DrawText("EASY (PRESS E)",screen_width/2-90,screen_height/2-95,20,BLACK);
        DrawRectangle(screen_width/2-150,screen_height/2,300,50,WHITE);
        DrawText("MEDIUM (PRESS M)",screen_width/2-90,screen_height/2+20,20,BLACK);
        DrawRectangle(screen_width/2-150,screen_height/2+110,300,50,WHITE);
        DrawText("HARD (PRESS H)",screen_width/2-90,screen_height/2+125,20,BLACK);
        if(IsKeyDown(KEY_E))
        {
            diff=0;
            menu=false;
        }
        if(IsKeyDown(KEY_M))
        {
            diff=1;
            obj_ball.update(screen_height,screen_width,score,win);
            menu=false;
        }
        if(IsKeyDown(KEY_H))
        {
            diff=2;
            obj_ball.update(screen_height,screen_width,score,win);
            menu=false;
        }
    }
    else if(win==false)
    {
        //Drawing task
        
        DrawCircle(obj_ball.centre_x,obj_ball.centre_y,obj_ball.radius, WHITE);
        DrawRectangle(person.centre_x,person.centre_y,person.breadth,person.length,WHITE);
        DrawRectangle(pc.centre_x,pc.centre_y,pc.breadth,pc.length,WHITE);
        DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);

        //Updating ball and paddle
        obj_ball.update(screen_height,screen_width,score,win);
        person.update(screen_height,true);
        pc.update(screen_height,screen_width,obj_ball);

        //Checking collision
        checking_collisionabyme(obj_ball,person,pc,person2,score,win,is_s);

        DrawText(TextFormat("%i",score[0]),screen_width/4-20,20,80,WHITE);
        DrawText(TextFormat("%i",score[1]),3*screen_width/4-20,20,80,WHITE);
    }
    else if(win ==true)
            {
                on_win(mm,score,win, is_s, is_t);
                
            }
        
}

void two_player(Ball &obj_ball, Paddle &person, Paddle &person2, CPUPaddle &pc,bool &mm, bool &win, bool &is_s, bool &is_t,vector<int> &score)
{
    const int screen_width = 1280;
    const int screen_height = 800;
       if(win==false)
            {
                //Drawing task
                DrawCircle(obj_ball.centre_x,obj_ball.centre_y,obj_ball.radius, WHITE);
                DrawRectangle(person.centre_x,person.centre_y,person.breadth,person.length,WHITE);
                DrawRectangle(person2.centre_x,person2.centre_y,person2.breadth,person2.length,WHITE);
                DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);

                //Updating ball and paddle
                obj_ball.update(screen_height,screen_width,score,win);
                person.update(screen_height,true);
                person2.update(screen_height,false);


                //Checking collision
                checking_collisionabyme(obj_ball,person,pc,person2,score,win,is_s);

                DrawText(TextFormat("%i",score[0]),screen_width/4-20,20,80,WHITE);
                DrawText(TextFormat("%i",score[1]),3*screen_width/4-20,20,80,WHITE);
            }
            else if(win ==true)
            {
                on_win(mm,score,win,is_s,is_t);
            }
}

int main(){

    //declaring variables
    const int screen_width = 1280;
    const int screen_height = 800;
    vector<int> score(2,0);
    bool win =false, menu=true, is_q=true, is_t=false, is_s=false, mm=true;

    
    //initating window
    InitWindow(screen_width, screen_height, "PONG!! Game");
    SetTargetFPS(60);

    //declaring objects
    Ball obj_ball(15,screen_width,screen_height);
    Paddle person(screen_width-30,screen_height/2-60,120,10);
    Paddle person2(30,screen_height/2-60,120,10);
    CPUPaddle pc(30,screen_height/2-60,120,10);
    
    //Game LOOP
    while (WindowShouldClose() == false and !IsKeyDown(KEY_Q))
    {
        
        BeginDrawing();
        ClearBackground(BLACK);
        if(!is_s and !is_t and is_q and mm)
        {
            menu=true;
            diff=0;
            DrawRectangle(screen_width/2-250,screen_height/2-110,400,50,WHITE);
            DrawText("SINGLE PLAYER (PRESS S)",screen_width/2-200,screen_height/2-95,20,BLUE);
            DrawRectangle(screen_width/2-250,screen_height/2,400,50,WHITE);
            DrawText("TWO PLAYER (PRESS T)",screen_width/2-200,screen_height/2+20,20,BLUE);
            DrawRectangle(screen_width/2-250,screen_height/2+110,400,50,WHITE);
            DrawText("QUIT (PRESS Q)",screen_width/2-200,screen_height/2+125,20,BLUE);
            if(IsKeyDown(KEY_Q))
            {
                is_q=false;
                mm=false;
            }
            if(IsKeyDown(KEY_S))
            {
                is_s=true;
                mm=false;
            }
            if(IsKeyDown(KEY_T))
            {
                is_t=true;
                mm=false;
            }
        }

        if(mm==false and is_s)
        {
            single_player(obj_ball,  person,  person2, pc,mm, win, is_s, is_t,score,menu);
        }
        if(mm ==false and is_t)
        {
            two_player(obj_ball,  person,  person2, pc,mm, win, is_s, is_t,score);
        }
       
        EndDrawing();
    }
    
    

    CloseWindow();
    return 0;
}
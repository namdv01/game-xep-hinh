#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"
#include <ctime>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
using namespace std;

SDL_Window *menuwindow=NULL;
SDL_Renderer *menurenderer=NULL;
int menuwidth=600,menuheight=336;
SDL_Texture *menutexture=NULL;

SDL_Window *playwindow=NULL;
SDL_Renderer *playrenderer=NULL;
SDL_Texture *playtexture=NULL;
int playwidth=360,playheight=560;

SDL_Window *finishwindow=NULL;
SDL_Renderer *finishrenderer=NULL;
SDL_Texture *finishtexture=NULL;
int finishwidth=626,finishheight=626;
int BOARD[M][N]={0};

int dx=0,rotation=0;float curren,last=0,delay=0.3f;

int main(int argc,char** argv)
{
   srand(time(NULL));
   SDL_Init(SDL_INIT_VIDEO);
   menuwindow=GetWindow(menuwindow,menuwidth,menuheight);
   menurenderer=GetRenderer(menuwindow,menurenderer);
   menutexture=Load(menurenderer,start);
   bool run=true;
   tetrino a[4],b[4],c[4];
   GAMEPHASE game=GAMESTART;
   int random,restorerandom=-1;int soft=0;int chuyen=0;
   int x,y;
   GetTetrino(a,random,restorerandom);
   GetShown(c,a);
   while(run)
   {
      curren=SDL_GetTicks()/1000.0f;
      SDL_Event e;
      while(SDL_PollEvent(&e))
      {
         if(e.type==SDL_QUIT) run=false;
         if(e.type==SDL_KEYDOWN)
         {
            if(e.key.keysym.sym==SDLK_RIGHT) dx=1;
            else if(e.key.keysym.sym==SDLK_LEFT) dx=-1;
            else if(e.key.keysym.sym==SDLK_UP) rotation=1;
            else if(e.key.keysym.sym==SDLK_DOWN) delay=0.05f;
            else if(e.key.keysym.sym==SDLK_SPACE) soft=1;

         }
         if(e.type==SDL_MOUSEBUTTONDOWN)
         {
                if(game==GAMESTART)
                {
                    x=e.button.x;
                    y=e.button.y;
                    if(x>=250&&x<=350&&y>=180&&y<=220)
                    {
                        chuyen=1;
                    }
                    if(x>=250&&x<=350&&y>=230&&y<=270)
                    {
                        run=false;
                    }
                }
                if(game==GAMEOVER)
                {
                    x=e.button.x;
                    y=e.button.y;
                    if(x>=190&&x<=430&&y>=420&&y<=480)
                    {
                        chuyen=2;
                    }
                }
         }
      }


      if(game==GAMESTART)
      {
        SDL_RenderClear(menurenderer);
        SDL_RenderCopy(menurenderer,menutexture,NULL,NULL);
        SDL_RenderPresent(menurenderer);
        if(chuyen==1)
        {
            game=GAMEPLAY;
            playwindow=GetWindow(playwindow,playwidth,playheight);
            playrenderer=GetRenderer(playwindow,playrenderer);
            playtexture=Load(playrenderer,play);
            menuwindow=DestroyWindow(menuwindow);
            menurenderer=DestroyRenderer(menurenderer);
            menutexture=DestroyTexture(menutexture);
            chuyen=0;
        }

      }
      if(game==GAMEPLAY)
      {
          SDL_RenderClear(playrenderer);
          SDL_RenderCopy(playrenderer,playtexture,NULL,NULL);

         if(curren>last+delay)
         {
            last=curren;
            SoftTetrino(playrenderer,a,b);
            if(!Check(a,BOARD))
            {
               if(BOARD[b[0].y][b[0].x]==0)
               {
                  for(int i=0;i<4;i++)
                  {
                     BOARD[b[i].y][b[i].x]=THUTU[restorerandom];
                  }
                  GetTetrino(a,random,restorerandom);
               }
            }
         }

         MoveTetrino(a,b,dx);
         if(!Check(a,BOARD))
         {
            for(int i=0;i<4;i++)
            a[i]=b[i];
         }

         if(soft==1)
         {
             while(Check(a,BOARD)) SoftTetrino(playrenderer,a,b);
             soft=0;
         }
         RotateTetrino(a,rotation);
         if(!Check(a,BOARD))
         {
            for(int i=0;i<4;i++)
            a[i]=b[i];
         }
         DrawTetrino(playrenderer,a);
         GetShown(c,a);
         DrawShown(playrenderer,a,c,BOARD);
         DrawNext(playrenderer,a,random);
         EraseBoard(BOARD);
         DrawBoard(playrenderer,BOARD);
         delay=0.3f;
         SDL_RenderPresent(playrenderer);
         if(GameLose(BOARD)==true)
         {
             game=GAMEOVER;
             finishwindow=GetWindow(finishwindow,finishwidth,finishheight);
             finishrenderer=GetRenderer(finishwindow,finishrenderer);
             finishtexture=Load(finishrenderer,finish);
             for(int i=0;i<M;i++)
             {
                 for(int j=0;j<N;j++)
                 {
                     BOARD[i][j]=0;
                 }
             }
         }
      }
      if(game==GAMEOVER)
      {
         playwindow=DestroyWindow(playwindow);
         playrenderer=DestroyRenderer(playrenderer);
         playtexture=DestroyTexture(playtexture);
         SDL_RenderCopy(finishrenderer,finishtexture,NULL,NULL);
         SDL_RenderPresent(finishrenderer);
         if(chuyen==2)
         {
             game=GAMEPLAY;
             playwindow=GetWindow(playwindow,playwidth,playheight);
             playrenderer=GetRenderer(playwindow,playrenderer);
             playtexture=Load(playrenderer,play);
             finishwindow=DestroyWindow(finishwindow);
             finishrenderer=DestroyRenderer(finishrenderer);
             finishtexture=DestroyTexture(finishtexture);
             chuyen=0;
         }
      }
   }
         finishwindow=DestroyWindow(finishwindow);
         finishrenderer=DestroyRenderer(finishrenderer);
         finishtexture=DestroyTexture(finishtexture);
   SDL_Quit();
   return 0;
}



#include "game.h"

color GetColor(int r,int g,int b,int a)
{
   color x;
   x.r=r;
   x.g=g;
   x.b=b;
   x.a=a;
   return x;
}
SDL_Window* GetWindow(SDL_Window* Window,int width,int height)
{
    Window=SDL_CreateWindow("game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
    return Window;
}

SDL_Renderer* GetRenderer(SDL_Window* Window,SDL_Renderer* Renderer)
{
    Renderer=SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED);
    return Renderer;
}

SDL_Texture* Load(SDL_Renderer* Renderer,const string path)
{
    SDL_Surface* sur=IMG_Load(path.c_str());
    SDL_Texture* texture=SDL_CreateTextureFromSurface(Renderer,sur);
    SDL_FreeSurface(sur);
    return texture;
}

SDL_Window* DestroyWindow(SDL_Window* Window)
{
    SDL_DestroyWindow(Window);
    Window=NULL;
    return Window;
}

SDL_Renderer* DestroyRenderer(SDL_Renderer* Renderer)
{
    SDL_DestroyRenderer(Renderer);
    Renderer=NULL;
    return Renderer;
}

SDL_Texture* DestroyTexture(SDL_Texture* Texture)
{
    SDL_DestroyTexture(Texture);
    Texture=NULL;
    return Texture;
}

void GetTetrino(tetrino a[4],int &random,int &restorerandom)
{
   if(restorerandom<0)
   {
      random=rand()%7;
      restorerandom=random;
      random=rand()%7;
      for(int i=0;i<4;i++)
      {
         a[i].x=SetTetrino[restorerandom][i]%4+4;
         a[i].y=SetTetrino[restorerandom][i]/4;
         a[i].mau=COLORS[restorerandom];
      }
   }
   else
   {

      restorerandom=random;
      for(int i=0;i<4;i++)
      {
         a[i].x=SetTetrino[restorerandom][i]%4+4;
         a[i].y=SetTetrino[restorerandom][i]/4;
         a[i].mau=COLORS[restorerandom];
      }
      random=rand()%7;
   }

}

void MoveTetrino(tetrino a[4],tetrino b[4],int &dx)
{
   for(int i=0;i<4;i++)
   {
      b[i]=a[i];
      a[i].x+=dx;
   }
   dx=0;
}

void RotateTetrino(tetrino a[4],int &rotation)
{
   if(rotation!=0)
   for(int i=0;i<4;i++)
   {
      tetrino p=a[1];
      int x=a[i].y-p.y;
      int y=a[i].x-p.x;
      a[i].x=p.x-x;
      a[i].y=p.y+y;
   }
   rotation=0;
}

void DrawTetrino(SDL_Renderer *renderer,tetrino a[4])
{
   SDL_Rect rect;
   for(int i=0;i<4;i++)
   {
      rect.x=a[i].x*SIZE+50;
      rect.y=a[i].y*SIZE+100;
      rect.h=rect.w=SIZE;
      SDL_SetRenderDrawColor(renderer,a[i].mau.r,a[i].mau.g,a[i].mau.b,a[i].mau.a);
      SDL_RenderFillRect(renderer,&rect);
      SDL_SetRenderDrawColor(renderer,0,0,0,0);
      SDL_RenderDrawRect(renderer,&rect);
   }
}

void SoftTetrino(SDL_Renderer *renderer,tetrino a[4],tetrino b[4])
{
   for(int i=0;i<4;i++)
   {
      b[i]=a[i];
      a[i].y++;
   }
}

bool Check(tetrino a[4],int BOARD[M][N])
{
   for(int i=0;i<4;i++)
   {
      if(a[i].x<0||a[i].x>=N||a[i].y>=M) return 0;
      else if(BOARD[a[i].y][a[i].x]>0) return 0;
   }
   return 1;
}

void DrawBoard(SDL_Renderer *renderer,int BOARD[M][N])
{
   for(int i=0;i<M;i++)
      {
         for(int j=0;j<N;j++)
         {
            if(BOARD[i][j]==0) continue;
            SDL_Rect rect2;
            rect2.x=j*SIZE+50;
            rect2.y=i*SIZE+100;
            rect2.h=rect2.w=SIZE;

            color z=COLORS[BOARD[i][j]-1];
            SDL_SetRenderDrawColor(renderer,z.r,z.g,z.b,z.a);
            SDL_RenderFillRect(renderer,&rect2);
            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderDrawRect(renderer,&rect2);
         }
      }
}

void EraseBoard(int BOARD[M][N])
{

   for(int i=M-1;i>=0;i--)
   {
      int tich=1;
      for(int j=N-1;j>=0;j--)
      {
         tich*=BOARD[i][j];
      }
      if(tich!=0)
      {
         for(int h=i;h>0;h--)
            {
               for(int k=N-1;k>=0;k--)
               {
                  BOARD[h][k]=BOARD[h-1][k];
               }
            }
      }
   }
}

void DrawNext(SDL_Renderer *renderer,tetrino a[4],int &random)
{

   SDL_Rect rect3;
   for(int i=0;i<4;i++)
   {
      rect3.x=(SetTetrino[random][i]%4)*SIZE+290;
      rect3.y=(SetTetrino[random][i]/4)*SIZE+140;
      rect3.h=rect3.w=SIZE;
      SDL_SetRenderDrawColor(renderer,COLORS[random].r,COLORS[random].g,COLORS[random].b,COLORS[random].a);
      SDL_RenderFillRect(renderer,&rect3);
      SDL_SetRenderDrawColor(renderer,0,0,0,0);
      SDL_RenderDrawRect(renderer,&rect3);
   }

}

bool GameLose(int BOARD[M][N])
{
   int tong=0;
   for(int i=0;i<N;i++)
   {
      tong+=BOARD[0][i];
   }
   if(tong!=0) return true;
   return false;
}

void GetShown(tetrino c[4],tetrino a[4])
{
    for(int i=0;i<4;i++)
    {
      c[i]=a[i];
    }
}

void DrawShown(SDL_Renderer* renderer,tetrino a[4],tetrino c[4],int BOARD[M][N])
{
    while(Check(c,BOARD))
    {
        for(int i=0;i<4;i++) c[i].y++;
    }
    for(int i=0;i<4;i++)
    {
        if(c[i].y>0) c[i].y--;
    }
    SDL_Rect rect;
    for(int i=0;i<4;i++)
    {
      rect.x=c[i].x*SIZE+50;
      rect.y=c[i].y*SIZE+100;
      rect.h=rect.w=SIZE;

      SDL_SetRenderDrawColor(renderer,a[i].mau.r,a[i].mau.g,a[i].mau.b,a[i].mau.a);
      SDL_RenderDrawRect(renderer,&rect);
    }
}



#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;
const string start="menutetris.png";
const string play="New Bitmap Image.png";
const string finish="gameover.png";
const int M=20; //CHIEU CAO BANG TINH THEO KHOI
const int N=10; //CHIEU RONG BANG TINH THEO KHOI
const int SIZE=20;  //KICH CO PHONG DAI
const int THUTU[]={1,2,3,4,5,6,7};  //DANH DAU THU TU CAC KHOI TUONG UNG

enum GAMEPHASE
{
   GAMESTART,GAMEPLAY,GAMEOVER    //TRANG THAI GAME
};


struct color
{
   int r,g,b,a; //KHOI TAO KIEU MAU
};
color GetColor(int r,int g,int b,int a);//HAM TRA VE MAU SAC
const color COLORS[]=
{
    //CAC MAU CUA KHOI HINH
   GetColor(255,0,0,0),
   GetColor(0,255,0,0),
   GetColor(0,0,255,0),
   GetColor(255,255,0,0),
   GetColor(255,0,255,0),
   GetColor(0,255,255,0),
   GetColor(255,127,64,0)
};
struct tetrino  //KHOI HINH
{
   int x,y; //TOA DO 1 VIEN TRONG THANH PHAN 4 VIEN TAO NEN KHOI
   color mau;   //MAU SAC TRONG 4 VIEN TAO KHOI SE GIONG NHAU
};
const int SetTetrino[7][4]=
{
   0,4,8,12,   //I
   1,4,5,9,    //T
   0,4,8,9,   //L
   0,1,4,5,   //O
   0,4,5,9,    //S
   1,4,5,8,   //Z
   1,5,8,9    //J
};
SDL_Window* GetWindow(SDL_Window* Window,int width,int height); //KHOI TAO MAN HINH
SDL_Renderer* GetRenderer(SDL_Window* Window,SDL_Renderer* Renderer);   //KHOI TAO RENDER
SDL_Texture* Load(SDL_Renderer* Renderer,const string path);   //LOAD KHUNG
SDL_Window* DestroyWindow(SDL_Window* Window);   //HUY MAN HINH
SDL_Renderer* DestroyRenderer(SDL_Renderer* Renderer);  //HUY RENDER
SDL_Texture* DestroyTexture(SDL_Texture* Texture);  //HUY TEXT
void GetTetrino(tetrino a[4],int &random,int &restorerandom);//KHOI TAO HINH DANG MAU SAC
void MoveTetrino(tetrino a[4],tetrino b[4],int &dx);    //DI CHUYEN KHOI
void RotateTetrino(tetrino a[4],int &rotation);     //XOAY KHOI
void DrawTetrino(SDL_Renderer *renderer,tetrino a[4]);  //VE KHOI HINH LEN MAN HINH
void SoftTetrino(SDL_Renderer *renderer,tetrino a[4],tetrino b[4]); //ROI KHOI
bool Check(tetrino a[4],int BOARD[M][N]);   //KIEM TRA CAC DIEU KIEN VI PHAM
void DrawBoard(SDL_Renderer *renderer,int BOARD[M][N]); //VE BANG
void EraseBoard(int BOARD[M][N]);   //CHINH SUA BANG KHI CO 1 DONG DAY
void DrawNext(SDL_Renderer *renderer,tetrino a[4],int &random); //VE NEXT CUA KHOI TAI TOA DO CO SAN
bool GameLose(int BOARD[M][N]); //DIEU KIEN GAMEOVER
void GetShown(tetrino c[4],tetrino a[4]);   //KHOI TAO BONG CUA 1 KHOI HINH
void DrawShown(SDL_Renderer* renderer,tetrino a[4],tetrino c[4],int BOARD[M][N]);   //VE BONG TAI DAY CUA BANG


#endif // GAME_H


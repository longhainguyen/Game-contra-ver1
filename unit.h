#ifndef UNIT_H_
#define UNIT_H_

#include<vector>
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include "TextObject.h"
#include"LoadTexture.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event e;

const int FRAME_PER_SECOND = 35;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;


typedef struct input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
};


#define BOSS_HEART 10
#define DISTANCE_ENEMY_MOVE 60
#define ENEMY_SPEED 3
#define PLAYER_SPEED 10
#define PLAYER_JUMP 15
#define NUM_OF_ENEMYS 10

#define MAP_WIDTH 100
#define MAP_HEIGHT 10

#define PIXEL_MONEY 5
#define PIXEL_HEART 7
#define PIXEL_SIXE 64
#define PIXEL_EMPTY 0


const char DATA_FILE[]="map\\map01.txt";

typedef struct MapPos
{
  int x;
  int y;
};

typedef struct MapCode
{
    int Array[MAP_HEIGHT][MAP_WIDTH];
    MapPos ArrayPos[MAP_HEIGHT][MAP_WIDTH];
    int startX,startY;
    int distance;
};

namespace SDLunit
{
    bool checkCollision(SDL_Rect a,SDL_Rect b);
    int ShowMenu(SDL_Renderer* gRenderer,TTF_Font* font,const std::string menu1,const std::string menu2, const std::string menu3);
    int Random(int min, int max);

}


#endif // UNIT_H_

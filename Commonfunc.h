#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <cstdlib>
// tạo cửa sổ và gắn nó = NUll;
static SDL_Window *g_window = NULL;
static SDL_Renderer *g_screen = NULL;

// static int Status_Play = 0;
//   liên quan đến chuuột
static SDL_Event g_event;

// Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 60;
// số hịnh ảnh trên 1 giây
const int FPS_SECOND = 60;

// const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0

#define TILE_SIZE 64

#define MAX_MAP_X 400

#define MAX_MAP_Y 10

#define UET 7

struct Input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
    int Throw_Right;
    int Throw_Left;
    int Slide_Right;
    int Slide_Left;
};

struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    // khai bao mang hai chieu luu toan bo trang thai
    int Tile[MAX_MAP_Y][MAX_MAP_X];
    const char *file_name;
};

//
// const int FPS = 60;

#endif
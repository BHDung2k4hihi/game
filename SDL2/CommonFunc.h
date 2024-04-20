#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;




const int FRAME_PER_SECOND = 35; //fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDERER_DRAW_COLOR = 0xff;

#define PLAYER_BULLET_SPEED 20

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};



typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name_;

};

namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect& Object1, const SDL_Rect& Object2);
}







#endif // !COMMON_FUNCTION_H_

﻿#pragma once

using namespace std;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define MAP_LIMIT_RIGHT 32*71
#define MAP_LIMIT_BOT 32*36
#define GRAVITY 0.002f

#define del 8 // sai số tỉ đối
// ID object
enum eType
{
	UNKNOWN_VALUE = -1,

	ALADIN	= 01,
	BRICK	= 10,
	BRICK2	= 11,
	GOOMBA	= 20,
	ENEMY1	= 30,
	ENEMY2	= 31,
	BAT		= 32,
	ENEMY3	= 33,

	LAND	= 99,
	LAND1	= 90,
	LAND2	= 91,
};
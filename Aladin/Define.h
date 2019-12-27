#pragma once

using namespace std;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define MAP_LIMIT_RIGHT 32*71
#define MAP_LIMIT_BOT 32*36
#define MAP2_LIMIT_RIGHT 32*26
#define MAP2_LIMIT_BOT 32*15
#define GRAVITY 0.002f

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Aladin X Mario"

#define MAX_FRAME_RATE			180

#define ID_TEX_ALADIN			0
#define ID_TEX_ALADIN_F			01
#define ID_TEX_ENEMY			10
#define ID_TEX_MISC				20
#define ID_TEX_MAP				30
#define ID_TEX_BRICK_2			40
#define	ID_TEX_JAFAR_R			11
#define	ID_TEX_JAFAR_L			12
#define ID_TEX_ITEM				15
#define ID_TEX_SHOP				16
#define ID_TEX_EXPLOSION		17
#define ID_TEX_EXgENIE			18
#define ID_TEX_LAND			99
#define ID_TEX_ENEMY1		50
#define ID_TEX_ENEMY1_FLIP	51
#define ID_TEX_ENEMY2		55
#define ID_TEX_ENEMY2_FLIP	56
#define ID_TEX_ITEM_COLLECT 60

#define del 8 // sai số tỉ đối
// ID object
enum eType
{
	UNKNOWN_VALUE = -1,

	ALADIN = 01,
	BRICK = 10,
	BRICK2 = 11,
	BRICKLINE = 12,
	GOOMBA = 20,
	ENEMY1 = 30,
	ENEMY2 = 31,
	BAT = 32,
	ENEMY3 = 33,
	APPLE = 34,
	JAFAR = 35,
	ANGFIRE = 36,
	FIREATTACK = 37,
	STAR	= 38,
	BONE    = 39,

	// ITEMS
	ITEMAPPLE = 50,
	ITEMRUBY  = 51,
	ITEMGENIE = 52,
	ITEMHEATH = 53,
	ITEMPOT	  = 54,
	SHOP	  = 55,

	LAND = 99,
	M2LAND = 98,
	LAND1 = 90,
	LAND2 = 91,
	LAND3 = 92,
	ROPE  = 93,
	ROPE_TRIGGER = 999,

	TEXSURFACE = 100,
	BACKGROUND2 = 200,
};
#ifndef _TILE_MAP
#define _TILE_MAP

#define TILE_SIZE 32
#define ID_TEX_TILE_MAP 99
#define ID_TEX_TILE_SET 98
#define FILE_PATH L"textures\\tile_map.png"
//Tile co ID dac biet 
#include <fstream>

#include "Sprites.h"
#include "Textures.h"
#include "Camera.h"

class Tile : public CSprite
{
	int tileX;
	int tileY;
	int tileSize;
public:
	Tile(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	// moi tile chua thoong tin vi tri x y trong tile map
	
};
#endif // !_TILE_MAP



class Tiles
{
	static Tiles *__instance;
	unordered_map<int, Tile*> tiles;
public:
	void AddTile(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	
	Tile* Get(int ID);
	Tile* &operator[](int id) { return tiles[id]; }

	
	static Tiles *GetInstance();
};


class TileMap
{
	int columns_Tile, rows_Tile;
	int tile_Map[500][500];

public:
	void LoadResource();
	void ReadMapFile(char* filename);
	void DrawMap(Camera*);
};
#pragma once

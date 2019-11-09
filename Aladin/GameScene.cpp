#include "GameScene.h"

void GameScene::LoadTileMap(int rows, int colums, int sizeCell)
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_TEX_TILE_MAP, L"texture\\tileset.png", D3DCOLOR_XRGB(0, 0, 0));
	
	Tiles *tiles = Tiles::GetInstance();

	LPDIRECT3DTEXTURE9 texTileSet = textures->Get(ID_TEX_TILE_MAP);
	
}

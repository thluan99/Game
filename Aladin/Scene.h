#pragma once

#include "debug.h"
#include "Define.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Camera.h"
#include "dxGraphics.h"
#include "TileMap.h"

#include "Aladin.h"
#include "Brick.h"
#include "Goomba.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bat.h"
#include "Land.h"
#include "Grid.h"
#include "texSurface.h"
#include "Apple.h"

class Scene
{
public:
	TileMap *tileMap;
	Apple *apple;
	vector<LPGAMEOBJECT> objects;
	CAladin *aladin;
	TextSurface *texSur;
	dxGraphics *dx_graphics;
	Camera *camera;
	CGame *game;
	Grid *grid;
	vector<Apple*> listApples;
public:
	Scene();
	virtual void CreateGrid(vector <CGameObject *> &objects) = 0;
	virtual void LoadResources(vector<CGameObject*>& objects) = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	~Scene();
};


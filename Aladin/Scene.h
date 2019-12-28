#pragma once

#include "debug.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Define.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Camera.h"
#include "dxGraphics.h"
#include "TileMap.h"

#include "Aladin.h"
#include "Brick.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bat.h"
#include "Land.h"
#include "Grid.h"
#include "texSurface.h"
#include "Apple.h"
#include "ItemApple.h"
#include "ItemGenie.h"
#include "ItemRuby.h"
#include "ItemsExHeath.h"
#include "PositionPot.h"
#include "Shop.h"
#include "Sword.h"
#include "UI.h"

class Scene
{
public:
	TileMap *tileMap;
	Apple *apple;
	Sword *sword;
	vector<LPGAMEOBJECT> objects;
	CAladin *aladin;
	TextSurface *texSur;
	dxGraphics *dx_graphics;
	Camera *camera;
	CGame *game;
	Grid *grid;
	vector<Apple*> listApples;
	UI* ui;
public:
	Scene();
	virtual void CreateGrid(vector <CGameObject *> &objects) = 0;
	virtual void LoadResources(vector<CGameObject*>& objects) = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	~Scene();
};


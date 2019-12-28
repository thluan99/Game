#pragma once

#include "Scene.h"
#include "Jafar.h"
#include "FireAngry.h"
#include "FireAttack.h"
#include "Star.h"
#include "Land.h"
#include "texSurface.h"

class Scene2 : public Scene
{
public:
	FireAngry *angFire;
	Jafar *jafar;
	FireAttack *fireAttack;
	vector<FireAttack*> listFire;
	Star *star;
	CLand *land;
	CAladin *tempAladin;
	
	TileMap *map2bk;
	TextSurface *bk2;
	float limit = 376;
	float limitLeft = 32, limitRight = 830 - ALADIN_BIG_BBOX_WIDTH;
public:
	Scene2();
	Scene2(vector<LPGAMEOBJECT> objects,
		dxGraphics *dx_graphics,
		Camera *camera,
		CGame *game);
	CGameObject * GetNewObjectEx(int ID);
	void CreateGrid(vector <CGameObject *> &objects);
	void LoadResources(vector<CGameObject*>& objects);
	void Resources(vector<CGameObject*>& objects);
	void Update(DWORD dt);
	void Render();

	~Scene2();
};
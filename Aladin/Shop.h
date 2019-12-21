#pragma once
#include "GameObject.h"

#define IT_SHOP_BBOX_WIDTH  25
#define IT_SHOP_BBOX_HEIGHT 50

#define SHOP_STATE_IDLE		01
#define	SHOP_STATE_ACTIVE	02
#define	SHOP_STATE_IDLE2	03

#define SHOP_ANI_IDLE		0
#define SHOP_ANI_ACTIVE		1
#define SHOP_ANI_IDLE2		2

class Shop : public CGameObject 
{
public:
	Shop();
	virtual void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~Shop();
};


#pragma once
#include "GameObject.h"

#define IT_APPLE_BBOX_WIDTH		12
#define IT_APPLE_BBOX_HEIGHT	12

#define APPLE_IT_IDLE			01
#define APPLE_IT_COLLECTED		02	

#define APPLE_IT_ANI_IDLE		0
#define APPLE_IT_ANI_COLLECTED	1

class ItemApple : public CGameObject
{
public:
	ItemApple();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~ItemApple();
};


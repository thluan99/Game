#pragma once
#include "GameObject.h"

#define IT_HEA_BBOX_WIDTH	20
#define IT_HEA_BBOX_HEIGHT	20

#define HEATH_STATE_IDLE		01
#define HEATH_STATE_COLLECTED	02

#define HEATH_ANI_IDLE		0
#define HEATH_ANI_COLLECTED 1

class ItemsExHeath : public CGameObject
{
public:
	ItemsExHeath();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~ItemsExHeath();
};


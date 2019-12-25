#pragma once
#include "GameObject.h"

#define IT_GENIE_BBOX_WIDTH  38
#define IT_GENIE_BBOX_HEIGHT 50

#define GENIE_STATE_IDLE 01
#define GENIE_STATE_2    02

#define GENIE_ANI_IDLE	0
#define GENIE_ANI_2		1

class ItemGenie : public CGameObject
{
public:
	bool isActive = false;

	ItemGenie();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~ItemGenie();
};


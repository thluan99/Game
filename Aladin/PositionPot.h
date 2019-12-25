#pragma once
#include "GameObject.h"

#define IT_POT_BBOX_WIDTH  20
#define IT_POT_BBOX_HEIGHT 30

#define POT_STATE_IDLE		01
#define	POT_STATE_ACTIVE	02
#define	POT_STATE_IDLE2		03

#define POT_ANI_IDLE		0
#define POT_ANI_ACTIVE		1
#define POT_ANI_IDLE2		2

class PositionPot : public CGameObject
{
public:
	bool isActive = false;

	PositionPot();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~PositionPot();
};


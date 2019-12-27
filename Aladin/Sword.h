#pragma once
#include "GameObject.h"
#include "debug.h"

#define SWORD_STATE_IDLE	01
#define SWORD_STATE_ACTIVE	02

#define ALADIN_BIG_BBOX_WIDTH  43
#define ALADIN_BIG_BBOX_HEIGHT 51

class Sword : public CGameObject
{
public:
	Sword();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~Sword();
};


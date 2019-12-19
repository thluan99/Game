#pragma once
#include "GameObject.h"
#include "debug.h"

#define STAR_BBOX_WIDTH		24
#define STAR_BBOX_HEIGHT	16

#define STAR_STATE_DESTROY	99
#define	STAR_ANI_DESTROY	1

class Star : public CGameObject
{

public:
	Star();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();

	~Star();
};


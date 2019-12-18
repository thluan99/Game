#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Aladin.h"
#include "Land.h"

#define FIRE_BBOX_HEIGHT 30
#define FIRE_BBOX_WIDTH	 30

#define FIRE_ACTIVE		01
#define	FIRE_DESTROY	02

class FireAttack : public CGameObject
{
public:
	float xFirst, yFirst;
public:
	FireAttack() { nx = -1;  vy = 0; };
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~FireAttack();
};


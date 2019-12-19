#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"
#include "Define.h"
#include "ActiveRange.h"

#define ENEMY_BBOX_WIDTH	47
#define ENEMY_BBOX_HEIGHT	52	
#define ID_TEX_ENEMY2		55
#define ID_TEX_ENEMY2_FLIP	56

#define ENEMY2_STATE_DIE	99	
#define ENEMY2_STATE_IDLE_LEFT	01	

class Enemy2 : public CGameObject
{
	int HP;

public:
	ActiveRange activeRange;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	Enemy2()
	{
		id = eType::ENEMY2;
		direction = 1;
		activeRange.CalculateActiveRange(this);
	};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};

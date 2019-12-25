#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"
#include "Define.h"
#include "ActiveRange.h"
#include "Bone.h"

#define ENEMY_BBOX_WIDTH	47
#define ENEMY_BBOX_HEIGHT	52	

#define ENEMY2_STATE_IDLE	00	
#define ENEMY2_STATE_IDLE_LEFT	01	
#define ENEMY2_STATE_ACTIVE 02
#define ENEMY2_STATE_DIE 99

#define ENEMY2_ANI_IDLE 0
#define ENEMY2_ANI_ACTIVE 1
#define ENEMY2_ANI_DIE 3

class Enemy2 : public CGameObject
{
	int HP;
	ActiveRange activeRange;

public:
	int trigger = 0;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	void SetPosition(float x, float y);
	Enemy2()
	{
		id = eType::ENEMY2;
		direction = 1;
		SetState(ENEMY2_STATE_IDLE);
		HP = 2;
	};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	ActiveRange GetActiveRange() { return activeRange; }
};

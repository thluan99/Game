#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"
#include "ActiveRange.h"

#define ENEMY_BBOX_WIDTH	47
#define ENEMY_BBOX_HEIGHT	52	
#define ID_TEX_ENEMY3		50
#define ID_TEX_ENEMY3_FLIP	51

#define ENEMY3_STATE_IDLE_LEFT	10
#define ENEMY3_STATE_IDLE_RIGHT 11
#define ENEMY3_STATE_HIT_LEFT	20
#define ENEMY3_STATE_HIT_RIGHT	21
#define ENEMY3_STATE_ATTACK_LEFT		35
#define ENEMY3_STATE_ATTACK_RIGHT		36
#define ENEMY3_STATE_RUN_LEFT			40
#define ENEMY3_STATE_RUN_RIGHT			41
#define ENEMY3_STATE_DIE				99	

#define ENEMY3_ANI_IDLE_LEFT	0
#define ENEMY3_ANI_IDLE_RIGHT	1
#define ENEMY3_ANI_RUN_LEFT		2
#define ENEMY3_ANI_RUN_RIGHT	3
#define ENEMY3_ANI_ATTACK_LEFT	4
#define ENEMY3_ANI_ATTACK_RIGHT	5
#define ENEMY3_ANI_HIT_LEFT		6
#define ENEMY3_ANI_HIT_RIGHT	7

class Enemy3 : public CGameObject
{
	int HP;

public:
	ActiveRange activeRange;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	Enemy3()
	{
		id = eType::ENEMY3;
		state = ENEMY3_STATE_IDLE_LEFT;
		direction = 1;
		activeRange.CalculateActiveRange(this);
	};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};
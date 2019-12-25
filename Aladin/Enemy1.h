#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"

#define ENEMY_BBOX_WIDTH	47
#define ENEMY_BBOX_HEIGHT	52	

#define ENEMY1_STATE_IDLE_LEFT	10
#define ENEMY1_STATE_IDLE_RIGHT 11
#define ENEMY1_STATE_HIT_LEFT	20
#define ENEMY1_STATE_HIT_RIGHT	21
#define ENEMY1_STATE_ATTACK_LEFT_MID	30
#define ENEMY1_STATE_ATTACK_RIGHT_MID	31
#define ENEMY1_STATE_ATTACK_LEFT		35
#define ENEMY1_STATE_ATTACK_RIGHT		36
#define ENEMY1_STATE_RUN_LEFT			40
#define ENEMY1_STATE_RUN_RIGHT			41
#define ENEMY1_STATE_DIE				99	

#define ENEMY1_ANI_IDLE_LEFT	0
#define ENEMY1_ANI_IDLE_RIGHT	1
#define ENEMY1_ANI_RUN_LEFT		2
#define ENEMY1_ANI_RUN_RIGHT	3
#define ENEMY1_ANI_ATTACK_LEFT_MID	4
#define ENEMY1_ANI_ATTACK_RIGHT_MID	5
#define ENEMY1_ANI_ATTACK_LEFT	6
#define ENEMY1_ANI_ATTACK_RIGHT	7
#define ENEMY1_ANI_HIT_LEFT		8
#define ENEMY1_ANI_HIT_RIGHT	9
#define ENEMY1_ANI_DIE			10

class Enemy1 : public CGameObject
{
	int HP;

public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	Enemy1()
	{
		id = eType::ENEMY1;
		state = ENEMY1_STATE_IDLE_RIGHT;
		direction = 1;
		HP = 2;
	};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};
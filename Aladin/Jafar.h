#pragma once
#include "GameObject.h"
#include "Apple.h"
#include "debug.h"

#define JAFAR_BBOX_WIDTH	50
#define JAFAR_BBOX_HEIGHT	65	

#define JAFAR_STATE_ATTACK_L	10
#define JAFAR_STATE_ATTACK_R	11
#define JAFAR_STATE_CB_ATTACK_L	12
#define JAFAR_STATE_CB_ATTACK_R	13
#define JAFAR_STATE_SNAKE_AT_L	20
#define JAFAR_STATE_SNAKE_AT_R	21
#define JAFAR_STATE_IDLE_L		0
#define JAFAR_STATE_IDLE_R		1
#define JAFAR_STATE_DIE			99

#define JAFAR_ANI_IDLE_R		0
#define JAFAR_ANI_IDLE_L		1
#define JAFAR_ANI_CB_ATTACK_R	2
#define JAFAR_ANI_CB_ATTACK_L	3
#define JAFAR_ANI_SNAKE_AT_R	4
#define JAFAR_ANI_SNAKE_AT_L	5 
#define JAFAR_ANI_ATTACK_R		6
#define JAFAR_ANI_ATTACK_L		7

class Jafar : public CGameObject
{
public:
	int henshinState = 15;
	float jafarX = 400;
	float jafarY = 280;
	Jafar() { SetState(JAFAR_STATE_CB_ATTACK_L);
	HP = 30;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();

	~Jafar();
};


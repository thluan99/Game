#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"
#include "Define.h"
#include "Aladin.h"

#define APPLE_BBOX_WIDTH	7
#define APPLE_BBOX_HEIGHT	7
#define ID_TEX_APPLE		66

#define APPLE_STATE_DIE		99	
#define APPLE_STATE_IDLE	01
#define	APPLE_STATE_FLY		11

#define APPLE_ANI_DIE		1
#define	APPLE_ANI_IDLE		0
#define	APPLE_ANI_RE_FLYING	3
#define	APPLE_ANI_FLYING	4


class Apple : public CGameObject
{

	bool	isNem;
public:
	float staticX;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void SetState(int state);
	virtual void LoadResources(int ID);
	float Calcu_Y_Apple(float);



	Apple() { id = eType::APPLE; 
		 state = APPLE_STATE_IDLE;
		isNem = false;
		vy = -0.13f;
	}
	Apple(CAladin* aladin_apple, float x, float y)
	{
		id = eType::APPLE;
		this->x = x;
		this->y = y;
		this->staticX = x;
		state = APPLE_STATE_IDLE;
		isNem = true;
	};
	Apple(float x, float y)
	{
		id = eType::APPLE;
		this->x = x;
		this->y = y;
		this->staticX = x;
		state = APPLE_STATE_IDLE;
		isNem = true;
	};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	void setNem(bool x) { isNem = x; }
	bool	getNem() { return isNem; }
	~Apple() { }
};

#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "Sprites.h"
#include "Textures.h"
#include "Define.h"

#define BAT_BBOX_WIDTH	47
#define BAT_BBOX_HEIGHT	52	
#define ID_TEX_BAT		55

#define BAT_STATE_DIE	99	
#define BAT_STATE_IDLE	01
#define BAT_STATE_WAKEUP	10
#define	BAT_STATE_FLY	11

#define BAT_ANI_IDLE	0
#define BAT_ANI_WAKEUP	1
#define	BAT_ANI_FLY	2
#define	BAT_ANI_RE_FLYING	3
#define	BAT_ANI_FLYING		4


class Bat : public CGameObject
{
	int HP;

public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	virtual void LoadResources(int ID);
	Bat()
	{
		id = eType::BAT;
		direction = 1;
	};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};
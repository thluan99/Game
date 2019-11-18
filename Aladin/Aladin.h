#pragma once
#include "GameObject.h"

#define ALADIN_WALKING_SPEED				0.2f 
//0.1f
#define ALADIN_JUMP_SPEED_Y					0.6f
#define ALADIN_JUMP_DEFLECT_SPEED			0.2f
#define ALADIN_GRAVITY						0.002f
#define ALADIN_DIE_DEFLECT_SPEED			0.5f

#define ALADIN_STATE_IDLE					0
#define ALADIN_STATE_WALKING_RIGHT			100
#define ALADIN_STATE_WALKING_LEFT			200
#define ALADIN_STATE_JUMP					300
#define ALADIN_STATE_DIE					400

#define ALADIN_ANI_BIG_IDLE_RIGHT			0
#define ALADIN_ANI_BIG_IDLE_LEFT			1

#define ALADIN_ANI_BIG_WALKING_RIGHT		2
#define ALADIN_ANI_BIG_WALKING_LEFT			3

#define	ALADIN_LEVEL_BIG					2

#define ALADIN_BIG_BBOX_WIDTH  43
#define ALADIN_BIG_BBOX_HEIGHT 51

#define ID_TEX_ALADIN			0
#define ID_TEX_ALADIN_F			01

class CAladin : public CGameObject
{
public: 
	CAladin() { id = eType::ALADIN; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void ReLoad();
};
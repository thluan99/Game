#pragma once
#include "GameObject.h"

#define ALADIN_WALKING_SPEED				0.15f 
//0.1f
#define ALADIN_JUMP_SPEED_Y					0.2f
#define ALADIN_JUMP_DEFLECT_SPEED			0.2f
#define ALADIN_GRAVITY						0.002f
#define ALADIN_DIE_DEFLECT_SPEED			0.5f

#define ALADIN_STATE_IDLE_RIGHT				0
#define ALADIN_STATE_IDLE_LEFT				1
#define ALADIN_STATE_WALKING_RIGHT			100
#define ALADIN_STATE_WALKING_LEFT			200

#define ALADIN_STATE_DIE					400
#define ALADIN_STATE_JUMP					300
#define ALADIN_STATE_JUMP_RIGHT				301
#define ALADIN_STATE_SIT_RIGHT				7
#define ALADIN_STATE_SIT_LEFT				8
#define ALADIN_STATE_PUSH_RIGHT				11
#define ALADIN_ANI_BIG_IDLE_RIGHT			0
#define ALADIN_ANI_BIG_IDLE_LEFT			1

#define ALADIN_ANI_BIG_WALKING_RIGHT		2
#define ALADIN_ANI_BIG_WALKING_LEFT			3


#define ALADIN_ANI_BIG_JUMP					4
#define ALADIN_ANI_BIG_JUMP_RIGHT			5

#define ALADIN_ANI_SIT_RIGHT				7
#define ALADIN_ANI_SIT_LEFT					8
#define ALADIN_ANI_PUSH_WALL_RIGHT			11
#define	ALADIN_LEVEL_BIG					2

#define ALADIN_BIG_BBOX_WIDTH  43
#define ALADIN_BIG_BBOX_HEIGHT 51

#define ID_TEX_ALADIN			0
#define ID_TEX_ALADIN_F			01

class CAladin : public CGameObject
{
	bool stateNhay;
	bool stateChem;
	bool stateDay;
public:
	CAladin() {
		id = eType::ALADIN;
		stateNhay = false;
		stateChem = false;
		stateDay = false;
		SetDirection(1);
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void ReLoad();

	void setNhay(bool state) { stateNhay = state; }
	void setChem(bool state) { stateChem = state; }
	void setDay(bool state) { stateDay = state; }
	bool getNhay() { return stateNhay; }
	bool getChem() { return stateChem; }
	bool getDay() { return stateDay; }
};
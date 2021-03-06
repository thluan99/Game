﻿#pragma once
#include "GameObject.h"
#include "FireAttack.h"
#include "PositionPot.h"
#include "ItemGenie.h"
#include "Star.h"
#include "ItemApple.h"
#include "ItemRuby.h"
#include "ItemsExHeath.h"
#include "Sword.h"

#define ALADIN_WALKING_SPEED				0.15f 
//0.1f
#define ALADIN_JUMP_SPEED_Y					0.15f
#define ALADIN_JUMP_DEFLECT_SPEED			0.2f
#define ALADIN_GRAVITY						0.002f
#define ALADIN_DIE_DEFLECT_SPEED			0.5f

#define ALADIN_STATE_IDLE					0		// đứng
#define ALADIN_STATE_IDLE_TRAI				1
#define ALADIN_STATE_DI				2		//đi
#define ALADIN_STATE_DI_TRAI				3
#define ALADIN_STATE_NHAY					4		//nhảy
#define ALADIN_STATE_ROI					5
#define ALADIN_STATE_NHAY_PHAI				6
#define ALADIN_STATE_NHAY_TRAI				7
#define ALADIN_STATE_CHEM				8		//chém
#define ALADIN_STATE_CHEM_TRAI				9
#define ALADIN_STATE_NGOI_CHEM		10
#define ALADIN_STATE_NGOI_CHEM_TRAI			11
#define ALADIN_STATE_NGOI				12		//ngồi 
#define ALADIN_STATE_NGOI_TRAI				13
#define ALADIN_STATE_NGUOC_LEN			14		//ngước lên
#define ALADIN_STATE_NGUOC_LEN_TRAI			15
#define ALADIN_STATE_DAY_PHAI				16		//đẩy
#define ALADIN_STATE_DAY_TRAI				17
#define ALADIN_STATE_DUNG_CHAY_PHAI			18		//dừng
#define ALADIN_STATE_DUNG_CHAY_TRAI			19
#define ALADIN_STATE_TREO					20
#define ALADIN_STATE_CHEM_MANH				21
#define ALADIN_STATE_NHAY_CHEM				22
#define ALADIN_STATE_NEM_TAO				23
#define ALADIN_STATE_NGOI_NEM_TAO			24
#define ALADIN_STATE_NHAY_NEM_TAO			25
#define ALADIN_STATE_IDLE_TAO				26
#define ALADIN_STATE_TREO_NHAY				27
#define ALADIN_STATE_TREO_NHAY_ROI			28
#define ALADIN_STATE_REBORN					29
#define ALADIN_STATE_DIE                    100


#define ALADIN_ANI_IDLE_PHAI				0		// đứng
#define ALADIN_ANI_IDLE_TRAI				1
#define ALADIN_ANI_DI_PHAI					2		//đi
#define ALADIN_ANI_DI_TRAI					3
#define ALADIN_ANI_NHAY						4		//nhảy
#define ALADIN_ANI_ROI						5
#define ALADIN_ANI_NHAY_PHAI				6
#define ALADIN_ANI_NHAY_TRAI				7
#define ALADIN_ANI_CHEM_PHAI				8		//chém
#define ALADIN_ANI_CHEM_TRAI				9
#define ALADIN_ANI_NGOI_CHEM_PHAI			10
#define ALADIN_ANI_NGOI_CHEM_TRAI			11
#define ALADIN_ANI_NGOI_PHAI				12		//ngồi
#define ALADIN_ANI_NGOI_TRAI				13
#define ALADIN_ANI_NGUOC_LEN_PHAI			14		//ngước lên
#define ALADIN_ANI_NGUOC_LEN_TRAI			15
#define ALADIN_ANI_DAY_PHAI					16		//đẩy
#define ALADIN_ANI_DAY_TRAI					17
#define ALADIN_ANI_DUNG_CHAY_PHAI			18		//dừng
#define ALADIN_ANI_DUNG_CHAY_TRAI			19
#define ALADIN_ANI_TREO						20
#define ALADIN_ANI_CHEM_MANH_PHAI			21
#define ALADIN_ANI_CHEM_MANH_TRAI			22
#define ALADIN_ANI_NHAY_CHEM_PHAI			23
#define ALADIN_ANI_NHAY_CHEM_TRAI			24
#define ALADIN_ANI_NEM_TAO_PHAI				25
#define ALADIN_ANI_NEM_TAO_TRAI				26
#define ALADIN_ANI_NGOI_NEM_TAO_PHAI		27
#define ALADIN_ANI_NGOI_NEM_TAO_TRAI		28
#define ALADIN_ANI_NHAY_NEM_TAO_PHAI		29
#define ALADIN_ANI_NHAY_NEM_TAO_TRAI		30
#define ALADIN_ANI_IDLE_APPLE_RIGHT			31
#define ALADIN_ANI_TREO_NHAY				32
#define ALADIN_ANI_TREO_NHAY_ROI			33
#define ALADIN_ANI_DIE					    34
#define ALADIN_ANI_REBORN					35
#define ALADIN_ANI_WALKING_PASSING			36


#define	ALADIN_LEVEL_BIG					2
#define ALADIN_BIG_BBOX_WIDTH  43
#define ALADIN_BIG_BBOX_HEIGHT 51

#define ID_TEX_ALADIN			0
#define ID_TEX_ALADIN_F			01

#define ALADIN_UNTOUCHABLE_TIME 1000


class CAladin : public CGameObject
{
	bool enableKey;
	bool isNhay;
	bool isChem;
	bool isNem;
	bool isRoi;

	int untouchable;
	DWORD untouchable_start;
public:
	int coins, lifes, scores, apples;
	float velJ;
	int timeIDLE;
	int countTiming;
	bool isStopAnimation;
	bool isPushingWall;

	bool isCollisonWithRope = false;
	bool isClimbingRope = false;
	int xSetCollision;
	int ySetCollision;
	int xReborn;
	int yReborn;
	int climDirection;
	bool climbActiveUp = false;
	bool climbActiveDown = false;
	
	bool CancelClimb = true;

	bool isSildeBoss = false;
	CAladin() {
		id = eType::ALADIN;
		state = ALADIN_STATE_IDLE;
		isNhay = false;
		isNem = false;
		isChem = false;
		enableKey = true;
		SetDirection(1);
		HP = 10;
		coins = 0;
		lifes = 1;
		scores = 00000;
		apples = 90;
		velJ = 0.0f;
		timeIDLE = 0;
		countTiming = 0;
		isStopAnimation = false;
		isPushingWall = false;
		climDirection = 0;

		untouchable = 0;
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void ReLoad();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void setNhay(bool x) {
		isNhay = x;
	}
	void setChem(bool x) {
		isChem = x;
	}
	void setNem(bool x) {
		isNem = x;
	}
	void setRoi(bool x) {
		isRoi = x;
	}
	bool getNhay() { return isNhay; }
	bool getRoi() { return isRoi; }
	bool getChem() { return isChem; }
	bool getNem() { return isNem; }
	void setEnableKey(bool x) { enableKey = x; }
	bool getEnableKey() { return enableKey; }
	
};
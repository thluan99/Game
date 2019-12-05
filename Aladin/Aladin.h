#pragma once
#include "GameObject.h"

#define ALADIN_WALKING_SPEED				0.2f 
//0.1f
#define ALADIN_JUMP_SPEED_Y					0.2f
#define ALADIN_JUMP_DEFLECT_SPEED			0.2f
#define ALADIN_GRAVITY						0.002f
#define ALADIN_DIE_DEFLECT_SPEED			0.5f

#define ALADIN_STATE_IDLE_PHAI				0		// đứng
#define ALADIN_STATE_IDLE_TRAI				1
#define ALADIN_STATE_DI_PHAI				2		//đi
#define ALADIN_STATE_DI_TRAI				3
#define ALADIN_STATE_NHAY					4		//nhảy
#define ALADIN_STATE_NHAY_PHAI				5
#define ALADIN_STATE_NHAY_TRAI				6
#define ALADIN_STATE_CHEM_PHAI				7		//chém
#define ALADIN_STATE_CHEM_TRAI				8
#define ALADIN_STATE_NGOI_CHEM_PHAI			9
#define ALADIN_STATE_NGOI_CHEM_TRAI			10
#define ALADIN_STATE_NGOI_PHAI				11		//ngồi
#define ALADIN_STATE_NGOI_TRAI				12
#define ALADIN_STATE_NGUOC_LEN_PHAI			13		//ngước lên
#define ALADIN_STATE_NGUOC_LEN_TRAI			14
#define ALADIN_STATE_DAY_PHAI				15		//đẩy
#define ALADIN_STATE_DAY_TRAI				16
#define ALADIN_STATE_DUNG_CHAY_PHAI			17		//dừng
#define ALADIN_STATE_DUNG_CHAY_TRAI			18
#define ADADIN_STATE_TREO					19
#define ALADIN_STATE_DIE                    100


#define ALADIN_ANI_IDLE_PHAI				0		// đứng
#define ALADIN_ANI_IDLE_TRAI				1
#define ALADIN_ANI_DI_PHAI					2		//đi
#define ALADIN_ANI_DI_TRAI					3
#define ALADIN_ANI_NHAY						4		//nhảy
#define ALADIN_ANI_NHAY_PHAI				5
#define ALADIN_ANI_NHAY_TRAI				6
#define ALADIN_ANI_CHEM_PHAI				7		//chém
#define ALADIN_ANI_CHEM_TRAI				8
#define ALADIN_ANI_NGOI_CHEM_PHAI			9
#define ALADIN_ANI_NGOI_CHEM_TRAI			10
#define ALADIN_ANI_NGOI_PHAI				11		//ngồi
#define ALADIN_ANI_NGOI_TRAI				12
#define ALADIN_ANI_NGUOC_LEN_PHAI			13		//ngước lên
#define ALADIN_ANI_NGUOC_LEN_TRAI			14
#define ALADIN_ANI_DAY_PHAI					15		//đẩy
#define ALADIN_ANI_DAY_TRAI					16
#define ALADIN_ANI_DUNG_CHAY_PHAI			17		//dừng
#define ALADIN_ANI_DUNG_CHAY_TRAI			18
#define ADADIN_ANI_TREO						19
#define ALADIN_ANI_DIE					    100


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
		state = ALADIN_STATE_IDLE_PHAI;
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
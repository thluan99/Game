#include <algorithm>
#include "debug.h"

#include "Aladin.h"
#include "Game.h"
#include "Brick.h"
#include "Goomba.h"

void CAladin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += ALADIN_GRAVITY*dt;

	if (this->x > MAP_LIMIT_RIGHT - 50)
		this->x = MAP_LIMIT_RIGHT - 50;
	if (this->x < 0) this->x = 0;
	if (this->y < 0) this->y = 0;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=ALADIN_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{	
		x += dx;
		y += dy;
		if ((vy - ALADIN_GRAVITY * dt) < dy)
			isRoi = true;
		else
		{
			if (isRoi == true)
			{
				state = ALADIN_STATE_IDLE;
				enableKey = true;
			}
			isRoi = false;
		}
		/*if (vy <=dy)
		{
			state = ALADIN_STATE_ROT ;
		}
		else state = ALADIN_STATE_IDLE;*/
		
	}
	else
	{		
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		
		if (nx!=0) vx = 0;
		if (ny != 0) { vy = 0; }

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is Goomba 
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx < 0)
				{
					return;
				}
			}
			
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CAladin::Render()
{
	if (isNhay==true)
		vy = -ALADIN_JUMP_SPEED_Y;
	int ani;
	switch (state)
	{
	case ALADIN_STATE_IDLE:
		ani = ALADIN_ANI_IDLE_PHAI;
		break;
	case ALADIN_STATE_DI:
		if (direction==1)
		{
			ani = ALADIN_ANI_DI_PHAI;
		}
		else
		{
			ani = ALADIN_ANI_DI_TRAI;
		}
		break;
	case ALADIN_STATE_NGOI:
		if (direction==1)
		{
			ani = ALADIN_ANI_NGOI_PHAI;
		}
		else
		{
			ani = ALADIN_ANI_NGOI_TRAI;
		}
		break;
	case ALADIN_STATE_NGUOC_LEN:
		if (direction == 1)
		{
			ani = ALADIN_ANI_NGUOC_LEN_PHAI;
		}
		else
		{
			ani = ALADIN_ANI_NGUOC_LEN_TRAI;
		}
		break;
	case ALADIN_STATE_CHEM:
		if (direction == 1)
		{
			ani = ALADIN_ANI_CHEM_PHAI;
		}
		else
		{
			ani = ALADIN_ANI_CHEM_TRAI;
		}
		break;
	case ALADIN_STATE_NGOI_CHEM:
		if (direction == 1)
		{
			ani = ALADIN_ANI_NGOI_CHEM_PHAI;
		}
		else
		{
			ani = ALADIN_ANI_NGOI_CHEM_TRAI;
		}
		break;
	case ALADIN_STATE_CHEM_MANH:
		if (direction == 1)
		{
			ani = ALADIN_ANI_CHEM_MANH_PHAI;
		}
		else
		{
			ani = ALADIN_ANI_CHEM_MANH_TRAI;
		}
		break;
	/*case ALADIN_STATE_DUNG_CHAY_PHAI:
		ani = ALADIN_ANI_DUNG_CHAY_PHAI;
		break;
	case ALADIN_STATE_DUNG_CHAY_TRAI:
		ani = ALADIN_ANI_DUNG_CHAY_TRAI;
		break;
	case ALADIN_STATE_NHAY:
		
			ani = ALADIN_ANI_NHAY;
		*/
		//break;
	
	}
	

	int alpha = 255;
	/*if (stateNhay == true)
	{
		int stt = 3;
		if (vx == 0)
			animations[ALADIN_ANI_NHAY]->RenderAladin(stt,x, y + ALADIN_BIG_BBOX_HEIGHT,this->direction, alpha);
		else animations[ALADIN_ANI_NHAY]->RenderAladin(stt, x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);

		if (stt == 0)
			stateNhay = false;
		else
			vy = -0.07;

	}
	else
		if (stateChem == true)
		{
			int i;
			if (direction == 1)
				i = 6;
			else i = 12;
			int stt;
			animations[i]->RenderAladin(stt, x, y+ ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
			if (stt == 0)
				stateChem = false;
		}
		else*/
	
	int stt = 0;
	 /*if (state == ALADIN_STATE_DUNG_CHAY_PHAI || state == ALADIN_STATE_DUNG_CHAY_TRAI)
	{
		animations[ani]->RenderAladin(stt, x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
		if (stt == 0)
			enableKey = false;
		else
		{
			enableKey = true;
			state = ALADIN_STATE_IDLE;

		}
	 }
	 else*/
	 
	if (isChem == true)
	{
		switch (state)
		{
		case ALADIN_STATE_IDLE:
			if (direction == 1)
				ani = ALADIN_ANI_CHEM_PHAI;
			else
			{
				ani = ALADIN_ANI_CHEM_TRAI;
			}
			break;
		case ALADIN_STATE_NGUOC_LEN:
			if (direction == 1)
				ani = ALADIN_ANI_CHEM_MANH_PHAI;
			else
			{
				ani = ALADIN_ANI_CHEM_MANH_TRAI;
			}
			break;
		case ALADIN_STATE_NGOI:
			if (direction == 1)
				ani = ALADIN_ANI_NGOI_CHEM_PHAI;
			else
			{
				ani = ALADIN_ANI_NGOI_CHEM_TRAI;
			}
			break;
		}
		animations[ani]->RenderAladin(stt, x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
		if (stt == 0)
			enableKey = false;
		else
		{
			enableKey = true;
			//state = ALADIN_STATE_IDLE;
			isChem = false;
		}
	}
	else if (isNhay == true )
	{
		switch (state)
		{
		case ALADIN_STATE_NGUOC_LEN:
		case ALADIN_STATE_IDLE:
			
				ani = ALADIN_ANI_NHAY;
			
			break;
		case ALADIN_STATE_DI:
			if (direction == 1)
				ani = ALADIN_ANI_NHAY_PHAI;
			else
			{
				ani = ALADIN_ANI_NHAY_TRAI;
			}
			break;
		}
		animations[ani]->RenderAladin(stt, x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
		if (stt == 0)
			enableKey = false;
		else
		{
			enableKey = true;
			//state = ALADIN_STATE_IDLE;
			isNhay = false;
		}
	}
	/*else if (isNem == true)
	{
		switch (state)
		{
		case ALADIN_STATE_NGUOC_LEN:
		case ALADIN_STATE_IDLE:

			ani = ALADIN_ANI_NHAY;

			break;
		case ALADIN_STATE_DI:
			if (direction == 1)
				ani = ALADIN_ANI_NHAY_PHAI;
			else
			{
				ani = ALADIN_ANI_NHAY_TRAI;
			}
			break;
		}
		animations[ani]->RenderAladin(stt, x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
		if (stt == 0)
			enableKey = false;
		else
		{
			enableKey = true;
			state = ALADIN_STATE_IDLE;
			isNhay = false;
		}
	}*/
	
	else
	{
	if (isRoi == true)
		ani = ALADIN_ANI_ROI;
		animations[ani]->RenderAladin(x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
	}
	
	/*switch (state)
	{
	case ALADIN_STATE_CHEM:
	case ALADIN_STATE_NGOI_CHEM:
	case ALADIN_STATE_NHAY:
		case ALADIN_STATE_CHEM_MANH:

		if (state == ALADIN_STATE_NHAY)
			vy = -ALADIN_JUMP_SPEED_Y;
		animations[ani]->RenderAladin(stt, x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
		if (stt == 0)
			enableKey = false;
		else
		{
			enableKey = true; 
			state = ALADIN_STATE_IDLE;
		}
	default:
		animations[ani]->RenderAladin(x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);
	}	*/

	//RenderBoundingBox();
}

void CAladin::SetState(int state)
{
	CGameObject::SetState(state);
	
	switch (state)
	{
	case ALADIN_STATE_DI:
		if (direction == 1)
		{
			vx = ALADIN_WALKING_SPEED;
		}
		else
		{
			vx = -ALADIN_WALKING_SPEED;
		}
		
		
		break;
	case ALADIN_STATE_DUNG_CHAY_PHAI:
	case ALADIN_STATE_DUNG_CHAY_TRAI:
		vx = 0;
		break;
	case ALADIN_STATE_CHEM_MANH:
		vx = 0;


		break;
	case ALADIN_STATE_NGUOC_LEN:
		vy = 0;
		break;
	case ALADIN_STATE_NHAY:
		// -ALADIN_JUMP_SPEED_Y;
		
		nx = ALADIN_STATE_NHAY;
		break;

	
	case ALADIN_STATE_IDLE:
		vx = 0;
		nx = ALADIN_STATE_IDLE;
		break;

	case ALADIN_STATE_NGOI:
		vx = 0;
		nx = ALADIN_STATE_NGOI;
		break;
	case ALADIN_STATE_CHEM:
		vx = 0;
		nx = ALADIN_STATE_CHEM;
		break;

	case ALADIN_STATE_NGOI_TRAI:
		vx = 0;
		nx = ALADIN_STATE_NGOI_TRAI;
		break;
	}
}

void CAladin::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_ALADIN, L"textures\\aladin.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ALADIN_F, L"textures\\aladin_flip.png", D3DCOLOR_XRGB(255, 0, 255));

	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texAladin = textures->Get(ID_TEX_ALADIN);
	LPDIRECT3DTEXTURE9 texAladin_f = textures->Get(ID_TEX_ALADIN_F);
	LPANIMATION ani;
	//----idle right------
	sprites->Add(20001, 3, 9, 37 + 3, 50 + 9, texAladin);
	sprites->Add(20002, 47, 11, 41 + 47, 47 + 11, texAladin);
	sprites->Add(20003, 95, 6, 40 + 95, 52 + 6, texAladin);
	sprites->Add(20004, 143, 3, 44 + 143, 55 + 3, texAladin);
	sprites->Add(20005, 197, 6, 41 + 197, 51 + 6, texAladin);
	sprites->Add(20006, 250, 5, 42 + 250, 51 + 5, texAladin);
	sprites->Add(20007, 303, 2, 44 + 303, 53 + 2, texAladin);
	ani = new CAnimation(115);	// idle big right
	ani->Add(20003);
	ani->Add(20004);
	ani->Add(20004);
	ani->Add(20005);
	ani->Add(20006);
	ani->Add(20007);
	ani->Add(20007);
	ani->Add(20006);
	ani->Add(20005);
	animations->Add(400, ani);
	//----idle left------
	sprites->Add(20008, 1081, 9, 1081 + 37, 9 + 50, texAladin_f);
	sprites->Add(20009, 1033, 11, 1033 + 41, 11 + 47, texAladin_f);
	sprites->Add(20010, 986, 6, 986 + 40, 6 + 52, texAladin_f);
	sprites->Add(20011, 934, 3, 934 + 44, 3 + 55, texAladin_f);
	sprites->Add(20012, 883, 6, 883 + 41, 6 + 51, texAladin_f);
	sprites->Add(20013, 829, 5, 829 + 42, 5 + 51, texAladin_f);
	sprites->Add(20014, 774, 2, 774 + 44, 2 + 53, texAladin_f);

	ani = new CAnimation(115);	// idle big left
	ani->Add(20010);
	ani->Add(20011);
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);
	ani->Add(20014);
	ani->Add(20014);
	ani->Add(20013);
	ani->Add(20012);
	animations->Add(401, ani);

	//----ngồi phải----
	sprites->Add(20015, 9, 640, 9 + 47, 640 + 33, texAladin);

	ani = new CAnimation(100);	// ngoi phải
	ani->Add(20015);
	animations->Add(402, ani);
	//----ngồi trái----
	sprites->Add(20016, 1065, 640, 1065 + 47, 640 + 33, texAladin_f);

	ani = new CAnimation(100);	// ngoi trái
	ani->Add(20016);
	animations->Add(403, ani);
	//---- ngước lên phải----
	
	sprites->Add(20022, 111, 491, 111 + 49, 58 + 491, texAladin);
	ani = new CAnimation(100);
	
	ani->Add(20022);
	animations->Add(404, ani);
	//---- ngước lên trái----
	
	sprites->Add(20027, 961, 491, 961 + 49, 58 + 491, texAladin_f);
	ani = new CAnimation(100);
	
	ani->Add(20027);
	animations->Add(405, ani);

	//----đi right--------
	sprites->Add(10002, 66, 1222, 66 + 43, 1222 + 51, texAladin);
	sprites->Add(10003, 120, 1220, 120 + 41, 1220 + 53, texAladin);
	sprites->Add(10004, 171, 1216, 171 + 41, 1216 + 57, texAladin);
	sprites->Add(10005, 220, 1216, 220 + 52, 1216 + 57, texAladin);
	sprites->Add(10006, 279, 1219, 279 + 46, 1219 + 54, texAladin);
	sprites->Add(10007, 334, 1215, 334 + 42, 1215 + 58, texAladin);
	sprites->Add(10008, 386, 1221, 286 + 41, 1221 + 52, texAladin);
	sprites->Add(10009, 440, 1219, 440 + 35, 1219 + 54, texAladin);
	sprites->Add(10010, 488, 1216, 488 + 49, 1216 + 57, texAladin);
	sprites->Add(10011, 547, 1215, 547 + 55, 1215 + 58, texAladin);
	sprites->Add(10012, 611, 1219, 611 + 55, 1219 + 55, texAladin);
	sprites->Add(10013, 679, 1218, 679 + 44, 1218 + 57, texAladin);

	ani = new CAnimation(100);	// walk right big
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	ani->Add(10007);
	ani->Add(10009);
	ani->Add(10010);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(500, ani);
	//----đi left-------
	sprites->Add(10051, 1012, 1222, 1012 + 43, 1222 + 51, texAladin_f);
	sprites->Add(10052, 960, 1220, 960 + 41, 1220 + 53, texAladin_f);
	sprites->Add(10053, 909, 1216, 909 + 41, 1216 + 57, texAladin_f);
	sprites->Add(10054, 849, 1216, 849 + 52, 1216 + 57, texAladin_f);
	sprites->Add(10055, 796, 1219, 796 + 46, 1219 + 54, texAladin_f);
	sprites->Add(10056, 745, 1215, 745 + 42, 1215 + 58, texAladin_f);
	sprites->Add(10057, 694, 1221, 694 + 41, 1221 + 52, texAladin_f);
	sprites->Add(10058, 646, 1219, 646 + 35, 1219 + 54, texAladin_f);
	sprites->Add(10059, 584, 1216, 584 + 49, 1216 + 57, texAladin_f);
	sprites->Add(10060, 519, 1215, 519 + 55, 1215 + 58, texAladin_f);
	sprites->Add(10061, 455, 1219, 455 + 55, 1219 + 55, texAladin_f);
	sprites->Add(10062, 398, 1218, 398 + 44, 1219 + 57, texAladin_f);


	ani = new CAnimation(100);	// // walk left big
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	ani->Add(10054);
	ani->Add(10055);
	ani->Add(10056);
	ani->Add(10057);
	ani->Add(10058);
	ani->Add(10059);
	ani->Add(10060);
	ani->Add(10061);
	ani->Add(10062);

	animations->Add(501, ani);
	//-------- nhảy up--------
	sprites->Add(10100, 8, 846, 8 + 59, 846 + 43, texAladin);
	sprites->Add(10101, 75, 828, 75 + 52, 828 + 62, texAladin);
	sprites->Add(10102, 137, 829, 137 + 54, 829 + 61, texAladin);
	sprites->Add(10103, 203, 824, 203 + 54, 824 + 69, texAladin);
	sprites->Add(10104, 269, 820, 269 + 51, 820 + 74, texAladin);
	ani = new CAnimation(100);	// jupm up
	ani->Add(10100);
	ani->Add(10101);
	ani->Add(10102);
	ani->Add(10103);
	ani->Add(10104);
	animations->Add(502, ani);
	//--- rớt xuống 
	sprites->Add(10105, 336, 829, 336 + 38, 829 + 66, texAladin);
	sprites->Add(10106, 390, 818, 390 + 35, 818 + 79, texAladin);
	sprites->Add(10107, 448, 808, 448 + 34, 808 + 93, texAladin);
	sprites->Add(10108, 504, 810, 504 + 34, 810 + 93, texAladin);
	sprites->Add(10109, 564, 812, 564 + 34, 812 + 93, texAladin);


	ani = new CAnimation(100);
	ani->Add(10105);
	ani->Add(10106);
	ani->Add(10107);
	ani->Add(10108);
	animations->Add(514, ani);
	// --------nhảy right--------
	sprites->Add(10110, 10, 705, 10 + 41, 705 + 42, texAladin);
	sprites->Add(10111, 66, 683, 66 + 45, 683 + 76, texAladin);
	sprites->Add(10112, 124, 686, 124 + 57, 686 + 57, texAladin);
	sprites->Add(10113, 199, 698, 199 + 58, 698 + 42, texAladin);
	sprites->Add(10114, 273, 696, 273 + 61, 696 + 48, texAladin);
	/*sprites->Add(10115, 350, 692, 350 + 58, 692 + 53, texAladin);
	sprites->Add(10116, 419, 688, 419 + 53, 688 + 58, texAladin);
	sprites->Add(10117, 491, 680, 491 + 50, 680 + 85, texAladin);
	sprites->Add(10118, 560, 719, 560 + 59, 719 + 44, texAladin);*/

	ani = new CAnimation(200);	// jupm
	ani->Add(10110);
	ani->Add(10111);
	ani->Add(10112);
	ani->Add(10113);
	ani->Add(10114);
	/*ani->Add(10115);
	ani->Add(10116);
	ani->Add(10117);
	ani->Add(10118);*/
	animations->Add(503, ani);
	// --------chém phải--------
	sprites->Add(10200, 5, 337, 5 + 45, 51 + 337, texAladin);
	sprites->Add(10201, 54, 326, 54 + 51, 326 + 62, texAladin);
	sprites->Add(10202, 115, 314, 115 + 45, 314 + 74, texAladin);
	sprites->Add(10203, 171, 324, 171 + 82, 324 + 64, texAladin);
	sprites->Add(10204, 260, 335, 260 + 51, 53 + 335, texAladin);

	ani = new CAnimation(100);	// chém phải
	ani->Add(10200);
	ani->Add(10201);
	ani->Add(10202);
	ani->Add(10203);
	ani->Add(10204);

	animations->Add(504, ani);
	// --------day tuong phải--------
	sprites->Add(10210, 7, 1959, 7 + 56, 1959 + 46, texAladin);
	sprites->Add(10211, 75, 1961, 75 + 65, 1961 + 44, texAladin);
	sprites->Add(10212, 175, 1961, 157 + 70, 1961 + 45, texAladin);
	sprites->Add(10213, 237, 1962, 237 + 77, 1962 + 44, texAladin);
	sprites->Add(10214, 327, 1964, 327 + 72, 44 + 1964, texAladin);
	sprites->Add(10215, 416, 1965, 416 + 66, 1965 + 44, texAladin);
	sprites->Add(10216, 495, 1965, 495 + 75, 1965 + 44, texAladin);
	sprites->Add(10217, 585, 1966, 585 + 81, 1966 + 44, texAladin);
	sprites->Add(10218, 681, 1968, 681 + 75, 1968 + 44, texAladin);

	ani = new CAnimation(100);	// day tuong phải
	ani->Add(10210);
	ani->Add(10211);
	ani->Add(10212);
	ani->Add(10213);
	ani->Add(10214);
	ani->Add(10215);
	ani->Add(10216);
	ani->Add(10217);
	ani->Add(10218);
	animations->Add(505, ani);
	//--------chém trái--------
	sprites->Add(10220, 1071, 337, 1071 + 45, 337 + 51, texAladin_f);
	sprites->Add(10221, 1016, 326, 1016 + 51, 326 + 62, texAladin_f);
	sprites->Add(10222, 961, 314, 961 + 45, 314 + 74, texAladin_f);
	sprites->Add(10223, 868, 324, 868 + 82, 324 + 64, texAladin_f);
	sprites->Add(10224, 810, 335, 810 + 51, 335 + 53, texAladin_f);
	ani = new CAnimation(100);
	ani->Add(10220);
	ani->Add(10221);
	ani->Add(10222);
	ani->Add(10223);
	ani->Add(10224);

	animations->Add(506, ani);
	// --------jump left--------
	sprites->Add(10230, 1070, 705, 1070 + 41, 705 + 42, texAladin_f);
	sprites->Add(10231, 1010, 683, 1010 + 45, 683 + 76, texAladin_f);
	sprites->Add(10232, 940, 686, 940 + 57, 686 + 57, texAladin_f);
	sprites->Add(10233, 864, 698, 864 + 58, 698 + 42, texAladin_f);
	sprites->Add(10234, 787, 696, 787 + 61, 696 + 48, texAladin_f);
	/*sprites->Add(10235, 713, 692, 713 + 58, 692 + 53, texAladin_f);
	sprites->Add(10236, 649, 688, 649 + 53, 688 + 58, texAladin_f);
	sprites->Add(10237, 580, 680, 580 + 50, 680 + 85, texAladin_f);
	sprites->Add(10238, 502, 719, 502 + 59, 719 + 44, texAladin_f);*/

	ani = new CAnimation(100);	// jupm
	ani->Add(10230);
	ani->Add(10231);
	ani->Add(10232);
	ani->Add(10233);
	ani->Add(10234);
	//ani->Add(10235);
	//ani->Add(10236);
	//ani->Add(10237);
	//ani->Add(10238);
	animations->Add(507, ani);

	//----ngồi đâm phải----
	sprites->Add(10240, 9, 640, 9+47, 640+33, texAladin);
	sprites->Add(10241, 64, 642, 64+45, 642+31, texAladin);
	sprites->Add(10242, 115, 640, 115+71, 640+33, texAladin);
	sprites->Add(10243, 193, 639, 193+92, 639+34, texAladin);
	sprites->Add(10244, 298, 640, 298 + 84, 640 + 33, texAladin);
	sprites->Add(10245, 392, 640, 392+71, 640+33, texAladin);
	sprites->Add(10246, 475, 642, 475+45, 642+31, texAladin);
	ani = new CAnimation(100);
	ani->Add(10240);
	ani->Add(10241);
	ani->Add(10242);
	ani->Add(10243);
	ani->Add(10244);
	ani->Add(10245);
	ani->Add(10246);
	animations->Add(508, ani);

	//----ngồi đâm trái----
	sprites->Add(10250, 1065, 640, 1065 + 47, 640 + 33, texAladin_f);
	sprites->Add(10251, 1012, 642, 1012 + 45, 642 + 31, texAladin_f);
	sprites->Add(10252, 935, 640, 935 + 71, 640 + 33, texAladin_f);
	sprites->Add(10253, 836, 639, 836 + 92, 639 + 34, texAladin_f);
	sprites->Add(10254, 739, 640, 739 + 84, 640 + 33, texAladin_f);
	sprites->Add(10255, 658, 640, 658 + 71, 640 + 33, texAladin_f);
	sprites->Add(10256, 601, 642, 601 + 45, 642 + 31, texAladin_f);
	ani = new CAnimation(100);
	ani->Add(10250);
	ani->Add(10251);
	ani->Add(10252);
	ani->Add(10253);
	ani->Add(10254);
	ani->Add(10255);
	ani->Add(10256);
	animations->Add(509, ani);

	//--- dừng chạy  phải
	sprites->Add(10260, 11, 1293, 11+57, 1293+57, texAladin);
	sprites->Add(10261, 83, 1294, 83+44, 1294+56, texAladin);
	sprites->Add(10262, 134, 1284,134+51, 1284+66, texAladin);
	sprites->Add(10263, 200, 1283, 200+46, 1283+65, texAladin);
	sprites->Add(10264, 256, 1285, 256+42, 1285+64, texAladin);
	sprites->Add(10265, 309, 1306,309+55, 1306+46, texAladin);
	sprites->Add(10266, 376, 1308, 376+52,1308+44, texAladin);
	sprites->Add(10267, 437, 1300,437+46,1300+52, texAladin);
	sprites->Add(10268, 498, 1294, 498+51, 1294+52, texAladin);
	ani = new CAnimation(100);
	ani->Add(10260);
	ani->Add(10261);
	ani->Add(10262);
	ani->Add(10263);
	ani->Add(10264);
	ani->Add(10265);
	ani->Add(10266);
	ani->Add(10267);
	ani->Add(10268);

	animations->Add(510, ani);

	//--- dừng chạy  trái
	sprites->Add(10270, 1053, 1293, 1053 + 57, 1293 + 57, texAladin_f);
	sprites->Add(10271, 994, 1294, 994 + 44, 1294 + 56, texAladin_f);
	sprites->Add(10272, 936, 1284, 936 + 51, 1284 + 66, texAladin_f);
	sprites->Add(10273, 875, 1283, 875 + 46, 1283 + 65, texAladin_f);
	sprites->Add(10274, 823, 1285, 823 + 42, 1285 + 64, texAladin_f);
	sprites->Add(10275, 757, 1306, 757 + 55, 1306 + 46, texAladin_f);
	sprites->Add(10276, 693, 1308, 693 + 52, 1308 + 44, texAladin_f);
	sprites->Add(10277, 638, 1300, 638 + 46, 1300 + 52, texAladin_f);
	sprites->Add(10278, 572, 1294, 572 + 51, 1294 + 52, texAladin_f);
	ani = new CAnimation(100);
	ani->Add(10270);
	ani->Add(10271);
	ani->Add(10272);
	ani->Add(10273);
	ani->Add(10274);
	ani->Add(10275);
	ani->Add(10276);
	ani->Add(10277);
	ani->Add(10278);

	animations->Add(511, ani);

	//----trèo dây thẳng đứng
	sprites->Add(10280, 11, 1362, 11 + 29, 1362 + 86, texAladin);
	sprites->Add(10281, 53, 1361, 53 + 28, 1361+89, texAladin);
	sprites->Add(10282, 94, 1374, 94+28, 1374+74, texAladin);
	sprites->Add(10283, 133, 1377, 133+42,1377+62, texAladin);
	sprites->Add(10284, 186, 1363, 186+31, 1363+76, texAladin);
	sprites->Add(10285, 231, 1358,231+29,1358+86, texAladin);
	sprites->Add(10286, 274, 1367,274+28,1367+79, texAladin);
	sprites->Add(10287, 314, 1377, 314+32, 1377+63, texAladin);
	sprites->Add(10288, 356, 1377, 356+42, 1377+62, texAladin);
	sprites->Add(10289, 406, 1362,406+28, 1362+81, texAladin);
	ani = new CAnimation(100);
	ani->Add(10280);
	ani->Add(10281);
	ani->Add(10282);
	ani->Add(10283);
	ani->Add(10284);
	ani->Add(10285);
	ani->Add(10286);
	ani->Add(10287);
	ani->Add(10288);
	ani->Add(10289);
	animations->Add(512, ani);
	// --------day tuong trái--------
	sprites->Add(10290, 1058, 1959, 1058 + 56, 1959 + 46, texAladin_f);
	sprites->Add(10291, 981, 1961, 981 + 65, 1961 + 44, texAladin_f);
	sprites->Add(10292, 894, 1961, 894 + 70, 1961 + 45, texAladin_f);
	sprites->Add(10293, 807, 1962, 807 + 77, 1962 + 44, texAladin_f);
	sprites->Add(10294, 722, 1964, 722 + 72, 44 + 1964, texAladin_f);
	sprites->Add(10295, 639, 1965, 639 + 66, 1965 + 44, texAladin_f);
	sprites->Add(10296, 551, 1965, 551 + 75, 1965 + 44, texAladin_f);
	sprites->Add(10297, 455, 1966, 455 + 81, 1966 + 44, texAladin_f);
	sprites->Add(10298, 365, 1968, 365 + 75, 1968 + 44, texAladin_f);

	ani = new CAnimation(100);	// day tuong trái
	ani->Add(10290);
	ani->Add(10291);
	ani->Add(10292);
	ani->Add(10293);
	ani->Add(10294);
	ani->Add(10295);
	ani->Add(10296);
	ani->Add(10297);
	ani->Add(10298);
	animations->Add(513, ani);

	// chém mạnh phải
	sprites->Add(10300, 11, 420, 11 + 42, 420 + 53, texAladin);
	sprites->Add(10301, 66, 413, 66+38, 413+60, texAladin);

	sprites->Add(10302, 111, 412, 111+65, 412+61, texAladin);   // lập 5 lần
	sprites->Add(10303, 193, 415, 193+47, 415+58, texAladin);
	sprites->Add(10304, 249, 418, 249+47, 418+54, texAladin);
	sprites->Add(10305, 298, 424, 298+54, 424+48, texAladin);
	sprites->Add(10306, 363, 401, 363+74, 401+71, texAladin);
	sprites->Add(10307, 452, 386, 452+54, 386+86, texAladin);
	sprites->Add(10308, 520, 401, 520+49, 401+71, texAladin);
	sprites->Add(10309, 584, 405,584+51, 405+67, texAladin);

	sprites->Add(10310, 111, 412, 111 + 65, 412 + 61, texAladin); //2
	sprites->Add(10311, 193, 415, 193 + 47, 415 + 58, texAladin);
	sprites->Add(10312, 249, 418, 249 + 47, 418 + 54, texAladin);
	sprites->Add(10313, 298, 424, 298 + 54, 424 + 48, texAladin);
	sprites->Add(10314, 363, 401, 363 + 74, 401 + 71, texAladin);
	sprites->Add(10315, 452, 386, 452 + 54, 386 + 86, texAladin);
	sprites->Add(10316, 520, 401, 520 + 49, 401 + 71, texAladin);
	sprites->Add(10317, 584, 405, 584 + 51, 405 + 67, texAladin);

	sprites->Add(10318, 111, 412, 111 + 65, 412 + 61, texAladin); //3
	sprites->Add(10319, 193, 415, 193 + 47, 415 + 58, texAladin);
	sprites->Add(10320, 249, 418, 249 + 47, 418 + 54, texAladin);
	sprites->Add(10321, 298, 424, 298 + 54, 424 + 48, texAladin);
	sprites->Add(10322, 363, 401, 363 + 74, 401 + 71, texAladin);
	sprites->Add(10323, 452, 386, 452 + 54, 386 + 86, texAladin);
	sprites->Add(10324, 520, 401, 520 + 49, 401 + 71, texAladin);
	sprites->Add(10325, 584, 405, 584 + 51, 405 + 67, texAladin);

	sprites->Add(10326, 111, 412, 111 + 65, 412 + 61, texAladin);  //4
	sprites->Add(10327, 193, 415, 193 + 47, 415 + 58, texAladin);
	sprites->Add(10328, 249, 418, 249 + 47, 418 + 54, texAladin);
	sprites->Add(10329, 298, 424, 298 + 54, 424 + 48, texAladin);
	sprites->Add(10330, 363, 401, 363 + 74, 401 + 71, texAladin);
	sprites->Add(10331, 452, 386, 452 + 54, 386 + 86, texAladin);
	sprites->Add(10332, 520, 401, 520 + 49, 401 + 71, texAladin);
	sprites->Add(10333, 584, 405, 584 + 51, 405 + 67, texAladin);

	sprites->Add(10334, 111, 412, 111 + 65, 412 + 61, texAladin); //5
	sprites->Add(10335, 193, 415, 193 + 47, 415 + 58, texAladin);
	sprites->Add(10336, 249, 418, 249 + 47, 418 + 54, texAladin);
	sprites->Add(10337, 298, 424, 298 + 54, 424 + 48, texAladin);
	sprites->Add(10338, 363, 401, 363 + 74, 401 + 71, texAladin);
	sprites->Add(10339, 452, 386, 452 + 54, 386 + 86, texAladin);
	sprites->Add(10340, 520, 401, 520 + 49, 401 + 71, texAladin);
	sprites->Add(10341, 584, 405, 584 + 51, 405 + 67, texAladin);

	sprites->Add(10342, 644, 415, 644+53, 415+57, texAladin);
	sprites->Add(10343, 704, 418, 704+46, 418+54, texAladin);

	ani = new CAnimation(70);	// chém mạnh
	ani->Add(10300);
	ani->Add(10301);
	ani->Add(10302);
	ani->Add(10303);
	ani->Add(10304);
	ani->Add(10305);
	ani->Add(10306);
	ani->Add(10307);
	ani->Add(10308);
	ani->Add(10309);
	ani->Add(10310);
	ani->Add(10311);
	ani->Add(10312);
	ani->Add(10313);
	ani->Add(10314);
	ani->Add(10315);
	ani->Add(10316);
	ani->Add(10317);
	ani->Add(10318);
	ani->Add(10319);
	ani->Add(10320);
	ani->Add(10321);
	ani->Add(10322);
	ani->Add(10323);
	ani->Add(10324);
	ani->Add(10325);
	ani->Add(10326);
	ani->Add(10327);
	ani->Add(10328);
	ani->Add(10329);
	ani->Add(10330);
	ani->Add(10331);
	ani->Add(10332);
	ani->Add(10333);
	ani->Add(10334);
	ani->Add(10335);
	ani->Add(10336);
	ani->Add(10337);
	ani->Add(10338);
	ani->Add(10339);
	ani->Add(10340);
	ani->Add(10341);
	ani->Add(10342);
	ani->Add(10343);
	
	animations->Add(515, ani);

	// chém mạnh trái
	sprites->Add(10400, 1068, 420, 1068 + 42, 420 + 53, texAladin_f);
	sprites->Add(10401, 1017, 413, 1017 + 38, 413 + 60, texAladin_f);

	sprites->Add(10402, 945, 412, 945 + 65, 412 + 61, texAladin_f);   // lập 5 lần
	sprites->Add(10403, 881, 415, 881 + 47, 415 + 58, texAladin_f);
	sprites->Add(10404, 825, 418, 825 + 47, 418 + 54, texAladin_f);
	sprites->Add(10405, 769, 424, 769 + 54, 424 + 48, texAladin_f);
	sprites->Add(10406, 684, 401, 684 + 74, 401 + 71, texAladin_f);
	sprites->Add(10407, 615, 386, 615 + 54, 386 + 86, texAladin_f);
	sprites->Add(10408, 552, 401, 552 + 49, 401 + 71, texAladin_f);
	sprites->Add(10409, 486, 405, 486 + 51, 405 + 67, texAladin_f);

	sprites->Add(10410, 945, 412, 945 + 65, 412 + 61, texAladin_f);   // lập 5 lần
	sprites->Add(10411, 881, 415, 881 + 47, 415 + 58, texAladin_f);
	sprites->Add(10412, 825, 418, 825 + 47, 418 + 54, texAladin_f);
	sprites->Add(10413, 769, 424, 769 + 54, 424 + 48, texAladin_f);
	sprites->Add(10414, 684, 401, 684 + 74, 401 + 71, texAladin_f);
	sprites->Add(10415, 615, 386, 615 + 54, 386 + 86, texAladin_f);
	sprites->Add(10416, 552, 401, 552 + 49, 401 + 71, texAladin_f);
	sprites->Add(10417, 486, 405, 486 + 51, 405 + 67, texAladin_f);

	sprites->Add(10418, 945, 412, 945 + 65, 412 + 61, texAladin_f);   // lập 5 lần
	sprites->Add(10419, 881, 415, 881 + 47, 415 + 58, texAladin_f);
	sprites->Add(10420, 825, 418, 825 + 47, 418 + 54, texAladin_f);
	sprites->Add(10421, 769, 424, 769 + 54, 424 + 48, texAladin_f);
	sprites->Add(10422, 684, 401, 684 + 74, 401 + 71, texAladin_f);
	sprites->Add(10423, 615, 386, 615 + 54, 386 + 86, texAladin_f);
	sprites->Add(10424, 552, 401, 552 + 49, 401 + 71, texAladin_f);
	sprites->Add(10425, 486, 405, 486 + 51, 405 + 67, texAladin_f);

	sprites->Add(10426, 945, 412, 945 + 65, 412 + 61, texAladin_f);   // lập 5 lần
	sprites->Add(10427, 881, 415, 881 + 47, 415 + 58, texAladin_f);
	sprites->Add(10428, 825, 418, 825 + 47, 418 + 54, texAladin_f);
	sprites->Add(10429, 769, 424, 769 + 54, 424 + 48, texAladin_f);
	sprites->Add(10430, 684, 401, 684 + 74, 401 + 71, texAladin_f);
	sprites->Add(10431, 615, 386, 615 + 54, 386 + 86, texAladin_f);
	sprites->Add(10432, 552, 401, 552 + 49, 401 + 71, texAladin_f);
	sprites->Add(10433, 486, 405, 486 + 51, 405 + 67, texAladin_f);

	sprites->Add(10434, 945, 412, 945 + 65, 412 + 61, texAladin_f);   // lập 5 lần
	sprites->Add(10435, 881, 415, 881 + 47, 415 + 58, texAladin_f);
	sprites->Add(10436, 825, 418, 825 + 47, 418 + 54, texAladin_f);
	sprites->Add(10437, 769, 424, 769 + 54, 424 + 48, texAladin_f);
	sprites->Add(10438, 684, 401, 684 + 74, 401 + 71, texAladin_f);
	sprites->Add(10439, 615, 386, 615 + 54, 386 + 86, texAladin_f);
	sprites->Add(10440, 552, 401, 552 + 49, 401 + 71, texAladin_f);
	sprites->Add(10441, 486, 405, 486 + 51, 405 + 67, texAladin_f);

	sprites->Add(10442, 424, 415, 424 + 53, 415 + 57, texAladin_f);
	sprites->Add(10443, 371, 418, 371 + 46, 418 + 54, texAladin_f);

	ani = new CAnimation(70);	// chém mạnh
	ani->Add(10400);
	ani->Add(10401);
	ani->Add(10402);
	ani->Add(10403);
	ani->Add(10404);
	ani->Add(10405);
	ani->Add(10406);
	ani->Add(10407);
	ani->Add(10408);
	ani->Add(10409);
	ani->Add(10410);
	ani->Add(10411);
	ani->Add(10412);
	ani->Add(10413);
	ani->Add(10414);
	ani->Add(10415);
	ani->Add(10416);
	ani->Add(10417);
	ani->Add(10418);
	ani->Add(10419);
	ani->Add(10420);
	ani->Add(10421);
	ani->Add(10422);
	ani->Add(10423);
	ani->Add(10424);
	ani->Add(10425);
	ani->Add(10426);
	ani->Add(10427);
	ani->Add(10428);
	ani->Add(10429);
	ani->Add(10430);
	ani->Add(10431);
	ani->Add(10432);
	ani->Add(10433);
	ani->Add(10434);
	ani->Add(10435);
	ani->Add(10436);
	ani->Add(10437);
	ani->Add(10438);
	ani->Add(10439);
	ani->Add(10440);
	ani->Add(10441);
	ani->Add(10442);
	ani->Add(10443);

	animations->Add(516, ani);
	//-- nhảy chém phải
	
	sprites->Add(10450, 13, 1077, 13+52, 1077+54, texAladin);
	sprites->Add(10451, 75, 1075, 75+50, 1075+52, texAladin);
	sprites->Add(10452, 140, 1067, 140+47, 1067+66, texAladin);
	sprites->Add(10453, 199, 1078, 199+52, 1078+56, texAladin);
	sprites->Add(10454, 266, 1079, 266+83, 1079+51, texAladin);
	sprites->Add(10455, 361, 1087, 361+47, 1087+55, texAladin);

	ani = new CAnimation(100);
	ani->Add(10450);
	ani->Add(10451);
	ani->Add(10452);
	ani->Add(10453);
	ani->Add(10454);
	ani->Add(10455);
	
	animations->Add(517, ani);
	//-- nhảy chém trái

	sprites->Add(10460, 1056, 1077, 1056 + 52, 1077 + 54, texAladin_f);
	sprites->Add(10461, 996, 1075, 996 + 50, 1075 + 52, texAladin_f);
	sprites->Add(10462, 934, 1067, 934 + 47, 1067 + 66, texAladin_f);
	sprites->Add(10463, 870, 1078, 870 + 52, 1078 + 56, texAladin_f);
	sprites->Add(10464, 772, 1079, 772 + 83, 1079 + 51, texAladin_f);
	sprites->Add(10465, 713, 1087, 713 + 47, 1087 + 55, texAladin_f);

	ani = new CAnimation(100);
	ani->Add(10460);
	ani->Add(10461);
	ani->Add(10462);
	ani->Add(10463);
	ani->Add(10464);
	ani->Add(10465);

	animations->Add(518, ani);

	//-- ném táo phải

	sprites->Add(10470, 7, 235, 7+43,235+56, texAladin);
	sprites->Add(10471, 57, 232, 57+41, 232+59, texAladin);
	sprites->Add(10472, 109, 233, 109+38, 233+58, texAladin);
	sprites->Add(10473, 163, 231, 163+46, 231+60, texAladin);
	sprites->Add(10474, 221, 233, 221+37, 233+58, texAladin);
	sprites->Add(10475, 268, 239, 268+39,239+52, texAladin);

	ani = new CAnimation(100);
	ani->Add(10470);
	ani->Add(10471);
	ani->Add(10472);
	ani->Add(10473);
	ani->Add(10474);
	ani->Add(10475);

	animations->Add(519, ani);
	//-- ném táo trái

	sprites->Add(10480, 1071, 235, 1071 + 43, 235 + 56, texAladin_f);
	sprites->Add(10481, 1023, 232, 1023 + 41, 232 + 59, texAladin_f);
	sprites->Add(10482, 974, 233, 974 + 38, 233 + 58, texAladin_f);
	sprites->Add(10483, 912, 231, 912 + 46, 231 + 60, texAladin_f);
	sprites->Add(10484, 863, 233, 863 + 37, 233 + 58, texAladin_f);
	sprites->Add(10485, 814, 239, 814 + 39, 239 + 52, texAladin_f);

	ani = new CAnimation(100);
	ani->Add(10480);
	ani->Add(10481);
	ani->Add(10482);
	ani->Add(10483);
	ani->Add(10484);
	ani->Add(10485);

	animations->Add(520, ani);

	//--ngồi ném táo phải

	sprites->Add(10490, 9, 571, 9+37, 571+44, texAladin);
	sprites->Add(10491, 58, 567, 58+37, 567+48, texAladin);
	sprites->Add(10492, 107, 571, 107+50, 571+48, texAladin);
	sprites->Add(10493, 164, 578, 164+82, 578+37, texAladin);
	sprites->Add(10494, 256, 579, 256+57, 579+37, texAladin);
	

	ani = new CAnimation(100);
	ani->Add(10490);
	ani->Add(10491);
	ani->Add(10492);
	ani->Add(10493);
	ani->Add(10494);
	

	animations->Add(521, ani);
	//--ngồi ném táo trái

	sprites->Add(10495, 1075, 571, 1075 + 37, 571 + 44, texAladin_f);
	sprites->Add(10496, 1026, 567, 1026 + 37, 567 + 48, texAladin_f);
	sprites->Add(10497, 964, 571, 964 + 50, 571 + 48, texAladin_f);
	sprites->Add(10498, 875, 578, 875 + 82, 578 + 37, texAladin_f);
	sprites->Add(10499, 808, 579, 808 + 57, 579 + 37, texAladin_f);


	ani = new CAnimation(100);
	ani->Add(10495);
	ani->Add(10496);
	ani->Add(10497);
	ani->Add(10498);
	ani->Add(10499);
	animations->Add(522, ani);
	//--nhảy ném táo phải

	sprites->Add(10500, 19, 1005, 19+49, 1005+55, texAladin);
	sprites->Add(10501, 77, 1007, 77+43, 1007+52, texAladin);
	sprites->Add(10502, 132, 1008, 132+39, 1008+53, texAladin);
	sprites->Add(10503, 185, 1008,185+52, 1008+53, texAladin);
	sprites->Add(10504, 253, 1012, 253+40, 1012+52, texAladin);


	ani = new CAnimation(100);
	ani->Add(10500);
	ani->Add(10501);
	ani->Add(10502);
	ani->Add(10503);
	ani->Add(10504);
	
	animations->Add(523, ani);
	//--nhảy ném táo trái
	sprites->Add(10505, 1053, 1005, 1053 + 49, 1005 + 55, texAladin_f);
	sprites->Add(10506, 1001, 1007, 1001 + 43, 1007 + 52, texAladin_f);
	sprites->Add(10507, 950, 1008, 950 + 39, 1008 + 53, texAladin_f);
	sprites->Add(10508, 884, 1008, 884 + 52, 1008 + 53, texAladin_f);
	sprites->Add(10509, 828, 1012, 828 + 40, 1012 + 52, texAladin_f);


	ani = new CAnimation(100);
	ani->Add(10505);
	ani->Add(10506);
	ani->Add(10507);
	ani->Add(10508);
	ani->Add(10509);

	animations->Add(524, ani);



	//---------------------------------------------------------
	this->AddAnimation(400);		 // 0 đứng phải
	this->AddAnimation(401);		 // 1 đứng trái
	this->AddAnimation(500);		 // 2 đi phải
	this->AddAnimation(501);		 // 3 đi trái
	this->AddAnimation(502);		// 4 nhảy
	this->AddAnimation(514);		 // 5 rớt xuống
	this->AddAnimation(503);		 // 6 nhảy phải
	this->AddAnimation(507);		// 7 nhảy trái
	this->AddAnimation(504);		// 8 chém phải
	this->AddAnimation(506);		 // 9 chém trái
	this->AddAnimation(508);		 // 10 ngồi chém phải
	this->AddAnimation(509);		// 11 ngồi chém trái
	this->AddAnimation(402);		// 12 ngoi phải-
	this->AddAnimation(403);		// 13 ngoi trái-
	this->AddAnimation(404);		// 14 ngước lên phải-
	this->AddAnimation(405);		// 15 ngước lên trái-
	this->AddAnimation(505);		// 16 day tuong phải-
	this->AddAnimation(513);		// 17 đẩy tường trái
	this->AddAnimation(510);		// 18 dừng phải-
	this->AddAnimation(511);		// 19 dừng trái-
	this->AddAnimation(512);		// 20 trèo lên
	this->AddAnimation(515);		// 21 chém mạnh phải
	this->AddAnimation(516);		// 22 chém mạnh trái
	this->AddAnimation(517);		// 23 nhảy chém phải
	this->AddAnimation(518);		// 24 nhảy chém trái
	this->AddAnimation(519);		// 25 ném táo phải	
	this->AddAnimation(520);		// 26 ném táo trái
	this->AddAnimation(521);		// 27 ngồi ném táo phải
	this->AddAnimation(522);		// 28 ngồi ném táo trái
	this->AddAnimation(523);		//	29 nhảy ném táo phải
	this->AddAnimation(524);		//	30 nhảy ném táo trái
}

void CAladin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (direction == 1)
	{
		left = x;
		top = y;
		right = x + ALADIN_BIG_BBOX_WIDTH;
		bottom = y + ALADIN_BIG_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x + ALADIN_BIG_BBOX_WIDTH;
		bottom = y + ALADIN_BIG_BBOX_HEIGHT;
	}
}

void CAladin::ReLoad()
{
}


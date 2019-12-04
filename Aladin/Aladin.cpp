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

	if (this->y > MAP_LIMIT_BOT - 100)
		this->y = MAP_LIMIT_BOT - 100;
	if (this->x > MAP_LIMIT_RIGHT - 50)
		this->x = MAP_LIMIT_RIGHT - 50;
	if (this->y < -50) this->y = -50;
	if (this->x < 0) this->x = 0;

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
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

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
	int ani;
	if (state == ALADIN_STATE_WALKING_RIGHT)
		ani = ALADIN_ANI_BIG_WALKING_RIGHT;
	else if (state == ALADIN_STATE_WALKING_LEFT)
		ani = ALADIN_ANI_BIG_WALKING_LEFT;
	else if (state == ALADIN_STATE_IDLE_LEFT)
		ani = ALADIN_ANI_BIG_IDLE_LEFT;
	else if (state == ALADIN_STATE_IDLE_RIGHT)
		ani = ALADIN_ANI_BIG_IDLE_RIGHT;
	else if (state == ALADIN_STATE_SIT_RIGHT)
		ani = ALADIN_ANI_SIT_RIGHT;
	else if (state == ALADIN_STATE_SIT_LEFT)
		ani = ALADIN_ANI_SIT_LEFT;

	int alpha = 255;
	if (stateNhay == true)
	{
		int stt = 3;
		if (vx == 0)
			animations[ALADIN_ANI_BIG_JUMP]->RenderAladin(stt,x, y + ALADIN_BIG_BBOX_HEIGHT,this->direction, alpha);
		else animations[ALADIN_ANI_BIG_JUMP]->RenderAladin(stt, x, y + ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);

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
		else
			animations[ani]->RenderAladin(x, y+ALADIN_BIG_BBOX_HEIGHT, this->direction, alpha);

	

	//RenderBoundingBox();
}

void CAladin::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ALADIN_STATE_WALKING_RIGHT:
		vx = ALADIN_WALKING_SPEED;
		nx = ALADIN_STATE_WALKING_RIGHT;
		break;

	case ALADIN_STATE_WALKING_LEFT:
		vx = -ALADIN_WALKING_SPEED;
		nx = ALADIN_STATE_WALKING_LEFT;
		break;

	case ALADIN_STATE_JUMP:
		vy = -ALADIN_JUMP_SPEED_Y;// -ALADIN_JUMP_SPEED_Y;
		nx = ALADIN_STATE_JUMP;
		break;

	case ALADIN_STATE_JUMP_RIGHT:
		vy = -ALADIN_JUMP_SPEED_Y;
		nx = ALADIN_STATE_JUMP_RIGHT;
		break;

	case ALADIN_STATE_IDLE_LEFT:
		vx = 0;
		nx = ALADIN_STATE_IDLE_LEFT;
		break;

	case ALADIN_STATE_IDLE_RIGHT:
		vx = 0;
		nx = ALADIN_STATE_IDLE_RIGHT;
		break;

	case ALADIN_STATE_SIT_RIGHT:
		vx = 0;
		nx = ALADIN_STATE_SIT_RIGHT;
		break;

	case ALADIN_STATE_SIT_LEFT:
		vx = 0;
		nx = ALADIN_STATE_SIT_LEFT;
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

	//----ngoi phải----
	sprites->Add(20015, 9, 640, 9 + 47, 640 + 33, texAladin);

	ani = new CAnimation(100);	// ngoi phải
	ani->Add(20015);
	animations->Add(402, ani);
	//----ngoi trái----
	sprites->Add(20016, 1065, 640, 1065 + 47, 640 + 33, texAladin_f);

	ani = new CAnimation(100);	// ngoi trái
	ani->Add(20016);
	animations->Add(403, ani);
	//---- ngước lên phải----
	sprites->Add(20020, 11, 496, 11 + 39, 496 + 53, texAladin);
	sprites->Add(20021, 59, 490, 59 + 45, 59 + 490, texAladin);
	sprites->Add(20022, 111, 491, 111 + 49, 58 + 491, texAladin);
	ani = new CAnimation(100);
	ani->Add(20020);
	ani->Add(20021);
	ani->Add(20022);
	animations->Add(404, ani);
	//---- ngước lên trái----
	sprites->Add(20025, 1071, 496, 1071 + 39, 496 + 53, texAladin);
	sprites->Add(20026, 1017, 490, 1017 + 45, 59 + 490, texAladin);
	sprites->Add(20027, 961, 491, 961 + 49, 58 + 491, texAladin);
	ani = new CAnimation(100);
	ani->Add(20025);
	ani->Add(20026);
	ani->Add(20027);
	animations->Add(405, ani);

	//----walk right--------
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
	//----walk left-------
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
	//-------- jump up--------
	sprites->Add(10100, 8, 846, 8 + 59, 846 + 43, texAladin);
	sprites->Add(10101, 75, 828, 75 + 52, 828 + 62, texAladin);
	sprites->Add(10102, 137, 829, 137 + 54, 829 + 61, texAladin);
	sprites->Add(10103, 203, 824, 203 + 54, 824 + 69, texAladin);
	sprites->Add(10104, 269, 820, 269 + 51, 820 + 74, texAladin);
	sprites->Add(10105, 336, 829, 336 + 38, 829 + 66, texAladin);
	sprites->Add(10106, 390, 818, 390 + 35, 818 + 79, texAladin);
	sprites->Add(10107, 448, 808, 448 + 34, 808 + 93, texAladin);
	sprites->Add(10108, 504, 810, 504 + 34, 810 + 93, texAladin);
	sprites->Add(10109, 564, 812, 564 + 34, 812 + 93, texAladin);


	ani = new CAnimation(100);	// jupm up
	ani->Add(10100);
	ani->Add(10101);
	ani->Add(10102);
	ani->Add(10103);
	ani->Add(10104);
	ani->Add(10105);
	ani->Add(10106);
	ani->Add(10107);
	ani->Add(10108);
	animations->Add(502, ani);
	// --------jump right--------
	sprites->Add(10110, 10, 705, 10 + 41, 705 + 42, texAladin);
	sprites->Add(10111, 66, 683, 66 + 45, 683 + 76, texAladin);
	sprites->Add(10112, 124, 686, 124 + 57, 686 + 57, texAladin);
	sprites->Add(10113, 199, 698, 199 + 58, 698 + 42, texAladin);
	sprites->Add(10114, 273, 696, 273 + 61, 696 + 48, texAladin);
	sprites->Add(10115, 350, 692, 350 + 58, 692 + 53, texAladin);
	sprites->Add(10116, 419, 688, 419 + 53, 688 + 58, texAladin);
	sprites->Add(10117, 491, 680, 491 + 50, 680 + 85, texAladin);
	sprites->Add(10118, 560, 719, 560 + 59, 719 + 44, texAladin);

	ani = new CAnimation(200);	// jupm
	ani->Add(10110);
	ani->Add(10111);
	ani->Add(10112);
	ani->Add(10113);
	ani->Add(10114);
	ani->Add(10115);
	ani->Add(10116);
	ani->Add(10117);
	ani->Add(10118);
	animations->Add(503, ani);
	// --------chem phải--------
	sprites->Add(10200, 5, 337, 5 + 45, 51 + 337, texAladin);
	sprites->Add(10201, 54, 326, 54 + 51, 326 + 62, texAladin);
	sprites->Add(10202, 115, 314, 115 + 45, 314 + 74, texAladin);
	sprites->Add(10203, 171, 324, 171 + 82, 324 + 64, texAladin);
	sprites->Add(10204, 260, 335, 260 + 51, 53 + 335, texAladin);

	ani = new CAnimation(100);	// chem phải
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
	sprites->Add(10230, 1070, 705, 1070 + 41, 705 + 42, texAladin);
	sprites->Add(10231, 1010, 683, 1010 + 45, 683 + 76, texAladin);
	sprites->Add(10232, 940, 686, 940 + 57, 686 + 57, texAladin);
	sprites->Add(10233, 864, 698, 864 + 58, 698 + 42, texAladin);
	sprites->Add(10234, 787, 696, 787 + 61, 696 + 48, texAladin);
	sprites->Add(10235, 713, 692, 713 + 58, 692 + 53, texAladin);
	sprites->Add(10236, 649, 688, 649 + 53, 688 + 58, texAladin);
	sprites->Add(10237, 580, 680, 580 + 50, 680 + 85, texAladin);
	sprites->Add(10238, 502, 719, 502 + 59, 719 + 44, texAladin);

	ani = new CAnimation(100);	// jupm
	ani->Add(10230);
	ani->Add(10231);
	ani->Add(10232);
	ani->Add(10233);
	ani->Add(10234);
	ani->Add(10235);
	ani->Add(10236);
	ani->Add(10237);
	ani->Add(10238);
	animations->Add(507, ani);



	this->AddAnimation(400);		// 0 idle right big ANI[0]
	this->AddAnimation(401);		// 1 idle left big  ANI[1]
	this->AddAnimation(500);		// 2 walk right big ANI[2]	
	this->AddAnimation(501);		// 3 walk left big  ANI[3]
	this->AddAnimation(502);		// 4 JUMP
	this->AddAnimation(503);		// 5 JUMP RIGHT
	this->AddAnimation(504);		// 6 chem phải
	this->AddAnimation(402);		// 7 ngoi phải
	this->AddAnimation(403);		// 8 ngoi trái
	this->AddAnimation(404);		// 9 ngước lên phải
	this->AddAnimation(405);		// 10 ngước lên trái
	this->AddAnimation(505);		// 11 day tuong phải
	this->AddAnimation(506);		// 12 chém trái
	this->AddAnimation(507);		// 13 nhảy trái
}

void CAladin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x- ALADIN_BIG_BBOX_WIDTH/2;
	top = y; 
	right = x + ALADIN_BIG_BBOX_WIDTH;
	bottom = y + ALADIN_BIG_BBOX_HEIGHT;
}

void CAladin::ReLoad()
{
}


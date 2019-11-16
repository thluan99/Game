#include <algorithm>
#include "debug.h"

#include "Aladin.h"
#include "Game.h"

#include "Goomba.h"

void CAladin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += ALADIN_GRAVITY*dt;

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

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -ALADIN_JUMP_DEFLECT_SPEED;
					}
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
	if (vx == 0)
	{
		if (nx > 0) ani = ALADIN_ANI_BIG_IDLE_RIGHT;
		else ani = ALADIN_ANI_BIG_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = ALADIN_ANI_BIG_WALKING_RIGHT;
	else ani = ALADIN_ANI_BIG_WALKING_LEFT;
	int alpha = 255;

	animations[ani]->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CAladin::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ALADIN_STATE_WALKING_RIGHT:
		vx = ALADIN_WALKING_SPEED;
		nx = 1;
		break;
	case ALADIN_STATE_WALKING_LEFT: 
		vx = -ALADIN_WALKING_SPEED;
		nx = -1;
		break;
	case ALADIN_STATE_JUMP: 
		vy = -ALADIN_JUMP_SPEED_Y;
	case ALADIN_STATE_IDLE: 
		vx = 0;
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

	// idle right
	sprites->Add(20001, 3, 9, 37 + 3, 50 + 9, texAladin);
	sprites->Add(20002, 47, 11, 41 + 47, 47 + 11, texAladin);
	sprites->Add(20003, 95, 6, 40 + 95, 52 + 6, texAladin);
	sprites->Add(20004, 143, 3, 44 + 143, 55 + 3, texAladin);
	sprites->Add(20005, 197, 6, 41 + 197, 51 + 6, texAladin);
	sprites->Add(20006, 250, 5, 42 + 250, 51 + 5, texAladin);
	sprites->Add(20007, 303, 2, 44 + 303, 53 + 2, texAladin);
	//----idle left------
	sprites->Add(20008, 1081, 9, 1081 + 37, 9 + 50, texAladin_f);
	sprites->Add(20009, 1033, 11, 1033 + 41, 11 + 47, texAladin_f);
	sprites->Add(20010, 986, 6, 986 + 40, 6 + 52, texAladin_f);
	sprites->Add(20011, 934, 3, 934 + 44, 3 + 55, texAladin_f);
	sprites->Add(20012, 883, 6, 883 + 41, 6 + 51, texAladin_f);
	sprites->Add(20013, 829, 5, 829 + 42, 5 + 51, texAladin_f);
	sprites->Add(20014, 774, 2, 774 + 44, 2 + 53, texAladin_f);


	//walk right--------
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
	sprites->Add(10013, 679, 1218, 679 + 44, 1218 + 57, texAladin); // Walk right

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


	//ANIMATION////////////////////////////////
	LPANIMATION ani;
	ani = new CAnimation(100);	// idle big right
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

	ani = new CAnimation(100);	// idle big left
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

	this->AddAnimation(400);		// idle right big ANI[0]
	this->AddAnimation(401);		// idle left big  ANI[1]

	this->AddAnimation(500);		// walk right big ANI[2]	
	this->AddAnimation(501);		// walk left big  ANI[3]

}

void CAladin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	right = x + ALADIN_BIG_BBOX_WIDTH;
	bottom = y + ALADIN_BIG_BBOX_HEIGHT;
}


#include "Bat.h"

void Bat::Render()
{
	int ani = 0;
	int alpha = 255;
	int stt = 0;

	if (state == BAT_STATE_DIE || state == BAT_STATE_FLYING)
	{
		if (isFall == false)
		{
			if (isDeath == false)
			{
				ani = BAT_ANI_DIE;
				animations[ani]->RenderAladin(stt, x, y + BAT_BBOX_HEIGHT, direction, alpha);
				if (stt != 0)
					isDeath = true;
			}
			else animations[0]->RenderAladin(x, y, 1, 0);
		}
		else
		{
			if (isDeath == false)
			{
				ani = BAT_ANI_FLYING;
				animations[ani]->RenderAladin(stt, x, y + BAT_BBOX_HEIGHT, direction, alpha);
				if (stt != 0)
					isDeath = true;
			}
			else
				animations[0]->RenderAladin(x, y, 1, 0);
		}
	}
	else
	{
		switch (state)
		{
		case BAT_STATE_IDLE:
			ani = BAT_ANI_IDLE;
			break;

		case BAT_STATE_WAKEUP:
			ani = BAT_ANI_FLY;
			break;

		case BAT_STATE_FLY:
			ani = BAT_ANI_FLY;
			break;
		}
		animations[ani]->Render(x, y, alpha);
	}	
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// caculate dx, dx
	this->dt = dt;
	//dx = vx * dt;
	//dy = vy * dt;
	// fall down
	vy = 0;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (HP <= 0)
	{
		vx = 0;
		if (isFall == false)
			SetState(BAT_STATE_DIE);
		else SetState(BAT_STATE_FLYING);
	}
	if (state != BAT_STATE_DIE && state != BAT_STATE_FLYING)
		CalcPotentialCollisions(coObjects, coEvents);

	if (state == BAT_STATE_IDLE)
	{
		
	}
	else if (GetState() == BAT_STATE_WAKEUP)
	{

	}

	if (coEvents.size() == 0)
	{

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (e->obj->GetId() == eType::ALADIN)
			{
				x += e->t*dx;
			}
			if (e->obj->GetId() == eType::APPLE)
			{
				HP = HP - 1;
				isFall = true;
			}
			if (e->obj->GetId() == eType::SWORD)
			{
				HP = HP - 1;
				DebugOut(L"[info] : sword !!!!!!");
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Bat::GoToXY(float& x, float& y, float x_des, float y_des)
{
	float vx = 0, vy = 0;
 
	if (x_des > x)
	{
		vx = 0.1f;
	
	}
	else if (x_des < x)
	{
		vx = -0.1f;

	}

	if (y_des > y)
	{
		vy = 0.15f;
	}
	else if (y_des < y)
	{
		vy = -0.15f;
	}

	x += vx * dt;
	y += vy * dt;
}

void Bat::SetState(int state)
{
	CGameObject::SetState(state);
}

void Bat::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_BAT, L"textures\\bat.png", D3DCOLOR_XRGB(255, 0, 255));

	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textEBat = textures->Get(ID_TEX_BAT);
	LPDIRECT3DTEXTURE9 textExplo = textures->Get(ID_TEX_EXPLOSION);

	LPANIMATION ani;
	//----------IDLE------------//
	sprites->Add(47000, 9, 18, 7 + 9, 16 + 18, textEBat);
	ani = new CAnimation(100);
	ani->Add(47000);
	animations->Add(100, ani);

	//----------WAKEUP------------//
	sprites->Add(47001, 20, 10, 21 + 20, 22 + 10, textEBat);
	sprites->Add(47002, 48, 13, 19 + 48, 23 + 13, textEBat);
	sprites->Add(47003, 76, 18, 21 + 76, 14 + 18, textEBat);
	ani = new CAnimation(100);
	ani->Add(47000);
	ani->Add(47001);
	ani->Add(47002);
	ani->Add(47003);
	animations->Add(200, ani);
	//----------FLY------------//
	sprites->Add(47011, 10, 60, 24 + 10, 15 + 60, textEBat);
	sprites->Add(47012, 39, 52, 13 + 39, 23 + 52, textEBat);
	sprites->Add(47013, 56, 58, 30 + 56, 17 + 58, textEBat);
	sprites->Add(47014, 89, 67, 32 + 89, 16 + 67, textEBat);
	sprites->Add(47015, 128, 67, 8 + 128, 25 + 67, textEBat);
	sprites->Add(47016, 143, 67, 20 + 143, 16 + 67, textEBat);
	sprites->Add(47017, 165, 61, 34 + 165, 14 + 61, textEBat);
	ani = new CAnimation(100);
	ani->Add(47011);
	ani->Add(47012);
	ani->Add(47013);
	ani->Add(47014);
	ani->Add(47015);
	ani->Add(47016);
	ani->Add(47017);
	animations->Add(300, ani);

	//----------RE_FLY_ing------------//
	sprites->Add(47021, 10, 119, 13 + 10, 13 + 119, textEBat);
	sprites->Add(47022, 38, 111, 51 + 38, 28 + 111, textEBat);
	sprites->Add(47023, 93, 113, 22 + 93, 23 + 113, textEBat);
	ani = new CAnimation(100);
	ani->Add(47021);
	ani->Add(47022);
	ani->Add(47023);
	animations->Add(400, ani);

	//----------FLY_ing------------//
	sprites->Add(47031, 128, 102, 20 + 128, 14 + 35 + 102, textEBat);
	sprites->Add(47032, 160, 106, 26 + 160, 12 + 36 + 106, textEBat);
	sprites->Add(47033, 199, 106, 29 + 199, 53 + 106, textEBat);
	sprites->Add(47034, 233, 105, 25 + 233, 10 + 32 + 105, textEBat);
	sprites->Add(47035, 275, 106, 23 + 275, 51 + 106, textEBat);
	sprites->Add(47036, 316, 106, 23 + 316, 51 + 106, textEBat);
	ani = new CAnimation(100);
	ani->Add(47031);
	ani->Add(47032);
	ani->Add(47033);
	ani->Add(47034);
	ani->Add(47035);
	ani->Add(47036);
	animations->Add(450, ani);

	// ENEMY DIE
	sprites->Add(9990, 30, 30, 19 + 30, 15 + 30, textExplo);
	sprites->Add(9991, 85, 5, 64 + 85, 43 + 5, textExplo);
	sprites->Add(9992, 160, 5, 70 + 160, 44 + 5, textExplo);
	sprites->Add(9993, 233, 3, 73 + 233, 46 + 3, textExplo);
	sprites->Add(9994, 329, 16, 36 + 329, 33 + 16, textExplo);
	sprites->Add(9995, 404, 15, 38 + 404, 34 + 15, textExplo);
	sprites->Add(9996, 481, 17, 38 + 481, 33 + 17, textExplo);
	sprites->Add(9997, 560, 18, 36 + 560, 32 + 18, textExplo);
	sprites->Add(9998, 639, 19, 35 + 639, 31 + 19, textExplo);
	sprites->Add(9999, 716, 19, 35 + 716, 31 + 19, textExplo);
	ani = new CAnimation(100);
	ani->Add(9990);
	ani->Add(9991);
	ani->Add(9992);
	ani->Add(9993);
	ani->Add(9994);
	ani->Add(9995);
	ani->Add(9996);
	ani->Add(9997);
	ani->Add(9998);
	ani->Add(9999);
	animations->Add(999, ani);

	this->AddAnimation(100);
	this->AddAnimation(200);
	this->AddAnimation(300);
	this->AddAnimation(400);
	this->AddAnimation(450);
	this->AddAnimation(999);			// ani die
}

void Bat::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state != BAT_STATE_FLYING && state != BAT_STATE_DIE)
	{
		l = x;
		t = y;
		r = x + BAT_BBOX_WIDTH;
		b = y + BAT_BBOX_HEIGHT;
	}
	else l = t = r = b = 0;
}

void Bat::ReLoad()
{
}

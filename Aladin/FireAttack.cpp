#include "FireAttack.h"

void FireAttack::Render()
{
	if (direction == -1)
		animations[1]->RenderAladin(x, y + FIRE_BBOX_HEIGHT, direction);
	else (animations[0]->RenderAladin(x, y + FIRE_BBOX_HEIGHT, direction));
	//RenderBoundingBox();
}

void FireAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->y >= 376 - FIRE_BBOX_HEIGHT)
	{
		this->y = 376 - FIRE_BBOX_HEIGHT;
		vy = 0;
	}
	else
		vy = 0.08f;	 // rơi
	if (direction == -1)		// hướng trái 
		vx = -0.1f;
	else vx = 0.1f;		// hướng phải

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += (vx*dt);		// tăng tọa độ
		y += (vy*dt);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->id == eType::M2LAND)
			{
				//DebugOut(L"[[][][][[][================");
			}
		}
	}
}

void FireAttack::SetState(int state)
{
	CGameObject::SetState(state);
}

void FireAttack::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;

	textures->Add(ID_TEX_JAFAR_R, L"textures\\Scene2\\SJafar.png", D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_JAFAR_L, L"textures\\Scene2\\SJafar_f.png", D3DCOLOR_XRGB(186, 254, 202));

	CAnimations *animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 textEFire = textures->Get(ID_TEX_JAFAR_R);
	LPDIRECT3DTEXTURE9 textEFire_f = textures->Get(ID_TEX_JAFAR_L);
	LPANIMATION ani;

	sprites->Add(48090, 8, 485, 75 + 8, 50 + 485, textEFire); // fire right
	sprites->Add(48091, 96, 487, 79 + 96, 48 + 487, textEFire);
	sprites->Add(48092, 189, 487, 94 + 189, 48 + 487, textEFire);
	sprites->Add(48093, 296, 490, 90 + 296, 45 + 490, textEFire);
	sprites->Add(48094, 400, 506, 77 + 400, 29 + 506, textEFire);
	sprites->Add(48095, 488, 504, 73 + 488, 31 + 504, textEFire);
	sprites->Add(48096, 568, 492, 64 + 568, 43 + 492, textEFire);
	sprites->Add(48097, 645, 484, 64 + 645, 51 + 484, textEFire);
	ani = new CAnimation(100);
	ani->Add(48090);
	ani->Add(48091);
	ani->Add(48092);
	ani->Add(48093);
	ani->Add(48094);
	ani->Add(48095);
	ani->Add(48096);
	ani->Add(48097);
	animations->Add(100, ani);

	sprites->Add(48100, 780, 485, 75 + 780, 50 + 485, textEFire_f); // fire left
	sprites->Add(48101, 688, 487, 79 + 688, 48 + 487, textEFire_f);
	sprites->Add(48102, 580, 487, 94 + 580, 48 + 487, textEFire_f);
	sprites->Add(48103, 477, 490, 90 + 477, 45 + 490, textEFire_f);
	sprites->Add(48104, 386, 506, 77 + 386, 29 + 506, textEFire_f);
	sprites->Add(48105, 302, 504, 73 + 302, 31 + 504, textEFire_f);
	sprites->Add(48106, 231, 492, 64 + 231, 43 + 492, textEFire_f);
	sprites->Add(48107, 154, 484, 64 + 154, 51 + 484, textEFire_f);
	ani = new CAnimation(100);
	ani->Add(48100);
	ani->Add(48101);
	ani->Add(48102);
	ani->Add(48103);
	ani->Add(48104);
	ani->Add(48105);
	ani->Add(48106);
	ani->Add(48107);
	animations->Add(101, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
}

void FireAttack::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + FIRE_BBOX_WIDTH;
	b = y + FIRE_BBOX_HEIGHT;
}

void FireAttack::ReLoad()
{
}


FireAttack::~FireAttack()
{
}

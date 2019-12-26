#include "Jafar.h"

void Jafar::Render()
{
	int ani = 0;
	int alpha = 255;
	int stt = 0;

	if (HP <= henshinState)
	{
		if (direction == -1)
			SetState(JAFAR_STATE_SNAKE_AT_L);
		else SetState(JAFAR_STATE_SNAKE_AT_R);

		if (state == JAFAR_STATE_SNAKE_AT_R)
			ani = JAFAR_ANI_SNAKE_AT_R;
		else if (state == JAFAR_STATE_SNAKE_AT_L)
			ani = JAFAR_ANI_SNAKE_AT_L;

		animations[ani]->RenderAladin(stt, x, y + JAFAR_BBOX_HEIGHT, direction);
	}


	if (HP > henshinState)
	{
		if (state == JAFAR_STATE_CB_ATTACK_L || state == JAFAR_STATE_CB_ATTACK_R)
		{
			if (direction == -1)
			{
				ani = JAFAR_ANI_CB_ATTACK_L;
				animations[ani]->RenderAladin(stt, x, y + JAFAR_BBOX_HEIGHT, direction);
				if (stt != 0)
					SetState(JAFAR_STATE_ATTACK_L);
			}
			else
			{
				ani = JAFAR_ANI_CB_ATTACK_R;
				animations[ani]->RenderAladin(stt, x, y + JAFAR_BBOX_HEIGHT, direction);
				if (stt != 0)
					SetState(JAFAR_STATE_ATTACK_R);
			}
		}
		else if (state == JAFAR_STATE_ATTACK_L || state == JAFAR_STATE_ATTACK_R)
		{
			if (direction == -1)
			{
				ani = JAFAR_ANI_ATTACK_L;
				animations[ani]->RenderAladin(stt, x, y + JAFAR_BBOX_HEIGHT, direction);
				if (stt != 0)
					SetState(JAFAR_STATE_CB_ATTACK_L);
			}
			else
			{
				ani = JAFAR_ANI_ATTACK_R;
				animations[ani]->RenderAladin(stt, x, y + JAFAR_BBOX_HEIGHT, direction);
				if (stt != 0)
					SetState(JAFAR_STATE_CB_ATTACK_R);
			}
		}
	}

	/*if (state == JAFAR_STATE_IDLE_R)
		ani = JAFAR_ANI_IDLE_R;
	else if (state == JAFAR_STATE_IDLE_L)
		ani = JAFAR_ANI_IDLE_L;*/
}

void Jafar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	// fall down
	vy = 0;

	x = jafarX;
	y = jafarY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Apple *>(e->obj))
			{
				Apple *apple = dynamic_cast<Apple*>(e->obj);
				if (this->GetState() != JAFAR_STATE_DIE)
					this->HP--;
				DebugOut(L"[INFO] : HP : %d", this->HP);
			}
			if (dynamic_cast<CAladin*>(e->obj))
			{
				if (nx != 0 || ny != 0)
				{
					e->obj->y += e->t*dy;
					e->obj->x += e->t*dx;
				}
				e->obj->HP--;
				DebugOut(L"HP-----------------");
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (this->HP <= 0)
	{
		SetState(JAFAR_STATE_DIE);
		HP = 0;
	}
}

void Jafar::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case JAFAR_STATE_IDLE_R:
		nx = 1;
		break;
	case JAFAR_STATE_IDLE_L:
		nx = -1;
		break;
	case JAFAR_STATE_ATTACK_R:
		nx = 1;
		break;
	case JAFAR_STATE_ATTACK_L:
		nx = -1;
		break;
	case JAFAR_STATE_SNAKE_AT_R:
		nx = 1;
		break;
	case JAFAR_STATE_SNAKE_AT_L:
		nx = -1;
		break;
	}
}

void Jafar::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;

	textures->Add(ID_TEX_JAFAR_R, L"textures\\Scene2\\SJafar.png", D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_JAFAR_L, L"textures\\Scene2\\SJafar_f.png", D3DCOLOR_XRGB(186, 254, 202));

	CAnimations *animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 textEJafar = textures->Get(ID_TEX_JAFAR_R);
	LPDIRECT3DTEXTURE9 textEJafar_f = textures->Get(ID_TEX_JAFAR_L);
	LPANIMATION ani;

	sprites->Add(48000, 8, 9, 64 + 8, 71 + 9, textEJafar); // idle right
	ani = new CAnimation(100);
	ani->Add(48000);
	animations->Add(100, ani);

	sprites->Add(48050, 791, 9, 64 + 791, 71 + 9, textEJafar_f); // idle left
	ani = new CAnimation(100);
	ani->Add(48050);
	animations->Add(101, ani);

	sprites->Add(48001, 80, 10, 57 + 80, 70 + 10, textEJafar); // cb attack right
	sprites->Add(48002, 144, 11, 55 + 144, 69 + 11, textEJafar);
	sprites->Add(48003, 208, 12, 51 + 208, 68 + 12, textEJafar);
	sprites->Add(48004, 272, 11, 64 + 272, 69 + 11, textEJafar);
	sprites->Add(48005, 344, 11, 82 + 344, 69 + 11, textEJafar);
	//sprites->Add(48007, 536, 11, 68 + 536, 69 + 11, textEJafar);
	ani = new CAnimation(100);
	ani->Add(48000);
	ani->Add(48001);
	ani->Add(48002);
	ani->Add(48003);
	ani->Add(48004);
	ani->Add(48005);
	//ani->Add(48007);
	animations->Add(102, ani);

	sprites->Add(48051, 726, 10, 57 + 726, 70 + 10, textEJafar_f); //cb attack left
	sprites->Add(48052, 664, 11, 55 + 664, 69 + 11, textEJafar_f);
	sprites->Add(48053, 604, 12, 51 + 604, 68 + 12, textEJafar_f);
	sprites->Add(48054, 527, 11, 64 + 527, 69 + 11, textEJafar_f);
	sprites->Add(48055, 437, 11, 82 + 437, 69 + 11, textEJafar_f);
	//sprites->Add(48057, 259, 11, 68 + 259, 69 + 11, textEJafar_f);
	ani = new CAnimation(100);
	ani->Add(48050);
	ani->Add(48051);
	ani->Add(48052);
	ani->Add(48053);
	ani->Add(48054);
	ani->Add(48055);
	animations->Add(103, ani);


	sprites->Add(48010, 8, 317, 70 + 8, 58 + 317, textEJafar);		// attack snake right
	sprites->Add(48011, 88, 311, 64 + 88, 64 + 311, textEJafar);
	sprites->Add(48012, 160, 303, 67 + 160, 72 + 303, textEJafar);
	sprites->Add(48013, 240, 303, 71 + 240, 72 + 303, textEJafar);
	sprites->Add(48014, 320, 291, 69 + 320, 84 + 291, textEJafar);
	sprites->Add(48015, 400, 292, 69 + 400, 83 + 292, textEJafar);
	sprites->Add(48016, 480, 293, 70 + 480, 82 + 293, textEJafar);
	sprites->Add(48017, 560, 293, 70 + 560, 82 + 293, textEJafar);
	sprites->Add(48018, 644, 292, 64 + 644, 84 + 292, textEJafar);
	sprites->Add(48019, 716, 294, 64 + 716, 82 + 294, textEJafar);
	sprites->Add(48020, 788, 315, 71 + 788, 61 + 315, textEJafar);
	ani = new CAnimation(150);
	ani->Add(48010);
	ani->Add(48011);
	ani->Add(48012);
	ani->Add(48013);
	ani->Add(48014);
	ani->Add(48015);
	ani->Add(48016);
	ani->Add(48017);
	ani->Add(48018);
	ani->Add(48019);
	ani->Add(48020);
	animations->Add(104, ani);

	sprites->Add(48060, 785, 317, 70 + 785, 58 + 317, textEJafar_f);		// attack snake left
	sprites->Add(48061, 711, 311, 64 + 711, 64 + 311, textEJafar_f);
	sprites->Add(48062, 636, 303, 67 + 636, 72 + 303, textEJafar_f);
	sprites->Add(48063, 552, 303, 71 + 552, 72 + 303, textEJafar_f);
	sprites->Add(48064, 474, 291, 69 + 474, 84 + 291, textEJafar_f);
	sprites->Add(48065, 394, 292, 69 + 394, 83 + 292, textEJafar_f);
	sprites->Add(48066, 313, 293, 70 + 313, 82 + 293, textEJafar_f);
	sprites->Add(48067, 233, 293, 70 + 233, 82 + 293, textEJafar_f);
	sprites->Add(48068, 155, 292, 64 + 155, 84 + 292, textEJafar_f);
	sprites->Add(48069, 83, 294, 64 + 83, 82 + 294, textEJafar_f);
	sprites->Add(48070, 4, 315, 71 + 4, 61 + 315, textEJafar_f);
	ani = new CAnimation(150);
	ani->Add(48060);
	ani->Add(48061);
	ani->Add(48062);
	ani->Add(48063);
	ani->Add(48064);
	ani->Add(48065);
	ani->Add(48066);
	ani->Add(48067);
	ani->Add(48068);
	ani->Add(48069);
	ani->Add(48070);
	animations->Add(105, ani);

	sprites->Add(48006, 440, 11, 85 + 440, 69 + 11, textEJafar); // attack right
	ani = new CAnimation(2000);
	ani->Add(48006);
	animations->Add(106, ani);

	sprites->Add(48056, 338, 11, 85 + 338, 69 + 11, textEJafar_f);
	ani = new CAnimation(2000);
	ani->Add(48056);
	animations->Add(107, ani);

	this->AddAnimation(100);		// 0 idle right
	this->AddAnimation(101);		// 1 idle left
	this->AddAnimation(102);		// 2 cb attack right
	this->AddAnimation(103);		// 3 cb attack left
	this->AddAnimation(104);		// 4 attack snake right
	this->AddAnimation(105);		// 5 attack snake left
	this->AddAnimation(106);		// 6 attack  right
	this->AddAnimation(107);		// 7 attack  left
}

void Jafar::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + JAFAR_BBOX_WIDTH;
	b = y + JAFAR_BBOX_HEIGHT;
}

void Jafar::ReLoad()
{
}

Jafar::~Jafar()
{
}

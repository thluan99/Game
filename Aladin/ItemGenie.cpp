#include "ItemGenie.h"



ItemGenie::ItemGenie()
{
	SetState(GENIE_STATE_IDLE);
}

void ItemGenie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = 0;
}

void ItemGenie::Render()
{
	int ani = 0;
	int stt = 0;
	if (state == GENIE_STATE_IDLE)
	{
		ani = GENIE_ANI_IDLE;
		animations[ani]->Render(x, y);
	}		
	else if (state == GENIE_STATE_2)
	{
		ani = GENIE_ANI_2;
		if (isActive == false)
		{
			animations[ani]->RenderAladin(stt, x, y + IT_GENIE_BBOX_HEIGHT, 1, 255);
			if (stt != 0)
				isActive = true;
		}	
		else
			animations[0]->RenderAladin(x, y, 1, 0);
	}	
}

void ItemGenie::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITGenie = textures->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texITExGenie = textures->Get(ID_TEX_EXgENIE);

	sprites->Add(70001, 335, 45, 38 + 335, 50 + 45, texITGenie); // active
	sprites->Add(70002, 389, 45, 43 + 389, 52 + 45, texITGenie);
	sprites->Add(70003, 443, 49, 44 + 443, 44 + 49, texITGenie);
	sprites->Add(70004, 497, 48, 45 + 497, 44 + 48, texITGenie);
	ani = new CAnimation(100);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70001);
	ani->Add(70002);
	ani->Add(70003);
	ani->Add(70004);
	animations->Add(100, ani);

	sprites->Add(70061, 312, 32, 19 + 312, 20 + 32, texITExGenie);
	sprites->Add(70062, 344, 25, 26 + 344, 27 + 25, texITExGenie);
	sprites->Add(70063, 384, 23, 30 + 384, 29 + 23, texITExGenie);
	sprites->Add(70064, 424, 9, 43 + 424, 43 + 9, texITExGenie);
	sprites->Add(70065, 480, 15, 37 + 480, 37 + 15, texITExGenie);
	sprites->Add(70066, 528, 9, 42 + 528, 43 + 9, texITExGenie);
	sprites->Add(70067, 584, 9, 41 + 584, 43 + 9, texITExGenie);
	sprites->Add(70068, 8, 67, 43 + 8, 41 + 67, texITExGenie); // active
	sprites->Add(70069, 64, 67, 42 + 64, 41 + 67, texITExGenie);
	sprites->Add(70070, 120, 69, 43 + 120, 39 + 69, texITExGenie);
	sprites->Add(70071, 176, 71, 43 + 176, 37 + 71, texITExGenie);
	sprites->Add(70072, 232, 71, 42 + 232, 37 + 71, texITExGenie);
	sprites->Add(70073, 288, 64, 43 + 288, 44 + 64, texITExGenie);
	sprites->Add(70074, 344, 73, 41 + 344, 35 + 73, texITExGenie);
	sprites->Add(70075, 392, 84, 41 + 392, 24 + 84, texITExGenie);
	sprites->Add(70076, 440, 84, 39 + 440, 24 + 84, texITExGenie);
	sprites->Add(70077, 488, 88, 26 + 488, 20 + 67, texITExGenie);
	sprites->Add(70078, 528, 89, 20 + 528, 19 + 89, texITExGenie);
	sprites->Add(70079, 566, 84, 10 + 566, 23 + 84, texITExGenie);
	ani = new CAnimation(100);
	ani->Add(70061);
	ani->Add(70062);
	ani->Add(70063);
	ani->Add(70064);
	ani->Add(70065);
	ani->Add(70066);
	ani->Add(70067);
	ani->Add(70068);
	ani->Add(70069);
	ani->Add(70070);
	ani->Add(70071);
	ani->Add(70072);
	ani->Add(70073);
	ani->Add(70074);
	ani->Add(70075);
	ani->Add(70076);
	ani->Add(70077);
	ani->Add(70078);
	ani->Add(70079);
	animations->Add(101, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
}

void ItemGenie::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state != GENIE_STATE_2)
	{
		l = x;
		t = y;
		r = x + IT_GENIE_BBOX_WIDTH;
		b = y + IT_GENIE_BBOX_HEIGHT;
	}	
	else
	{
		l = t = r = b = 0;
	}
}

void ItemGenie::ReLoad()
{
}


ItemGenie::~ItemGenie()
{
}

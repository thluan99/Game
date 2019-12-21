#include "ItemGenie.h"



ItemGenie::ItemGenie()
{
}

void ItemGenie::Render()
{
	int ani = 0;
	if (state == GENIE_STATE_IDLE)
		ani = GENIE_ANI_IDLE;	
	else if (state == GENIE_STATE_2)
		ani = GENIE_ANI_2;

	animations[ani]->Render(x, y);
}

void ItemGenie::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITGenie = textures->Get(ID_TEX_ITEM);

	sprites->Add(70001, 335, 45, 38 + 335, 50 + 45, texITGenie); // active
	ani = new CAnimation(100);
	ani->Add(70001);
	animations->Add(100, ani);

	sprites->Add(70002, 389, 45, 43 + 389, 52 + 45, texITGenie);
	sprites->Add(70003, 443, 49, 44 + 443, 44 + 49, texITGenie);
	sprites->Add(70004, 497, 48, 45 + 497, 44 + 48, texITGenie);
	ani = new CAnimation(100);
	ani->Add(70001);
	ani->Add(70002);
	ani->Add(70003);
	ani->Add(70004);
	animations->Add(101, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
}

void ItemGenie::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + IT_GENIE_BBOX_WIDTH;
	b = y + IT_GENIE_BBOX_HEIGHT;
}

void ItemGenie::ReLoad()
{
}


ItemGenie::~ItemGenie()
{
}

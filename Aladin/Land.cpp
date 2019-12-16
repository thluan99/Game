#include "Land.h"

void CLand::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CLand::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;


	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;

	LPDIRECT3DTEXTURE9 textLand = textures->Get(ID_TEX_LAND);
	sprites->Add(1000, 0, 0, 1, 1, textLand);

	ani = new CAnimation(100);		// text
	ani->Add(1000);
	animations->Add(111, ani);

	this->AddAnimation(111);
}

void CLand::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (id == eType::LAND)
	{
		l = x;
		t = y;
		r = MAP_LIMIT_RIGHT;
		b = y + LAND_BBOX_HEIGHT;
	}
	else if (id == eType::LAND1)
	{
		l = x;
		t = y;
		r = x + LANDEX_BBOX_WIDTH;
		b = y + LAND1_BBOX_HEIGHT;
	}
	else if (id == eType::LAND2)
	{
		l = x;
		t = y;
		r = x + LANDEX_BBOX_WIDTH;
		b = y + LAND2_BBOX_HEIGHT;
	}
	else if (id == eType::LAND3)
	{
		l = x;
		t = y;
		r = x + LAND3_BBOX_WIDTH;
		b = y + LAND3_BBOX_HEIGHT;
	}
	else if (id == eType::M2LAND)
	{
		l = x;
		t = y;
		r = x + MAP2_LIMIT_RIGHT;
		b = y + LAND_BBOX_HEIGHT;
	}
}

void CLand::ReLoad()
{
}

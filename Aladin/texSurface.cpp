#include "texSurface.h"

void TextSurface::Render()
{
	//RenderBoundingBox();
	if (this->id == eType::BACKGROUND2)
		animations[5]->Render(0, 0);
	else
	{
		animations[0]->Render(177, 776);
		animations[1]->Render(16 * 31 + 1, 30 * 32);
		animations[2]->Render(16 * 51 + 1, 23 * 16 + 8);
		animations[3]->Render(16 * 73 + 1, 29 * 32);
		animations[4]->Render(16 * 137, 2 * 32 + 8);
	}
}

void TextSurface::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;

	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;

	textures->Add(ID_TEX_BK_M2, L"textures\\Scene2\\pillars.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 text_surbk2 = textures->Get(ID_TEX_BK_M2);
	LPDIRECT3DTEXTURE9 text_sur = textures->Get(ID_TEX_MAP);
	sprites->Add(60000, 177, 1147, 40 + 177, 341 + 1147, text_sur);
	ani = new CAnimation(100);		//1
	ani->Add(60000);
	animations->Add(100, ani);

	sprites->Add(60001, 497, 1144, 32 + 497, 160 + 1144, text_sur);
	ani = new CAnimation(100);
	ani->Add(60001);
	animations->Add(101, ani);

	sprites->Add(60002, 817, 1144, 32 + 817, 744 + 1144, text_sur);
	ani = new CAnimation(100);
	ani->Add(60002);
	animations->Add(102, ani);

	sprites->Add(60003, 1169, 1144, 32 + 1169, 192 + 1144, text_sur);
	ani = new CAnimation(100);
	ani->Add(60003);
	animations->Add(103, ani);

	sprites->Add(60004, 2192, 1144, 78 + 2192, 208 + 1144, text_sur);
	ani = new CAnimation(100);
	ani->Add(60004);
	animations->Add(104, ani);

	sprites->Add(60005, 0, 0, 830, 450, text_surbk2);
	ani = new CAnimation(100);
	ani->Add(60005);
	animations->Add(105, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
	this->AddAnimation(102);
	this->AddAnimation(103);
	this->AddAnimation(104);
	this->AddAnimation(105);
}

void TextSurface::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void TextSurface::ReLoad()
{
}

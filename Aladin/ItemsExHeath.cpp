#include "ItemsExHeath.h"



ItemsExHeath::ItemsExHeath()
{
}

void ItemsExHeath::Render()
{
	animations[0]->Render(x, y);
}

void ItemsExHeath::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITHeath = textures->Get(ID_TEX_ITEM);

	sprites->Add(70015, 343, 171, 19 + 343, 24 + 171, texITHeath);
	sprites->Add(70016, 366, 173, 17 + 366, 23 + 173, texITHeath);
	sprites->Add(70017, 387, 175, 16 + 387, 21 + 175, texITHeath);
	sprites->Add(70018, 406, 175, 17 + 406, 21 + 175, texITHeath);
	sprites->Add(70019, 426, 173, 19 + 426, 23 + 173, texITHeath);
	sprites->Add(70020, 448, 174, 17 + 448, 23 + 174, texITHeath);
	sprites->Add(70021, 467, 176, 16 + 467, 21 + 176, texITHeath);
	sprites->Add(70022, 486, 176, 17 + 486, 21 + 176, texITHeath);
	ani = new CAnimation(100);
	ani->Add(70015);
	ani->Add(70016);
	ani->Add(70017);
	ani->Add(70018);
	ani->Add(70019);
	ani->Add(70020);
	ani->Add(70021);
	ani->Add(70022);
	animations->Add(100, ani);

	this->AddAnimation(100);
}

void ItemsExHeath::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + IT_HEA_BBOX_WIDTH;
	b = y + IT_HEA_BBOX_HEIGHT;
}

void ItemsExHeath::ReLoad()
{
}


ItemsExHeath::~ItemsExHeath()
{
}

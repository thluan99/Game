#include "ItemApple.h"



ItemApple::ItemApple()
{
}

void ItemApple::Render()
{
	animations[0]->Render(x, y);
}

void ItemApple::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITApple = textures->Get(ID_TEX_ITEM);

	sprites->Add(70000, 341, 17, 11 + 341, 12 + 17, texITApple);
	ani = new CAnimation(100);
	ani->Add(70000);
	animations->Add(100, ani);

	this->AddAnimation(100);
}

void ItemApple::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + IT_APPLE_BBOX_WIDTH;
	b = y + IT_APPLE_BBOX_HEIGHT;
}

void ItemApple::ReLoad()
{
}


ItemApple::~ItemApple()
{
}

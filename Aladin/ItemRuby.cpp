#include "ItemRuby.h"



ItemRuby::ItemRuby()
{
}

void ItemRuby::Render()
{
	animations[0]->RenderAladin(x, y + IT_RUBY_BBOX_HEIGHT, -1);
}

void ItemRuby::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITRuby = textures->Get(ID_TEX_ITEM);

	sprites->Add(70005, 340, 111, 17 + 340, 16 + 111, texITRuby);
	sprites->Add(70006, 363, 111, 17 + 363, 16 + 111, texITRuby);
	sprites->Add(70007, 386, 111, 17 + 386, 16 + 111, texITRuby);
	sprites->Add(70008, 409, 111, 17 + 409, 16 + 111, texITRuby);
	sprites->Add(70009, 432, 110, 17 + 432, 17 + 110, texITRuby);
	sprites->Add(70010, 454, 107, 32 + 454, 21 + 107, texITRuby);
	sprites->Add(70011, 492, 110, 23 + 492, 18 + 110, texITRuby);
	sprites->Add(70012, 522, 112, 17 + 522, 16 + 112, texITRuby);
	sprites->Add(70013, 545, 112, 17 + 545, 16 + 112, texITRuby);
	ani = new CAnimation(100);
	ani->Add(70005);
	ani->Add(70006);
	ani->Add(70007);
	ani->Add(70008);
	ani->Add(70009);
	ani->Add(70010);
	ani->Add(70011);
	ani->Add(70012);
	ani->Add(70013);
	animations->Add(100, ani);

	this->AddAnimation(100);
}

void ItemRuby::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + IT_RUBY_BBOX_WIDTH;
	b = y + IT_RUBY_BBOX_HEIGHT;
}

void ItemRuby::ReLoad()
{
}


ItemRuby::~ItemRuby()
{
}

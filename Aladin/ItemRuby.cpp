#include "ItemRuby.h"



ItemRuby::ItemRuby()
{
	SetState(RUBY_IT_STATE_IDLE);
}

void ItemRuby::Render()
{
	int ani = 0;
	int stt = 0;
	if (state == RUBY_IT_STATE_IDLE)
	{
		ani = RUBY_IT_ANI_IDLE;
		animations[ani]->Render(x, y);
	}
	else if (state == RUBY_IT_STATE_COLLECTED)
	{
		ani = RUBY_IT_ANI_COLLECTED;
		if (isDeath == false)
		{
			animations[ani]->RenderAladin(stt, x, y + IT_RUBY_BBOX_HEIGHT, 1, 255);
			if (stt != 0)
				isDeath = true;
		}
		else
			animations[0]->RenderAladin(x, y, 1, 0);
	}
}

void ItemRuby::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITRuby = textures->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texITCollect = textures->Get(ID_TEX_ITEM_COLLECT);

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

	sprites->Add(9970, 13, 19, 6 + 13, 6 + 19, texITCollect);
	sprites->Add(9971, 55, 13, 10 + 55, 16 + 13, texITCollect);
	sprites->Add(9972, 99, 11, 12 + 99, 18 + 11, texITCollect);
	sprites->Add(9973, 137, 7, 22 + 137, 24 + 7, texITCollect);
	sprites->Add(9974, 177, 5, 34 + 177, 32 + 5, texITCollect);
	sprites->Add(9975, 221, 1, 40 + 221, 38 + 1, texITCollect);
	sprites->Add(9976, 287, 7, 32 + 287, 28 + 7, texITCollect);
	sprites->Add(9977, 327, 11, 34 + 327, 26 + 11, texITCollect);
	sprites->Add(9978, 371, 15, 34 + 371, 22 + 15, texITCollect);
	sprites->Add(9979, 419, 19, 34 + 419, 20 + 19, texITCollect);
	sprites->Add(9980, 463, 25, 12 + 463, 14 + 25, texITCollect);
	ani = new CAnimation(60);
	ani->Add(9970);
	ani->Add(9971);
	ani->Add(9972);
	ani->Add(9973);
	ani->Add(9974);
	ani->Add(9975);
	ani->Add(9976);
	ani->Add(9977);
	ani->Add(9978);
	ani->Add(9979);
	ani->Add(9980);
	animations->Add(101, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
}

void ItemRuby::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state != RUBY_IT_STATE_COLLECTED)
	{
		l = x;
		t = y;
		r = x + IT_RUBY_BBOX_WIDTH;
		b = y + IT_RUBY_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
}

void ItemRuby::ReLoad()
{
}


ItemRuby::~ItemRuby()
{
}

#include "ItemsExHeath.h"



ItemsExHeath::ItemsExHeath()
{
	SetState(HEATH_STATE_IDLE);
}

void ItemsExHeath::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = 0;
}

void ItemsExHeath::Render()
{
	int ani = 0;
	int stt = 0;
	if (state == HEATH_STATE_IDLE)
	{
		ani = HEATH_ANI_IDLE;
		animations[ani]->Render(x, y);
	}
	else if (state == HEATH_STATE_COLLECTED)
	{
		ani = HEATH_ANI_COLLECTED;
		if (isDeath == false)
		{
			animations[ani]->RenderAladin(stt, x, y + IT_HEA_BBOX_HEIGHT, 1, 255);
			if (stt != 0)
				isDeath = true;
		}
		else
			animations[0]->RenderAladin(x, y, 1, 0);
	}
}

void ItemsExHeath::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITHeath = textures->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texITCollect = textures->Get(ID_TEX_ITEM_COLLECT);

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

void ItemsExHeath::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state != HEATH_STATE_COLLECTED)
	{
		l = x;
		t = y;
		r = x + IT_HEA_BBOX_WIDTH;
		b = y + IT_HEA_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
}

void ItemsExHeath::ReLoad()
{
}


ItemsExHeath::~ItemsExHeath()
{
}

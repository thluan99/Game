#include "ItemApple.h"



ItemApple::ItemApple()
{
	SetState(APPLE_IT_IDLE);
}

void ItemApple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = 0;
}

void ItemApple::Render()
{
	int ani = 0;
	int stt = 0;
	if (state == APPLE_IT_IDLE)
	{
		ani = APPLE_IT_ANI_IDLE;
		animations[ani]->Render(x, y);
	}
	else if (state == APPLE_IT_COLLECTED)
	{
		ani = APPLE_IT_ANI_COLLECTED;
		if (isDeath == false)
		{
			animations[ani]->RenderAladin(stt, x, y + IT_APPLE_BBOX_HEIGHT, 1, 255);
			if (stt != 0)
				isDeath = true;
		}
		else
			animations[0]->RenderAladin(x, y, 1, 0);
	}
}

void ItemApple::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITApple = textures->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texITCollect = textures->Get(ID_TEX_ITEM_COLLECT);


	sprites->Add(70000, 341, 17, 11 + 341, 12 + 17, texITApple);
	ani = new CAnimation(100);
	ani->Add(70000);
	animations->Add(10099, ani);

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
	animations->Add(10199, ani);


	this->AddAnimation(10099);
	this->AddAnimation(10199);
}

void ItemApple::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state != APPLE_IT_COLLECTED)
	{
		l = x;
		t = y;
		r = x + IT_APPLE_BBOX_WIDTH;
		b = y + IT_APPLE_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
}

void ItemApple::ReLoad()
{
}


ItemApple::~ItemApple()
{
}

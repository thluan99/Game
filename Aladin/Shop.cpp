#include "Shop.h"



Shop::Shop()
{
}

void Shop::Render()
{
	int ani = 1;
	if (state == SHOP_STATE_IDLE)
		ani = SHOP_ANI_IDLE;
	else if (state == SHOP_STATE_ACTIVE)
		ani = SHOP_ANI_ACTIVE;
	else if (state == SHOP_STATE_IDLE2)
		ani = SHOP_ANI_IDLE2;

	animations[ani]->RenderAladin(x, y, -1);
}

void Shop::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = 0;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
}

void Shop::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITShop = textures->Get(ID_TEX_SHOP);

	sprites->Add(70040, 5, 8, 26 + 5, 52 + 8, texITShop);
	ani = new CAnimation(100);
	ani->Add(70040);
	animations->Add(100, ani);

	sprites->Add(70041, 38, 6, 27 + 38, 54 + 6, texITShop);
	sprites->Add(70042, 73, 5, 28 + 73, 55 + 5, texITShop);
	sprites->Add(70043, 108, 4, 28 + 108, 56 + 4, texITShop);
	sprites->Add(70044, 146, 4, 28 + 146, 56 + 4, texITShop);
	sprites->Add(70045, 183, 4, 28 + 183, 56 + 4, texITShop);
	sprites->Add(70046, 219, 4, 28 + 219, 56 + 4, texITShop);
	sprites->Add(70050, 254, 12, 35 + 254, 48 + 12, texITShop);
	sprites->Add(70051, 295, 14, 50 + 295, 46 + 14, texITShop);
	sprites->Add(70052, 355, 10, 67 + 355, 50 + 10, texITShop);
	sprites->Add(70053, 436, 11, 58 + 436, 50 + 11, texITShop);
	sprites->Add(70054, 505, 10, 52 + 505, 50 + 10, texITShop);
	sprites->Add(70055, 565, 10, 52 + 565, 50 + 10, texITShop);
	sprites->Add(70056, 627, 10, 52 + 627, 50 + 10, texITShop);
	ani = new CAnimation(150);
	ani->Add(70041);
	ani->Add(70042);
	ani->Add(70043);
	ani->Add(70044);
	ani->Add(70045);
	ani->Add(70046);
	ani->Add(70050);
	ani->Add(70051);
	ani->Add(70052);
	ani->Add(70053);
	ani->Add(70054);
	ani->Add(70055);
	ani->Add(70056);
	animations->Add(101, ani);

	sprites->Add(70056, 627, 10, 52 + 627, 50 + 10, texITShop);
	ani = new CAnimation(100);
	ani->Add(70056);
	animations->Add(102, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
	this->AddAnimation(102);
}

void Shop::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + IT_SHOP_BBOX_WIDTH;	
	b = y + IT_SHOP_BBOX_HEIGHT;
}

void Shop::ReLoad()
{
}


Shop::~Shop()
{
}

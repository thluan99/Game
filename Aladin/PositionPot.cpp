#include "PositionPot.h"



PositionPot::PositionPot()
{
}

void PositionPot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void PositionPot::Render()
{
	int ani = 1;
	if (state == POT_STATE_IDLE)
		ani = POT_ANI_IDLE;
	else if (state == POT_STATE_ACTIVE)
		ani = POT_ANI_ACTIVE;

	animations[ani]->RenderAladin(x, y + IT_POT_BBOX_HEIGHT, 1);
}

void PositionPot::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	this->id = ID;

	LPDIRECT3DTEXTURE9 texITPot = textures->Get(ID_TEX_ITEM);

	sprites->Add(70034, 19, 424, 20 + 19, 33 + 424, texITPot);
	ani = new CAnimation(100);
	ani->Add(70034);
	animations->Add(100, ani);

	sprites->Add(70025, 49, 428, 24 + 49, 29 + 428, texITPot);
	sprites->Add(70026, 78, 437, 34 + 78, 20 + 437, texITPot);
	sprites->Add(70027, 119, 425, 20 + 119, 34 + 425, texITPot);
	sprites->Add(70028, 145, 425, 23 + 145, 34 + 425, texITPot);
	sprites->Add(70029, 174, 426, 26 + 174, 33 + 426, texITPot);
	sprites->Add(70030, 207, 426, 24 + 207, 34 + 426, texITPot);
	sprites->Add(70031, 239, 427, 20 + 239, 34 + 427, texITPot);
	sprites->Add(70032, 270, 428, 24 + 270, 33 + 428, texITPot);
	sprites->Add(70033, 302, 429, 23 + 302, 33 + 429, texITPot);
	ani = new CAnimation(100);
	ani->Add(70034);
	ani->Add(70025);
	ani->Add(70026);
	ani->Add(70027);
	ani->Add(70028);
	ani->Add(70029);
	ani->Add(70030);
	ani->Add(70031);
	ani->Add(70032);
	ani->Add(70033);
	animations->Add(101, ani);

	ani = new CAnimation(100);
	ani->Add(70033);
	animations->Add(102, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
	this->AddAnimation(102);
}

void PositionPot::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + IT_POT_BBOX_WIDTH;	
	b = y + IT_POT_BBOX_HEIGHT;
}

void PositionPot::ReLoad()
{
}


PositionPot::~PositionPot()
{
}

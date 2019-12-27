#include "Sword.h"



Sword::Sword()
{

}

void Sword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	if (direction == 1)
		vx = 0.2f;
	else vx = -0.2f;
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (e->obj->GetId() != ENEMY1 && e->obj->GetId() != ENEMY2 && e->obj->GetId() != ENEMY3 && e->obj->GetId() != BAT)
			{
				x = e->t*dx;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Sword::Render()
{
	animations[0]->Render(x, y);
}

void Sword::SetState(int state)
{
	CGameObject::SetState(state);
}

void Sword::LoadResources(int ID)
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

void Sword::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + 10;
	b = y + ALADIN_BIG_BBOX_HEIGHT + 20;
}

void Sword::ReLoad()
{
}


Sword::~Sword()
{
}

#include  "Apple.h"
#include "Aladin.h"
#include "debug.h"

void Apple::Render()
{
	int ani;

	int alpha = 255;
	if (state == APPLE_STATE_DIE)
		ani = APPLE_ANI_DIE;
	else
	{
		ani = APPLE_ANI_IDLE;
	}
	animations[ani]->Render(x, y, 255);
}

float Apple::Calcu_Y_Apple(float vy)
{

	return vy + 0.01f;

}


void Apple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == APPLE_STATE_IDLE)
	{
		//vy = 0.1;
		vy = Calcu_Y_Apple(vy);

		if (direction == 1)
			vx = 0.4f;
		else
			vx = -0.4f;
		x += (vx*dt);
		y += (vy*dt);
	}
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//if (state != _STATE_DIE)
	//{
	//	CalcPotentialCollisions(coObjects, coEvents);
	//	//delete this;
	//}

	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	//	// block 
	//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty * dy + ny * 0.4f;

	//	if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;
	//	state = APPLE_STATE_DIE;
	//}

	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Apple::SetState(int state)
{
	CGameObject::SetState(state);
}
void Apple::LoadResources(int ID)
{
	//textures = CTextures::GetInstance();
	//sprites = CSprites::GetInstance();
	//textures->Add(ID_TEX_APPLE, L"textures\\aladin.png", D3DCOLOR_XRGB(255, 0, 0));
	//CAnimations *animations = CAnimations::GetInstance();

	//LPDIRECT3DTEXTURE9 textAPPLE = textures->Get(ID_TEX_APPLE);
	//// idle
	//LPANIMATION ani;
	//sprites->Add(200, 373, 24, 373 + 7, 24 + 7, textAPPLE);
	//ani = new CAnimation(100);
	//ani->Add(200);
	//animations->Add(999, ani);
	//// die
	//sprites->Add(201, 394, 23, 394 + 7, 23 + 10, textAPPLE);
	//sprites->Add(202, 414, 18, 414 + 20, 18 + 18, textAPPLE);
	//sprites->Add(203, 444, 16, 444 + 29, 16 + 22, textAPPLE);
	//sprites->Add(204, 485, 14, 485 + 31, 14 + 25, textAPPLE);
	//sprites->Add(205, 532, 13, 532 + 30, 13 + 27, textAPPLE);
	//ani = new CAnimation(100);
	//ani->Add(201);
	//ani->Add(202);
	//ani->Add(203);
	//ani->Add(204);
	//ani->Add(205);
	//animations->Add(998, ani);

	this->AddAnimation(999);
	this->AddAnimation(998);

}
void Apple::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + APPLE_BBOX_WIDTH;
	b = y + APPLE_BBOX_HEIGHT;
}

void Apple::SetPosition(float x, float y)
{
	this->staticX = x;
	this->x = x;
	this->y = y;
}

void Apple::ReLoad()
{
}
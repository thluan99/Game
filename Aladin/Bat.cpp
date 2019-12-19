#include "Bat.h"

void Bat::Render()
{
	int ani = 0;
	int alpha = 255;

	animations[2]->Render(x, y, alpha);
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// caculate dx, dx
	CGameObject::Update(dt);

	activeRange.CalculateActiveRange(this);
	// fall down
	vy += GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != BAT_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Bat::SetState(int state)
{
	CGameObject::SetState(state);
}

void Bat::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_BAT, L"textures\\bat.png", D3DCOLOR_XRGB(255, 0, 255));

	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textEBat = textures->Get(ID_TEX_BAT);

	LPANIMATION ani;
	//----------IDLE------------//
	sprites->Add(47000, 9, 18, 7 + 9, 16 + 18, textEBat);
	ani = new CAnimation(100);
	ani->Add(47000);
	animations->Add(100, ani);

	//----------WAKEUP------------//
	sprites->Add(47001, 20, 10, 21 + 20, 22 + 10, textEBat);
	sprites->Add(47002, 48, 13, 19 + 48, 23 + 13, textEBat);
	sprites->Add(47003, 76, 18, 21 + 76, 14 + 18, textEBat);
	ani = new CAnimation(100);
	ani->Add(47000);
	ani->Add(47001);
	ani->Add(47002);
	ani->Add(47003);
	animations->Add(200, ani);
	//----------FLY------------//
	sprites->Add(47011, 10, 60, 24 + 10, 15 + 60, textEBat);
	sprites->Add(47012, 39, 52, 13 + 39, 23 + 52, textEBat);
	sprites->Add(47013, 56, 58, 30 + 56, 17 + 58, textEBat);
	sprites->Add(47014, 89, 67, 32 + 89, 16 + 67, textEBat);
	sprites->Add(47015, 128, 67, 8 + 128, 25 + 67, textEBat);
	sprites->Add(47016, 143, 67, 20 + 143, 16 + 67, textEBat);
	sprites->Add(47017, 165, 61, 34 + 165, 14 + 61, textEBat);
	ani = new CAnimation(100);
	ani->Add(47011);
	ani->Add(47012);
	ani->Add(47013);
	ani->Add(47014);
	ani->Add(47015);
	ani->Add(47016);
	ani->Add(47017);
	animations->Add(300, ani);

	//----------RE_FLY_ing------------//
	sprites->Add(47021, 10, 119, 13 + 10, 13 + 119, textEBat);
	sprites->Add(47022, 38, 111, 51 + 38, 28 + 111, textEBat);
	sprites->Add(47023, 93, 113, 22 + 93, 23 + 113, textEBat);
	ani = new CAnimation(100);
	ani->Add(47021);
	ani->Add(47022);
	ani->Add(47023);
	animations->Add(400, ani);

	//----------FLY_ing------------//
	sprites->Add(47031, 128, 102, 20 + 128, 14 + 35 + 102, textEBat);
	sprites->Add(47032, 160, 106, 26 + 160, 12 + 36 + 106, textEBat);
	sprites->Add(47033, 199, 106, 29 + 199, 53 + 106, textEBat);
	sprites->Add(47034, 233, 105, 25 + 233, 10 + 32 + 105, textEBat);
	sprites->Add(47035, 275, 106, 23 + 275, 51 + 106, textEBat);
	sprites->Add(47036, 316, 106, 23 + 316, 51 + 106, textEBat);
	ani = new CAnimation(100);
	ani->Add(47031);
	ani->Add(47032);
	ani->Add(47033);
	ani->Add(47034);
	ani->Add(47035);
	ani->Add(47036);
	animations->Add(450, ani);

	this->AddAnimation(100);
	this->AddAnimation(200);
	this->AddAnimation(300);
	this->AddAnimation(400);
	this->AddAnimation(450);
}

void Bat::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BAT_BBOX_WIDTH;
	b = y + BAT_BBOX_HEIGHT;
}

void Bat::ReLoad()
{
}

#include "Enemy2.h"

void Enemy2::Render()
{
	int ani = 0;
	int alpha = 255;

	animations[1]->RenderAladin(x, y + ENEMY_BBOX_HEIGHT, direction, alpha);
}

void Enemy2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// caculate dx, dx
	CGameObject::Update(dt);
	// fall down
	vy = 0;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ENEMY2_STATE_DIE)
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

void Enemy2::SetState(int state)
{
	CGameObject::SetState(state);
}

void Enemy2::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_ENEMY2, L"textures\\enemy2.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMY2_FLIP, L"textures\\enemy2_flip.png", D3DCOLOR_XRGB(255, 0, 255));

	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textE2 = textures->Get(ID_TEX_ENEMY2);
	LPDIRECT3DTEXTURE9 textE2_f = textures->Get(ID_TEX_ENEMY2_FLIP);

	LPANIMATION ani;
	//----------IDLE LEFT ------------//
	sprites->Add(46051, 774, 73, 86 + 774, 26 + 73, textE2_f);
	sprites->Add(46052, 687, 68, 80 + 687, 29 + 68, textE2_f);
	sprites->Add(46053, 605, 52, 75 + 605, 45 + 52, textE2_f);
	sprites->Add(46054, 523, 37, 62 + 523, 60 + 37, textE2_f);
	sprites->Add(46055, 453, 29, 50 + 453, 67 + 29, textE2_f);
	sprites->Add(46056, 393, 25, 48 + 393, 71 + 25, textE2_f);
	sprites->Add(46057, 334, 22, 48 + 334, 75 + 22, textE2_f);
	sprites->Add(46058, 273, 16, 51 + 273, 81 + 16, textE2_f);
	sprites->Add(46059, 216, 16, 51 + 216, 81 + 16, textE2_f);
	sprites->Add(46060, 154, 16, 52 + 154, 81 + 16, textE2_f);
	sprites->Add(46061, 74, 16, 68 + 74, 81 + 16, textE2_f);
	sprites->Add(46062, 4, 8, 65 + 4, 89 + 8, textE2_f);
	sprites->Add(46063, 805, 122, 50 + 805, 82 + 122, textE2_f);
	sprites->Add(46064, 744, 123, 49 + 744, 81 + 123, textE2_f);
	sprites->Add(46065, 675, 121, 61 + 675, 84 + 121, textE2_f);
	sprites->Add(46066, 601, 130, 64 + 601, 75 + 130, textE2_f);
	sprites->Add(46067, 515, 121, 74 + 515, 85 + 121, textE2_f);
	sprites->Add(46068, 411, 115, 81 + 411, 91 + 115, textE2_f);
	sprites->Add(46069, 294, 126, 95 + 294, 77 + 126, textE2_f);
	sprites->Add(46070, 215, 125, 60 + 215, 79 + 125, textE2_f);
	ani = new CAnimation(150);
	ani->Add(46051);
	ani->Add(46052);
	ani->Add(46053);
	ani->Add(46054);
	ani->Add(46055);
	ani->Add(46056);
	ani->Add(46057);
	ani->Add(46058);
	ani->Add(46059);
	ani->Add(46060);
	ani->Add(46061);
	ani->Add(46062);
	ani->Add(46063);
	ani->Add(46064);
	ani->Add(46065);
	ani->Add(46066);
	ani->Add(46067);
	ani->Add(46068);
	ani->Add(46069);
	ani->Add(46070);
	animations->Add(101, ani);
	//----------IDLE Right ------------//
	sprites->Add(46001, 8, 73, 86 + 8, 26 + 73, textE2);
	sprites->Add(46002, 101, 68, 80 + 101, 29 + 68, textE2);
	sprites->Add(46003, 188, 52, 75 + 188, 45 + 52, textE2);
	sprites->Add(46004, 283, 37, 62 + 283, 60 + 37, textE2);
	sprites->Add(46005, 365, 29, 50 + 365, 67 + 29, textE2);
	sprites->Add(46006, 427, 25, 48 + 427, 71 + 25, textE2);
	sprites->Add(46007, 486, 22, 48 + 486, 75 + 22, textE2);
	sprites->Add(46008, 544, 16, 51 + 544, 81 + 16, textE2);
	sprites->Add(46009, 601, 16, 51 + 601, 81 + 16, textE2);
	sprites->Add(46010, 662, 16, 52 + 662, 81 + 16, textE2);
	sprites->Add(46011, 726, 16, 68 + 726, 81 + 16, textE2);
	sprites->Add(46012, 799, 8, 65 + 799, 89 + 8, textE2);
	sprites->Add(46013, 13, 122, 50 + 13, 82 + 122, textE2);
	sprites->Add(46014, 75, 123, 49 + 75, 81 + 123, textE2);
	sprites->Add(46015, 132, 121, 61 + 132, 84 + 121, textE2);
	sprites->Add(46016, 203, 130, 64 + 203, 75 + 130, textE2);
	sprites->Add(46017, 279, 121, 74 + 279, 85 + 121, textE2);
	sprites->Add(46018, 376, 115, 81 + 376, 91 + 115, textE2);
	sprites->Add(46019, 479, 126, 95 + 479, 77 + 126, textE2);
	sprites->Add(46020, 593, 125, 60 + 593, 79 + 125, textE2);
	ani = new CAnimation(150);
	ani->Add(46001);
	ani->Add(46002);
	ani->Add(46003);
	ani->Add(46004);
	ani->Add(46005);
	ani->Add(46006);
	ani->Add(46007);
	ani->Add(46008);
	ani->Add(46009);
	ani->Add(46010);
	ani->Add(46011);
	ani->Add(46012);
	ani->Add(46013);
	ani->Add(46014);
	ani->Add(46015);
	ani->Add(46016);
	ani->Add(46017);
	ani->Add(46018);
	ani->Add(46019);
	ani->Add(46020);
	animations->Add(100, ani);

	this->AddAnimation(100);		// 0 idle
	this->AddAnimation(101);
}

void Enemy2::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + ENEMY_BBOX_WIDTH;
	b = y + ENEMY_BBOX_HEIGHT;
}

void Enemy2::ReLoad()
{
}

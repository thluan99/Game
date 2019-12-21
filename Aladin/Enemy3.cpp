#include "Enemy3.h"

void Enemy3::Render()
{
	int ani = 0;
	int alpha = 255;

	if (state == ENEMY3_STATE_ATTACK_LEFT)
		ani = ENEMY3_ANI_ATTACK_LEFT;
	else if (state == ENEMY3_STATE_ATTACK_RIGHT)
		ani = ENEMY3_ANI_ATTACK_RIGHT;
	else if (state == ENEMY3_STATE_IDLE_RIGHT)
		ani = ENEMY3_ANI_IDLE_RIGHT;
	else if (state == ENEMY3_STATE_IDLE_LEFT)
		ani = ENEMY3_ANI_IDLE_LEFT;
	else if (state == ENEMY3_STATE_RUN_LEFT)
		ani = ENEMY3_ANI_RUN_LEFT;
	else if (state == ENEMY3_STATE_RUN_RIGHT)
		ani = ENEMY3_ANI_RUN_RIGHT;
	else if (state == ENEMY3_STATE_HIT_LEFT)
		ani = ENEMY3_ANI_HIT_LEFT;
	else if (state == ENEMY3_STATE_HIT_RIGHT)
		ani = ENEMY3_ANI_HIT_RIGHT;

	animations[3]->RenderAladin(x, y + ENEMY_BBOX_HEIGHT, direction, alpha);
}

void Enemy3::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// caculate dx, dx
	CGameObject::Update(dt);
	// fall down
	vy = 0;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ENEMY3_STATE_DIE)
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
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Enemy3::SetState(int state)
{
	CGameObject::SetState(state);
}

void Enemy3::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_ENEMY3, L"textures\\enemy1.png", D3DCOLOR_XRGB(120, 193, 152));
	textures->Add(ID_TEX_ENEMY3_FLIP, L"textures\\enemy1_flip.png", D3DCOLOR_XRGB(120, 193, 152));

	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textE3 = textures->Get(ID_TEX_ENEMY3);
	LPDIRECT3DTEXTURE9 textE3_f = textures->Get(ID_TEX_ENEMY3_FLIP);

	LPANIMATION ani;
	//----------IDLE LEFT ------------//
	sprites->Add(50000, 8, 175, 44 + 8, 58 + 175, textE3);
	ani = new CAnimation(100);
	ani->Add(50000);
	animations->Add(100, ani);
	//----------IDLE RIGHT ------------//
	sprites->Add(59999, 444, 175, 44 + 444, 58 + 175, textE3_f);
	ani = new CAnimation(100);
	ani->Add(59999);
	animations->Add(999, ani);

	//----------RUN LEFT ------------//
	sprites->Add(50001, 2, 9, 45 + 2, 67 + 9, textE3);
	sprites->Add(50002, 53, 10, 45 + 53, 66 + 10, textE3);
	sprites->Add(50003, 109, 11, 46 + 109, 65 + 11, textE3);
	sprites->Add(50004, 164, 11, 45 + 164, 65 + 11, textE3);
	sprites->Add(50005, 214, 10, 37 + 214, 66 + 10, textE3);
	sprites->Add(50006, 259, 9, 43 + 259, 67 + 9, textE3);
	sprites->Add(50007, 308, 9, 50 + 308, 67 + 9, textE3);
	sprites->Add(50008, 363, 11, 36 + 363, 65 + 11, textE3);
	ani = new CAnimation(100);
	ani->Add(50001);
	ani->Add(50002);
	ani->Add(50003);
	ani->Add(50004);
	ani->Add(50005);
	ani->Add(50006);
	ani->Add(50007);
	ani->Add(50008);
	animations->Add(200, ani);
	//----------RUN RIGHT ------------//
	sprites->Add(50051, 449, 9, 45 + 449, 67 + 9, textE3_f);
	sprites->Add(50052, 398, 10, 45 + 398, 66 + 10, textE3_f);
	sprites->Add(50053, 341, 11, 46 + 341, 65 + 11, textE3_f);
	sprites->Add(50054, 287, 11, 45 + 287, 65 + 11, textE3_f);
	sprites->Add(50055, 245, 10, 37 + 245, 66 + 10, textE3_f);
	sprites->Add(50056, 194, 9, 43 + 194, 67 + 9, textE3_f);
	sprites->Add(50057, 138, 9, 50 + 138, 67 + 9, textE3_f);
	sprites->Add(50058, 97, 11, 36 + 97, 65 + 11, textE3_f);
	ani = new CAnimation(100);
	ani->Add(50051);
	ani->Add(50052);
	ani->Add(50053);
	ani->Add(50054);
	ani->Add(50055);
	ani->Add(50056);
	ani->Add(50057);
	ani->Add(50058);
	animations->Add(201, ani);

	//----------ATTACK LEFT ------------//
	sprites->Add(51001, 9, 82, 37 + 9, 74 + 82, textE3);
	sprites->Add(51002, 53, 96, 49 + 53, 60 + 96, textE3);
	sprites->Add(51003, 109, 98, 92 + 109, 58 + 98, textE3);
	sprites->Add(51004, 203, 97, 86 + 203, 59 + 97, textE3);
	sprites->Add(51005, 292, 96, 77 + 292, 60 + 96, textE3);
	sprites->Add(51006, 382, 96, 41 + 382, 60 + 96, textE3);
	ani = new CAnimation(100);
	ani->Add(51001);
	ani->Add(51002);
	ani->Add(51003);
	ani->Add(51004);
	ani->Add(51005);
	ani->Add(51006);
	animations->Add(300, ani);
	//----------ATTACK RIGHT ------------//
	sprites->Add(51051, 450, 82, 37 + 450, 74 + 82, textE3_f);
	sprites->Add(51052, 394, 96, 49 + 394, 60 + 96, textE3_f);
	sprites->Add(51053, 295, 98, 92 + 295, 58 + 98, textE3_f);
	sprites->Add(51054, 207, 97, 86 + 207, 59 + 97, textE3_f);
	sprites->Add(51055, 127, 96, 77 + 127, 60 + 96, textE3_f);
	sprites->Add(51056, 73, 96, 41 + 73, 60 + 96, textE3_f);
	ani = new CAnimation(100);
	ani->Add(51051);
	ani->Add(51052);
	ani->Add(51053);
	ani->Add(51054);
	ani->Add(51055);
	ani->Add(51056);
	animations->Add(301, ani);

	//----------HIT LEFT ------------//
	sprites->Add(52001, 59, 185, 40 + 59, 48 + 185, textE3);
	sprites->Add(52002, 114, 160, 39 + 114, 73 + 160, textE3);
	sprites->Add(52003, 161, 165, 41 + 161, 68 + 165, textE3);
	sprites->Add(52004, 210, 171, 46 + 210, 62 + 171, textE3);
	sprites->Add(52005, 268, 162, 42 + 268, 71 + 162, textE3);
	sprites->Add(52006, 318, 184, 47 + 318, 49 + 184, textE3);
	sprites->Add(52007, 378, 185, 40 + 378, 48 + 185, textE3);
	sprites->Add(52008, 433, 166, 45 + 433, 67 + 166, textE3);
	ani = new CAnimation(100);
	ani->Add(52001);
	ani->Add(52002);
	ani->Add(52003);
	ani->Add(52004);
	ani->Add(52005);
	ani->Add(52006);
	ani->Add(52007);
	ani->Add(52008);
	animations->Add(400, ani);
	//----------HIT RIGHT ------------//
	sprites->Add(52051, 397, 185, 40 + 397, 48 + 185, textE3_f);
	sprites->Add(52052, 343, 160, 39 + 343, 73 + 160, textE3_f);
	sprites->Add(52053, 294, 165, 41 + 294, 68 + 165, textE3_f);
	sprites->Add(52054, 240, 171, 46 + 240, 62 + 171, textE3_f);
	sprites->Add(52055, 186, 162, 42 + 186, 71 + 162, textE3_f);
	sprites->Add(52056, 131, 184, 47 + 131, 49 + 184, textE3_f);
	sprites->Add(52057, 78, 185, 40 + 78, 48 + 185, textE3_f);
	sprites->Add(52058, 18, 166, 45 + 18, 67 + 166, textE3_f);
	ani = new CAnimation(100);
	ani->Add(52051);
	ani->Add(52052);
	ani->Add(52053);
	ani->Add(52054);
	ani->Add(52055);
	ani->Add(52056);
	ani->Add(52057);
	ani->Add(52058);
	animations->Add(401, ani);

	this->AddAnimation(100);		// 0 idle
	this->AddAnimation(101);		// 1 idle right
	this->AddAnimation(200);		// 2 run
	this->AddAnimation(201);		// 3 run right
	this->AddAnimation(300);		// 4 attack
	this->AddAnimation(301);		// 5 attack right
	this->AddAnimation(400);		// 6 hit
	this->AddAnimation(401);		// 7 hit right
}

void Enemy3::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + ENEMY_BBOX_WIDTH;
	b = y + ENEMY_BBOX_HEIGHT;
}

void Enemy3::ReLoad()
{
}

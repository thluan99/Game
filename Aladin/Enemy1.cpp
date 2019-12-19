#include "Enemy1.h"

void Enemy1::Render()
{
	int ani;
	int alpha = 255;
	if (state == ENEMY1_STATE_IDLE_LEFT)
		ani = ENEMY1_ANI_IDLE_LEFT;
	else if (state == ENEMY1_STATE_RUN_LEFT)
		ani = ENEMY1_ANI_RUN_LEFT;
	else if (state == ENEMY1_STATE_ATTACK_LEFT_MID)
		ani = ENEMY1_ANI_ATTACK_LEFT_MID;
	else if (state == ENEMY1_STATE_ATTACK_LEFT)
		ani = ENEMY1_ANI_ATTACK_LEFT;
	else if (state == ENEMY1_STATE_HIT_LEFT)
		ani = ENEMY1_ANI_HIT_LEFT;
	else if (state == ENEMY1_STATE_IDLE_RIGHT)
		ani = ENEMY1_ANI_IDLE_RIGHT;
	else if (state == ENEMY1_STATE_RUN_RIGHT)
		ani = ENEMY1_ANI_RUN_RIGHT;
	else if (state == ENEMY1_STATE_ATTACK_RIGHT_MID)
		ani = ENEMY1_ANI_ATTACK_RIGHT_MID;
	else if (state == ENEMY1_STATE_ATTACK_RIGHT)
		ani = ENEMY1_ANI_ATTACK_RIGHT;
	else if (state == ENEMY1_STATE_HIT_RIGHT)
		ani = ENEMY1_ANI_HIT_RIGHT;

	animations[ani]->RenderAladin(x, y + ENEMY_BBOX_HEIGHT, direction, alpha);
}

void Enemy1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// caculate dx, dx
	CGameObject::Update(dt);
	// fall down
	vy += GRAVITY * dt;
	activeRange.CalculateActiveRange(this);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ENEMY1_STATE_DIE)
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

void Enemy1::SetState(int state)
{
	CGameObject::SetState(state);
	vx = 0;
	switch (state)
	{
	case ENEMY1_STATE_IDLE_LEFT:
		nx = -1;
		break;
	case ENEMY1_STATE_IDLE_RIGHT:
		nx = 1;
		break;
	case ENEMY1_STATE_HIT_LEFT:
		nx = -1;
		break;
	case ENEMY1_STATE_HIT_RIGHT:
		nx = 1;
		break;
	case ENEMY1_STATE_ATTACK_LEFT:
		nx = -1;
		break;
	case ENEMY1_STATE_ATTACK_RIGHT:
		nx = 1;
		break;
	case ENEMY1_STATE_ATTACK_LEFT_MID:
		nx = -1;
		break;
	case ENEMY1_STATE_ATTACK_RIGHT_MID:
		nx = 1;
		break;
	case ENEMY1_STATE_RUN_LEFT:
		nx = -1;
		break;
	case ENEMY1_STATE_RUN_RIGHT:
		nx = 1;
		break;
	}
}

void Enemy1::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_ENEMY1, L"textures\\enemy1.png", D3DCOLOR_XRGB(120, 193, 152));
	textures->Add(ID_TEX_ENEMY1_FLIP, L"textures\\enemy1_flip.png", D3DCOLOR_XRGB(120, 193, 152));

	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textE1 = textures->Get(ID_TEX_ENEMY1);
	LPDIRECT3DTEXTURE9 textE1_f = textures->Get(ID_TEX_ENEMY1_FLIP);

	LPANIMATION ani;
	//----------IDLE LEFT ------------//
	sprites->Add(40001, 3, 449, 44 + 3, 53 + 449, textE1);
	sprites->Add(40002, 56, 448, 37 + 56, 54 + 448, textE1);
	sprites->Add(40003, 98, 449, 54 + 98, 53 + 449, textE1);
	sprites->Add(40004, 157, 449, 58 + 157, 53 + 449, textE1);
	sprites->Add(40005, 221, 449, 49 + 221, 53 + 449, textE1);
	sprites->Add(40006, 278, 449, 44 + 278, 53 + 449, textE1);
	ani = new CAnimation(100);
	ani->Add(40001);
	ani->Add(40002);
	ani->Add(40003);
	ani->Add(40004);
	ani->Add(40005);
	ani->Add(40006);
	animations->Add(100, ani);

	//----------IDLE RIGHT ------------//
	sprites->Add(40051, 447, 449, 44 + 447, 53 + 449, textE1_f);
	sprites->Add(40052, 403, 448, 37 + 403, 54 + 448, textE1_f);
	sprites->Add(40053, 344, 449, 54 + 344, 53 + 449, textE1_f);
	sprites->Add(40054, 281, 449, 58 + 281, 53 + 449, textE1_f);
	sprites->Add(40055, 226, 449, 49 + 226, 53 + 449, textE1_f);
	sprites->Add(40056, 174, 449, 44 + 174, 53 + 449, textE1_f);
	ani = new CAnimation(100);
	ani->Add(40051);
	ani->Add(40052);
	ani->Add(40053);
	ani->Add(40054);
	ani->Add(40055);
	ani->Add(40056);
	animations->Add(101, ani);

	//----------RUN LEFT--------------//
	sprites->Add(41001, 2, 320, 47 + 2, 52 + 320, textE1);
	sprites->Add(41002, 55, 318, 52 + 55, 54 + 318, textE1);
	sprites->Add(41003, 111, 317, 56 + 111, 55 + 317, textE1);
	sprites->Add(41004, 173, 318, 51 + 173, 54 + 318, textE1);
	sprites->Add(41005, 230, 320, 49 + 230, 52 + 320, textE1);
	sprites->Add(41006, 284, 319, 42 + 284, 53 + 319, textE1);
	sprites->Add(41007, 334, 316, 44 + 334, 56 + 316, textE1);
	sprites->Add(41008, 382, 318, 47 + 382, 54 + 318, textE1);
	ani = new CAnimation(100);
	ani->Add(41001);
	ani->Add(41002);
	ani->Add(41003);
	ani->Add(41004);
	ani->Add(41005);
	ani->Add(41006);
	ani->Add(41007);
	ani->Add(41008);
	animations->Add(200, ani);

	//----------RUN RIGHT--------------//
	sprites->Add(41051, 447, 320, 47 + 447, 52 + 320, textE1_f);
	sprites->Add(41052, 389, 318, 52 + 389, 54 + 318, textE1_f);
	sprites->Add(41053, 329, 317, 56 + 329, 55 + 317, textE1_f);
	sprites->Add(41054, 272, 318, 51 + 272, 54 + 318, textE1_f);
	sprites->Add(41055, 217, 320, 49 + 217, 52 + 320, textE1_f);
	sprites->Add(41056, 170, 319, 42 + 170, 53 + 319, textE1_f);
	sprites->Add(41057, 118, 316, 44 + 118, 56 + 316, textE1_f);
	sprites->Add(41058, 67, 318, 47 + 67, 54 + 318, textE1_f);
	ani = new CAnimation(100);
	ani->Add(41051);
	ani->Add(41052);
	ani->Add(41053);
	ani->Add(41054);
	ani->Add(41055);
	ani->Add(41056);
	ani->Add(41057);
	ani->Add(41058);
	animations->Add(201, ani);

	//---------------ATTACK-MID-LEFT------------//
	sprites->Add(42001, 6, 573, 55 + 6, 52 + 573, textE1);
	sprites->Add(42002, 65, 581, 67 + 65, 44 + 581, textE1);
	sprites->Add(42003, 140, 583, 70 + 140, 42 + 583, textE1);
	sprites->Add(42004, 216, 582, 75 + 216, 43 + 582, textE1);
	sprites->Add(42005, 297, 580, 88 + 297, 45 + 580, textE1);
	sprites->Add(42006, 395, 579, 95 + 395, 46 + 579, textE1);
	ani = new CAnimation(100);
	ani->Add(42001);
	ani->Add(42002);
	ani->Add(42003);
	ani->Add(42004);
	ani->Add(42005);
	ani->Add(42006);
	animations->Add(300, ani);

	//---------------ATTACK-MID-RIGHT------------//
	sprites->Add(42051, 435, 573, 55 + 435, 52 + 573, textE1_f);
	sprites->Add(42052, 361, 581, 67 + 361, 44 + 581, textE1_f);
	sprites->Add(42053, 286, 583, 70 + 286, 42 + 583, textE1_f);
	sprites->Add(42054, 205, 582, 75 + 205, 43 + 582, textE1_f);
	sprites->Add(42055, 111, 580, 88 + 111, 45 + 580, textE1_f);
	sprites->Add(42056, 6, 579, 95 + 6, 46 + 579, textE1_f);
	ani = new CAnimation(100);
	ani->Add(42051);
	ani->Add(42052);
	ani->Add(42053);
	ani->Add(42054);
	ani->Add(42055);
	ani->Add(42056);
	animations->Add(301, ani);

	//---------------ATTACK-LEFT------------//
	sprites->Add(43001, 6, 642, 43 + 6, 60 + 642, textE1);
	sprites->Add(43002, 61, 629, 43 + 61, 73 + 629, textE1);
	sprites->Add(43003, 116, 636, 52 + 116, 66 + 636, textE1);
	sprites->Add(43004, 178, 646, 114 + 178, 56 + 646, textE1);
	sprites->Add(43005, 296, 629, 94 + 296, 73 + 629, textE1);
	ani = new CAnimation(100);
	ani->Add(43001);
	ani->Add(43002);
	ani->Add(43003);
	ani->Add(43004);
	ani->Add(43005);
	animations->Add(400, ani);

	//---------------ATTACK-RIGHT------------//
	sprites->Add(43051, 447, 642, 43 + 447, 60 + 642, textE1_f);
	sprites->Add(43052, 392, 629, 43 + 392, 73 + 629, textE1_f);
	sprites->Add(43053, 328, 636, 52 + 328, 66 + 636, textE1_f);
	sprites->Add(43054, 204, 646, 114 + 204, 56 + 646, textE1_f);
	sprites->Add(43055, 105, 629, 94 + 105, 73 + 629, textE1_f);
	ani = new CAnimation(100);
	ani->Add(43051);
	ani->Add(43052);
	ani->Add(43053);
	ani->Add(43054);
	ani->Add(43055);
	animations->Add(401, ani);

	//--------------HIT_LEFT-----------------//
	sprites->Add(44001, 6, 812, 54 + 6, 48 + 812, textE1);
	sprites->Add(44002, 71, 789, 63 + 71, 71 + 789, textE1);
	sprites->Add(44003, 138, 803, 65 + 138, 57 + 803, textE1);
	sprites->Add(44004, 210, 794, 71 + 210, 66 + 794, textE1);
	sprites->Add(44005, 290, 796, 74 + 290, 64 + 796, textE1);
	sprites->Add(44006, 382, 804, 66 + 382, 56 + 804, textE1);
	ani = new CAnimation(100);
	ani->Add(44001);
	ani->Add(44002);
	ani->Add(44003);
	ani->Add(44004);
	ani->Add(44005);
	ani->Add(44006);
	animations->Add(500, ani);
	//--------------HIT_LEFT-----------------//
	sprites->Add(44051, 436, 812, 54 + 436, 48 + 812, textE1_f);
	sprites->Add(44052, 362, 789, 63 + 362, 71 + 789, textE1_f);
	sprites->Add(44053, 293, 803, 65 + 293, 57 + 803, textE1_f);
	sprites->Add(44054, 215, 794, 71 + 215, 66 + 794, textE1_f);
	sprites->Add(44055, 132, 796, 74 + 132, 64 + 796, textE1_f);
	sprites->Add(44056, 48, 804, 66 + 48, 56 + 804, textE1_f);
	ani = new CAnimation(100);
	ani->Add(44051);
	ani->Add(44052);
	ani->Add(44053);
	ani->Add(44054);
	ani->Add(44055);
	ani->Add(44056);
	animations->Add(501, ani);

	this->AddAnimation(100);			// 0 idle left
	this->AddAnimation(101);			// 1 idle right
	this->AddAnimation(200);			// 2 run left
	this->AddAnimation(201);			// 3 run right
	this->AddAnimation(300);			// 4 attack mid left
	this->AddAnimation(301);			// 5 attack mid right
	this->AddAnimation(400);			// 6 attack left
	this->AddAnimation(401);			// 7 attack right
	this->AddAnimation(500);			// 8 hit left
	this->AddAnimation(501);			// 9 hit right
}

void Enemy1::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (direction == 1)
	{
		left = x;
		top = y;
		right = x + ALADIN_BIG_BBOX_WIDTH;
		bottom = y + ALADIN_BIG_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x + ALADIN_BIG_BBOX_WIDTH;
		bottom = y + ALADIN_BIG_BBOX_HEIGHT;
	}
}

void Enemy1::ReLoad()
{
}

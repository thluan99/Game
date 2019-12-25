#include "Bone.h"

void Bone::Render()
{
	animations[0]->Render(x, y);
}

float Bone::Random(int a, int b)
{
	return rand() % b + a;
}


void Bone::CalculateVeloc()
{
	vx = (Random(-30.0f, 30.0f) / 100) * (rand() & 1 ? 1 : -1);
	vy = Random(-30, -10.0f) / 100;
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	x += dx;
	y += dy;

	vy += 0.01f;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
		{
			e->obj->HP -= 2;
			DebugOut(L"HP ---\n");
		}
		else
			delete e;
	}
}

void Bone::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BONE_BBOX_WIDTH;
	b = y + BONE_BBOX_HEIGHT;
}

void Bone::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_ENEMY2, L"textures\\enemy2.png", D3DCOLOR_XRGB(255, 0, 255));
	CAnimations* animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 tex_Bone = textures->Get(ID_TEX_ENEMY2);

	LPANIMATION ani;

	sprites->Add(50001, 665, 129, 665 + 16, 129 + 5, tex_Bone);
	sprites->Add(50002, 688, 122, 688 + 6, 122 + 15, tex_Bone);
	sprites->Add(50003, 700, 122, 700 + 12, 122 + 13, tex_Bone);
	sprites->Add(50004, 718, 126, 718 + 6, 126 + 8, tex_Bone);

	ani = new CAnimation(100);
	ani->Add(50001);
	ani->Add(50002);
	ani->Add(50003);
	ani->Add(50004);

	animations->Add(501, ani);
	this->AddAnimation(501);
}

void Bone::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	//activeRange.CalculateActiveRange(this);
	//activeRange.left += 50;
	//activeRange.top += 50;
	//activeRange.right += 50;
}
void Bone::ReLoad()
{

}
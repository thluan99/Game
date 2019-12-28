#include "MonKey.h"



MonKey::MonKey()
{
	vy = 0;
}

void MonKey::Render()
{
	animations[1]->Render(x, y);
}

void MonKey::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = 0;
	vx = -0.1f;
	x += dx;
}

void MonKey::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;

	textures->Add(ID_TEX_MONKEY, L"textures\\Monkey.png", D3DCOLOR_XRGB(255, 0, 255));

	CAnimations *animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 texMon = textures->Get(ID_TEX_MONKEY);
	LPANIMATION ani;

	sprites->Add(90000, 11, 32, 68 + 11, 29 + 32, texMon);
	sprites->Add(90001, 86, 25, 57 + 86, 36 + 25, texMon);
	sprites->Add(90002, 152, 17, 57 + 152, 44 + 17, texMon);
	sprites->Add(90003, 218, 7, 58 + 218, 54 + 7, texMon);
	sprites->Add(90004, 258, 8, 51 + 258, 53 + 8, texMon);
	sprites->Add(90005, 350, 13, 63 + 350, 48 + 13, texMon);

	ani = new CAnimation(100);
	ani->Add(90000);
	ani->Add(90001);
	ani->Add(90002);
	ani->Add(90003);
	ani->Add(90004);
	ani->Add(90005);
	animations->Add(100, ani);

	sprites->Add(90010, 18, 84, 26 + 18, 33 + 84, texMon);
	sprites->Add(90011, 52, 84, 42 + 52, 33 + 84, texMon);
	sprites->Add(90012, 101, 85, 52 + 101, 32 + 85, texMon);
	sprites->Add(90013, 161, 80, 40 + 161, 37 + 80, texMon);
	sprites->Add(90014, 211, 81, 35 + 211, 36 + 81, texMon);
	sprites->Add(90015, 255, 81, 45 + 255, 36 + 81, texMon);
	sprites->Add(90016, 312, 83, 50 + 312, 34 + 83, texMon);
	sprites->Add(90017, 371, 86, 46 + 371, 31 + 86, texMon);

	ani = new CAnimation(100);
	ani->Add(90010);
	ani->Add(90011);
	ani->Add(90012);
	ani->Add(90013);
	ani->Add(90014);
	ani->Add(90015);
	ani->Add(90016);
	ani->Add(90017);
	animations->Add(101, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
}

void MonKey::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = b = r = 0;
}

void MonKey::ReLoad()
{
}


MonKey::~MonKey()
{
}

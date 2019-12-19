#include "FireAngry.h"



FireAngry::FireAngry()
{
}

void FireAngry::Render()
{
	animations[0]->Render(384, 280 + 20);
	animations[0]->Render(400, 280 + 20);
	animations[0]->Render(416, 280 + 20);
}

void FireAngry::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;

	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	textures->Add(ID_TEX_JAFAR_R, L"textures\\Scene2\\SJafar.png", D3DCOLOR_XRGB(186, 254, 202));

	LPDIRECT3DTEXTURE9 text_AngFire = textures->Get(ID_TEX_JAFAR_R);

	sprites->Add(48080, 14, 392, 24 + 14, 47 + 392, text_AngFire);
	sprites->Add(48081, 46, 386, 22 + 46, 46 + 386, text_AngFire);
	sprites->Add(48082, 78, 392, 24 + 78, 47 + 392, text_AngFire);
	sprites->Add(48083, 110, 389, 27 + 110, 50 + 389, text_AngFire);
	sprites->Add(48084, 150, 393, 35 + 150, 46 + 393, text_AngFire);

	ani = new CAnimation(100);		//1
	ani->Add(48080);
	ani->Add(48081);
	ani->Add(48082);
	ani->Add(48083);
	ani->Add(48084);
	animations->Add(100, ani);

	this->AddAnimation(100);
}

void FireAngry::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}


void FireAngry::ReLoad()
{
}

FireAngry::~FireAngry()
{
}

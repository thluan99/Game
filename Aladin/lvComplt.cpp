#include "lvComplt.h"



lvComplt::lvComplt()
{

}

void lvComplt::Render()
{
	animations[0]->Render(SCREEN_WIDTH / 2 - 232 / 2, y);
}

void lvComplt::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;


	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;

	textures->Add(ID_TEX_LVCOMLT, L"textures\\levelComplt.png", D3DCOLOR_XRGB(186, 254, 202));
	LPDIRECT3DTEXTURE9 texCom = textures->Get(ID_TEX_LVCOMLT);

	sprites->Add(99900, 0, 0, 232, 141, texCom);
	ani = new CAnimation(100);		// text
	ani->Add(99900);
	animations->Add(111, ani);

	this->AddAnimation(111);
}

void lvComplt::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void lvComplt::ReLoad()
{
}


lvComplt::~lvComplt()
{
}

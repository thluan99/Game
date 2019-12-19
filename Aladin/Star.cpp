#include "Star.h"

Star::Star()
{
	vy = 0.1f;
}

void Star::Render()
{
	if (state == STAR_STATE_DESTROY)
	{
		animations[1]->Render(x, y);
	}
	else
		animations[0]->Render(x, y);
}

void Star::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Star::SetState(int state)
{
	CGameObject::SetState(state);
}

void Star::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	this->id = ID;

	textures->Add(ID_TEX_JAFAR_R, L"textures\\Scene2\\SJafar.png", D3DCOLOR_XRGB(186, 254, 202));

	CAnimations *animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 textEStar = textures->Get(ID_TEX_JAFAR_R);
	LPANIMATION ani;

	sprites->Add(48100, 198, 425, 28 + 198, 14 + 425, textEStar);
	sprites->Add(48101, 238, 423, 24 + 238, 16 + 423, textEStar);
	sprites->Add(48102, 270, 424, 26 + 270, 15 + 424, textEStar);
	ani = new CAnimation(100);
	ani->Add(48100);
	ani->Add(48101);
	ani->Add(48102);
	animations->Add(100, ani);

	sprites->Add(48105, 310, 426, 14 + 310, 13 + 426, textEStar);
	sprites->Add(48106, 334, 425, 21 + 334, 14 + 425, textEStar);
	sprites->Add(48107, 382, 418, 15 + 382, 21 + 418, textEStar);
	ani = new CAnimation(300);
	ani->Add(48105);
	ani->Add(48106);
	ani->Add(48107);
	animations->Add(101, ani);

	this->AddAnimation(100);
	this->AddAnimation(101);
}

void Star::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void Star::ReLoad()
{
}


Star::~Star()
{
}

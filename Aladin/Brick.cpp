#include "Brick.h"

void CBrick::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::LoadResources(int ID)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPANIMATION ani;
	
	this->id = ID;

	if (this->id == eType::BRICK)
	{
		textures->Add(ID_TEX_MAP, L"textures\\map_tex.png", D3DCOLOR_XRGB(163, 73, 164));

		LPDIRECT3DTEXTURE9 texBrick = textures->Get(ID_TEX_MAP);
		sprites->Add(40001, 73, 1770, 73 + 34, 1770 + 17, texBrick);

		ani = new CAnimation(100);		// brick
		ani->Add(40001);
		animations->Add(601, ani);

		this->AddAnimation(601);
	}
	else if (this->id == eType::BRICK2)
	{
		textures->Add(ID_TEX_BRICK_2, L"textures\\tileset.png", (BACKGROUND_COLOR));
		// BRICK VER 2
		LPDIRECT3DTEXTURE9 texBrick2 = textures->Get(ID_TEX_BRICK_2);
		sprites->Add(40002, 96, 0, 96 + 32, 0 + 32, texBrick2);

		ani = new CAnimation(100);		// brick 2
		ani->Add(40002);
		animations->Add(602, ani);

		this->AddAnimation(602);
	}
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrick::ReLoad()
{
}

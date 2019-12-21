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
		LPDIRECT3DTEXTURE9 texBrick = textures->Get(ID_TEX_MAP);
		sprites->Add(40001, 1, 1770, 1 + 31, 1770 + 15, texBrick);
		sprites->Add(40002, 37, 1770, 37 + 31, 1770 + 15, texBrick);
		sprites->Add(40003, 73, 1770, 73 + 34, 1770 + 17, texBrick);
		sprites->Add(40004, 112, 1770, 112 + 38, 1770 + 21, texBrick);
		sprites->Add(40005, 155, 1770, 155 + 40, 1770 + 24, texBrick);

		ani = new CAnimation(100);		// brick
		ani->Add(40001);
		ani->Add(40002);
		ani->Add(40003);
		ani->Add(40004);
		ani->Add(40005);

		animations->Add(601, ani);

		this->AddAnimation(601);
	}
	else if (this->id == eType::BRICK2)
	{
		// BRICK VER 2
		LPDIRECT3DTEXTURE9 texBrick_BALL = textures->Get(ID_TEX_MAP);
		sprites->Add(40006, 227, 1770, 227 + 14, 1770 + 45, texBrick_BALL);
		sprites->Add(40007, 246, 1770, 246 + 15, 1770 + 47, texBrick_BALL);
		sprites->Add(40008, 266, 1770, 266 + 15, 1770 + 50, texBrick_BALL);
		sprites->Add(40009, 286, 1770, 286 + 15, 1770 + 52, texBrick_BALL);
		sprites->Add(40010, 306, 1770, 306 + 16, 1770 + 56, texBrick_BALL);
		sprites->Add(40011, 327, 1770, 327 + 16, 1770 + 60, texBrick_BALL);
		sprites->Add(40012, 348, 1770, 348 + 18, 1770 + 65, texBrick_BALL);
		sprites->Add(40013, 371, 1770, 371 + 21, 1770 + 67, texBrick_BALL);
		sprites->Add(40014, 397, 1770, 397 + 26, 1770 + 65, texBrick_BALL);
		sprites->Add(40015, 428, 1770, 428 + 28, 1770 + 63, texBrick_BALL);
		sprites->Add(40016, 461, 1770, 461 + 30, 1770 + 59, texBrick_BALL);
		sprites->Add(40017, 496, 1770, 496 + 31, 1770 + 57, texBrick_BALL);
		sprites->Add(40018, 532, 1770, 532 + 32, 1770 + 56, texBrick_BALL);
		sprites->Add(40019, 569, 1770, 569 + 33, 1770 + 53, texBrick_BALL);
		sprites->Add(40020, 607, 1770, 607 + 33, 1770 + 52, texBrick_BALL);

		ani = new CAnimation(100);		// brick 2		// brick 2
		ani->Add(40006);
		ani->Add(40007);
		ani->Add(40008);
		ani->Add(40009);
		ani->Add(40010);
		ani->Add(40011);
		ani->Add(40012);
		ani->Add(40013);
		ani->Add(40014);
		ani->Add(40015);
		ani->Add(40016);
		ani->Add(40017);
		ani->Add(40018);
		ani->Add(40019);
		ani->Add(40020);

		animations->Add(602, ani);

		this->AddAnimation(602);
	}
	else if (this->id == eType::BRICKLINE)
	{
		LPDIRECT3DTEXTURE9 texBrick_LINE = textures->Get(ID_TEX_MAP);
		sprites->Add(40021, 1, 1799, 1 + 23, 1799 + 20, texBrick_LINE);
		sprites->Add(40022, 29, 1799, 29 + 23, 1799 + 23, texBrick_LINE);
		sprites->Add(40023, 57, 1799, 57 + 26, 1799 + 28, texBrick_LINE);
		sprites->Add(40024, 88, 1799, 88 + 33, 1799 + 31, texBrick_LINE);
		sprites->Add(40025, 126, 1799, 126 + 42, 1799 + 34, texBrick_LINE);
		sprites->Add(40026, 173, 1799, 173 + 49, 1799 + 35, texBrick_LINE);

		ani = new CAnimation(100);
		ani->Add(40021);
		ani->Add(40022);
		ani->Add(40023);
		ani->Add(40024);
		ani->Add(40025);
		ani->Add(40026);

		animations->Add(603, ani);
		this->AddAnimation(603); //gai 
	}

}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (id == eType::BRICK)
	{
		int curr_f = GetAnimation()[0]->GetCurrentFrame();
		if (curr_f >= 3)
		{
			l = x;
			t = y;
			r = l + (animations[0]->frames[curr_f]->GetSprite()->GetWidth());
			b = t + (animations[0]->frames[curr_f]->GetSprite()->GetHeight());
		}
		else
		{
			l = 0;
			t = 0;
			r = 0;
			b = 0;
		}
	}
	else if (id == eType::BRICK2)
	{
		int curr_f = GetAnimation()[0]->GetCurrentFrame();
		if (curr_f >= 9)
		{
			l = x;
			t = y;
			r = l + (animations[0]->frames[curr_f]->GetSprite()->GetWidth());
			b = t + (animations[0]->frames[curr_f]->GetSprite()->GetHeight());
		}
		else
		{
			l = 0;
			t = 0;
			r = 0;
			b = 0;
		}
	}
	else if (id == eType::BRICKLINE)
	{
		int curr_f = GetAnimation()[0]->GetCurrentFrame();
		if (curr_f >= 2)
		{
			l = x;
			t = y;
			r = l + (animations[0]->frames[curr_f]->GetSprite()->GetWidth());
			b = t + (animations[0]->frames[curr_f]->GetSprite()->GetHeight());
		}
	}
}

void CBrick::ReLoad()
{
}

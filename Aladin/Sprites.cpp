﻿#include "Sprites.h"
#include "Game.h"
#include "debug.h"


CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}
CSprite::CSprite(int id, int left, int top, int right, int bottom,int gapx, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->gapx = gapx;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

void CSprites::Add(int id, int left, int top, int right, int bottom,int gapx, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom,gapx, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	alpha = 255;
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::RenderUI(float x, float y, int alpha)
{
	alpha = 255;
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	frames[currentFrame]->GetSprite()->Draw(x, y - hei, alpha);
}


int CAnimation::RenderJustOne(float x, float y, int alpha)
{
	alpha = 255;

	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
		}
		if (currentFrame >= frames.size())
		{
			currentFrame = frames.size() -  1;
		}
	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	frames[currentFrame]->GetSprite()->Draw(x, y - hei, alpha);

	if (currentFrame == frames.size() - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void CAnimation::RenderAladin( float x, float y, int direct, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0; 
			}
		}

	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	int w = frames[currentFrame]->GetSprite()->GetWidth();

	if (direct == 1)
		frames[currentFrame]->GetSprite()->Draw(x, y - hei, alpha);
	else if (direct == -1)
		frames[currentFrame]->GetSprite()->Draw(x - w / 2, y - hei, alpha);
}

void CAnimation::RenderAladinSpecial(float x, float y, int direct, int status,  int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = frames.size() - 1;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			if (status == 1)
				currentFrame++;
			else if (status == -1)
			{
				currentFrame--;
			}

			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
			}
			if (currentFrame == -1)
			{
				currentFrame = frames.size() - 1;
			}
		}

	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	int w = frames[currentFrame]->GetSprite()->GetWidth();

	if (direct == 1)
		frames[currentFrame]->GetSprite()->Draw(x, y - hei, alpha);
	else if (direct == -1)
		frames[currentFrame]->GetSprite()->Draw(x - w / 2, y - hei, alpha);
}



//Truyền BBox X và BBox Y vào
void CAnimation::RenderAladinF1(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
			}
		}

	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	int wid = frames[currentFrame]->GetSprite()->GetWidth();
	frames[currentFrame]->GetSprite()->Draw(x - wid, y - hei, alpha);
}

//Truyền BBox Y vào, không truyền BBox Y
void CAnimation::RenderAladinF_1(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
			}
		}

	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	int wid = frames[currentFrame]->GetSprite()->GetWidth();
	frames[currentFrame]->GetSprite()->Draw(x - 22, y - hei, alpha);
}

void CAnimation::RenderAladin(int &stt,float x, float y, int direct, int alpha)
{
	if (stt == -1)
	{
		currentFrame = 0;
	}
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
				stt = 1;
			}
			else
				stt = 0;
		}

	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	int w = frames[currentFrame]->GetSprite()->GetWidth();

	if (direct == 1)
		frames[currentFrame]->GetSprite()->Draw(x, y - hei, alpha);
	else if (direct == -1)
		frames[currentFrame]->GetSprite()->Draw(x - w / 2, y - hei, alpha);

}

void CAnimation::RenderAladinGap(int& stt, float x, float y, int direct, int alpha)
{
	if (stt == -1)
	{
		currentFrame = 0;
	}
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
				stt = 1;
			}
			else
				stt = 0;
		}

	}
	int hei = frames[currentFrame]->GetSprite()->GetHeight();
	int w = frames[currentFrame]->GetSprite()->GetWidth();
	int gap = frames[currentFrame]->GetSprite()->GetGapx();

	frames[currentFrame]->GetSprite()->Draw(x - gap, y - hei, alpha);

}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}
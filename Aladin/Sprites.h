#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
protected:
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;
	int anchor2Left, anchor2Top;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite() {}
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	CSprite(int id, int left, int top, int right, int bottom, int anchor2Left, int anchor2Top, LPDIRECT3DTEXTURE9 tex);
	void Draw(float x, float y, int alpha = 255);
	void DrawEx(float x, float  y, int alpha = 255);

	int GetHeight() { return bottom - top; }
	int GetWidth() { return right - left; }
	int GetAnchorLeft() { return anchor2Left; }
	int GetAnchorTop() { return anchor2Top; }
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void AddEx(int id, int left, int top, int right, int bottom, int Anchor2Left, int Anchor2Top, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	LPSPRITE &operator[](int id) {return sprites[id];}

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
public:
	vector<LPANIMATION_FRAME> frames;
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha=255);
	void RenderAladin(float x, float y, int direct, int alpha = 255);
	void RenderAladin(int&, float x, float y, int direct, int alpha = 255);
	int GetCurrentFrame() { return currentFrame; }

};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};


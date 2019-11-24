#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  34
#define BRICK_BBOX_HEIGHT 17

#define ID_TEX_MAP				30
#define ID_TEX_BRICK_2			40


class CBrick : public CGameObject
{
public:
	virtual void Render();
	virtual void LoadResources(int ID);
	CBrick() { w = 34; h = 17;};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};
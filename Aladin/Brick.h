#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  34
#define BRICK_BBOX_HEIGHT 17

class CBrick : public CGameObject
{
public:
	virtual void Render();
	CBrick() {};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
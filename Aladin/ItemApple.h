#pragma once
#include "GameObject.h"

#define IT_APPLE_BBOX_WIDTH  12
#define IT_APPLE_BBOX_HEIGHT 12

class ItemApple : public CGameObject
{
public:
	ItemApple();
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~ItemApple();
};


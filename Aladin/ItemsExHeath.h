#pragma once
#include "GameObject.h"

#define IT_HEA_BBOX_WIDTH  20
#define IT_HEA_BBOX_HEIGHT 20

class ItemsExHeath : public CGameObject
{
public:
	ItemsExHeath();
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~ItemsExHeath();
};


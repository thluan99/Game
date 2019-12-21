#pragma once
#include "GameObject.h"

#define IT_RUBY_BBOX_WIDTH  15
#define IT_RUBY_BBOX_HEIGHT 15

class ItemRuby : public CGameObject
{
public:
	ItemRuby();
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~ItemRuby();
};


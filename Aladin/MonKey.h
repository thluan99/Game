#pragma once
#include "GameObject.h"
class MonKey : public CGameObject
{
public:
	MonKey();
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~MonKey();
};


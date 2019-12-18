#pragma once
#include "GameObject.h"

class FireAngry : public CGameObject
{
public:
	FireAngry();
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~FireAngry();
};


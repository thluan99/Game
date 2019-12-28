#pragma once
#include "GameObject.h"
class lvComplt : public CGameObject
{
public:
	lvComplt();
	virtual void Render();
	virtual void LoadResources(int ID);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
	~lvComplt();
};


#pragma once
#include "GameObject.h"


class TextSurface : public CGameObject
{
public:
	virtual void Render();
	virtual void LoadResources(int ID);
	TextSurface() { };
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};
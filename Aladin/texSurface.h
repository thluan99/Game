#pragma once
#include "GameObject.h"

#define ID_TEX_BK_M2 70

class TextSurface : public CGameObject
{
public:
	virtual void Render();
	virtual void LoadResources(int ID);
	TextSurface() { };
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};
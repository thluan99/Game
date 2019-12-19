#pragma once
#include "GameObject.h"

#define LAND_BBOX_HEIGHT 10
#define LAND1_BBOX_HEIGHT 8
#define LAND2_BBOX_HEIGHT 16
#define LAND3_BBOX_HEIGHT 32
#define LAND3_BBOX_WIDTH  16
#define LANDEX_BBOX_WIDTH 32

#define ID_TEX_LAND			99


class CLand : public CGameObject
{
public:
	virtual void Render();
	virtual void LoadResources(int ID);
	CLand() { w = MAP_LIMIT_RIGHT; h = LAND_BBOX_HEIGHT; };
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void ReLoad();
};
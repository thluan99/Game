#pragma once
#include "GameObject.h"
#include "Enemy2.h"
#include "ActiveRange.h"

#define BONE_BBOX_HEIGHT 15
#define BONE_BBOX_WIDTH 16

class Bone :
	public CGameObject
{
public:
	ActiveRange activeRange;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void LoadResources(int ID);
	void SetPosition(float, float);

	Bone()
	{
		id = eType::BONE;
		CalculateVeloc();
	};


	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void ReLoad();

	void CalculateVeloc();
};


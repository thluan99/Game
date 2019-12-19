#pragma once
#define RANGE 200

#include "GameObject.h"
class ActiveRange
{
public:

	int left, top, right, bottom;
	ActiveRange() {}

	ActiveRange(CGameObject* monster)
	{
		CalculateActiveRange(monster);
	}

	void CalculateActiveRange(CGameObject* monster)
	{
		left = monster->x - RANGE;
		top = monster->y - RANGE;
		right = monster->x + RANGE;
		bottom = monster->y + RANGE;
	}

};


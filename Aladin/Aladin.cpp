#include <algorithm>
#include "debug.h"

#include "Aladin.h"
#include "Game.h"

#include "Goomba.h"

void CAladin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += ALADIN_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=ALADIN_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -ALADIN_JUMP_DEFLECT_SPEED;
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CAladin::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) ani = ALADIN_ANI_BIG_IDLE_RIGHT;
		else ani = ALADIN_ANI_BIG_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = ALADIN_ANI_BIG_WALKING_RIGHT;
	else ani = ALADIN_ANI_BIG_WALKING_LEFT;
	int alpha = 255;

	animations[ani]->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CAladin::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ALADIN_STATE_WALKING_RIGHT:
		vx = ALADIN_WALKING_SPEED;
		nx = 1;
		break;
	case ALADIN_STATE_WALKING_LEFT: 
		vx = -ALADIN_WALKING_SPEED;
		nx = -1;
		break;
	case ALADIN_STATE_JUMP: 
		vy = -ALADIN_JUMP_SPEED_Y;
	case ALADIN_STATE_IDLE: 
		vx = 0;
		break;

	}
}

void CAladin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	right = x + ALADIN_BIG_BBOX_WIDTH;
	bottom = y + ALADIN_BIG_BBOX_HEIGHT;
}


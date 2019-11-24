#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Define.h"
#include "Sprites.h"
#include "Textures.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:
	int Health;
	int id;
	int gridID;

	int direction;	// hướng -1 : trái, 1: phải
	eType type; // Loại Object

	float x; 
	float y;
	float firstPosX;
	float firstPosY;
	float w; // width
	float h; // height

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;

	DWORD dt; 
	CTextures * textures;
	CSprites * sprites;
	vector<LPANIMATION> animations;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetHealth();
	void SetHealth(int h);
	void SubHealth(int th);
	void SetDirection(int d);
	int GetDirection();
	void SetId(int ID);
	int GetId();
	float GetX() { return x; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	float GetY() { return y; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void LoadResources(int ID) = 0;
	virtual void ReLoad() = 0;


	~CGameObject();
};


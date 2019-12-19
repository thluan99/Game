#pragma once

#include "Scene.h"
#include "Scene2.h"

class Scene1 : public Scene
{
public:
	Scene1();
	Scene1(vector<LPGAMEOBJECT> objects,
		dxGraphics *dx_graphics,
		Camera *camera,
		CGame *game);
	CGameObject * GetNewObjectEx(int ID);
	void CreateGrid(vector <CGameObject *> &objects);
	void LoadResources(vector<CGameObject*>& objects);
	void Update(DWORD dt);
	void Render();
	void Clear();
	~Scene1();
};


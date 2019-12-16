#pragma once

#include "Scene.h"

class Scene2 : public Scene
{
public:
	Scene2();
	Scene2(vector<LPGAMEOBJECT> objects,
		dxGraphics *dx_graphics,
		Camera *camera,
		CGame *game);
	CGameObject * GetNewObjectEx(int ID);
	void CreateGrid(vector <CGameObject *> &objects);
	void LoadResources(vector<CGameObject*>& objects);
	void Resources(vector<CGameObject*>& objects);
	void Update(DWORD dt);
	void Render();
	~Scene2();
};
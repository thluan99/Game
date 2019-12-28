#pragma once
#include "Scene.h"

class SceneChange : public Scene
{
public:
	SceneChange();
	virtual void CreateGrid(vector <CGameObject *> &objects) = 0;
	virtual void LoadResources(vector<CGameObject*>& objects);
	virtual void Update(DWORD dt);
	virtual void Render();
	~SceneChange();
};


#pragma once
#include "Scene.h"
#include "MonKey.h"
#include "lvComplt.h"

class SceneChange : public Scene
{
public:

	MonKey *monkey;
	lvComplt *lvCom;

	SceneChange();
	SceneChange(vector<LPGAMEOBJECT> objects,
		dxGraphics *dx_graphics,
		Camera *camera,
		CGame *game);
	virtual void CreateGrid(vector <CGameObject *> &objects);
	virtual void LoadResources(vector<CGameObject*>& objects);
	virtual void Update(DWORD dt);
	virtual void Render();
	~SceneChange();
};


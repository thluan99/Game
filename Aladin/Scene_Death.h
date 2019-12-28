#pragma once
#include "Scene.h"
#include "Define.h"
#include "MonKey.h"
#include <Windows.h>
class Scene_Death :
	public Scene
{
	int stt_scene;

public:
	MonKey* monkey;

	Scene_Death() { stt_scene = 0; }
	Scene_Death(
		vector<LPGAMEOBJECT> objects,
		dxGraphics* dx_graphics,
		Camera* camera,
		CGame* game);
	void CreateGrid(vector <CGameObject*>& objects) {}
	void LoadResources(vector <CGameObject*>& objects);
	void Resources();
	void Update(DWORD dt);
	void Render();

};


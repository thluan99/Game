#pragma once
#include "Scene.h"
#include "Define.h"

#define BACKGROUND_ 90900
#define START 90901
#define START_C 90902
#define EXIT  90903
#define EXIT_C 90904

class Scene_Menu :
	public Scene
{
	int stt_scene;
public:
	int start_;
	int exit_;

	CTextures* textures;
	CSprites* sprites;

	Scene_Menu() { stt_scene = 0; }
	Scene_Menu(
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


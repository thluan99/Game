#include "Scene_Death.h"

Scene_Death::Scene_Death(vector<LPGAMEOBJECT> objects,
	dxGraphics* dx_graphics,
	Camera* camera,
	CGame* game)
{
	this->objects = objects;
	this->dx_graphics = dx_graphics;
	this->camera = camera;
	this->game = game;
	stt_scene = 0;
}

void Scene_Death::LoadResources(vector <CGameObject*>& objects)
{
	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	objects.push_back(aladin);

	monkey = new MonKey();
	monkey->LoadResources(eType::MONKEY);
	monkey->SetPosition(aladin->x + 40, aladin->y + 60);
	objects.push_back(monkey);

}

void Scene_Death::Resources()
{

}

void Scene_Death::Render()
{

	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);


		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
		if (camera)
		{
			camera->SetTransform(dx_graphics);
		}

		aladin->animations[ALADIN_ANI_DIE]->RenderAladin(stt_scene, camera->cameraX - 20, camera->cameraY + 30, aladin->direction);
		monkey->animations[0]->RenderAladinF1(camera->cameraX + 80, camera->cameraY + 60);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void Scene_Death::Update(DWORD dt)
{
	aladin->setEnableKey(false);

	if (stt_scene == 1)
	{

	}
}

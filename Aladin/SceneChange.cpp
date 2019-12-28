#include "SceneChange.h"



SceneChange::SceneChange()
{
}

SceneChange::SceneChange(vector<LPGAMEOBJECT> objects, dxGraphics * dx_graphics, Camera * camera, CGame * game)
{
	this->objects = objects;
	this->dx_graphics = dx_graphics;
	this->camera = camera;
	this->game = game;
	objects.clear();
}

void SceneChange::CreateGrid(vector<CGameObject*>& objects)
{
}

void SceneChange::LoadResources(vector<CGameObject*>& objects)
{
	monkey = new MonKey();
	monkey->LoadResources(eType::MONKEY);
	monkey->SetPosition(SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	lvCom = new lvComplt();
	lvCom->LoadResources(eType::LV_COMPLT);
	lvCom->SetPosition(SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);

	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(monkey->x + 100, monkey->y);

	this->objects = objects;
}

void SceneChange::Update(DWORD dt)
{
	camera->Follow(aladin);
	camera->Update(3);

	aladin->x += -0.1f*dt;
	monkey->x += -0.1f*dt;
}

void SceneChange::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_CHANGE_SCENE);


		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
		if (camera)
		{
			camera->SetTransform(dx_graphics);
		}
		lvCom->Render();
		aladin->animations[ALADIN_ANI_WALKING_PASSING]->RenderAladin(aladin->x, aladin->y, -1, 255);
		monkey->animations[1]->RenderAladin(monkey->x, monkey->y, -1, 255);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


SceneChange::~SceneChange()
{
}

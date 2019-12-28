#include "Scene_Menu.h"

Scene_Menu::Scene_Menu(vector<LPGAMEOBJECT> objects, dxGraphics* dx_graphics, Camera* camera, CGame* game)
{
	this->objects = objects;
	this->dx_graphics = dx_graphics;
	this->camera = camera;
	this->game = game;
	stt_scene = 0;
	start_ = 1;
	exit_ = 0;
}

void Scene_Menu::LoadResources(vector<CGameObject*>& objects)
{
	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	objects.push_back(aladin);

	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_MENU, L"textures\\menu.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MENU_UI, L"textures\\menu_ui.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texBackground = textures->Get(ID_TEX_MENU);
	LPDIRECT3DTEXTURE9 texMENU_UI = textures->Get(ID_TEX_MENU_UI);

	sprites->Add(90900, 0, 0, 320, 256, texBackground); //backgroundd
	sprites->Add(90901, 379, 12, 379 + 119, 12 + 46, texMENU_UI); // ui Start 
	sprites->Add(90902, 250, 12, 250 + 119, 12 + 46, texMENU_UI); // ui Start choose
	sprites->Add(90903, 383, 82, 383 + 51, 82 + 25, texMENU_UI); // ui exit
	sprites->Add(90904, 254, 82, 254 + 51, 82 + 25, texMENU_UI); // ui exit choose
}
void Scene_Menu::Resources()
{

}
void Scene_Menu::Render()
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

		sprites->Get(BACKGROUND_)->Draw(camera->cameraX - SCREEN_WIDTH / 2, camera->cameraY - SCREEN_HEIGHT / 2);
		if (start_ == 1)
		{
			sprites->Get(START_C)->Draw(camera->cameraX - 30, camera->cameraY -30);
		}
		else
		{
			sprites->Get(START)->Draw(camera->cameraX -30, camera->cameraY - 30);
		}

		if (exit_ == 1)
		{
			sprites->Get(EXIT_C)->Draw(camera->cameraX, camera->cameraY + 20);
		}
		else
		{
			sprites->Get(EXIT)->Draw(camera->cameraX, camera->cameraY + 20);
		}

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


void Scene_Menu::Update(DWORD dt)
{

}


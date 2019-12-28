#include "SceneChange.h"



SceneChange::SceneChange()
{
}

void SceneChange::LoadResources(vector<CGameObject*>& objects)
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_APPLE, L"textures\\levelComplt.png", D3DCOLOR_XRGB(0, 0, 0));
}

void SceneChange::Update(DWORD dt)
{
}

void SceneChange::Render()
{
}


SceneChange::~SceneChange()
{
}

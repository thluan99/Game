#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <sstream>
#include <iostream>

#include "Sprites.h"
#include "Textures.h"
#include "Define.h"
#include "Aladin.h"
#include "Camera.h"

#define NUM_0 99100
#define NUM_1 99101
#define NUM_2 99102
#define NUM_3 99103
#define NUM_4 99104
#define NUM_5 99105
#define NUM_6 99106
#define NUM_7 99107
#define NUM_8 99108
#define NUM_9 99109

#define NUM_0_S 99110
#define NUM_1_S 99111
#define NUM_2_S 99112
#define NUM_3_S 99113
#define NUM_4_S 99114
#define NUM_5_S 99115
#define NUM_6_S 99116
#define NUM_7_S 99117
#define NUM_8_S 99118
#define NUM_9_S 99119


#define UI_ANI_HEAL_FULL 0
#define UI_ANI_HEAL_9HP  1
#define UI_ANI_HEAL_8HP  2
#define UI_ANI_HEAL_7HP  3
#define UI_ANI_HEAL_6HP  4
#define UI_ANI_HEAL_5HP  5
#define UI_ANI_HEAL_4HP  6
#define UI_ANI_HEAL_3HP  7
#define UI_ANI_HEAL_2HP  8
#define UI_ANI_HEAL_1HP  9
#define UI_ANI_HEAL_0HP  10

#define UI_ANI_LIFE		 11
#define UI_ANI_COIN		 12
#define UI_ANI_APPLE	 13



class UI
{
private:
	static UI* __instance;

	CTextures* textures;
	CSprites* sprites;
	vector<LPANIMATION> animations;

	CAladin* aladin;
	Camera* camera;
public:
	int scores;
	int lifes;//
	int apples;//
	int coins;//
	int healths; //

	void Update(DWORD dt);
	void Render();
	void LoadResources();
	void RenderNUM(int, int x, int y);
	void RenderNUM_S(int, int x, int y);

	static UI* GetInstance(CAladin*);

	UI()
	{
	}

	UI(CAladin* aladin)
	{
		this->aladin = aladin;
		camera = Camera::GetInstance();
		textures = CTextures::GetInstance();
		sprites = CSprites::GetInstance();
	}

	void AddAnimation(int aniId)
	{
		LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
		animations.push_back(ani);
	}
};


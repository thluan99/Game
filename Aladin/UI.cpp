#include "UI.h"

UI* UI::__instance = NULL;

UI* UI::GetInstance(CAladin *aladin)
{
	if (__instance == NULL) __instance = new UI(aladin);
	return __instance;
}

void UI::Update(DWORD dt)
{
	this->scores = aladin->scores;
	this->lifes = aladin->lifes;
	this->coins = aladin->coins;
	this->healths = aladin->HP;
	this->apples = aladin->apples;
}

void UI::Render()
{
	//render health
	if (this->healths == 10)
	{
		animations[UI_ANI_HEAL_FULL]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 9)
	{
		animations[UI_ANI_HEAL_9HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 8)
	{
		animations[UI_ANI_HEAL_8HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 7)
	{
		animations[UI_ANI_HEAL_7HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 6)
	{
		animations[UI_ANI_HEAL_6HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 5)
	{
		animations[UI_ANI_HEAL_5HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 4)
	{
		animations[UI_ANI_HEAL_4HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 3)
	{
		animations[UI_ANI_HEAL_3HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 2)
	{
		animations[UI_ANI_HEAL_2HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths == 1)
	{
		animations[UI_ANI_HEAL_1HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}
	else if (this->healths <= 0)
	{
		animations[UI_ANI_HEAL_0HP]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY - SCREEN_HEIGHT / 2 + 42);
	}

	//Render life
	animations[UI_ANI_LIFE]->RenderUI(camera->cameraX - SCREEN_WIDTH / 2 + 10, camera->cameraY + SCREEN_HEIGHT / 2 - 10);
	RenderNUM_S(lifes, camera->cameraX - SCREEN_WIDTH / 2 + 35, camera->cameraY + SCREEN_HEIGHT / 2 - 36);
	//Remder coins
	animations[UI_ANI_COIN]->RenderUI(camera->cameraX + SCREEN_WIDTH / 2 - 100, camera->cameraY + SCREEN_HEIGHT / 2 - 10);
	RenderNUM_S(coins, camera->cameraX + SCREEN_WIDTH / 2 - 80, camera->cameraY + SCREEN_HEIGHT / 2 - 26);
	//render apples
	animations[UI_ANI_APPLE]->RenderUI(camera->cameraX + SCREEN_WIDTH / 2 - 50, camera->cameraY + SCREEN_HEIGHT / 2 - 10);
	RenderNUM_S(apples, camera->cameraX + SCREEN_WIDTH / 2 - 38, camera->cameraY + SCREEN_HEIGHT / 2 - 26);
	//Render Scores
	RenderNUM(scores, camera->cameraX + SCREEN_WIDTH / 2 - 100, camera->cameraY - SCREEN_HEIGHT / 2 + 10);
}

void UI::RenderNUM(int number, int x, int y)
{
	stringstream string_Str;
	string_Str << number;
	string str_num = string_Str.str();
	for (int i = 0; i < str_num.size(); i++)
	{
		switch (str_num[i])
		{
		case '0':
			sprites->Get(NUM_0)->Draw(x + i * 15, y);
			break;
		case '1':
			sprites->Get(NUM_1)->Draw(x + i * 15, y);
			break;
		case '2':
			sprites->Get(NUM_2)->Draw(x + i * 15, y);
			break;
		case '3':
			sprites->Get(NUM_3)->Draw(x + i * 15, y);
			break;
		case '4':
			sprites->Get(NUM_4)->Draw(x + i * 15, y);
			break;
		case '5':
			sprites->Get(NUM_5)->Draw(x + i * 15, y);
			break;
		case '6':
			sprites->Get(NUM_6)->Draw(x + i * 15, y);
			break;
		case '7':
			sprites->Get(NUM_7)->Draw(x + i * 15, y);
			break;
		case '8':
			sprites->Get(NUM_8)->Draw(x + i * 15, y);
			break;
		case '9':
			sprites->Get(NUM_9)->Draw(x + i * 15, y);
			break;
		default:
			break;
		}
	}
}

void UI::RenderNUM_S(int number, int x, int y)
{
	stringstream string_Str;
	string_Str << number;
	string str_num = string_Str.str();
	for (int i = 0; i < str_num.size(); i++)
	{
		switch (str_num[i])
		{
		case '0':
			sprites->Get(NUM_0_S)->Draw(x + i * 12, y);
			break;
		case '1':
			sprites->Get(NUM_1_S)->Draw(x + i * 12, y);
			break;
		case '2':
			sprites->Get(NUM_2_S)->Draw(x + i * 12, y);
			break;
		case '3':
			sprites->Get(NUM_3_S)->Draw(x + i * 12, y);
			break;
		case '4':
			sprites->Get(NUM_4_S)->Draw(x + i * 12, y);
			break;
		case '5':
			sprites->Get(NUM_5_S)->Draw(x + i * 12, y);
			break;
		case '6':
			sprites->Get(NUM_6_S)->Draw(x + i * 12, y);
			break;
		case '7':
			sprites->Get(NUM_7_S)->Draw(x + i * 12, y);
			break;
		case '8':
			sprites->Get(NUM_8_S)->Draw(x + i * 12, y);
			break;
		case '9':
			sprites->Get(NUM_9_S)->Draw(x + i * 12, y);
			break;
		default:
			break;
		}
	}
}

void UI::LoadResources()
{
	CAnimations* animations = CAnimations::GetInstance();

	textures->Add(ID_TEX_UI, L"textures\\items.png", D3DCOLOR_XRGB(248, 0, 248));
	textures->Add(ID_TEX_UI_FONT_SCORE, L"textures\\fonts_nums.png", D3DCOLOR_XRGB(255, 0, 255));
	
	LPANIMATION ani;
	
	LPDIRECT3DTEXTURE9 tex_UI = textures->Get(ID_TEX_UI);
	LPDIRECT3DTEXTURE9 tex_UI_font = textures->Get(ID_TEX_UI_FONT_SCORE);

	//full HP
	sprites->Add(99001, 34, 487, 34 + 144, 487 + 32, tex_UI);
	sprites->Add(99002, 188, 487, 188 + 144, 487 + 32, tex_UI);
	sprites->Add(99003, 339, 487, 339 + 144, 487 + 32, tex_UI);
	sprites->Add(99004, 487, 487, 487 + 144, 487 + 32, tex_UI);

	ani = new CAnimation(100);
	ani->Add(99001);
	ani->Add(99002);
	ani->Add(99003);
	ani->Add(99004);

	animations->Add(9901, ani);
	this->AddAnimation(9901); //Animation _ full _0

	//HP - 1
	sprites->Add(99005, 34, 535, 34 + 131, 535 + 32, tex_UI);
	sprites->Add(99006, 175, 535, 175 + 131, 535 + 32, tex_UI);
	sprites->Add(99007, 313, 535, 313 + 130, 535 + 32, tex_UI);
	sprites->Add(99008, 449, 535, 449 + 130, 535 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99005);
	ani->Add(99006);
	ani->Add(99007);
	ani->Add(99008);
	animations->Add(9902, ani);
	this->AddAnimation(9902); //Animation_  -1 __1

	//HP -2
	sprites->Add(99009, 34, 581, 34 + 120, 581 + 32, tex_UI);
	sprites->Add(99010, 164, 581, 164 + 120, 581 + 32, tex_UI);
	sprites->Add(99011, 294, 581, 294 + 119, 581 + 32, tex_UI);
	sprites->Add(99012, 423, 581, 423 + 119, 581 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99009);
	ani->Add(99010);
	ani->Add(99011);
	ani->Add(99012);
	animations->Add(9903, ani);
	this->AddAnimation(9903); // 2

	//HP -3
	sprites->Add(99013, 34, 628, 34 + 112, 628 + 32, tex_UI);
	sprites->Add(99014, 156, 628, 156 + 112, 628 + 32, tex_UI);
	sprites->Add(99015, 278, 628, 278 + 111, 628 + 32, tex_UI);
	sprites->Add(99016, 399, 628, 399 + 111, 628 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99013);
	ani->Add(99014);
	ani->Add(99015);
	ani->Add(99016);
	animations->Add(9904, ani);
	this->AddAnimation(9904);// 3

	//Hp - 4
	sprites->Add(99017, 34, 675, 34 + 104, 675 + 32, tex_UI);
	sprites->Add(99018, 148, 675, 148 + 104, 675 + 32, tex_UI);
	sprites->Add(99019, 262, 675, 262 + 103, 675 + 32, tex_UI);
	sprites->Add(99020, 375, 675, 375 + 103, 675 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99017);
	ani->Add(99018);
	ani->Add(99019);
	ani->Add(99020);
	animations->Add(9905, ani);
	this->AddAnimation(9905); //4

	//Hpp -5
	sprites->Add(99021, 34, 722, 34 + 96, 722 + 32, tex_UI);
	sprites->Add(99022, 140, 722, 140 + 96, 722 + 32, tex_UI);
	sprites->Add(99023, 246, 722, 246 + 95, 722 + 32, tex_UI);
	sprites->Add(99024, 351, 722, 351 + 95, 722 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99021);
	ani->Add(99022);
	ani->Add(99023);
	ani->Add(99024);
	animations->Add(9906, ani);
	this->AddAnimation(9906);//5

	//hp - 6
	sprites->Add(99025, 34, 769, 34 + 88, 769 + 32, tex_UI);
	sprites->Add(99026, 133, 769, 133 + 88, 769 + 32, tex_UI);
	sprites->Add(99027, 231, 769, 231 + 87, 769 + 32, tex_UI);
	sprites->Add(99028, 328, 769, 328 + 87, 769 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99025);
	ani->Add(99026);
	ani->Add(99027);
	ani->Add(99028);
	animations->Add(9907, ani);
	this->AddAnimation(9907); //6

	//HP - 7
	sprites->Add(99029, 34, 816, 34 + 80, 816 + 32, tex_UI);
	sprites->Add(99030, 124, 816, 124 + 80, 816 + 32, tex_UI);
	sprites->Add(99031, 214, 816, 214 + 79, 816 + 32, tex_UI);
	sprites->Add(99032, 303, 816, 303 + 79, 816 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99029);
	ani->Add(99030);
	ani->Add(99031);
	ani->Add(99032);
	animations->Add(9908, ani);
	this->AddAnimation(9908); //7

	//HP -8
	sprites->Add(99033, 34, 863, 34 + 71, 863 + 32, tex_UI);
	sprites->Add(99034, 115, 863, 115 + 71, 863 + 32, tex_UI);
	sprites->Add(99035, 196, 863, 196 + 72, 863 + 32, tex_UI);
	sprites->Add(99036, 278, 863, 278 + 72, 863 + 32, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99033);
	ani->Add(99034);
	ani->Add(99035);
	ani->Add(99036);
	animations->Add(9909, ani);
	this->AddAnimation(9909);//8

	//HP - 9
	sprites->Add(99037, 34, 910, 34 + 63, 910 + 29, tex_UI);
	sprites->Add(99038, 107, 910, 107 + 63, 910 + 29, tex_UI);
	sprites->Add(99039, 180, 910, 180 + 64, 910 + 29, tex_UI);
	sprites->Add(99040, 254, 9101, 254 + 64, 910 + 30, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99037);
	ani->Add(99038);
	ani->Add(99039);
	ani->Add(99040);
	animations->Add(9910, ani);
	this->AddAnimation(9910); //9

	//HP empty
	sprites->Add(99041, 34, 954, 34 + 48, 954 + 24, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99041);
	animations->Add(9911, ani);
	this->AddAnimation(9911); //10

	//Life
	sprites->Add(99042, 245, 52, 245 + 22, 52 + 25, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99042);
	animations->Add(9912, ani);
	this->AddAnimation(9912); //11

	//Coin
	sprites->Add(99043, 386, 111, 386 + 17, 111 + 16, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99043);
	animations->Add(9913, ani);
	this->AddAnimation(9913); //12

	//Apple
	sprites->Add(99044, 341, 17, 341 + 11, 17 + 12, tex_UI);
	ani = new CAnimation(100);
	ani->Add(99044);
	animations->Add(9914, ani);
	this->AddAnimation(9914); // 13

	//number
	sprites->Add(99100, 57, 34, 57 + 14, 34 + 17, tex_UI_font); //0
	sprites->Add(99101, 87, 32, 87 + 11, 32 + 19, tex_UI_font); // 1
	sprites->Add(99102, 114, 34, 114 + 15, 34 + 17, tex_UI_font); // 2
	sprites->Add(99103, 143, 33, 143 + 16, 33 + 20, tex_UI_font); // 3
	sprites->Add(99104, 176, 32, 176 + 17, 32 + 20, tex_UI_font); // 4
	sprites->Add(99105, 208, 32, 208 + 14, 32 + 21, tex_UI_font); // 5
	sprites->Add(99106, 238, 34, 238 + 14, 34 + 17, tex_UI_font); // 6
	sprites->Add(99107, 266, 32, 266 + 17, 32 + 25, tex_UI_font);//7
	sprites->Add(99108, 299, 34, 299 + 12, 34 + 17, tex_UI_font);//8
	sprites->Add(99109, 327, 32, 327 + 14, 32 + 22, tex_UI_font);//9

	//number small
	sprites->Add(99110, 57, 68, 57 + 10, 68 + 12, tex_UI_font);
	sprites->Add(99111, 77, 67, 77 + 8, 67 + 13, tex_UI_font);
	sprites->Add(99112, 95, 68, 95 + 11, 68 + 12, tex_UI_font);
	sprites->Add(99113, 114, 67, 114 + 11, 67 + 14, tex_UI_font);
	sprites->Add(99114, 135, 67, 135 + 12, 67 + 14, tex_UI_font);
	sprites->Add(99115, 157, 67, 157 + 10, 67 + 14, tex_UI_font);
	sprites->Add(99116, 177, 68, 177 + 10, 68 + 12, tex_UI_font);
	sprites->Add(99117, 196, 67, 196 + 12, 67 + 17, tex_UI_font);
	sprites->Add(99118, 217, 68, 217 + 9, 68 + 12, tex_UI_font);
	sprites->Add(99119, 236, 67, 236 + 10, 67 + 15, tex_UI_font);
	//Sprites::Get(ID)->Draw()
}

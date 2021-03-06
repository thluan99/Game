﻿/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Define.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Camera.h"
#include "dxGraphics.h"
#include "TileMap.h"

#include "Aladin.h"
#include "Brick.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bat.h"
#include "Land.h"
#include "Grid.h"
#include "texSurface.h"
#include "Apple.h"
#include "Scene.h"
#include "Scene1.h"
#include "Scene2.h"
#include "SceneChange.h"
#include "Scene_Death.h"
#include "Scene_Menu.h"
#include "UI.h"

CGame *game;
Camera *camera;
UI* ui;

Grid *grid;

dxGraphics *dx_graphics;
vector<LPGAMEOBJECT> objects;

Scene1 * scene1;
Scene2 * scene2;
SceneChange *sceneC;
SceneChange *sceneC2;
Scene_Death* scene_death;
Scene_Menu* scene_menu;
Scene *scene;

int currentScene = 0;
int nextSceneX = 2176;
int nextSceneY = 64, nextSceneYx = 64 + 128;

int checkChange = 0;
//---------------KeyBoard -------------------------
#pragma region KeyBoard

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	//---------------test--------------------//
	if (currentScene == 1 || currentScene == 2)
	{

		switch (KeyCode)
		{
		case DIK_5:
			for (int i = 1; i < scene->grid->cells.size(); i++)
				for (int j = 0; j < scene->grid->cells[i]->listGameObject.size(); j++)
					if (scene->grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
						scene->grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_ATTACK_LEFT);
			break;
		case DIK_1:
			for (int i = 1; i < scene->grid->cells.size(); i++)
				for (int j = 0; j < scene->grid->cells[i]->listGameObject.size(); j++)
					if (scene->grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
						scene->grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_ATTACK_RIGHT_MID);
			break;
		case DIK_2:
			for (int i = 1; i < scene->grid->cells.size(); i++)
				for (int j = 0; j < scene->grid->cells[i]->listGameObject.size(); j++)
					if (scene->grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
						scene->grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_HIT_LEFT);
			break;
		case DIK_3:
			for (int i = 1; i < scene->grid->cells.size(); i++)
				for (int j = 0; j < scene->grid->cells[i]->listGameObject.size(); j++)
					if (scene->grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
						scene->grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_IDLE_RIGHT);
			break;
		case DIK_4:
			for (int i = 1; i < scene->grid->cells.size(); i++)
				for (int j = 0; j < scene->grid->cells[i]->listGameObject.size(); j++)
					if (scene->grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
						scene->grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_RUN_LEFT);
			break;
			//---------hack ??? ---------//
		// ---- ĐÂY LÀ PHẦN PHỤC VỤ CHO TEST VÀ GHI FILE --------------//
		case DIK_HOME:
			scene->aladin->SetX(scene->aladin->GetX() + 50);
			break;
		case DIK_END:
			scene->aladin->SetX(scene->aladin->GetX() - 50);
			break;
		case DIK_8:
			scene->aladin->SetPosition(2100, 50);
			break;
			//case DIK_9:
			//	if (currentScene == 1)
			//	{
			//		scene1->grid->InitWriteGrid(scene1->objects);
			//		DebugOut(L"[INFO] : Rewrite file gridWrite.txt\n");
			//	}break;
			//case DIK_0:
			//	if (currentScene == 1)
			//	{
			//		ofstream ofs;
			//		ofs.open("textures\\gridWrite.txt", ofstream::out | ofstream::trunc);
			//		ofs.close();
			//		DebugOut(L"[INFO] : Clear file gridWrite.txt\n");
			//	}break;

			//---------end test------------//
		}
		//------------------end test ----------------------//

		switch (KeyCode)
		{
		case DIK_A:
			scene->aladin->SetState(ALADIN_STATE_IDLE);
			if (currentScene == 1)
				scene->aladin->SetPosition(500.0f, 1000.0f);
			scene->aladin->setEnableKey(true);
			scene->aladin->SetSpeed(0, 0);
			break;
		case DIK_RIGHT:
			if (scene->aladin->getEnableKey() == true) {
				scene->aladin->SetDirection(1);
				scene->aladin->SetState(ALADIN_STATE_DI);

				if (scene->aladin->isStopAnimation == true)
				{
					scene->aladin->isStopAnimation = false;
					scene->aladin->countTiming = 0;
				}
			}
			else {
				if (scene->aladin->getNhay() == true)
					scene->aladin->vx = ALADIN_WALKING_SPEED;
			}
			scene->aladin->isStopAnimation = false;
			break;
		case DIK_LEFT:
			if (scene->aladin->getEnableKey() == true) {
				scene->aladin->SetDirection(-1);
				scene->aladin->SetState(ALADIN_STATE_DI);

				if (scene->aladin->isStopAnimation == true)
				{
					scene->aladin->isStopAnimation = false;
					scene->aladin->countTiming = 0;
				}
			}
			else {
				if (scene->aladin->getNhay() == true)
					scene->aladin->vx = -ALADIN_WALKING_SPEED;

			}
			scene->aladin->isStopAnimation = false;
			break;
		case DIK_UP:
			if (scene->aladin->getEnableKey() == true) {
				if (scene->aladin->isCollisonWithRope || scene->aladin->GetState() == ALADIN_STATE_TREO)
				{
					scene->aladin->SetState(ALADIN_STATE_TREO);
					scene->aladin->vy = -0.1f;
					scene->aladin->x = scene->aladin->xSetCollision;
					scene->aladin->climDirection = 1;
				}
				else
					scene->aladin->SetState(ALADIN_STATE_NGUOC_LEN);
			}
			break;
		case DIK_DOWN:
			if (scene->aladin->getEnableKey() == true) {
				if (scene->aladin->isCollisonWithRope || scene->aladin->GetState() == ALADIN_STATE_TREO)
				{
					scene->aladin->SetState(ALADIN_STATE_TREO);
					scene->aladin->vy = 0.1f;
					scene->aladin->x = scene->aladin->xSetCollision;
					scene->aladin->climDirection = -1;
				}
				else
				{
					scene->aladin->SetState(ALADIN_STATE_NGOI);
				}
			}
			break;
		case DIK_C:
			if (scene->aladin->getEnableKey() == true) {
				scene->aladin->setChem(true);
				scene->aladin->timeIDLE = 0;
				scene->sword = new Sword();
				scene->sword->LoadResources(eType::SWORD);

				if (scene->aladin->direction == 1)
					scene->sword->SetPosition(scene->aladin->x - 20, scene->aladin->y - 20);
				else scene->sword->SetPosition(scene->aladin->x + ALADIN_BIG_BBOX_WIDTH + 20, scene->aladin->y - 20);

				scene->objects.push_back(scene->sword);
				if (currentScene == 1)
					for (int i = 1; i < scene->grid->cells.size(); i++)
						if (scene->grid->isInCell(scene->sword, scene->grid->cells[i]->x, scene->grid->cells[i]->y))
						{
							scene->grid->cells[i]->listGameObject.push_back(scene->sword);
							//DebugOut(L"[info] : aaaaaaaaaaaaaaaaaaaaaa");
						}
			}
			break;
		case DIK_X:
			if (scene->aladin->getEnableKey() == true && scene->aladin->GetState() != ALADIN_STATE_NGOI) {
				if (scene->aladin->GetState() == ALADIN_STATE_TREO)
				{
					scene->aladin->SetState(ALADIN_STATE_TREO_NHAY);
				}
				scene->aladin->setNhay(true);
			}
			break;
		case DIK_Z:
			if (scene->aladin->getEnableKey() == true) {
				scene->aladin->setNem(true);

				scene->aladin->timeIDLE = 0;
				if (scene->aladin->apples > 0)
				{
					scene->aladin->apples--;
					scene->apple = new Apple();
					scene->apple->LoadResources(eType::APPLE);
					//apple = new Apple(scene->aladin->x + 20, scene->aladin->y);
					if (scene->aladin->state == ALADIN_STATE_NGOI)
					{
						scene->apple->SetPosition(scene->aladin->x + 10, scene->aladin->y + 20);
					}
					else
					{
						scene->apple->SetPosition(scene->aladin->x + 10, scene->aladin->y);
					}
					//DebugOut(L"aladin x: %d \n apple x: %d \n", scene->aladin->x + 10, scene->apple->x);
					scene->apple->setNem(true);
					if (scene->aladin->direction == 1)
						scene->apple->direction = 1;
					else scene->apple->direction = -1;
					scene->objects.push_back(scene->apple);
					scene->listApples.push_back(scene->apple);
					if (currentScene == 1)
					{
						for (int i = 1; i < scene->grid->cells.size(); i++)
						{
							if (scene->grid->isInCell(scene->apple, scene->grid->cells[i]->x, scene->grid->cells[i]->y))
							{
								scene->grid->cells[i]->listGameObject.push_back(scene->apple);
							}
						}
					}
				}
			}
			break;

		case DIK_Q:
			scene->aladin->setEnableKey(true);
			break;
		default:
			break;
		}
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	if (currentScene == 1 || currentScene == 2)
	{

		switch (KeyCode)
		{
		case DIK_RIGHT:
			if (scene->aladin->getEnableKey() == true)
				//	if(scene->aladin->GetState()==ALADIN_STATE_DI && scene->aladin->getChem()==false && scene->aladin->getNem() == false && scene->aladin->getNem() == false)
			{
				scene->aladin->SetState(ALADIN_STATE_IDLE);
				if (scene->aladin->countTiming >= 100)
				{
					scene->aladin->isStopAnimation = true;
					scene->aladin->SetState(ALADIN_STATE_DUNG_CHAY_PHAI);
					//DebugOut(L"Timing came");
					scene->aladin->countTiming = 0;
				}
				else scene->aladin->isStopAnimation = false;

				if (scene->aladin->isPushingWall == true)
				{
					scene->aladin->isPushingWall = false;
					scene->aladin->SetState(ALADIN_STATE_IDLE);
				}
			}
			scene->aladin->countTiming = 0;
			scene->aladin->timeIDLE = 0;

			break;
		case DIK_LEFT:
			if (scene->aladin->getEnableKey() == true)
				//	if (scene->aladin->GetState() == ALADIN_STATE_DI && scene->aladin->getChem() == false && scene->aladin->getNem() == false && scene->aladin->getNem() == false)
			{
				scene->aladin->SetState(ALADIN_STATE_IDLE);

				if (scene->aladin->countTiming >= 100)
				{
					scene->aladin->isStopAnimation = true;
					scene->aladin->SetState(ALADIN_STATE_DUNG_CHAY_TRAI);
					//DebugOut(L"Timing came");
					scene->aladin->countTiming = 0;
				}
				else scene->aladin->isStopAnimation = false;

				if (scene->aladin->isPushingWall == true)
				{
					scene->aladin->isPushingWall = false;
					scene->aladin->SetState(ALADIN_STATE_IDLE);
				}
			}
			scene->aladin->countTiming = 0;
			scene->aladin->timeIDLE = 0;

			break;
		case DIK_UP:
			if (scene->aladin->getEnableKey() == true)
			{
				if (scene->aladin->isCollisonWithRope == true)
				{
					scene->aladin->SetState(ALADIN_STATE_TREO);
					scene->aladin->vy = 0;
					scene->aladin->climDirection = 0;
				}
				else
					scene->aladin->SetState(ALADIN_STATE_IDLE);
			}
			break;
		case DIK_DOWN:
			if (scene->aladin->getEnableKey() == true)
			{
				if (scene->aladin->isCollisonWithRope == true)
				{
					scene->aladin->SetState(ALADIN_STATE_TREO);
					scene->aladin->vy = 0;
					scene->aladin->climDirection = 0;
				}
				else
					scene->aladin->SetState(ALADIN_STATE_IDLE);
			}
			break;
		case DIK_C:
			if (scene->aladin->getEnableKey() == true) {
				if (game->IsKeyDown(DIK_DOWN))
					scene->aladin->SetState(ALADIN_STATE_NGOI);
				else
					scene->aladin->SetState(ALADIN_STATE_IDLE);
			}

			break;
		case DIK_X:
			scene->aladin->timeIDLE = 0;
			break;
		}
	}
}
void CSampleKeyHander::KeyState(BYTE* states)
{
	if (currentScene == 1 || currentScene == 2)
	{
		// disable control key when scene->aladin die 
		if (scene->aladin->GetState() == ALADIN_STATE_DIE) return;
		if (scene->aladin->getEnableKey() == true)
		{
			if (game->IsKeyDown(DIK_RIGHT))
			{
				scene->aladin->SetDirection(1);
				scene->aladin->SetState(ALADIN_STATE_DI);
			}
			else if (game->IsKeyDown(DIK_LEFT))
			{
				scene->aladin->SetDirection(-1);
				scene->aladin->SetState(ALADIN_STATE_DI);
			}
			else if (game->IsKeyDown(DIK_UP))
			{
				if (scene->aladin->isCollisonWithRope)
				{
					scene->aladin->SetState(ALADIN_STATE_TREO);
					scene->aladin->vy = -0.1f;
					scene->aladin->x = scene->aladin->xSetCollision;
					scene->aladin->climDirection = 1;
				}
				else
					scene->aladin->SetState(ALADIN_STATE_NGUOC_LEN);

			}
			else if (game->IsKeyDown(DIK_DOWN))
			{
				if (scene->aladin->isCollisonWithRope)
				{
					scene->aladin->SetState(ALADIN_STATE_TREO);
					scene->aladin->vy = 0.1f;
					scene->aladin->x = scene->aladin->xSetCollision;
					scene->aladin->climDirection = -1;
				}
				else
					scene->aladin->SetState(ALADIN_STATE_NGOI);
			}
		}
		/*else
		{
			aladin->SetState(ALADIN_STATE_IDLE);
		}*/
	}
	if (currentScene == 0)
	{
		if (game->IsKeyDown(DIK_UP))
		{
			if (scene_menu->start_ == 0)
				{
					scene_menu->start_ = 1;
				}
			else
				{
					scene_menu->start_ = 0;
				}

			if (scene_menu->exit_ == 0)
				{
					scene_menu->exit_ = 1;
				}
				else
				{
					scene_menu->exit_ = 0;
				}
		}

		else if (game->IsKeyDown(DIK_DOWN))
		{

			if (scene_menu->start_ == 0)
			{
				scene_menu->start_ = 1;
			}
			else
			{
				scene_menu->start_ = 0;
			}

			if (scene_menu->exit_ == 0)
			{
				scene_menu->exit_ = 1;
			}
			else
			{
				scene_menu->exit_ = 0;
			}
		}
		else if (game->IsKeyDown(DIK_SPACE))
		{
			if (scene_menu->start_ == 1)
			{
				scene = scene1;
				currentScene = 1;
				scene1->CreateGrid(objects);
				scene1->LoadResources(objects);
				scene1->ui = UI::GetInstance(scene1->aladin);
			}
			else 
			{
				exit(0);
			}
		}
	}
}
#pragma endregion
//----------------EndKeyBoard----------------------

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and aladin object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/

void CreateGrid(vector <CGameObject *> &objects)
{
	if (currentScene == 1)
		scene1->CreateGrid(objects);
	else if (currentScene == 2)
		scene2->CreateGrid(objects);
	else if (currentScene == 5)
		scene_death->CreateGrid(objects);
	else if (currentScene == 0)
		scene_menu->CreateGrid(objects);
}

void Resources()
{
	// Lay tu file text trong thu muc : textures//temp//resources
	// SU DUNG KHI CAN LOAD LAI OBJECT TRONG MAP
}

void LoadResources()
{
	if (currentScene == 1)
		scene1->LoadResources(objects);
	else if (currentScene == 2)
		scene2->LoadResources(objects);
	else if (currentScene == 3)
		sceneC->LoadResources(objects);
	else if (currentScene == 9)
		sceneC2->LoadResources(objects);
	else if (currentScene == 5)
		scene_death->LoadResources(objects); 
	else if (currentScene == 0)
		scene_menu->LoadResources(objects);
}

void Update(DWORD dt)
{

	if (currentScene == 1 || currentScene == 2)
	{
		if (scene1->aladin->GetX() > nextSceneX&& scene1->aladin->GetY() > nextSceneY&& scene1->aladin->GetY() < nextSceneYx)
		{
			nextSceneX = nextSceneY = nextSceneYx = -128;
		scene1->Clear();
		scene1->objects.clear();
		objects.clear();
		
		currentScene = 3;
		sceneC->LoadResources(objects);
		scene = sceneC;
		checkChange = 1;
		}
	}
	
	if (currentScene == 1 || currentScene == 2)
	{
		if (scene->aladin->lifes <= 0 && scene->aladin->HP <= 0)
		{
			currentScene = 5;
			scene_death->LoadResources(objects);
			scene = scene_death;
		}
	}
	if (checkChange == 1)
	{
		if (sceneC->aladin->GetX() <= 0)
		{
			currentScene = 2;
			scene2->LoadResources(objects);
			scene = scene2;
			checkChange = 0;
		}
	}
	if (currentScene == 2)
	{
		if (scene2->jafar->HP <= 0)
		{
			currentScene = 9;
			sceneC2->LoadResources(objects);
			scene = sceneC2;
		}
	}

	if (currentScene == 1)
		scene1->Update(dt);
	else if (currentScene == 2)
		scene2->Update(dt);
	else if (currentScene == 3)
		sceneC->Update(dt);
	else if (currentScene == 9)
		sceneC2->Update(dt);
	else if (currentScene == 5)
		scene_death->Update(dt);
	else if (currentScene == 0)
		scene_menu->Update(dt);

	if (currentScene == 5)
	{
		if (scene_death->stt_scene == 1)
		{
			currentScene = 0;
			scene = scene_menu;
			scene_menu->LoadResources(objects);
		}
	}
}

/*
	Render a frame 
*/
void Render()
{
	if (currentScene == 1)
		scene1->Render();
	else if (currentScene == 2)
		scene2->Render();
	else if (currentScene == 3)
		sceneC->Render();
	else if (currentScene == 9)
		sceneC2->Render();
	else if (currentScene == 2)
		scene2->Render();
	else if (currentScene == 5)
		scene_death->Render();
	else if (currentScene == 0)
		scene_menu->Render();
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			Render();
			Update(dt);
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((int)time(NULL));

	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	dx_graphics = dxGraphics::GetInstance();
	dx_graphics->Init(hWnd);

	game = CGame::GetInstance();
	game->Init(hWnd);


	camera = Camera::GetInstance();

	//grid = new Grid(MAP_LIMIT_RIGHT, MAP_LIMIT_BOT, 32 * 10);
	scene1 = new Scene1(objects, dx_graphics, camera, game);
	scene2 = new Scene2(objects, dx_graphics, camera, game);
	sceneC = new SceneChange(objects, dx_graphics, camera, game);
	sceneC2 = new SceneChange(objects, dx_graphics, camera, game);
	scene_death = new Scene_Death(objects, dx_graphics, camera, game);
	scene_menu = new Scene_Menu(objects, dx_graphics, camera, game);

	scene = scene_menu;
	//CreateGrid(objects);
	LoadResources();

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 1.5f, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
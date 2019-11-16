/* =============================================================
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
#include "Goomba.h"
#include "Grid.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Aladin X Mario"

#define MAX_FRAME_RATE			120

#define ID_TEX_ALADIN			0
#define ID_TEX_ALADIN_F			01
#define ID_TEX_ENEMY			10
#define ID_TEX_MISC				20
#define ID_TEX_MAP				30
#define ID_TEX_BRICK_2			40

CGame *game;
CAladin *aladin;
Camera *camera;

Grid *grid;

dxGraphics *dx_graphics;
vector<LPGAMEOBJECT> objects;
TileMap *tileMap;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_X:
		aladin->SetState(ALADIN_STATE_JUMP);
		break;
	case DIK_A: // reset
		aladin->SetState(ALADIN_STATE_IDLE);
		aladin->SetPosition(50.0f,0.0f);
		aladin->SetSpeed(0, 0);
		break;
	case DIK_9:
		grid->InitWriteGrid(objects);
		DebugOut(L"[INFO] : Rewrite file gridWrite.txt\n");
		break;
	case DIK_0:
		ofstream ofs;
		ofs.open("textures\\gridWrite.txt", ofstream::out | ofstream::trunc);
		ofs.close();
		DebugOut(L"[INFO] : Clear file gridWrite.txt\n");
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Aladin die 
	if (aladin->GetState() == ALADIN_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		aladin->SetState(ALADIN_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		aladin->SetState(ALADIN_STATE_WALKING_LEFT);
	else
		aladin->SetState(ALADIN_STATE_IDLE);
}

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
void LoadResources()
{
	tileMap = new TileMap();
	tileMap->LoadResource();
	tileMap->ReadMapFile("textures/tileset.txt");

	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(50.f, 0.0f);
	objects.push_back(aladin);

	grid->LoadResourses(objects);

	//CTextures * textures = CTextures::GetInstance();

	//textures->Add(ID_TEX_ALADIN, L"textures\\aladin.png",D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_ALADIN_F, L"textures\\aladin_flip.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	//textures->Add(ID_TEX_MAP, L"textures\\map_tex.png", D3DCOLOR_XRGB(163, 73, 164));
	//textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add(ID_TEX_BRICK_2, L"textures\\tileset.png",(BACKGROUND_COLOR));

	//CSprites * sprites = CSprites::GetInstance();
	//CAnimations * animations = CAnimations::GetInstance();
	//
	//LPDIRECT3DTEXTURE9 texAladin = textures->Get(ID_TEX_ALADIN);
	//LPDIRECT3DTEXTURE9 texAladin_f = textures->Get(ID_TEX_ALADIN_F);
	//// idle right
	//sprites->Add(20001, 3, 9, 37 + 3, 50 + 9, texAladin);
	//sprites->Add(20002, 47, 11, 41 + 47, 47 + 11, texAladin);
	//sprites->Add(20003, 95, 6, 40 + 95, 52 + 6, texAladin);
	//sprites->Add(20004, 143, 3, 44 + 143, 55 + 3, texAladin);
	//sprites->Add(20005, 197, 6, 41 + 197, 51 + 6, texAladin);
	//sprites->Add(20006, 250, 5, 42 + 250, 51 + 5, texAladin);
	//sprites->Add(20007, 303, 2, 44 + 303, 53 + 2, texAladin);		
	////----idle left------
	//sprites->Add(20008, 1081, 9, 1081 + 37, 9 + 50, texAladin_f);
	//sprites->Add(20009, 1033, 11, 1033 + 41, 11 + 47, texAladin_f);
	//sprites->Add(20010, 986, 6, 986 + 40, 6 + 52, texAladin_f);
	//sprites->Add(20011, 934, 3, 934 + 44, 3 + 55, texAladin_f);
	//sprites->Add(20012, 883, 6, 883 + 41, 6 + 51, texAladin_f);
	//sprites->Add(20013, 829, 5, 829 + 42, 5 + 51, texAladin_f);
	//sprites->Add(20014, 774, 2, 774 + 44, 2 + 53, texAladin_f);

	//
	////walk right--------
	//sprites->Add(10002, 66, 1222, 66 + 43, 1222 + 51, texAladin);
	//sprites->Add(10003, 120, 1220, 120 + 41, 1220 + 53, texAladin);
	//sprites->Add(10004, 171, 1216, 171 + 41, 1216 + 57, texAladin);
	//sprites->Add(10005, 220, 1216, 220 + 52, 1216 + 57, texAladin);
	//sprites->Add(10006, 279, 1219, 279 + 46, 1219 + 54, texAladin);
	//sprites->Add(10007, 334, 1215, 334 + 42, 1215 + 58, texAladin);
	//sprites->Add(10008, 386, 1221, 286 + 41, 1221 + 52, texAladin);
	//sprites->Add(10009, 440, 1219, 440 + 35, 1219 + 54, texAladin);
	//sprites->Add(10010, 488, 1216, 488 + 49, 1216 + 57, texAladin);
	//sprites->Add(10011, 547, 1215, 547 + 55, 1215 + 58, texAladin);
	//sprites->Add(10012, 611, 1219, 611 + 55, 1219 + 55, texAladin);
	//sprites->Add(10013, 679, 1218, 679 + 44, 1218 + 57, texAladin); // Walk right

	////----walk left-------
	//sprites->Add(10051, 1012, 1222, 1012 + 43, 1222 + 51, texAladin_f);
	//sprites->Add(10052, 960, 1220, 960 + 41, 1220 + 53, texAladin_f);
	//sprites->Add(10053, 909, 1216, 909 + 41, 1216 + 57, texAladin_f);
	//sprites->Add(10054, 849, 1216, 849 + 52, 1216 + 57, texAladin_f);
	//sprites->Add(10055, 796, 1219, 796 + 46, 1219 + 54, texAladin_f);
	//sprites->Add(10056, 745, 1215, 745 + 42, 1215 + 58, texAladin_f);
	//sprites->Add(10057, 694, 1221, 694 + 41, 1221 + 52, texAladin_f);
	//sprites->Add(10058, 646, 1219, 646 + 35, 1219 + 54, texAladin_f);
	//sprites->Add(10059, 584, 1216, 584 + 49, 1216 + 57, texAladin_f);
	//sprites->Add(10060, 519, 1215, 519 + 55, 1215 + 58, texAladin_f);
	//sprites->Add(10061, 455, 1219, 455 + 55, 1219 + 55, texAladin_f);
	//sprites->Add(10062, 398, 1218, 398 + 44, 1219 + 57, texAladin_f);

	//LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	//sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	//sprites->Add(30002, 25, 14, 41, 29, texEnemy);
	//sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite

	//LPDIRECT3DTEXTURE9 texBrick = textures->Get(ID_TEX_MAP);
	//sprites->Add(40001, 73, 1770, 73 + 34, 1770 + 17, texBrick);
	//// BRICK VER 2
	//LPDIRECT3DTEXTURE9 texBrick2 = textures->Get(ID_TEX_BRICK_2);
	//sprites->Add(40002, 96, 0, 96 + 32, 0 + 32, texBrick2);
	//LPDIRECT3DTEXTURE9 texBrick3 = textures->Get(ID_TEX_BRICK_2);
	//sprites->Add(40003, 512, 0, 512 + 32, 0 + 32, texBrick3);

	////ANIMATION////////////////////////////////
	//LPANIMATION ani;
	//ani = new CAnimation(100);	// idle big right
	//ani->Add(20003);
	//ani->Add(20004);
	//ani->Add(20004);
	//ani->Add(20005);
	//ani->Add(20006);
	//ani->Add(20007);
	//ani->Add(20007);
	//ani->Add(20006);
	//ani->Add(20005);
	//animations->Add(400, ani);

	//ani = new CAnimation(100);	// idle big left
	//ani->Add(20010);
	//ani->Add(20011);
	//ani->Add(20011);
	//ani->Add(20012);
	//ani->Add(20013);
	//ani->Add(20014);
	//ani->Add(20014);
	//ani->Add(20013);
	//ani->Add(20012);
	//animations->Add(401, ani);

	//ani = new CAnimation(100);	// walk right big
	//ani->Add(10003);
	//ani->Add(10004);
	//ani->Add(10005);
	//ani->Add(10006);
	//ani->Add(10007);
	//ani->Add(10009);
	//ani->Add(10010);
	//ani->Add(10011);
	//ani->Add(10012);
	//ani->Add(10013);
	//animations->Add(500, ani);

	//ani = new CAnimation(100);	// // walk left big
	//ani->Add(10051);
	//ani->Add(10052);
	//ani->Add(10053);
	//ani->Add(10054);
	//ani->Add(10055);
	//ani->Add(10056);
	//ani->Add(10057);
	//ani->Add(10058);
	//ani->Add(10059);
	//ani->Add(10060);
	//ani->Add(10061);
	//ani->Add(10062);

	//animations->Add(501, ani);

	//ani = new CAnimation(100);		// brick
	//ani->Add(40001);
	//animations->Add(601, ani);

	//ani = new CAnimation(100);		// brick 2
	//ani->Add(40002);
	//animations->Add(602, ani);

	//ani = new CAnimation(100);		// brick 3
	//ani->Add(40003);
	//animations->Add(603, ani);

	//ani = new CAnimation(300);		// Goomba walk
	//ani->Add(30001);
	//ani->Add(30002);
	//animations->Add(701, ani);

	//ani = new CAnimation(1000);		// Goomba dead
	//ani->Add(30003);
	//animations->Add(702, ani);

	//aladin = new CAladin();
	//aladin->AddAnimation(400);		// idle right big ANI[0]
	//aladin->AddAnimation(401);		// idle left big  ANI[1]

	//aladin->AddAnimation(500);		// walk right big ANI[2]	
	//aladin->AddAnimation(501);		// walk left big  ANI[3]

	//aladin->SetPosition(50.0f, 0);
	//objects.push_back(aladin);

	//for (int i = 0; i < 25; i++)
	//{
	//	CBrick *brick = new CBrick();
	//	brick->id = eType::BRICK;
	//	brick->AddAnimation(601);
	//	brick->SetPosition(34 + i*34, 150);
	//	objects.push_back(brick);
	//}

	//for (int i = 0; i < 54; i++)
	//{
	//	CBrick *brick = new CBrick();
	//	brick->id = eType::BRICK;
	//	brick->AddAnimation(601);
	//	brick->SetPosition(34 + i * 34, 500);
	//	objects.push_back(brick);
	//}

	//for (int  i = 1; i < 19; i++) // brick 2
	//{
	//	CBrick *brick = new CBrick();
	//	brick->id = eType::BRICK2;
	//	brick->AddAnimation(602);
	//	brick->SetPosition(0, i * 32);
	//	objects.push_back(brick);
	//}

	//for (int i = 1; i < 19; i++) // brick 2
	//{
	//	CBrick *brick = new CBrick();
	//	brick->id = eType::BRICK2;
	//	brick->AddAnimation(602);
	//	brick->SetPosition(32 * 59, i * 32);
	//	objects.push_back(brick);
	//}

	//// and Goombas 
	//for (int i = 0; i < 4; i++)
	//{
	//	goomba = new CGoomba();
	//	goomba->AddAnimation(701);
	//	goomba->AddAnimation(702);
	//	goomba->SetPosition(300 + i*60, 135);
	//	goomba->SetState(GOOMBA_STATE_WALKING);
	//	objects.push_back(goomba);
	//}
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Aladin is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}


	// Update camera to follow aladin
	camera->Follow(aladin);
	camera->Update();
}

/*
	Render a frame 
*/
void Render()
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

		tileMap->DrawMap(camera);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
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
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	dx_graphics = dxGraphics::GetInstance();
	dx_graphics->Init(hWnd);

	game = CGame::GetInstance();
	game->Init(hWnd);

	grid = new Grid(32 * 60, 32 * 20, 32 * 10, objects);

	LoadResources();

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	camera = Camera::GetInstance();

	

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 1.5f, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
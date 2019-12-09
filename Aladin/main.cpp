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
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bat.h"
#include "Land.h"
#include "Grid.h"
#include "texSurface.h"

CGame *game;
CAladin *aladin;
Camera *camera;

Grid *grid;

dxGraphics *dx_graphics;
TextSurface *texSur;
vector<LPGAMEOBJECT> objects;
TileMap *tileMap;
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
	switch (KeyCode)
	{
	case DIK_5:
		for (int i = 1; i < grid->cells.size(); i++)
			for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
				if (grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
					grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_ATTACK_LEFT);
		break;
	case DIK_1:
		for (int i = 1; i < grid->cells.size(); i++)
			for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
				if (grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
					grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_ATTACK_RIGHT_MID);
		break;
	case DIK_2:
		for (int i = 1; i < grid->cells.size(); i++)
			for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
				if (grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
					grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_HIT_LEFT);
		break;
	case DIK_3:
		for (int i = 1; i < grid->cells.size(); i++)
			for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
				if (grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
					grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_IDLE_RIGHT);
		break;
	case DIK_4:
		for (int i = 1; i < grid->cells.size(); i++)
			for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
				if (grid->cells[i]->listGameObject[j]->id == eType::ENEMY1)
					grid->cells[i]->listGameObject[j]->SetState(ENEMY1_STATE_RUN_LEFT);
		break;
		//---------hack ??? ---------//
	// ---- ĐÂY LÀ PHẦN PHỤC VỤ CHO TEST VÀ GHI FILE --------------//
	case DIK_HOME:
		aladin->SetX(aladin->GetX() + 50);
		break;
	case DIK_END:
		aladin->SetX(aladin->GetX() - 50);
		break;
	case DIK_9:
		grid->WriteGrid(objects);
		DebugOut(L"[INFO] : Rewrite file gridWrite.txt\n");
		break;
	case DIK_0:
		ofstream ofs;
		ofs.open("textures\\gridWrite1.txt", ofstream::out | ofstream::trunc);
		ofs.close();
		DebugOut(L"[INFO] : Clear file gridWrite.txt\n");
		break;
	
	//---------end test------------//
	}
	//------------------end test ----------------------//
//	switch (KeyCode)
//	{
//
//	case DIK_A: // reset
//		aladin->SetState(ALADIN_STATE_IDLE);
//		aladin->SetPosition(50.0f, 0.0f);
//		aladin->SetSpeed(0, 0);
//		break;
//	case DIK_RIGHT:
//		if (aladin->getEnableKey() == true) {
//			aladin->SetDirection(1);
//			aladin->SetState(ALADIN_STATE_DI);
//		}
//
//		break;
//	case DIK_LEFT:
//		if (aladin->getEnableKey() == true) {
//			aladin->SetDirection(-1);
//			aladin->SetState(ALADIN_STATE_DI);
//		}
//
//		break;
//	case DIK_UP:
//		if (aladin->getEnableKey() == true) {
//			aladin->SetState(ALADIN_STATE_NGUOC_LEN);
//		}
//
//		break;
//	case DIK_DOWN:
//		if (aladin->getEnableKey() == true) {
//			aladin->SetState(ALADIN_STATE_NGOI);
//		}
//
//		break;
//	case DIK_C:
//		if (aladin->getEnableKey() == true) {
//
//			if (aladin->GetState() == ALADIN_STATE_NGOI)
//				aladin->SetState(ALADIN_STATE_NGOI_CHEM);
//			else
//				aladin->SetState(ALADIN_STATE_CHEM);
//		}
//		break;
//	case DIK_X:
//		if (aladin->getEnableKey() == true) {
//			aladin->SetState(ALADIN_STATE_NHAY);
//		}
//		break;
//	case DIK_S:
//		if (aladin->getEnableKey() == true) {
//			aladin->SetState(ALADIN_STATE_CHEM_MANH);
//		}
//		break;
//
//	}
	switch (KeyCode)
	{
	case DIK_A:
		aladin->SetState(ALADIN_STATE_IDLE);
		aladin->SetPosition(50.0f, 0.0f);
		aladin->setEnableKey(true);
		aladin->SetSpeed(0, 0);
		break;
	case DIK_RIGHT:
		if (aladin->getEnableKey() == true) {
			aladin->SetDirection(1);
			aladin->SetState(ALADIN_STATE_DI);
		}
		else {
			if (aladin->getNhay()==true)
				aladin->vx=  ALADIN_WALKING_SPEED;
			
		}
		break;
	case DIK_LEFT:
		if (aladin->getEnableKey() == true) {
			aladin->SetDirection(-1);
			aladin->SetState(ALADIN_STATE_DI);
		}
		else {
			if (aladin->getNhay() == true)
				aladin->vx = -ALADIN_WALKING_SPEED;

		}
		break;
	case DIK_UP:
		if (aladin->getEnableKey() == true) {
			aladin->SetState(ALADIN_STATE_NGUOC_LEN);
			}

		break;
	case DIK_DOWN:
		if (aladin->getEnableKey() == true) {
			aladin->SetState(ALADIN_STATE_NGOI);
		}
		break;
	case DIK_C:
		if (aladin->getEnableKey() == true) {
			aladin->setChem(true);
		}
		break;
	case DIK_X:
		if (aladin->getEnableKey() == true && aladin->GetState()!=ALADIN_STATE_NGOI) {
			aladin->setNhay(true);
		}
		break;
	case DIK_Z:
		if (aladin->getEnableKey() == true ) {
			aladin->setNem(true);
		}
		break;
	
	case DIK_Q:
		aladin->setEnableKey(true);
		break;
	default:
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{	
	case DIK_RIGHT:
		if(aladin->getEnableKey()==true)
		//	if(aladin->GetState()==ALADIN_STATE_DI && aladin->getChem()==false && aladin->getNem() == false && aladin->getNem() == false)
		aladin->SetState(ALADIN_STATE_IDLE);
		break;
	case DIK_LEFT:		
		if (aladin->getEnableKey() == true)
		//	if (aladin->GetState() == ALADIN_STATE_DI && aladin->getChem() == false && aladin->getNem() == false && aladin->getNem() == false)
		aladin->SetState(ALADIN_STATE_IDLE);
		break;
	case DIK_UP:
		if (aladin->getEnableKey() == true)
		aladin->SetState(ALADIN_STATE_IDLE);
		break;
	case DIK_DOWN:
		if (aladin->getEnableKey() == true)
		aladin->SetState(ALADIN_STATE_IDLE);
		break;
	case DIK_C:
		if (aladin->getEnableKey() == true){ 
			if(game->IsKeyDown(DIK_DOWN))
				aladin->SetState(ALADIN_STATE_NGOI); 
			else 
				aladin->SetState(ALADIN_STATE_IDLE);
		}
			
		break;
	}
}
void CSampleKeyHander::KeyState(BYTE* states)
{
	// disable control key when Aladin die 
	if (aladin->GetState() == ALADIN_STATE_DIE) return;
	if (aladin->getEnableKey() == true)
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			aladin->SetDirection(1);
			aladin->SetState(ALADIN_STATE_DI);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			aladin->SetDirection(-1);
			aladin->SetState(ALADIN_STATE_DI);
		}
		else if (game->IsKeyDown(DIK_UP))
		{
			aladin->SetState(ALADIN_STATE_NGUOC_LEN);
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			aladin->SetState(ALADIN_STATE_NGOI);
		}
		
	}
	/*else
	{
		aladin->SetState(ALADIN_STATE_IDLE);
	}*/
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

CGameObject * GetNewObjectEx(int ID)
{
	switch (ID)
	{
	case eType::BRICK:
		return new CBrick();

	case eType::BRICK2:
		return new CBrick();

	case eType::GOOMBA:
		return new CGoomba();

	case eType::ENEMY1:
		return new Enemy1();

	case eType::ENEMY2:
		return new Enemy2();

	case eType::BAT:
		return new Bat();

	case eType::ENEMY3:
		return new Enemy3();

	case eType::LAND:
		return new CLand();

	case eType::LAND1:
		return new CLand();

	case eType::LAND2:
		return new CLand();

	case eType::LAND3:
		return new CLand();
	}
	return NULL;
}

void CreateGrid(vector <CGameObject *> &objects, Grid *&grid)
{
	int numCells, cells_size, columns, rows, width, height;
	int cellID, numObjTypeCell, numObjForType, typeObj;
	ifstream inFile;

	inFile.open("textures\\gridWrite1.txt", ios::in);
  
	CTextures* textures;
	textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MAP, L"textures\\map_tex.png", D3DCOLOR_XRGB(163, 73, 164));
	textures->Add(ID_TEX_BRICK_2, L"textures\\tileset.png", (BACKGROUND_COLOR));
	textures->Add(ID_TEX_LAND, L"textures\\pixel.png", D3DCOLOR_XRGB(255, 255, 255));

	if (inFile.is_open())
	{
		inFile >> numCells >> cells_size >> columns >> rows >> width >> height;
		grid = new Grid(width, height, cells_size);

		for (int n = 1; n <= numCells; n++)
		{
				inFile >> cellID >> numObjTypeCell;
				vector <CGameObject *> l_gameObject;
				grid->AddCell(cellID, l_gameObject);

				if (numObjTypeCell == 0)
				{
					DebugOut(L"Nothing\n");
					continue;
				}
				for (int i = 0; i < numObjTypeCell; i++)
				{
					inFile >> typeObj >> numObjForType;
					for (int j = 0; j < numObjForType; j++)
					{
						float objX, objY;
						inFile >> objX >> objY;
						CGameObject * gameObject = GetNewObjectEx(typeObj);
						gameObject->gridID = cellID;
						gameObject->firstPosX = objX;
						gameObject->firstPosY = objY;
						gameObject->LoadResources(typeObj);
						gameObject->SetPosition(objX, objY);

						objects.push_back(gameObject);
						
						//grid->TestObjInWhatCell(gameObject);
						grid->cells[cellID]->listGameObject.push_back(gameObject);
					}
					DebugOut(L"-----------[Doc file]\n");
			}
		}
	}
}

void Resources()
{
	// Lay tu file text trong thu muc : textures//temp//resources
	// SU DUNG KHI CAN LOAD LAI OBJECT TRONG MAP
}

void LoadResources()
{
	tileMap = new TileMap();
	tileMap->LoadResource();
	tileMap->ReadMapFile("textures/tile_map.txt");

	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(100.f, 0.0f);
	objects.push_back(aladin);

	texSur = new TextSurface();
	texSur->LoadResources(eType::TEXSURFACE);

	//Resources();
	//grid->LoadResourses(objects, aladin);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Aladin is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	//vector<LPGAMEOBJECT> coObjects;
	//for (int i = 1; i < objects.size(); i++)
	//{
	//	coObjects.push_back(objects[i]);
	//}

	//for (int i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Update(dt,&coObjects);
	//}

	grid->UpdateCollision(dt, aladin);

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

		/*for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();*/
		aladin->Render();
		grid->RenderObjectEx(camera, objects);
		texSur->Render();

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
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	dx_graphics = dxGraphics::GetInstance();
	dx_graphics->Init(hWnd);

	game = CGame::GetInstance();
	game->Init(hWnd);

	//grid = new Grid(MAP_LIMIT_RIGHT, MAP_LIMIT_BOT, 32 * 10);

	CreateGrid(objects, grid);

	LoadResources();

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	camera = Camera::GetInstance();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 1.5f, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
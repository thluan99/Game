#include "Scene1.h"



Scene1::Scene1()
{
}

Scene1::Scene1(vector<LPGAMEOBJECT> objects, dxGraphics * dx_graphics,
	Camera * camera, CGame * game)
{
	this->objects = objects;
	this->dx_graphics = dx_graphics;
	this->camera = camera;
	this->game = game;
}

CGameObject * Scene1::GetNewObjectEx(int ID)
{
	switch (ID)
	{
	case eType::BRICK:
		return new CBrick();

	case eType::BRICK2:
		return new CBrick();

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

	case eType::APPLE:
		return new Apple();
	}
	return NULL;
}

void Scene1::CreateGrid(vector<CGameObject*>& objects)
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
	this->objects = objects;
	this->grid = grid;
}

void Scene1::LoadResources(vector<CGameObject*> &objects)
{
	tileMap = new TileMap();
	tileMap->LoadResource(L"textures/tile_map.png");
	tileMap->ReadMapFile("textures/tile_map.txt");

	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(50.f, 1000.0f);
	objects.push_back(aladin);

	texSur = new TextSurface();
	texSur->LoadResources(eType::TEXSURFACE);

	//load apple
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_APPLE, L"textures\\aladin.png", D3DCOLOR_XRGB(255, 0, 255));
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textAPPLE = textures->Get(ID_TEX_APPLE);
	// idle
	LPANIMATION ani;
	sprites->Add(200, 373, 24, 373 + 7, 24 + 7, textAPPLE);
	ani = new CAnimation(100);
	ani->Add(200);
	animations->Add(999, ani);
	// die
	sprites->Add(201, 394, 23, 394 + 7, 23 + 10, textAPPLE);
	sprites->Add(202, 414, 18, 414 + 20, 18 + 18, textAPPLE);
	sprites->Add(203, 444, 16, 444 + 29, 16 + 22, textAPPLE);
	sprites->Add(204, 485, 14, 485 + 31, 14 + 25, textAPPLE);
	sprites->Add(205, 532, 13, 532 + 30, 13 + 27, textAPPLE);
	ani = new CAnimation(100);
	ani->Add(201);
	ani->Add(202);
	ani->Add(203);
	ani->Add(204);
	ani->Add(205);
	animations->Add(998, ani);

	apple = new Apple();
}

void Scene1::Update(DWORD dt)
{
	grid->UpdateCollision(dt, aladin);
	for (int i = 0; i < listApples.size(); i++)
	{
		if (listApples[i]->getNem() == true)
		{
			listApples[i]->Update(dt);
			//DebugOut(L"============ %d\n", listApples[i]->GetX());
		}
	}

	for (int i = 0; i < listApples.size(); i++)
	{
		if (abs(listApples[i]->staticX - listApples[i]->GetX()) > 1000)
		{
			listApples.erase(listApples.begin() + i);
			OutputDebugString(L"xóa doi tuong");
		}
	}
	// Update camera to follow aladin
	camera->Follow(aladin);
	camera->Update(1);

	if (aladin->GetX() > MAP_LIMIT_RIGHT - 50)
		aladin->SetX(MAP_LIMIT_RIGHT - 50);
	if (aladin->GetX() < 0) aladin->SetX(0);
	if (aladin->GetY() < 0) aladin->SetY(0);
}

void Scene1::Render()
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

		for (int i = listApples.size() - 1; i >= 0; i--)
		{
			if (listApples[i]->getNem() == true)
			{
				listApples[i]->Render();
				//DebugOut(L"============ %d\n", listApples[i]->GetX());
			}
		}
		grid->RenderObjectEx(camera, objects);

		texSur->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void Scene1::Clear()
{
	grid->ClearGrid();
	tileMap->ClearMap();
}


Scene1::~Scene1()
{
}

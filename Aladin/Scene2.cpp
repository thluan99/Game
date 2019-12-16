#include "Scene2.h"



Scene2::Scene2()
{
}

Scene2::Scene2(vector<LPGAMEOBJECT> objects, dxGraphics * dx_graphics,
	Camera * camera, CGame * game)
{
	this->objects = objects;
	this->dx_graphics = dx_graphics;
	this->camera = camera;
	this->game = game;
}

CGameObject * Scene2::GetNewObjectEx(int ID)
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

	case eType::M2LAND:
		return new CLand();

	case eType::APPLE:
		return new Apple();
	}
	return NULL;
}

void Scene2::CreateGrid(vector<CGameObject*>& objects)
{
	int numCells, cells_size, columns, rows, width, height;
	int cellID, numObjTypeCell, numObjForType, typeObj;
	ifstream inFile;

	inFile.open("textures\\Scene2\\gridWrite2.txt", ios::in);

	CTextures* textures;
	textures = CTextures::GetInstance();

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

void Scene2::LoadResources(vector<CGameObject*> &objects)
{
	tileMap = new TileMap();
	tileMap->LoadResource(L"textures/Scene2/tile_map2.png");
	tileMap->ReadMapFile("textures/Scene2/tile_map2.txt");

	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(50.f, 100.0f);
	objects.push_back(aladin);

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
	//this->Resources(objects);

	apple = new Apple();

	this->objects = objects;
}

void Scene2::Resources(vector<CGameObject*> &objects)
{
	CLand *land = new CLand();
	land->LoadResources(M2LAND);
	land->SetPosition(0, 384 + 16);
	objects.push_back(land);
}

void Scene2::Update(DWORD dt)
{
	camera->Follow(aladin);
	camera->Update(2);

	grid->UpdateCollision(dt, aladin);
	for (int i = 0; i < listApples.size(); i++)
	{
		if (listApples[i]->getNem() == true)
		{
			listApples[i]->Update(dt);


			DebugOut(L"============ %d\n", listApples[i]->GetX());
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

	if (aladin->GetX() > MAP2_LIMIT_RIGHT - 50)
		aladin->SetX(MAP2_LIMIT_RIGHT - 50);
	if (aladin->GetX() < 0) aladin->SetX(0);
	if (aladin->GetY() < 0) aladin->SetY(0);
}

void Scene2::Render()
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
		if (apple->getNem() == true)
			apple->Render();
		grid->RenderObjectEx(camera, objects);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


Scene2::~Scene2()
{
}

#include "Scene1.h"
#include <math.h>


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
	this->aladin = new CAladin();
}

CGameObject * Scene1::GetNewObjectEx(int ID)
{
	switch (ID)
	{
	case eType::BRICK:
		return new CBrick();

	case eType::BRICK2:
		return new CBrick();

	case eType::BRICKLINE:
		return new CBrick();

	case eType::BRICKv2:
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

	case eType::ROPE:
		return new CLand();

	case eType::ROPE_TRIGGER:
		return new CLand();

	case eType::ITEMAPPLE:
		return new ItemApple ();

	case eType::ITEMGENIE:
		return new ItemGenie();

	case eType::ITEMRUBY:
		return new ItemRuby();

	case eType::ITEMHEATH:
		return new ItemsExHeath();

	case eType::ITEMPOT:
		return new PositionPot();

	case eType::SHOP:
		return new Shop();
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
	textures->Add(ID_TEX_ITEM, L"textures\\item.png", D3DCOLOR_XRGB(248, 0, 248));
	textures->Add(ID_TEX_SHOP, L"textures\\shop.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_EXgENIE, L"textures\\eDie.png", D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_EXPLOSION, L"textures\\explosionE.png", BACKGROUND_COLOR);
	textures->Add(ID_TEX_ENEMY1, L"textures\\enemy1.png", D3DCOLOR_XRGB(120, 193, 152));
	textures->Add(ID_TEX_ENEMY1_FLIP, L"textures\\enemy1_flip.png", D3DCOLOR_XRGB(120, 193, 152));
	textures->Add(ID_TEX_ITEM_COLLECT, L"textures\\item_collect.png", BACKGROUND_COLOR);
	textures->Add(ID_TEX_ENEMY2, L"textures\\enemy2.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMY2_FLIP, L"textures\\enemy2_flip.png", D3DCOLOR_XRGB(255, 0, 255));

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

					if (gameObject->id == eType::BAT)
					{
						Bat* bat = dynamic_cast<Bat*>(gameObject);
						bat->SetPositionDefault(objX, objY);
					}

					objects.push_back(gameObject);

					//grid->TestObjInWhatCell(gameObject);
					grid->cells[cellID]->listGameObject.push_back(gameObject);
				}
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
	aladin->xReborn = aladin->x;
	aladin->yReborn = aladin->y;
	objects.push_back(aladin);

	ui = UI::GetInstance(aladin);
	ui->LoadResources();

	texSur = new TextSurface();
	texSur->LoadResources(eType::TEXSURFACE);

	//load apple
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();

	textures->Add(ID_TEX_APPLE, L"textures\\aladin.png", D3DCOLOR_XRGB(255, 0, 255));

	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 textAPPLE = textures->Get(ID_TEX_APPLE);
	LPDIRECT3DTEXTURE9 tex_Enemy2 = textures->Get(ID_TEX_ENEMY2);
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

void Scene1::Resources()
{
}

void Scene1::Update(DWORD dt)
{
	// ---------- update apple----///
	Apple *app = new Apple();
	int isAppNull = 1;
	for (int i = 1; i <= grid->cells.size(); i++)
	{
		for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
		{
			if (grid->cells[i]->listGameObject[j]->id == eType::APPLE)
			{
				app = dynamic_cast<Apple*>(grid->cells[i]->listGameObject[j]);
				if (abs(app->staticX - app->GetX() > 1000))
					grid->cells[i]->listGameObject.erase(grid->cells[i]->listGameObject.begin() + j);
				else isAppNull = 0;
			}
		}
	}

	if (isAppNull == 0)
	{
		for (int i = 1; i <= grid->cells.size(); i++)
		{
			if (grid->isInCell(app, grid->cells[i]->x, grid->cells[i]->y))
			{
				int hApp = 0;
				for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
				{
					if ((grid->cells[i]->listGameObject[j]->GetId() == eType::APPLE))
					{
						hApp = 1;
						break;
					}
				}
				if (hApp == 0)
					grid->cells[i]->listGameObject.push_back(app);
			}
			else
			{
				for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
					if (grid->cells[i]->listGameObject[j]->GetId() == eType::APPLE)
						grid->cells[i]->listGameObject.erase(grid->cells[i]->listGameObject.begin() + j);
			}

		}
	}
	//-----------------
	Sword * so = new Sword();
	int isNull = 1;
	for (int i = 1; i <= grid->cells.size(); i++)
	{
		for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
			if (grid->cells[i]->listGameObject[j]->GetId() == eType::SWORD)
			{
				so = dynamic_cast<Sword*>(grid->cells[i]->listGameObject[j]);
				isNull = 0;
			}				
	}
	if (isNull == 0)
	{
		for (int i = 1; i <= grid->cells.size(); i++)
		{
			if (grid->isInCell(so, grid->cells[i]->x, grid->cells[i]->y))
				grid->cells[i]->listGameObject.push_back(so);
			else
				for (int j = 0; j < grid->cells[i]->listGameObject.size(); j++)
					if (grid->cells[i]->listGameObject[j]->GetId() == eType::SWORD)
						grid->cells[i]->listGameObject.erase(grid->cells[i]->listGameObject.begin() + j);
		}
	}


	for (int i = 1; i <= grid->cells.size(); i++)
	{
		for (int j = 0; j < grid->cells.at(i)->listGameObject.size(); j++)
		{
			Bat* bat = dynamic_cast<Bat*>(grid->cells.at(i)->listGameObject[j]);
			Enemy2* enemy2 = dynamic_cast<Enemy2*>(grid->cells.at(i)->listGameObject[j]);

			if (grid->cells[i]->listGameObject[j]->id != eType::APPLE)
			{
				if (aladin->GetX() > grid->cells[i]->listGameObject[j]->GetX())
					grid->cells[i]->listGameObject[j]->SetDirection(1);
				else grid->cells[i]->listGameObject[j]->SetDirection(-1);
			}

			if (grid->cells[i]->listGameObject[j]->id == eType::SWORD)
			{
				if (aladin->direction == 1)
				{
					sword->SetDirection(1);
					if (grid->cells[i]->listGameObject[j]->x > aladin->x + ALADIN_BIG_BBOX_WIDTH * 1.5)
						grid->cells[i]->listGameObject.erase(grid->cells[i]->listGameObject.begin() + j);
				}
				else
				{
					sword->SetDirection(-1);
					if (grid->cells[i]->listGameObject[j]->x < aladin->x - ALADIN_BIG_BBOX_WIDTH * 1.5)
						grid->cells[i]->listGameObject.erase(grid->cells[i]->listGameObject.begin() + j);
				}
			}

			if (bat)
			{
				if (bat->isDeath == false)
				{

					if ((aladin->x >= bat->GetActiveRange().left && aladin->x <= bat->GetActiveRange().right)
						&& (aladin->y >= bat->GetActiveRange().top && aladin->y <= bat->GetActiveRange().bottom))
					{
						bat->SetState(BAT_STATE_WAKEUP);
					}
					else
					{
						if (bat->GetState() != BAT_STATE_IDLE)
						{
							bat->SetState(BAT_STATE_FLY);
							//bat->SetPosition(bat->x_default, bat->y_default);
							if (abs(bat->x_default - bat->x) <= 5.0f && abs(bat->y_default - bat->y) <= 5.0f)
							{
								bat->SetPosition(bat->x_default, bat->y_default);
								bat->SetState(BAT_STATE_IDLE);
							}
						}

					}

					if (bat->GetState() == BAT_STATE_WAKEUP)
					{
						//GoToXY(x, y, coObjects->at(i)->x, coObjects->at(i)->y);
						bat->GoToXY(bat->x, bat->y, aladin->x, aladin->y);
					}
					else if (bat->GetState() == BAT_STATE_FLY)
					{
						bat->GoToXY(bat->x, bat->y, bat->x_default, bat->y_default);
					}
					else if (bat->GetState() == BAT_STATE_DIE || bat->GetState() == BAT_STATE_FLYING)
					{
						bat->vx = 0;
					}
				}
			}
			if (enemy2)
			{
				if ((aladin->x >= enemy2->GetActiveRange().left && aladin->x <= enemy2->GetActiveRange().right)
					&& (aladin->y >= enemy2->GetActiveRange().top && aladin->y <= enemy2->GetActiveRange().bottom))
				{
					if (enemy2->GetState() != ENEMY2_STATE_DIE)
						enemy2->SetState(ENEMY2_STATE_ACTIVE);
				}
				
				if (enemy2->trigger == 1)
				{
					for (int i = 0; i < 6; i++)
					{
						Bone* bone = new Bone();
						bone->LoadResources(BONE);
						bone->SetPosition(enemy2->x, enemy2->y);
						listBone.push_back(bone);
					}
					enemy2->trigger = 0;
					enemy2->SetState(ENEMY2_STATE_DIE);
				}
			}
		}
	}

	grid->UpdateCollision(dt, aladin);
	
	//for (int i = 0; i < listApples.size(); i++)
	//{
	//	if (listApples[i]->getNem() == true)
	//	{
	//		listApples[i]->Update(dt);
	//		//DebugOut(L"============ %d\n", listApples[i]->GetX());
	//	}
	//}
	vector<LPGAMEOBJECT>* l_aladin = new vector<LPGAMEOBJECT>();
	l_aladin->push_back(aladin);

	for (int i = listBone.size() - 1; i >= 0; i--)
	{
		listBone[i]->Update(dt, l_aladin);
	}

	for (int i = 0; i < listApples.size(); i++)
	{
		if (abs(listApples[i]->staticX - listApples[i]->GetX()) > 1000)
		{
			listApples.erase(listApples.begin() + i);
			OutputDebugString(L"x�a doi tuong");
		}
	}
	// Update camera to follow aladin
	camera->Follow(aladin);
	camera->Update(1);

	if (aladin->GetX() > MAP_LIMIT_RIGHT - 50)
		aladin->SetX(MAP_LIMIT_RIGHT - 50);
	if (aladin->GetX() < 0) aladin->SetX(0);
	if (aladin->GetY() < 0) aladin->SetY(0);

	ui->Update(dt);
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

		/*for (int i = listApples.size() - 1; i >= 0; i--)
		{
			if (listApples[i]->getNem() == true)
			{
				listApples[i]->Render();
			}
		}*/

		for (int i = listBone.size() - 1; i >= 0; i--)
		{
			listBone[i]->Render();
		}

		grid->RenderObjectEx(camera, objects);
		aladin->Render();
		texSur->Render();
		ui->Render();

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

#include "Scene2.h"



Scene2::Scene2()
{
	objects.clear();
}

Scene2::Scene2(vector<LPGAMEOBJECT> objects, dxGraphics * dx_graphics,
	Camera * camera, CGame * game)
{
	this->objects = objects;
	this->dx_graphics = dx_graphics;
	this->camera = camera;
	this->game = game;
	objects.clear();
}

CGameObject * Scene2::GetNewObjectEx(int ID)
{
	switch (ID)
	{
	case eType::M2LAND:
		return new CLand();

	case eType::APPLE:
		return new Apple();

	case eType::JAFAR:
		return new Jafar();

	case eType::FIREATTACK:
		return new FireAttack();
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
	//map2bk = new TileMap();
	//map2bk->LoadResource(L"textures/Scene2/tile_map22.png");
	//map2bk->ReadMapFile("textures/Scene2/tile_map22.txt");

	tileMap = new TileMap();
	tileMap->LoadResource(L"textures/Scene2/tile_map2.png");
	tileMap->ReadMapFile("textures/Scene2/tile_map2.txt");

	bk2 = new TextSurface();
	bk2->LoadResources(eType::BACKGROUND2);
	bk2->SetPosition(0, 0);

	aladin = new CAladin();
	aladin->LoadResources(eType::ALADIN);
	aladin->SetPosition(50.f, 100.0f);
	objects.push_back(aladin);

	jafar = new Jafar();
	jafar->LoadResources(eType::JAFAR);
	jafar->SetPosition(400.0f, 280.0f);
	objects.push_back(jafar);

	angFire = new FireAngry();
	angFire->LoadResources(eType::ANGFIRE);

	fireAttack = new FireAttack();
	fireAttack->LoadResources(eType::FIREATTACK);
	fireAttack->xFirst = jafar->x;
	fireAttack->SetPosition(jafar->x + 20, jafar->y + 50);
	listFire.push_back(fireAttack);
	objects.push_back(fireAttack);

	star = new Star();
	star->LoadResources(eType::STAR);
	star->SetPosition(jafar->x, jafar->y + 20);
	objects.push_back(star);

	land = new CLand();
	land->LoadResources(eType::M2LAND);
	land->SetPosition(0, 376);
	objects.push_back(land);

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
	//objects.push_back(apple);
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
	vector<LPGAMEOBJECT> coObjects;

	camera->Follow(aladin);
	camera->Update(2);

	// GIOI HAN DUOI CUA ALADIN
	if (aladin->y > limit - ALADIN_BIG_BBOX_HEIGHT) aladin->y = limit - ALADIN_BIG_BBOX_HEIGHT;
	if (aladin->x < limitLeft) aladin->x = limitLeft;
	if (aladin->x > limitRight) aladin->x = limitRight;
	// HP > BIEN HINH && HP < BIEN HINH
	if (jafar->HP > jafar->henshinState)
	{          
		if (jafar->GetX() > aladin->GetX())
			jafar->SetState(JAFAR_STATE_ATTACK_L);
		else jafar->SetState(JAFAR_STATE_ATTACK_R);
	}
	else if (jafar->HP <= jafar->henshinState)
	{
		if (jafar->GetX() >= aladin->GetX())
			jafar->SetState(JAFAR_STATE_SNAKE_AT_L);
		else jafar->SetState(JAFAR_STATE_SNAKE_AT_R);
	}

	for (int i = 0; i < listApples.size(); i++)
	{
		if (abs(listApples[i]->staticX - listApples[i]->GetX()) > 1000)
		{
			listApples.erase(listApples.begin() + i);
			OutputDebugString(L"xóa doi tuong");
		}
	}

	//--------------------------------------------

	//grid->UpdateCollision(dt, aladin);
	// CAC SAO SE DI CHUYEN VE HUONG ALADIN
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->id == eType::STAR)
		{
			if (aladin->x > objects[i]->x) objects[i]->x = objects[i]->x + 2.8f;
			if (aladin->x < objects[i]->x) objects[i]->x = objects[i]->x - 2.8f;
			if (aladin->y > objects[i]->y) objects[i]->y = objects[i]->y + 2.8f;
			if (aladin->y < objects[i]->y) objects[i]->y = objects[i]->y - 2.8f;
		}
	// TAO FIREATTACK VA SAO
	for (int i = 0; i < objects.size(); i++)
	{
		if (jafar->HP <= jafar->henshinState)
		{
			if (objects[i]->id == eType::FIREATTACK && objects[i]->fireFlag == false)
			{
				if (abs(jafar->GetX() - objects[i]->GetX()) > 200)
				{
					FireAttack *freAttack = new FireAttack();
					freAttack->LoadResources(eType::FIREATTACK);
					freAttack->xFirst = jafar->x;
					freAttack->SetPosition(jafar->x + 20, jafar->y + 50);
					if (aladin->GetX() > jafar->GetX())
						freAttack->direction = 1;
					else freAttack->direction = -1;
					objects.push_back(freAttack);
					objects[i]->fireFlag = true;
				}
			}
			if (objects[i]->id == eType::FIREATTACK &&
				(abs(jafar->GetX() - objects[i]->GetX()) > 300))
			{
				objects.erase(objects.begin() + i);
				DebugOut(L"Xoa lua!");
			}
		}
		else
		{
			if (objects[i]->id == eType::STAR && objects[i]->fireFlag == false)
			{
				if (abs((jafar->GetX() + 20) - objects[i]->GetX()) > 30)
				{
					Star *s = new Star();
					s->LoadResources(eType::STAR);
					if (jafar->GetX() < aladin->GetX())
						s->SetPosition(jafar->x + 20, jafar->y + 20);
					else s->SetPosition(jafar->x + 20, jafar->y + 20);
					objects.push_back(s);
					objects[i]->fireFlag = true;
				}
			}

			if (objects[i]->id == eType::STAR)
			{
				if (objects[i]->GetState() == STAR_STATE_DESTROY)
				{
					Star *s = dynamic_cast<Star*>(objects[i]);
					if (aladin->GetX() < jafar->GetX())
						aladin->vx = +0.1f;
					else aladin->vx = -0.1f;
					objects.erase(objects.begin() + i);
					DebugOut(L"Xoa star============");
				}
			}
		}

	}

	// THEM SAO KHI DI VE BEN PHAI
	int countStar = 0;
	for (int i = 0; i < objects.size(); i++)
		if (jafar->HP > jafar->henshinState && objects[i]->id == eType::STAR)
			countStar++;
	if (countStar == 0 && jafar->HP > jafar->henshinState)
	{
		Star *s = new Star();
		s->LoadResources(eType::STAR);
		if (jafar->direction = 1)
			s->SetPosition(jafar->x + 20, jafar->y + 20);
		else s->SetPosition(jafar->x, jafar->y + 20);
		objects.push_back(s);
	}
	else if (countStar != 0 && jafar->HP <= jafar->henshinState)
		for (int i = 0; i < objects.size(); i++)
			if (objects[i]->id == eType::STAR)
				objects.erase(objects.begin() + i);
	// CAP NHAT TRANG THAI ALADIN KHI SAO TRUNG TOA DO VOI ALADIN
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->id == eType::STAR && jafar->HP > jafar->henshinState)
		{
			int space = ALADIN_BIG_BBOX_WIDTH;
			if (aladin->direction == -1) space = 0;
			if (objects[i]->GetX() > aladin->GetX() - 5 && objects[i]->GetX() < aladin->GetX() + space &&
				objects[i]->GetY() > aladin->GetY() - 5)
			{
				objects[i]->SetState(STAR_STATE_DESTROY);
				DebugOut(L"Out put aladin == star");
			}
		}

	//-----

	//----////----//---//--/-/-/-/-//-//-/-----//

	// ADD OBJECTS VAO LIST DE XET COLISION
	for (int i = 0; i < objects.size(); i++)
	{
		if (jafar->HP > jafar->henshinState)
			if (objects[i]->id == eType::FIREATTACK)
				continue;
		coObjects.push_back(objects[i]);
	}
	// XET COLLISION
	for (int i = 0; i < objects.size(); i++)
	{
		if (jafar->HP > jafar->henshinState)
			if (objects[i]->id == eType::FIREATTACK)
				continue;
		if (objects[i]->id == eType::APPLE)
		{
			Apple *a = dynamic_cast<Apple*>(objects[i]);
			if (a->getNem() == true)
				objects[i]->Update(dt, &coObjects);
			continue;
		}
		objects[i]->Update(dt, &coObjects);
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

		//map2bk->DrawMap(camera);
		bk2->Render();
		tileMap->DrawMap(camera);

		if (apple->getNem() == true)
			apple->Render();

		/*for (int i = listApples.size() - 1; i >= 0; i--)
		{
			if (listApples[i]->getNem() == true)
			{
				listApples[i]->Render();
			}
		}*/
		if (jafar->HP <= jafar->henshinState)
			angFire->Render();
		//grid->RenderObjectEx(camera, objects);
		//jafar->Render();
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->id == eType::ALADIN)
				continue;
			if (jafar->HP > jafar->henshinState)
				if (objects[i]->id == eType::FIREATTACK)
					continue;
			objects[i]->Render();
		}	
		aladin->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


Scene2::~Scene2()
{
}

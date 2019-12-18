#include "Grid.h"
#include"debug.h"

using namespace std;

Grid::Grid(int width, int height, int cell_Size)
{
	this->cell_Size = cell_Size;
	this->rows = (height - 1) / this->cell_Size + 1;
	this->collums = (width - 1) / this->cell_Size + 1;

	//Giữ lấy object 
	//InitWriteGrid(objects);
}
#pragma region Old AddCell
void Grid::Add(int ID, int x, int y, vector<CGameObject*> l_gameObject)
{
	Cell *cell = new Cell();
	cell->ID = ID;
	cell->x = x;
	cell->y = y;
	cell->listGameObject = l_gameObject;
	cells[ID] = cell;
}
#pragma endregion

#pragma region Old WriteFile
void Grid::WriteFile(ofstream &outF, int ID, int x, int y, int ObjID, int objx, int objy)
{
	if (outF.is_open())
		outF << ID << " " << x << " " << y << " " << ObjID << " " << objx << " " << objy << endl;
}

void Grid::InitWriteGrid(vector<LPGAMEOBJECT> objects)
{
	int count = 1;
	SetFile("textures\\gridWrite.txt");
	//mở file, ghi map xuống grid
	ofstream outF(gridPathWrite, ios::out | ios::trunc);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < collums; j++)
		{
			int posX, posY;
			vector<CGameObject *> listGameObject;
			//add cell vao cells 

			//lay thong so toa do cua cell
			posX = j;
			posY = i;

			for (int k = 0; k < objects.size(); k++)
			{
				//nếu nằm trong cell thì thêm vào list
				if (isInCell(objects[k], posX, posY))
				{
					listGameObject.push_back(objects[k]);
					WriteFile(outF, count, posX, posY, objects[k]->id, objects[k]->x, objects[k]->y);
					DebugOut(L"[]");
				}
			}

			//thêm list gameobject vào cell
			Add(count, posX, posY, listGameObject);
			DebugOut(L"\n[INFO] : Cell thu %d, %d, %d \n", count, posX, posY);
			count++;
		}
	outF.close();//đóng file
}
#pragma endregion

#pragma region Old LoadResources
CGameObject * GetNewObject(int ID)
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
	}
	return NULL;
}

void Grid::LoadResourses(vector<LPGAMEOBJECT> &objects, CAladin * aladin)
{
	int ID, objID;
	float x, y, objX, objY;
	ifstream inFile;
	//SetFile("textures\\gridWrite.txt");
	int flagEx = 0;

	inFile.open("textures\\gridWrite.txt", ios::in);

	if (inFile.is_open())
	{
		CGameObject* object;

		while (!inFile.eof())
		{
			inFile >> ID >> x >> y >> objID >> objX >> objY;
			while (ID > flagEx)
			{
				vector<CGameObject*> listGameObj;
				flagEx = flagEx + 1;
				Add(flagEx, x, y, listGameObj);
			}

			CGameObject * object = GetNewObject(objID);
			object->gridID = ID;
			object->firstPosX = objX;
			object->firstPosY = objY;

			object->LoadResources(objID);
			object->SetPosition(objX, objY);

			objects.push_back(object);

			cells[ID]->listGameObject.push_back(object);
			DebugOut(L"[INFO] : doc file");
		}
		cout << endl;
	}
	inFile.close();
}

#pragma endregion

//hàm xét object có trong 1 cell nào hay không
#pragma region IsInCell
bool Grid::isInCell(LPGAMEOBJECT gameObject, int cellPosX, int cellPosY)
{
	float left, top, right, bottom;
	gameObject->GetBoundingBox(left, top, right, bottom);
	float objX = gameObject->x;
	float objY = gameObject->y;
	//objX objY toa độ của x, y của object
	//cellPosX cellPosY cột và hàng của object trong Grid

	if (
		//góc  trên bên trái
		((int)objX / cell_Size == cellPosX && (int)objY / cell_Size == cellPosY) ||
		//góc trên bên phải
		((int)(objX + (right - left)) / cell_Size == cellPosX && (int)objY / cell_Size == cellPosY) ||
		//góc dưới bên trái
		((int)(objY + (bottom - top)) / cell_Size == cellPosY && (int)objX / cell_Size == cellPosX) ||
		//góc dưới bên phải
		((int)(objY + (bottom - top)) / cell_Size == cellPosY && (int)(objX + (right - left)) / cell_Size == cellPosX)
		)
		return true;
	return false;
}
bool Grid::isInCellMin(LPGAMEOBJECT gameObject, int cellPosX, int cellPosY)
{
	float left, top, right, bot;
	gameObject->GetBoundingBox(left, top, right, bot);
	float objX = gameObject->x;
	float objY = gameObject->y;
	if ((int)objX / cell_Size == cellPosX && (int)objY / cell_Size == cellPosY)
		return true;
	return false;
}

#pragma endregion

void Grid::AddCell(int ID, vector<CGameObject*> l_gameObject)
{
	Cell *cell = new Cell();
	cell->ID = ID;
	cell->x = (ID - 1) - collums*(int)((ID - 1)/collums);
	cell->y = (ID - 1) / collums;
	cell->listGameObject = l_gameObject;
	cells[ID] = cell;
}

void Grid::TestObjInWhatCell(CGameObject * obj)
{
	for (int i = 1; i <= cells.size(); i++)
		if (isInCell(obj, cells[i]->x, cells[i]->y) == true)
			cells[i]->listGameObject.push_back(obj);
}

void Grid::WriteGrid(vector<CGameObject *> objects)
{
	int countIDCell = 1;
	ofstream outF("textures\\gridWrite1.txt", ios::out | ios::trunc);

	collums = (MAP_LIMIT_RIGHT - 1)/ cell_Size + 1;
	rows = (MAP_LIMIT_BOT - 1) / cell_Size + 1;
	int numCells = collums*rows;

	if (outF.is_open())
	{		
		// số ô << kích thước ô << số cột << số hàng
		outF << numCells << " " << cell_Size << " " << collums << " " << rows << " " << MAP_LIMIT_RIGHT << " " << MAP_LIMIT_BOT << endl;

		for (int i = 1; i <= numCells; i++)
		{
			vector<CGameObject*> listO;
			if (cells[i] == NULL)
				AddCell(i, listO);

			int flagObjID = -1;		// cờ đổi loại obj
			int flagObjIDCount = 0;	// cờ đếm số loại obj trong 1 cell
			outF << countIDCell;															// Ghi so thu tu ô
			for (int j = 0; j < cells[i]->listGameObject.size(); j++)
			{
				if (flagObjID != cells[i]->listGameObject[j]->id)
				{
					flagObjIDCount++;
					flagObjID = cells[i]->listGameObject[j]->id;
				}
			}
			outF << " " << flagObjIDCount;

			flagObjID = -1;

			for (int j = 0; j < cells[i]->listGameObject.size(); j++)
			{
				if (flagObjID != cells[i]->listGameObject[j]->id)					// Mỗi ô được ghi thành 1 hàng
				{
					int countObjType = 0;											// Biến đếm số lg obj của 1 đối tượng
					vector <CGameObject *> listObjType;								// list chứa obj giống nhau		

					flagObjID = cells[i]->listGameObject[j]->id;
					for (int k = 0; k < cells[i]->listGameObject.size(); k++)
					{
						if (flagObjID == cells[i]->listGameObject[k]->id)
						{
							listObjType.push_back(cells[i]->listGameObject[k]);
							countObjType++;
						}
					}
					outF << " " << flagObjID << " " << countObjType;
					int objx, objy;
					for (int k = 0; k < listObjType.size(); k++)
						outF << " " << listObjType[k]->x << " " << listObjType[k]->y;
				}
			}
			outF << endl;

			countIDCell++;
		}
	}
}

#pragma region OldRender
void Grid::RenderObject(Camera * &camera, vector<LPGAMEOBJECT> &objects)
{
	int left = (camera->cameraX - SCREEN_WIDTH / 2) / cell_Size;
	int top = (camera->cameraY - SCREEN_HEIGHT / 2) / cell_Size;
	int right = (camera->cameraX + SCREEN_WIDTH / 2) / cell_Size;
	int bot = (camera->cameraY + SCREEN_HEIGHT / 2) / cell_Size;
	int countID;
	int setLeftCount = left + 1;

	for (int i = top; i <= bot; i++)
	{
		countID = setLeftCount;
		for (int j = left; j <= right; j++)
		{
			for (int k = 0; k < objects.size(); k++)
			{
				if (objects[k]->gridID == countID)
				{
					objects[k]->Render();
					//DebugOut(L"\n[INFO] : Render Object");
				}
			}
			countID++;
		}
		setLeftCount = setLeftCount + collums;
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->x < left*cell_Size || objects[i]->y < top*cell_Size || objects[i]->x > right*cell_Size + cell_Size || objects[i]->y > bot*cell_Size + cell_Size)
		{
			objects[i]->ReLoad();
		}
	}
}

#pragma endregion

void Grid::RenderObjectEx(Camera *camera, vector<LPGAMEOBJECT> &objects)
{
	for (int n = 1; n <= cells.size(); n++)
	{
		if (isCellInCamera(camera, cells[n]) == true)
		{
			if (!cells[n]->listGameObjectTemp.empty())
				for (int j = 0; j < cells[n]->listGameObjectTemp.size(); j++)
					cells[n]->listGameObject.push_back(cells[n]->listGameObjectTemp[j]);
			if (!cells[n]->listGameObject.empty())
				for (int i = 0; i < cells[n]->listGameObject.size(); i++)
				{
					cells[n]->listGameObject[i]->ReLoad();
					cells[n]->listGameObject[i]->Render();
				}
			cells[n]->listGameObjectTemp.clear();
			//(L"[INFO] : clear temp list");
		}
		else
		{	
			if (!cells[n]->listGameObject.empty())
				for (int i = 0; i < cells[n]->listGameObject.size(); i++)
					cells[n]->listGameObjectTemp.push_back(cells[n]->listGameObject[i]);
			cells[n]->listGameObject.clear();
			//DebugOut(L"[INFO] : clear list");
		}
	}
}

bool Grid::isCellInCamera(Camera *camera, Cell *cell)
{
	int left = (camera->cameraX - SCREEN_WIDTH / 2) / cell_Size;
	int top = (camera->cameraY - SCREEN_HEIGHT / 2) / cell_Size;
	int right = (camera->cameraX + SCREEN_WIDTH / 2) / cell_Size;
	int bot = (camera->cameraY + SCREEN_HEIGHT / 2) / cell_Size;

	if (cell->x >= left && cell->x <= right && cell->y >= top && cell->y <= bot)
		return true;
	return false;
}

void Grid::UpdateCollision(DWORD dt, CAladin *&aladin)
{
	vector<CGameObject*> coObj4Aladin;
	for (int i = 1; i <= cells.size(); i++)
	{
		vector <CGameObject*> coObjects;
		for (int j = 0; j < cells[i]->listGameObject.size(); j++)
		{
			if (isInCell(aladin, cells[i]->x, cells[i]->y))
			{
				coObj4Aladin.push_back(cells[i]->listGameObject[j]);
			}

			coObjects.push_back(cells[i]->listGameObject[j]);
		/*if (isInCell(aladin, cells[i]->x, cells[i]->y))
			aladin->Update(dt, &coObjects);*/
		}
		for (int j = 0; j < cells[i]->listGameObject.size(); j++)
			cells[i]->listGameObject[j]->Update(dt, &coObjects);
	}
	aladin->Update(dt, &coObj4Aladin);
}

Cell* Grid::Get(int ID)
{
	return cells[ID];
}

Grid::~Grid()
{
	ClearGrid();
}

void Grid::ClearGrid()
{
	for (int i = 1; i <= cells.size(); i++)
		cells[i]->listGameObject.clear();
	cells.clear();
}

void Grid::SetFile(char * str)
{
	gridPathWrite = str;
}
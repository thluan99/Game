#include "Grid.h"
#include"debug.h"

using namespace std;

Grid::Grid(int width, int height, int cell_Size, vector<LPGAMEOBJECT> objects)
{
	this->cell_Size = cell_Size;
	this->rows = height / this->cell_Size;
	this->collums = width / this->cell_Size;

	//Giữ lấy object 
	//InitWriteGrid(objects);
}

void Grid::Add(int ID, int x, int y, list<CGameObject*> l_gameObject)
{
	Cell *cell = new Cell();
	cell->ID = ID;
	cell->x = x;
	cell->y = y;
	cell->listGameObject = l_gameObject;
	cells[ID] = cell;
}

void Grid::InitWriteGrid(vector<LPGAMEOBJECT> objects)
{
	int count = 1;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < collums; j++)
		{
			int posX, posY;
			list<CGameObject *> listGameObject;
			//add cell vao cells 

			//lay thong so 
			posX = j;
			posY = i;

			for (int k = 0; k < objects.size(); k++)
			{
				float left, top, right, bot;
				objects[k]->GetBoundingBox(left, top, right, bot);
				float objX = objects[k]->x;
				float objY = objects[k]->y;

				if ((int)objX / cell_Size == posX && (int)objY / cell_Size == posY)
				{
					listGameObject.push_back(objects[k]);
					WriteFile(count, posX, posY, objects[k]->id, objX, objY);
					DebugOut(L"[]");
				}
				else if ((int)(objX + (right - left)) / cell_Size == posX && (int)objY / cell_Size == posY)
				{
					listGameObject.push_back(objects[k]);
					WriteFile(count, posX, posY, objects[k]->id, objX, objY);
					DebugOut(L"[]");
				}
				else if ((int)objY / cell_Size == posY && (int)(objX + (right - left)) / cell_Size == posX)
				{
					listGameObject.push_back(objects[k]);
					WriteFile(count, posX, posY, objects[k]->id, objX, objY);
					DebugOut(L"[]");
				}
				else if ((int)(objY + (bot - top)) / cell_Size == posY && (int)(objX + (right - left)) / cell_Size == posX)
				{
					listGameObject.push_back(objects[k]);
					WriteFile(count, posX, posY, objects[k]->id, objX, objY);
					DebugOut(L"[]");
				}
			}
			Add(count, posX, posY, listGameObject);
			DebugOut(L"\n[INFO] : Cell thu %d, %d, %d \n", count, posX, posY);
			count++;
		}
}

void Grid::WriteFile(int ID, int x, int y, int ObjID, int objx, int objy)
{
	SetFile("textures\\gridWrite.txt");
	ofstream outF(gridPathWrite, ios::out|ios::app);
	if (outF.is_open())
		outF << ID << " "<< x << " " << y << " " << ObjID << " " << objx << " " << objy << endl;
	outF.close();
}

CGameObject * GetNewObject(int ID)
{
	switch (ID)
	{
	case eType::BRICK:
		return new CBrick();

	case eType::BRICK2:
		return new CBrick();

	case eType::GOOMBA:
		return new CGoomba();
	}
	return NULL;
}

void Grid::LoadResourses(vector<LPGAMEOBJECT> &objects)
{
	int ID, objID;
	float x, y, objX, objY;
	ifstream inFile;
	//SetFile("textures\\gridWrite.txt");

	inFile.open("textures\\gridWrite.txt", ios::in);

	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile >> ID >> x >> y >> objID >> objX >> objY;
			CGameObject * object = GetNewObject(objID);
			object->LoadResources(objID);
			object->SetPosition(objX, objY);
	
			objects.push_back(object);
			DebugOut(L"[INFO] : doc file");
		}
		cout << endl;
	}
	inFile.close();
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
	cells.clear();
}

void Grid::SetFile(char * str)
{
	gridPathWrite = str;
}

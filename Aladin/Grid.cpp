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
	SetFile("textures\\gridWrite.txt");
	//mở file, ghi map xuống grid
	ofstream outF(gridPathWrite, ios::out | ios::trunc);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < collums; j++)
		{
			int posX, posY;
			list<CGameObject *> listGameObject;
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

//hàm xét object có trong 1 cell nào hay không
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

void Grid::WriteFile(ofstream &outF, int ID, int x, int y, int ObjID, int objx, int objy)
{
	
	if (outF.is_open())
		outF << ID << " "<< x << " " << y << " " << ObjID << " " << objx << " " << objy << endl;
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
		CGameObject* object;

		while (!inFile.eof())
		{
			inFile >> ID >> x >> y >> objID >> objX >> objY;
			object = GetNewObject(objID);
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



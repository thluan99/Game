#ifndef _GRID_H
#define _GRID_H

#include <vector>
#include <map>
#include "Sprites.h"
#include "GameObject.h"
#include "Brick.h"
#include "Goomba.h"
#include "Define.h"
#include "Aladin.h"
#include "Camera.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include <fstream>
#include <iostream>

using namespace std;

typedef struct StructCell
{
	int ID;
	int x, y;

	vector<CGameObject *> listGameObject;
	vector<CGameObject *> listGameObjectTemp;

}Cell;


class Grid
{
private:

	int rows, collums;
	char * gridPathWrite;
public:
	//Lưu các đối tượng vào mảng
	unordered_map<int, Cell *> cells;

public:
	int cell_Size;

	void Add(int ID, int x, int y, vector<CGameObject*>);
	void AddCell(int ID, vector<CGameObject*> l_gameObject);
	void TestObjInWhatCell(CGameObject * obj);
	void InitWriteGrid(vector<LPGAMEOBJECT> objects);
	void WriteGrid(vector<CGameObject*> objects);
	Cell* Get(int ID);

	Grid(int width, int height, int size_Cell);
	~Grid();

	void ClearGrid();
	void SetFile(char *str);
	bool isInCell(LPGAMEOBJECT, int cellPosX, int cellPosY);
	bool isInCellMin(LPGAMEOBJECT gameObject, int cellPosX, int cellPosY);
	void WriteFile(ofstream &outF, int ID, int x, int y, int ObjID, int objx, int objy);
	void RenderObject(Camera *&camera, vector<LPGAMEOBJECT> &objects);
	void RenderObjectEx(Camera * camera, vector<LPGAMEOBJECT>& objects);
	bool isCellInCamera(Camera * camera, Cell * cell);
	void LoadResourses(vector<LPGAMEOBJECT> &objects, CAladin * aladin);

	void UpdateCollision(DWORD dt, CAladin *&aladin);

};
#endif // !_GRID_H

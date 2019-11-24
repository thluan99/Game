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
#include <fstream>
#include <iostream>

using namespace std;

typedef struct StructCell
{
	int ID;
	int x, y;

	list<CGameObject *> listGameObject;

}Cell;


class Grid
{
private:

	int rows, collums;
	char * gridPathWrite;

	//Lưu các đối tượng vào mảng
	unordered_map<int, Cell *> cells;

public:
	int cell_Size;

	void Add(int ID, int x, int y, list<CGameObject*>);
	void InitWriteGrid(vector<LPGAMEOBJECT> objects);
	Cell* Get(int ID);

	Grid(int width, int height, int size_Cell, vector<LPGAMEOBJECT> objects);
	~Grid();

	void ClearGrid();
	void SetFile(char *str);sss
	bool isInCell(LPGAMEOBJECT, int cellPosX, int cellPosY);
	void WriteFile(ofstream &outF, int ID, int x, int y, int ObjID, int objx, int objy);
	void RenderObject(Camera *&camera, vector<LPGAMEOBJECT> &objects);
	void LoadResourses(vector<LPGAMEOBJECT> &objects);

};
#endif // !_GRID_H

#ifndef _GRID_H
#define _GRID_H

#include <vector>
#include <map>
#include "Sprites.h"
#include "GameObject.h"
#include <fstream>

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
	int cell_Size;
	int rows, collums;
	char * gridPathWrite;

	//Lưu các đối tượng vào mảng
	unordered_map<int, Cell *> cells;

public:
	

	void Add(int ID, int x, int y, list<CGameObject*>);
	void InitWriteGrid(vector<LPGAMEOBJECT> objects);
	Cell* Get(int ID);

	Grid(int width, int height, int size_Cell, vector<LPGAMEOBJECT> objects);
	~Grid();

	void ClearGrid();
	void SetFile(char *str);
	void WriteFile(int ID, int x, int y, int ObjID, int objx, int objy);

};
#endif // !_GRID_H

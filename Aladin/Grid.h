#ifndef _GRID_H
#define _GRID_H

#include <vector>
#include "Sprites.h"

using namespace std;

class Grid
{
private:
	int cell_Size;
	int rows, collums;

	//Lưu các đối tượng vào mảng
	vector<CSprite *> *cells;

public:
	Grid(int width, int height, int size_Cell);
	~Grid();

	void ClearGrid();
};

#endif // !_GRID_H
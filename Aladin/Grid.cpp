#include "Grid.h"

Grid::Grid(int width, int height, int size_Cell)
{
	this->rows = height / cell_Size;
	this->collums = width / cell_Size;

	//Giữ lấy object 
	cells = new vector<CSprite*>[rows * collums];
}

Grid::~Grid()
{
	delete[] cells;
}

void Grid::ClearGrid()
{
	for (int i = 0; i < rows * collums; i++)
	{
		cells[i].clear();
	}
}
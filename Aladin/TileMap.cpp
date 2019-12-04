#include "TileMap.h"
#include "debug.h"

Tile::Tile(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	this->tileSize = TILE_SIZE;
}



Tiles *Tiles::__instance = NULL;

Tiles *Tiles::GetInstance()
{
	if (__instance == NULL) __instance = new Tiles();
	return __instance;
}

void Tiles::AddTile(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	Tile *s = new Tile(id, left, top, right, bottom, tex);
	tiles[id] = s;
}

Tile* Tiles::Get(int ID)
{
	return tiles[ID];
}

//TileMap
//=====================================
//Doc file text mặc định là tileset.txt
//=====================================
void TileMap::ReadMapFile(char* filename)
{
	ifstream reader(filename);

	if (reader.fail())
		MessageBox(NULL, L"LOI khong tim thay file ", L"ERROR", MB_OK);

	reader  >> rows_Tile >> columns_Tile; //dong dau tien ROWS COLUMNS
	for (int i = 0; i < rows_Tile; i++)
	{
		for (int j = 0; j < columns_Tile; j++)
		{
			//lưu giá trị đọc được vào mảng
			reader >> tile_Map[i][j];
		}
	}
	reader.close();
}


//=====================================
//Vẽ map lên màn hình lấy nguồn từ tiles, tiles được tạo và có giá trị từ hàm  LoadResources()
//=====================================
void TileMap::DrawMap(Camera *camera)
{
	Tiles *tiles = Tiles::GetInstance();
	for (int i = 0; i < rows_Tile; i++)
	{
		for (int j = 0; j < columns_Tile; j++)
		{
			if (tile_Map[i][j] != 0 && isInCamera(j,i,camera)) // kiểm tra cell nào trong cam thì render ra
			{
				//Vì j là columns nên nó sẽ gắn liền với giá trị tọa độ x, i là y
				tiles->Get(tile_Map[i][j])->Draw(j*TILE_SIZE, i*TILE_SIZE);
			}			
		}
	}
}

//====================================
//kiểm tra cell có trong grid
//====================================
bool TileMap::isInCamera(int x, int y, Camera* camera)
{
	if ((x * TILE_SIZE >= camera->GetXCam() - camera->GetWidth() / 2 - TILE_SIZE ||
		x * TILE_SIZE <= camera->GetXCam() + camera->GetWidth() / 2) &&
		(y * TILE_SIZE >= camera->GetYCam() - camera->GetHeight() / 2 - TILE_SIZE ||
			y * TILE_SIZE <= camera->GetYCam() + camera->GetHeight() / 2))
		return true;
	else
		return false;

}


//======================================
//Hàm này thực hiện cắt file ảnh tileset rồi lưu từng ảnh vào tiles.
//======================================
void TileMap::LoadResource()
{
	CTextures *textures = CTextures::GetInstance();

	textures->Add(ID_TEX_TILE_SET, FILE_PATH, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texTileSet = textures->Get(ID_TEX_TILE_SET);
	D3DXIMAGE_INFO info;
	HRESULT re = D3DXGetImageInfoFromFile(FILE_PATH, &info);
	if (re != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", FILE_PATH);
		return;
	}

	int rows = info.Height / TILE_SIZE;
	int columns = info.Width / TILE_SIZE;

	//Tạo đối tượng tiles để chứa ảnh cắt
	Tiles *tiles = Tiles::GetInstance();
	int count = 1;

	//Cắt ảnh
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			tiles->AddTile(count, j * TILE_SIZE, i * TILE_SIZE, j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE, texTileSet);
			//Cộng số lên để đánh ID cho từng ảnh riêng lẻ
			count++;
		}
}

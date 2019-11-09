#pragma once
#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Define.h"

class dxGraphics
{
public:
	static dxGraphics * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
public:

	static dxGraphics * GetInstance();
	void Init(HWND);
	dxGraphics();
	~dxGraphics();
};


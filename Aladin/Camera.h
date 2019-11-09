#ifndef CAMERA_H
#define	CAMERA_H

#include <DirectXMath.h>
#include "Sprites.h"
#include "Aladin.h"
#include "dxGraphics.h"

class Camera
{
public:
	Camera(int width, int height, float, DirectX::XMFLOAT3 scaleFactors);
	static Camera * GetInstance();
	~Camera();

	//Game fun
	void Update();
	void Follow(CAladin *following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform(dxGraphics* ) const;
	float cameraX;
	float cameraY;
	float GetXCam() { return cameraX; }
	float GetYCam() { return cameraY; }
	void SetXCam(float camx) { this->cameraX = camx; }
	void SetYCam(float camy) { this->cameraY = camy; }

	int GetHeight() { return height; }
	int GetWidth() { return width; }

private:
	static Camera * __instance;

	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	CAladin *following;

	int height;
	int width;
	float angle;

};
#endif/*Camera.h*/
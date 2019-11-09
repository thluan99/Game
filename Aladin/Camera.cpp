#include "Camera.h"


Camera * Camera::__instance = NULL;

Camera::Camera(int width, int height,float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->scaleFactors = scaleFactors;
	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f); //doan nay khong hieu 
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::~Camera()
{

}

void Camera::Follow(CAladin * following)
{
	this->following = following;
}

void Camera::Unfollow()
{
	this->following = nullptr;
}

bool Camera::IsFollowing() const
{
	return this->following != nullptr;
}

void Camera::Update()
{
	//cameraX = width / 2, cameraY = height / 2;

	if (this->following)
	{
		this->following->GetPosition(cameraX, cameraY);
	}

	//doan nay khong can thiet 
	this->viewMatrix = D3DXMATRIX(
		1, 0 , 0, 0,
		0, 1 , 0, 0,
		0, 0 , 1 ,0,
		0, 0 , 0, 1
	);

	//doan nay cung khong can thiet
	this->identityMatrix._22 = -1.0f;
	this->identityMatrix._41 = -cameraX;
	this->identityMatrix._42 = 600;
}

void Camera::SetTransform(dxGraphics *dx_Graphics) const
{
	
	dxGraphics::GetInstance()->d3ddv->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	//dxGraphics::GetInstance()->d3ddv->SetTransform(D3DTS_WORLD, &identityMatrix);
	//dxGraphics::GetInstance()->d3ddv->SetTransform(D3DTS_VIEW, &viewMatrix);
}

Camera *Camera::GetInstance()
{
	if (__instance == NULL) __instance =  new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	return __instance;
}
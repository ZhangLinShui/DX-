#pragma once
#include "Object.h"
class CCamera :
	public CObject
{
public:
	CCamera();
	~CCamera();
	BOOL Init(TiXmlElement *node);
	void InitCamera(D3DXVECTOR3 Pos);
	void SetCamera();
	D3DXVECTOR3&  GetRightDir();
	D3DXVECTOR3&  GetUpDir();
	D3DXVECTOR3&  GetForwordDir();
	void SetRightDir(D3DXVECTOR3 dir);
	void SetUpDir(D3DXVECTOR3 dir);
	void SetForwordDir(D3DXVECTOR3 dir);
	float GetCamareToObjectDist();
private:
	D3DXVECTOR3 cameraRightDir;
	D3DXVECTOR3 cameraUpDir;
	D3DXVECTOR3 cameraForwordDir;
	float CamareToObjectDist;
	D3DXMATRIX matView;//π€≤Ïæÿ’Û
	D3DXMATRIX matProj;//Õ∂”∞æÿ’Û
	LPDIRECT3DDEVICE9  m_pDevice;
	HWND m_hwnd;
};


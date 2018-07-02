#pragma once
#include "Object.h"
struct CUSTOMVERTEX1
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	DWORD color;
};
struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos;
	DWORD color;
	D3DXVECTOR2 texUV;
};
struct CUSTOMVERTEX2//客户纹理 texture 缩写
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	DWORD color;
	D3DXVECTOR2 texUV;
	D3DXVECTOR2 texUV2;
};
#define D3DXFVF_CUSTOMVERTEX   D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1
#define D3DXFVF_CUSTOMVERTEX1   D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_NORMAL
#define D3DXFVF_CUSTOMVERTEX2   D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX2|D3DFVF_NORMAL

class CRenderObject :
	public CObject
{
public:
	CRenderObject();
	~CRenderObject();
	void SetWorldMatrix(D3DXMATRIX mat) { matWorld = mat; }
	D3DXMATRIX&	  GetmatWorld();
	D3DXVECTOR3&  GetRightDir();
	D3DXVECTOR3&  GetUpDir();
	D3DXVECTOR3&  GetForwordDir();
	D3DXVECTOR3&  GetCurrentDir();
	void SetmatWorld();
	void SetRightDir(D3DXVECTOR3 dir);
	void SetUpDir(D3DXVECTOR3 dir);
	void SetForwordDir(D3DXVECTOR3 dir);
	void SetCurrentDir(D3DXVECTOR3 dir);

	D3DXMATRIX GetWorldMatrix() { return matWorld; }
protected:
	D3DXMATRIX   matWorld;
	D3DXVECTOR3  RightDir;
	D3DXVECTOR3  UpDir;
	D3DXVECTOR3  ForwordDir;
	D3DXVECTOR3  CurrentDir;//人物当前的水平朝向
	LPDIRECT3DDEVICE9 m_pDeive;
};


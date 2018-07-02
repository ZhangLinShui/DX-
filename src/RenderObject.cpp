#include "stdafx.h"
#include "RenderObject.h"


CRenderObject::CRenderObject()
{
}


CRenderObject::~CRenderObject()
{
}

D3DXMATRIX& CRenderObject::GetmatWorld()
{
	return matWorld;
}
D3DXVECTOR3& CRenderObject::GetRightDir()
{
	return RightDir;
}
D3DXVECTOR3& CRenderObject::GetUpDir()
{
	return UpDir;
}
D3DXVECTOR3& CRenderObject::GetForwordDir()
{
	return ForwordDir;
}

D3DXVECTOR3& CRenderObject::GetCurrentDir()
{
	return CurrentDir;
}

void CRenderObject::SetmatWorld()
{
	D3DXMatrixIdentity(&matWorld);
	matWorld._11 = RightDir.	x;		matWorld._12 = RightDir.	y;		matWorld._13 = RightDir.	z;
	matWorld._21 = UpDir.		x;		matWorld._22 = UpDir.		y;		matWorld._23 = UpDir.		z;
	matWorld._31 = ForwordDir.	x;		matWorld._32 = ForwordDir.	y;		matWorld._33 = ForwordDir.	z;
	matWorld._41 = GetPos().	x;		matWorld._42 = GetPos().	y;		matWorld._43 = GetPos().	z;
	/*D3DXMATRIX mat;
	D3DXMatrixScaling(&mat, 2, 2, 2);
	matWorld = mat*matWorld;*/
}
void CRenderObject::SetRightDir(D3DXVECTOR3 dir)
{
	RightDir = dir;
}

void CRenderObject::SetUpDir(D3DXVECTOR3 dir)
{
	UpDir = dir;
}

void CRenderObject::SetForwordDir(D3DXVECTOR3 dir)
{
	ForwordDir = dir;
}

void CRenderObject::SetCurrentDir(D3DXVECTOR3 dir)
{
	CurrentDir = dir;
}

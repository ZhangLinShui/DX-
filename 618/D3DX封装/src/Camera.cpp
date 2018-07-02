#include "stdafx.h"
#include "Camera.h"


CCamera::CCamera()
{
	m_lType = OB_TYPE_CAMERA;
}

CCamera::~CCamera()
{
}

BOOL CCamera::Init(TiXmlElement *node)
{
	TiXmlElement* childnode = node->FirstChildElement("Pos");
	m_vPos.x = atof(childnode->Attribute("x"));
	m_vPos.y = atof(childnode->Attribute("y"));
	m_vPos.z = atof(childnode->Attribute("z"));
	D3DXVECTOR3 Pos2;//看向的位置
	childnode = node->FirstChildElement("Pos2");
	Pos2.x = atof(childnode->Attribute("x"));
	Pos2.y = atof(childnode->Attribute("y"));
	Pos2.z = atof(childnode->Attribute("z"));
	InitCamera(Pos2);
	return TRUE;
}

void CCamera::InitCamera(D3DXVECTOR3 Pos)
{
	cameraUpDir = { 0, 1, 0 };
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResource("设备接口");
	m_hwnd = (HWND)CPlatform::GetsinglenPtr()->FindResource("窗口句柄");
	RECT rc;
	GetClientRect(m_hwnd, &rc);
	D3DXMATRIX matProject;
	D3DXMatrixIdentity(&matProject);
	D3DXMatrixPerspectiveFovLH(&matProject, D3DX_PI / 4, rc.right*1.0f / rc.bottom, 0.1, 10000);//创建透视矩阵 截头体视场
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProject);
	cameraForwordDir = Pos - m_vPos;
	CamareToObjectDist = D3DXVec3Length(&cameraForwordDir);
	D3DXVec3Normalize(&cameraForwordDir, &cameraForwordDir);
	D3DXVec3Cross(&cameraRightDir, &cameraUpDir, &cameraForwordDir);
	D3DXVec3Cross(&cameraUpDir, &cameraForwordDir, &cameraRightDir);
}
void CCamera::SetCamera()
{
	D3DXMatrixIdentity(&matView);//观察矩阵
	matView._11 = cameraRightDir.x; matView._21 = cameraRightDir.y; matView._31 = cameraRightDir.z;
	matView._12 = cameraUpDir.x; matView._22 = cameraUpDir.y; matView._32 = cameraUpDir.z;
	matView._13 = cameraForwordDir.x; matView._23 = cameraForwordDir.y; matView._33 = cameraForwordDir.z;
	matView._41 = -D3DXVec3Dot(&GetPos(), &cameraRightDir);
	matView._42 = -D3DXVec3Dot(&GetPos(), &cameraUpDir);
	matView._43 = -D3DXVec3Dot(&GetPos(), &cameraForwordDir);
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
}

D3DXVECTOR3& CCamera::GetRightDir()
{
	return cameraRightDir;
}

D3DXVECTOR3& CCamera::GetUpDir()
{
	return cameraUpDir;
}

D3DXVECTOR3& CCamera::GetForwordDir()
{
	return cameraForwordDir;
}

void CCamera::SetRightDir(D3DXVECTOR3 dir)
{
	cameraRightDir = dir;
}

void CCamera::SetUpDir(D3DXVECTOR3 dir)
{
	cameraUpDir = dir;
}

void CCamera::SetForwordDir(D3DXVECTOR3 dir)
{
	cameraForwordDir = dir;
}

float CCamera::GetCamareToObjectDist()
{
	return CamareToObjectDist;
}

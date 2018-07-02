#pragma once


#include "RenderObject.h"
#include ".\character.h"

class CPlayer :public CRenderObject
{
public:
	MyEnum player_stage;
	CPlayer();
	~CPlayer();
	BOOL Init(TiXmlElement* node);
	void Draw();
	void						SetAnimation(enMotionType perAni) { m_pMeshDate->ChangeMotionType(perAni); }
	D3DXMATRIX GetMatInverse() { return m_matInverse; }
	D3DXVECTOR3 GetMin() 
	{
		return D3DXMin; 
	}
	CUSTOMVERTEXLINE&Getstart(int i) 
	{ 
		return start[i]; }
private:
	string m_TextruePath;
	LPD3DXMESH m_Mesh;
	DWORD g_dwNumMaterail;
	vector<LPDIRECT3DTEXTURE9> g_vecTex;
	D3DMATERIAL9 g_Material;
	LPD3DXMESH m_pSphereMesh;
	D3DXVECTOR3 pCenter;
	D3DXMATRIX              m_matInverse;

	CCharacter *m_pMeshDate;

	float r;
	float m_fMoveSpeed;
	float Roate, Scalex, Scaley, Scalez;
	float					RoteX, RoteY, RoteZ;
	/******************************画线**********************************/
	
	CUSTOMVERTEXLINE line[8];
	CUSTOMVERTEXLINE start[6];
	/******************************画线**********************************/

	/****************************包围盒********************/
	LPD3DXMESH					m_BoxMesh;
	WORD						*m_BoxIndex;
	CUSTOMVERTEX1				*m_CustomBoxVer;
	DWORD						NumFaces;
	DWORD						NumVertices;
	D3DXVECTOR3					D3DXMin;
	D3DXVECTOR3					D3DXMax;
	/****************************包围盒********************/
	
};
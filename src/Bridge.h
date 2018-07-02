#pragma once
#include "RenderObject.h"
class CBridge :
	public CRenderObject
{
public:
	CBridge();
	~CBridge();
	BOOL Init(TiXmlElement *node);
	void Draw();
	D3DXMATRIX GetMatInverse();
	LPD3DXMESH GetMesh();
	void CreatBox();
private:
	LPD3DXMESH					m_Mesh;
	DWORD						m_dwNumMaterail;
	vector<LPDIRECT3DTEXTURE9>  m_vecTex;
	vector<D3DMATERIAL9>		m_vecMatera;
	D3DXMATRIX					m_matInverse;
	D3DMATERIAL9				g_Material;
	/****************************АќЮЇКа********************/
	LPD3DXMESH					m_BoxMesh;
	WORD						*m_BoxIndex;
	CUSTOMVERTEX1				*m_CustomBoxVer;
	DWORD						NumFaces;
	DWORD						NumVertices;
	D3DXVECTOR3					D3DXMin;
	D3DXVECTOR3					D3DXMax;
	/****************************АќЮЇКа********************/
};


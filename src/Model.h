#pragma once
#include "RenderObject.h"
class CModel :
	public CRenderObject
{
public:
	CModel();
	~CModel();
public:
	BOOL Init(TiXmlElement* element);
	void Draw();
	LPD3DXMESH GetMesh();
	LPD3DXMESH GetBoxMesh();
	//CubePoints& GetVertexBuffers() { return VertexBuffer; }
	void CreatBox();
	D3DXVECTOR3 GetVertex(int i);
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVB;			//顶点缓冲接口指针
	LPDIRECT3DINDEXBUFFER9				m_pIB;			//索引缓冲接口指针
	vector<LPDIRECT3DTEXTURE9>			g_vecTex;
	vector<D3DMATERIAL9>				g_vecMaterail;
	DWORD								g_dNumMaterail;
	LPD3DXMESH							m_Mesh;
	//D3DXVECTOR3							D3DXMin;
	//D3DXVECTOR3							D3DXMax;
	//CubePoints							VertexBuffer;//包围盒和顶点
	/****************************包围盒********************/
	LPD3DXMESH							m_BoxMesh;
	WORD								*m_BoxIndex;
	CUSTOMVERTEX1						*m_CustomBoxVer;
	DWORD								NumFaces;
	DWORD								NumVertices;
	D3DXVECTOR3							D3DXMin;
	D3DXVECTOR3							D3DXMax;
	/****************************包围盒********************/
};


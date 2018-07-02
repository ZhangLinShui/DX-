#pragma once
#include "RenderObject.h"
class CHourse :
	public CRenderObject
{
public:
	CHourse();
	~CHourse();
	BOOL Init(TiXmlElement *node);
	void Draw();
	D3DXMATRIX GetMatInverse();
	LPD3DXMESH GetMesh();
private:
	LPD3DXMESH m_Mesh;
	DWORD m_dwNumMaterail;
	vector<LPDIRECT3DTEXTURE9> m_vecTex;
	vector<D3DMATERIAL9>        m_vecMatera;
	D3DXMATRIX                 m_matInverse;
	D3DMATERIAL9 g_Material;
};


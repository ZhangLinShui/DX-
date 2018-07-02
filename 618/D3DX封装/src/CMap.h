#pragma once
#include "RenderObject.h"
class CCMap :
	public CRenderObject
{
public:
	CCMap();
	~CCMap();
	void CreateMap(DWORD row, DWORD col, DWORD width, DWORD height, D3DXVECTOR3 pos, DWORD color);
	BOOL Init(TiXmlElement *name);
	void SetMapColor(DWORD color)
	{
		colorTerrain = color;
	}
	void Draw();
	DWORD GetWidth();
	DWORD GetHeight();
	D3DXVECTOR3 GetPosY(D3DXVECTOR3 pos);
	D3DXMATRIX GetMatInverse();
	LPD3DXMESH GetMesh();
private:
	LPD3DXMESH m_Mesh;
	CUSTOMVERTEX2 *m_CustomVer;//顶点数组
	unsigned short aa ;
	DWORD  *m_Index;//顶点索引数组
	DWORD colorTerrain;
	int VertexNum;//顶点数组的个数 
	int IndexNum;//矩形的个数*6顶点索引的个数
	CPicture *MapHighImage;
	LPDIRECT3DTEXTURE9 m_pText;
	LPDIRECT3DTEXTURE9 m_pText2;
	LPDIRECT3DVERTEXBUFFER9 m_pVerBuff;//顶点缓冲接口指针
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuff;//索引缓冲接口指针
	DWORD width;
	DWORD height;
	DWORD Width;
	DWORD Height;
	D3DMATERIAL9 g_Material;
	D3DXMATRIX m_matInverse;
};


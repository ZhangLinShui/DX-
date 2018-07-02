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
	CUSTOMVERTEX2 *m_CustomVer;//��������
	unsigned short aa ;
	DWORD  *m_Index;//������������
	DWORD colorTerrain;
	int VertexNum;//��������ĸ��� 
	int IndexNum;//���εĸ���*6���������ĸ���
	CPicture *MapHighImage;
	LPDIRECT3DTEXTURE9 m_pText;
	LPDIRECT3DTEXTURE9 m_pText2;
	LPDIRECT3DVERTEXBUFFER9 m_pVerBuff;//���㻺��ӿ�ָ��
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuff;//��������ӿ�ָ��
	DWORD width;
	DWORD height;
	DWORD Width;
	DWORD Height;
	D3DMATERIAL9 g_Material;
	D3DXMATRIX m_matInverse;
};


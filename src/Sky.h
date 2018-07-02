#pragma once
#include "RenderObject.h"
class CSky :
	public CRenderObject
{
public:
	CSky();
	~CSky();
	BOOL Init(TiXmlElement *node);
	void Draw();
	void ChangePos(D3DXVECTOR3 pos);
private:
	CUSTOMVERTEX *m_CustomVer;
	WORD  *m_Index;
	CPicture *SkyImage;
	LPDIRECT3DTEXTURE9* g_pTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVerBuff;//顶点缓冲接口指针
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuff;//索引缓冲接口指针
	void*  pVBData;
	void* pIBData;
	D3DMATERIAL9 g_Material;
};


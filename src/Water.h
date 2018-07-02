#pragma once
#include "RenderObject.h"
class CWater :
	public CRenderObject
{
public:
	CWater();
	~CWater();
	BOOL Init(TiXmlElement *node);
	void Draw();
	void DoFrame();
private:
	LPDIRECT3DTEXTURE9 m_pText;
	LPDIRECT3DTEXTURE9* m_pWaterText;
	LPDIRECT3DVERTEXBUFFER9 m_pVerBuff;//���㻺��ӿ�ָ��
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuff;//��������ӿ�ָ��
	CUSTOMVERTEX *m_CustomVer;
	WORD  *m_Index;
	void*  pVBData;
	void* pIBData;
	D3DMATERIAL9 g_Material;
	int m_wCurFrame;
	int m_Count;
};


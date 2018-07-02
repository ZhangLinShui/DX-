#include "stdafx.h"
#include "Sky.h"


CSky::CSky()
{
	m_lType = OB_TYPE_SKY;
}


CSky::~CSky()
{
}

BOOL CSky::Init(TiXmlElement *node)
{
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResourceA("设备接口");
	m_pDevice->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX), 0, D3DXFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVerBuff, 0);
	m_pDevice->CreateIndexBuffer(36 * sizeof(CUSTOMVERTEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuff,0);
	m_pVerBuff->Lock(0, 24 * sizeof(CUSTOMVERTEX), &pVBData, 0);
	
	m_CustomVer = new CUSTOMVERTEX[24];
	//前面
	m_CustomVer[0] = { {  3000,  3000,   -3000 },0x00ffffff ,{ 0,0 } };//左上
	m_CustomVer[1] = { {  -3000, 3000,   -3000 },0x00ffffff ,{ 1,0 } };//右上
	m_CustomVer[2] = { {  -3000, -3000,  -3000 },0x00ffffff ,{ 1,1 } };//右下
	m_CustomVer[3] = { {  3000,  -3000,  -3000 },0x00ffffff ,{ 0,1 } };//左下
	//后面
	m_CustomVer[4] = { {  -3000, 3000,   3000  },0x00ffffff ,{ 0,0 } };//左上
	m_CustomVer[5] = { {  3000,  3000,   3000  },0x00ffffff ,{ 1,0 } };//右上
	m_CustomVer[6] = { {  3000,  -3000,  3000  },0x00ffffff ,{ 1,1 } };//右下
	m_CustomVer[7] = { {  -3000, -3000,  3000  },0x00ffffff ,{ 0,1 } };//左下
	//左面			    
	m_CustomVer[8] = { {  -3000, 3000,   -3000 },0x00ffffff ,{ 0,0 } };//左上
	m_CustomVer[9] = { {  -3000, 3000,   3000  },0x00ffffff ,{ 1,0 } };//右上
	m_CustomVer[10] = { { -3000, -3000,  3000  },0x00ffffff ,{ 1,1 } };//右下
	m_CustomVer[11] = { { -3000, -3000,  -3000 },0x00ffffff ,{ 0,1 } };//左下
	//右面
	m_CustomVer[12] = { { 3000,  3000,   3000  },0x00ffffff ,{ 0,0 } };//左上
	m_CustomVer[13] = { { 3000,  3000,   -3000 },0x00ffffff ,{ 1,0 } };//右上
	m_CustomVer[14] = { { 3000,  -3000,  -3000 },0x00ffffff ,{ 1,1 } };//右下
	m_CustomVer[15] = { { 3000,  -3000,  3000  },0x00ffffff ,{ 0,1 } };//左下
	//上面															  
	m_CustomVer[16] = { { -3000, 3000,   -3000 },0x00ffffff ,{ 0,0 } };//左上
	m_CustomVer[17] = { { 3000,  3000,   -3000 },0x00ffffff ,{ 1,0 } };//右上
	m_CustomVer[18] = { { 3000,  3000,   3000  },0x00ffffff ,{ 1,1 } };//右下
	m_CustomVer[19] = { { -3000, 3000,   3000  },0x00ffffff ,{ 0,1 } };//左下
	//下面															  
	m_CustomVer[20] = { { -3000, -3000,  3000  },0x00ffffff ,{ 0,0 } };//左上
	m_CustomVer[21] = { { 3000,  -3000,  3000  },0x00ffffff ,{ 1,0 } };//右上
	m_CustomVer[22] = { { 3000,  -3000,  -3000 },0x00ffffff ,{ 1,1 } };//右下
	m_CustomVer[23] = { { -3000, -3000,  -3000 },0x00ffffff ,{ 0,1 } };//左下
	memcpy(pVBData, m_CustomVer, 24 * sizeof(CUSTOMVERTEX));
	m_pVerBuff->Unlock();

	m_pIndexBuff->Lock(0, 36 * sizeof(WORD), &pIBData, 0);
	m_Index = new WORD[36];
	//前面  顺时针
	m_Index[0] = 0;   m_Index[1] = 1;   m_Index[2] = 3;
	m_Index[3] = 3;   m_Index[4] = 1;   m_Index[5] = 2;
	//后面  顺时针    				    
	m_Index[6] = 4;   m_Index[7] = 5;   m_Index[8] = 7;
	m_Index[9] = 7;   m_Index[10] = 5;   m_Index[11] = 6;
	//左面  顺时针
	m_Index[12] = 8;  m_Index[13] = 9;  m_Index[14] = 11;
	m_Index[15] = 11; m_Index[16] = 9; m_Index[17] = 10;
	//右面  顺时针
	m_Index[18] = 12; m_Index[19] = 13; m_Index[20] = 15;
	m_Index[21] = 15; m_Index[22] = 13; m_Index[23] = 14;
	//上面  顺时针
	m_Index[24] = 16; m_Index[25] = 17; m_Index[26] = 19;
	m_Index[27] = 19; m_Index[28] = 17; m_Index[29] = 18;
	//下面  顺时针
	m_Index[30] = 20; m_Index[31] = 21; m_Index[32] = 23;
	m_Index[33] = 23; m_Index[34] = 21; m_Index[35] = 22;
	memcpy(pIBData, m_Index, 36 * sizeof(WORD));
	m_pIndexBuff->Unlock();

	g_pTex = new LPDIRECT3DTEXTURE9[6];
	D3DXCreateTextureFromFile(m_pDevice, "./res/object/map/cloudy_noon_FR.jpg", &g_pTex[0]);
	D3DXCreateTextureFromFile(m_pDevice, "./res/object/map/cloudy_noon_BK.jpg", &g_pTex[1]);
	D3DXCreateTextureFromFile(m_pDevice, "./res/object/map/cloudy_noon_LF.jpg", &g_pTex[2]);
	D3DXCreateTextureFromFile(m_pDevice, "./res/object/map/cloudy_noon_RT.jpg", &g_pTex[3]);
	D3DXCreateTextureFromFile(m_pDevice, "./res/object/map/cloudy_noon_UP.jpg", &g_pTex[4]);
	D3DXCreateTextureFromFile(m_pDevice, "./res/object/map/cloudy_noon_DN.jpg", &g_pTex[5]);
	return TRUE;
}

void CSky::Draw()
{
	ZeroMemory(&g_Material, sizeof(g_Material));
	g_Material.Ambient.r = 1.0f;
	g_Material.Ambient.g = 1.0f;
	g_Material.Ambient.b = 1.0f;
	g_Material.Diffuse.r = g_Material.Diffuse.g = g_Material.Diffuse.b = 1.0f;
	//g_Material.Specular.r = g_Material.Specular.g = g_Material.Specular.b = 1.0f;
	//g_Material.Emissive.g = 1.0f;
	g_Material.Power = 50;
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	m_pDevice->SetMaterial(&g_Material);
	D3DXMatrixIdentity(&matWorld);
	m_pDevice->SetFVF(D3DXFVF_CUSTOMVERTEX);
	m_pDevice->SetStreamSource(0, m_pVerBuff, 0, sizeof(CUSTOMVERTEX));
	m_pDevice->SetIndices(m_pIndexBuff);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	//m_pDeive->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	for (int i = 0; i < 6; i++)
	{
		m_pDevice->SetTexture(0, g_pTex[i]);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, i * 6, 2);
	}
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void CSky::ChangePos(D3DXVECTOR3 pos)
{
	//m_pVerBuff->Lock(0, 24 * sizeof(CUSTOMVERTEX), &pVBData, 0);
	//for (int i = 0;i < 24;i++)
	//{
	//	m_CustomVer[i].pos += pos;
	//}
	//memcpy(pVBData, m_CustomVer, 24 * sizeof(CUSTOMVERTEX));
	//m_pVerBuff->Unlock();
}

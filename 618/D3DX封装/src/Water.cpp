#include "stdafx.h"
#include "Water.h"


CWater::CWater()
{
	m_lType = OB_TYPE_WATER;
}


CWater::~CWater()
{
}

BOOL CWater::Init(TiXmlElement *node)
{
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResourceA("设备接口");
	m_pDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, D3DXFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVerBuff, 0);
	m_pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuff, 0);//D3DPOOL_MANA
	m_pVerBuff->Lock(0, 4 * sizeof(CUSTOMVERTEX), &pVBData, 0);
	m_CustomVer = new CUSTOMVERTEX[4];
	m_CustomVer[0] = { { -950,-140,700 },0x880000ff,{ 0,0 } };
	m_CustomVer[1] = { { -950 + 127 * 15,-140,700 },0x880000ff,{ 1 * 5,0 } };
	m_CustomVer[2] = { { -950 + 127 * 15,-140,700 - 127 * 15 },0x880000ff,{ 1 * 5,1 * 5 } };
	m_CustomVer[3] = { { -950,-140,700 - 127 * 15 },0x880000ff,{ 0,1 * 5 } };
	memcpy(pVBData, m_CustomVer, 4 * sizeof(CUSTOMVERTEX));
	m_pVerBuff->Unlock();
	m_pIndexBuff->Lock(0, 6 * sizeof(WORD), &pIBData, 0);
	m_Index = new WORD[6]{ 0,1,2,0,2,3, };
	memcpy(pIBData, m_Index, 6 * sizeof(WORD));
	m_pIndexBuff->Unlock();
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water.tga", &m_pText);
	m_wCurFrame = 0;
	m_Count = 21;
	m_pWaterText = new LPDIRECT3DTEXTURE9[21];
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a000.bmp.tga", &m_pWaterText[0]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a010.bmp.tga", &m_pWaterText[1]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a020.bmp.tga", &m_pWaterText[2]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a030.bmp.tga", &m_pWaterText[3]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a040.bmp.tga", &m_pWaterText[4]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a050.bmp.tga", &m_pWaterText[5]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a060.bmp.tga", &m_pWaterText[6]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a070.bmp.tga", &m_pWaterText[7]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a080.bmp.tga", &m_pWaterText[8]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a090.bmp.tga", &m_pWaterText[9]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a100.bmp.tga", &m_pWaterText[10]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a110.bmp.tga", &m_pWaterText[11]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a120.bmp.tga", &m_pWaterText[12]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a130.bmp.tga", &m_pWaterText[13]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a140.bmp.tga", &m_pWaterText[14]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a150.bmp.tga", &m_pWaterText[15]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a160.bmp.tga", &m_pWaterText[16]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a170.bmp.tga", &m_pWaterText[17]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a180.bmp.tga", &m_pWaterText[18]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a190.bmp.tga", &m_pWaterText[19]);
	D3DXCreateTextureFromFile(m_pDevice, "../bin/res/water_a197.bmp.tga", &m_pWaterText[20]);
	m_pText = m_pWaterText[m_wCurFrame];
	return TRUE;
}

void CWater::Draw()
{
	ZeroMemory(&g_Material, sizeof(g_Material));
	//g_Material.Ambient.r = 1.0f;
	/*g_Material.Ambient.r = 0.2f; g_Material.Ambient.g = 0.2f;*/ g_Material.Ambient.b = 0.2f;
	//g_Material.Diffuse.r = 1.0f; g_Material.Diffuse.g = 1.0f; g_Material.Diffuse.b = 1.0f;
	//g_Material.Specular.r = g_Material.Specular.g = g_Material.Specular.b = 1.0f;
	//g_Material.Emissive.g = 1.0f;
	g_Material.Power = 50;
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	m_pDevice->SetFVF(D3DXFVF_CUSTOMVERTEX);
	m_pDevice->SetStreamSource(0, m_pVerBuff, 0, sizeof(CUSTOMVERTEX));
	m_pDevice->SetIndices(m_pIndexBuff);
	D3DXMatrixIdentity(&matWorld);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//m_pDeive->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//m_pDeive->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	//m_pDeive->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDevice->SetTexture(0, m_pText);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DoFrame();
}

void CWater::DoFrame()
{
	static DWORD pretime = timeGetTime();
	DWORD curtime = timeGetTime();
	if (curtime - pretime > 150)
	{
		m_wCurFrame++;
		if (m_wCurFrame == m_Count)
			m_wCurFrame = 0;
		m_pText = m_pWaterText[m_wCurFrame];
		pretime = curtime;
	}
}

#include "stdafx.h"
#include "Hourse.h"


CHourse::CHourse()
{
	m_lType = OB_TYPE_HOURSE;
}


CHourse::~CHourse()
{
}

BOOL CHourse::Init(TiXmlElement *node)
{
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResourceA("设备接口");
	LPD3DXBUFFER materialBuf;
	D3DXLoadMeshFromXA("res/object/map/house1.X", 0, m_pDevice, 0, &materialBuf, 0, &m_dwNumMaterail, &m_Mesh);
	D3DXMATERIAL* arrMaterial = (D3DXMATERIAL*)materialBuf->GetBufferPointer();
	for (int i = 0; i < m_dwNumMaterail; i++)
	{
		m_vecMatera.push_back(arrMaterial[i].MatD3D);
		LPDIRECT3DTEXTURE9 pTex=NULL;
		if (arrMaterial[i].pTextureFilename)
		{
			D3DXCreateTextureFromFile(m_pDevice, arrMaterial[i].pTextureFilename, &pTex);
		}
		else
		{
			pTex = NULL;
		}
		m_vecTex.push_back(pTex);
	}
	D3DXComputeNormals(m_Mesh, NULL);//计算法线
	D3DXMATRIX mat1, mat2, mat3;
	D3DXMatrixIdentity(&mat1);
	

	m_vPos = { 300 ,0 ,70 };
	D3DXMatrixTranslation(&mat1, m_vPos.x, m_vPos.y, m_vPos.z);
	//D3DXMatrixRotationY(&mat2, D3DX_PI / 1.8);
	D3DXMatrixScaling(&mat3, 2, 2, 2);
	matWorld = mat3*mat1;
	D3DXMatrixInverse(&m_matInverse, NULL, &matWorld);
	return TRUE;

}

void CHourse::Draw()
{
	//ZeroMemory(&g_Material, sizeof(g_Material));
	////g_Material.Ambient.r = 1.0f;
	//g_Material.Ambient.r = 0.2f; g_Material.Ambient.g = 0.2f; g_Material.Ambient.b = 0.2f;
	//g_Material.Diffuse.r = 1.0f; g_Material.Diffuse.g = 1.0f; g_Material.Diffuse.b = 1.0f;
	////g_Material.Specular.r = g_Material.Specular.g = g_Material.Specular.b = 1.0f;
	////g_Material.Emissive.g = 1.0f;
	//g_Material.Power = 50;
	//m_pDeive->SetRenderState(D3DRS_SPECULARENABLE, true);
	m_pDevice->SetMaterial(&g_Material);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	for (int i = 0; i < m_dwNumMaterail; i++)
	{
		m_pDevice->SetTexture(0, m_vecTex[i]);
		m_pDevice->SetMaterial(&m_vecMatera[i]);
		m_Mesh->DrawSubset(i);		//绘制子集
	}
	//m_pDeive->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

D3DXMATRIX CHourse::GetMatInverse()
{
	return m_matInverse;
}

LPD3DXMESH CHourse::GetMesh()
{
	return m_Mesh;
}

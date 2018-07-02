#include "stdafx.h"
#include "Bridge.h"


CBridge::CBridge()
{
	m_lType = OB_TYPE_BRIDGE;
}


CBridge::~CBridge()
{
}

BOOL CBridge::Init(TiXmlElement *node)
{
	LPD3DXBUFFER   materialBuf;
	m_pDeive = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResource("设备接口");
	D3DXLoadMeshFromXA("./res/object/map/TyrandeWoodBridgeLarge.x", 0, m_pDeive, 0, &materialBuf, 0, &m_dwNumMaterail, &m_Mesh);
	D3DXMATERIAL* arrMaterial = (D3DXMATERIAL*)materialBuf->GetBufferPointer();
	for (int i = 0; i < m_dwNumMaterail; i++)
	{
		m_vecMatera.push_back(arrMaterial[i].MatD3D);
		LPDIRECT3DTEXTURE9 pTex;
		if (arrMaterial[i].pTextureFilename)
		{
			D3DXCreateTextureFromFile(m_pDeive, arrMaterial[i].pTextureFilename, &pTex);
		}
		else
		{
			pTex = NULL;
		}
		m_vecTex.push_back(pTex);
	}
	WORD a;
	a = m_Mesh->GetNumFaces();
	D3DXComputeNormals(m_Mesh, NULL);
	D3DXMATRIX mat1, mat2, mat3;
	D3DXMatrixIdentity(&mat1);
	m_vPos = { 100 ,0 ,300 };
	D3DXMatrixTranslation(&mat1, m_vPos.x, m_vPos.y, m_vPos.z);
	
	//D3DXMatrixRotationY(&mat2, D3DX_PI / 1.8);
	//D3DXMatrixScaling(&mat3, 4, 3.3, 4.5);
	D3DXMatrixScaling(&mat3, 1, 1, 1);
	matWorld = mat3*mat1;
	D3DXMatrixInverse(&m_matInverse, NULL, &matWorld);

	CreatBox();

	return TRUE;
}

void CBridge::Draw()
{
	ZeroMemory(&g_Material, sizeof(g_Material));
	//g_Material.Ambient.r = 1.0f;
	g_Material.Ambient.r = 0.2f; g_Material.Ambient.g = 0.2f; g_Material.Ambient.b = 0.2f;
	g_Material.Diffuse.r = 1.0f; g_Material.Diffuse.g = 1.0f; g_Material.Diffuse.b = 1.0f;
	//g_Material.Specular.r = g_Material.Specular.g = g_Material.Specular.b = 1.0f;
	//g_Material.Emissive.g = 1.0f;
	g_Material.Power = 50;
	m_pDeive->SetRenderState(D3DRS_SPECULARENABLE, true);
	m_pDeive->SetMaterial(&g_Material);
	m_pDeive->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDeive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDeive->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	for (int i = 0; i < m_dwNumMaterail; i++)
	{
 		m_pDeive->SetTexture(0, m_vecTex[i]);
		m_pDeive->SetMaterial(&m_vecMatera[i]);
		m_Mesh->DrawSubset(i);		//绘制子集
	}
	/*m_pDeive->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_BoxMesh->DrawSubset(0);*/
	m_pDeive->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

}

D3DXMATRIX CBridge::GetMatInverse()
{
	return m_matInverse;
}

LPD3DXMESH CBridge::GetMesh()
{
	return m_Mesh;
}

void CBridge::CreatBox()
{
	/********************************包围盒*********************************/
	void* pVBData;
	void* pIBData;
	m_Mesh->LockVertexBuffer(0, &pVBData);//加锁m_Mesh的顶点数组 并且把值拷贝给pVBData
	m_Mesh->UnlockVertexBuffer();
	
	NumFaces = 12;
	NumVertices = 8;
	D3DXComputeBoundingBox((D3DXVECTOR3*)pVBData, m_Mesh->GetNumVertices(), m_Mesh->GetNumBytesPerVertex(), &D3DXMin, &D3DXMax);
	//D3DXComputeBoundingSphere((D3DXVECTOR3*)pVBData, m_Mesh->GetNumVertices(), m_Mesh->GetNumBytesPerVertex(), &pCenter, &r);
	D3DXCreateMeshFVF(NumFaces, NumVertices, 0/*索引缓冲数组的元素的格式（单个元素占16位字节 或者32位字节）*/, D3DXFVF_CUSTOMVERTEX1, m_pDeive, &m_BoxMesh);
	void* pVBData2;
	m_BoxMesh->LockVertexBuffer(0, &pVBData2);
	m_CustomBoxVer = new CUSTOMVERTEX1[8];
	m_CustomBoxVer[0] = { { D3DXMin.x,D3DXMin.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	m_CustomBoxVer[1] = { { D3DXMin.x,D3DXMax.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	m_CustomBoxVer[2] = { { D3DXMax.x,D3DXMax.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	m_CustomBoxVer[3] = { { D3DXMax.x,D3DXMin.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	m_CustomBoxVer[4] = { { D3DXMin.x,D3DXMin.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	m_CustomBoxVer[5] = { { D3DXMin.x,D3DXMax.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	m_CustomBoxVer[6] = { { D3DXMax.x,D3DXMax.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	m_CustomBoxVer[7] = { { D3DXMax.x,D3DXMin.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	memcpy(pVBData2, m_CustomBoxVer, 8 * sizeof(CUSTOMVERTEX1));
	m_BoxMesh->UnlockVertexBuffer();
	//g_pVB->Unlock();
	m_BoxMesh->LockIndexBuffer(0, &pIBData);
	//g_pIB->Lock(0, 36 * sizeof(WORD), (void**)&pIBData, 0);
	m_BoxIndex = new WORD[36];

	//前面 front side  顺时针
	m_BoxIndex[0] = 0; m_BoxIndex[1] = 1; m_BoxIndex[2] = 2;
	m_BoxIndex[3] = 0; m_BoxIndex[4] = 2; m_BoxIndex[5] = 3;
	//后面 back side   逆时针
	m_BoxIndex[6] = 4; m_BoxIndex[7] = 6; m_BoxIndex[8] = 5;
	m_BoxIndex[9] = 4; m_BoxIndex[10] = 7; m_BoxIndex[11] = 6;
	//左面 left side   顺时针
	m_BoxIndex[12] = 4; m_BoxIndex[13] = 5; m_BoxIndex[14] = 1;
	m_BoxIndex[15] = 4; m_BoxIndex[16] = 1; m_BoxIndex[17] = 0;
	//右面 left side   顺时针
	m_BoxIndex[18] = 3; m_BoxIndex[19] = 2; m_BoxIndex[20] = 6;
	m_BoxIndex[21] = 3; m_BoxIndex[22] = 6; m_BoxIndex[23] = 7;
	//顶面 top	 	   顺时针
	m_BoxIndex[24] = 1; m_BoxIndex[25] = 5; m_BoxIndex[26] = 6;
	m_BoxIndex[27] = 1; m_BoxIndex[28] = 6; m_BoxIndex[29] = 2;
	//底面 bottom      顺时针
	m_BoxIndex[30] = 4; m_BoxIndex[31] = 0; m_BoxIndex[32] = 3;
	m_BoxIndex[33] = 4; m_BoxIndex[34] = 3; m_BoxIndex[35] = 7;
	memcpy(pIBData, m_BoxIndex, 36 * sizeof(WORD));//将数据从m_BoxIndex拷贝到pIBData指向的显存空间
	m_BoxMesh->UnlockIndexBuffer();
	//g_pIB->Unlock();
	D3DXComputeNormals(m_BoxMesh, NULL);
	/********************************包围盒*********************************/
}

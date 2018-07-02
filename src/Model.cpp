#include "stdafx.h"
#include "Model.h"


CModel::CModel()
{
	m_lType = OB_TYPE_MODEL;
}


CModel::~CModel()
{
}

BOOL CModel::Init(TiXmlElement* element)
{
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResourceA("设备接口");
	TiXmlElement* childNode = element->FirstChildElement("Mesh");
	string Modedata = childNode->GetText();
	LPD3DXBUFFER   materialBuf1;
	D3DXLoadMeshFromX(Modedata.c_str(), 0, m_pDevice, 0, &materialBuf1, 0, &g_dNumMaterail, &m_Mesh);
	D3DXMATERIAL* arrMaterial = (D3DXMATERIAL*)materialBuf1->GetBufferPointer();
	childNode = element->FirstChildElement("Path");
	Modedata = childNode->GetText();
	for (int i = 0; i < g_dNumMaterail; i++)
	{
		g_vecMaterail.push_back(arrMaterial[i].MatD3D);
		Modedata += arrMaterial[i].pTextureFilename;
		LPDIRECT3DTEXTURE9 pTex;
		if (arrMaterial[i].pTextureFilename)
		{
			D3DXCreateTextureFromFile(m_pDevice, Modedata.c_str(), &pTex);
		}
		else
		{
			pTex = NULL;
		}
		g_vecTex.push_back(pTex);
	}
	m_Mesh->GetVertexBuffer(&m_pVB);
	m_Mesh->GetIndexBuffer(&m_pIB);
	
	//void* pVBData;
	//void* pIBData;
	//m_Mesh->LockVertexBuffer(0, &pVBData);//加锁m_Mesh的顶点数组 并且把值拷贝给pVBData
	//m_Mesh->UnlockVertexBuffer();
	//D3DXComputeBoundingBox((D3DXVECTOR3*)pVBData, m_Mesh->GetNumVertices(), m_Mesh->GetNumBytesPerVertex(), &D3DXMin, &D3DXMax);
	//VertexBuffer.FrontUp = D3DXVECTOR3{ D3DXMin.x,D3DXMin.y,D3DXMin.z }			;
	//VertexBuffer.FrontDown = D3DXVECTOR3{ D3DXMin.x,D3DXMax.y,D3DXMin.z }		;
	//VertexBuffer.FrontLeft = D3DXVECTOR3{ D3DXMax.x,D3DXMax.y,D3DXMin.z }		;
	//VertexBuffer.FrontRight = D3DXVECTOR3{ D3DXMax.x,D3DXMin.y,D3DXMin.z }		;
	//VertexBuffer.BackUp = D3DXVECTOR3{ D3DXMin.x,D3DXMin.y,D3DXMax.z }			;
	//VertexBuffer.BackDown = D3DXVECTOR3{ D3DXMin.x,D3DXMax.y,D3DXMax.z }		;
	//VertexBuffer.BackLeft = D3DXVECTOR3{ D3DXMax.x,D3DXMax.y,D3DXMax.z }		;
	//VertexBuffer.BackRight = D3DXVECTOR3{ D3DXMax.x,D3DXMin.y,D3DXMax.z }		;
	CreatBox();
	return TRUE;
}
D3DXVECTOR3 CModel::GetVertex(int i)
{
	return *(D3DXVECTOR3*)((BYTE*)m_pVB + i*m_Mesh->GetNumBytesPerVertex());
}
void CModel::Draw()
{
	m_pDevice->SetTransform(D3DTS_WORLD, &this->GetWorldMatrix());
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	for (int i = 0; i < g_dNumMaterail; i++)
	{
		m_pDevice->SetTexture(0, g_vecTex[i]);
		m_pDevice->SetMaterial(&g_vecMaterail[i]);
		m_Mesh->DrawSubset(i);
	}

	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_BoxMesh->DrawSubset(0);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

LPD3DXMESH CModel::GetMesh()
{
	return m_Mesh;
}

LPD3DXMESH CModel::GetBoxMesh()
{
	return m_BoxMesh;
}

void CModel::CreatBox()
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
	D3DXCreateMeshFVF(NumFaces, NumVertices, 0/*索引缓冲数组的元素的格式（单个元素占16位字节 或者32位字节）*/, D3DXFVF_CUSTOMVERTEX1, m_pDevice, &m_BoxMesh);
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



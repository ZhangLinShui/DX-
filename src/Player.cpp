#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
	m_lType = OB_TYPE_PLAYER;
}
CPlayer::~CPlayer()
{
}
BOOL CPlayer::Init(TiXmlElement* node)
{
	m_fMoveSpeed = atof(node->Attribute("MoveSpeed"));
	TiXmlElement* childnode = node->FirstChildElement("Pos");
	m_vPos.x = atof(childnode->Attribute("x"));
	m_vPos.y = atof(childnode->Attribute("y"));
	m_vPos.z = atof(childnode->Attribute("z"));
	childnode = node->FirstChildElement("Scale");
	Scalex = atof(childnode->Attribute("scalex"));
	Scaley = atof(childnode->Attribute("scaley"));
	Scalez = atof(childnode->Attribute("scalez"));
	childnode = node->FirstChildElement("Roate");
	RoteX = atof(childnode->Attribute("x"));
	RoteY = atof(childnode->Attribute("y"));
	RoteZ = atof(childnode->Attribute("z"));
	Roate = atoi(childnode->GetText());
	/*childnode = node->FirstChildElement("ResName");
	string name = childnode->GetText();*/

	/*childnode = node->FirstChildElement("Path");
	m_TextruePath = (childnode->GetText());*/
	RightDir = { 1, 0, 0 };
	UpDir = { 0, 1, 0 };
	ForwordDir = { 0, 0, 1 };
	CurrentDir = { 0, 0, 1 };
	m_pDeive = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResource("设备接口");
	
	m_pMeshDate = new CCharacter();
	//m_pMeshDate->SetDevice(m_pDeive);
	m_pMeshDate->Init(node);

	
	/*LPD3DXBUFFER   materialBuf;
	D3DXLoadMeshFromXA(name.c_str(), 0, m_pDeive, 0, &materialBuf, 0, &g_dwNumMaterail, &m_Mesh);
	D3DXMATERIAL* arrMaterial = (D3DXMATERIAL*)materialBuf->GetBufferPointer();

	for (int i = 0; i < g_dwNumMaterail; i++)
	{
		LPDIRECT3DTEXTURE9 pTex;
		if (arrMaterial[i].pTextureFilename)
		{
			string strPath = m_TextruePath;
			string strTexName = arrMaterial[i].pTextureFilename;
			strPath += strTexName;
			D3DXCreateTextureFromFile(m_pDeive, strPath.c_str(), &pTex);
		}
		else
		{
			pTex = NULL;
		}
		g_vecTex.push_back(pTex);
	}*/

	//void* pVBData;
	//void* pIBData;
	//m_Mesh->LockVertexBuffer(0, &pVBData);
	//m_Mesh->UnlockVertexBuffer();
	//
	//NumFaces = 12;
	//NumVertices = 8;
	//D3DXComputeBoundingBox((D3DXVECTOR3*)pVBData, m_Mesh->GetNumVertices(), m_Mesh->GetNumBytesPerVertex(), &D3DXMin, &D3DXMax);
	////D3DXComputeBoundingSphere((D3DXVECTOR3*)pVBData, m_Mesh->GetNumVertices(), m_Mesh->GetNumBytesPerVertex(), &pCenter, &r);
	//D3DXCreateMeshFVF(NumFaces, NumVertices, 0, D3DXFVF_CUSTOMVERTEX1, m_pDeive, &m_BoxMesh);
	//void* pVBData2;
	//m_BoxMesh->LockVertexBuffer(0, &pVBData2);
	//m_CustomBoxVer = new CUSTOMVERTEX1[8];
	//m_CustomBoxVer[0] = { { D3DXMin.x,D3DXMin.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	//m_CustomBoxVer[1] = { { D3DXMin.x,D3DXMax.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	//m_CustomBoxVer[2] = { { D3DXMax.x,D3DXMax.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	//m_CustomBoxVer[3] = { { D3DXMax.x,D3DXMin.y,D3DXMin.z },{ 1,1,1 },0x00ff00ff };
	//m_CustomBoxVer[4] = { { D3DXMin.x,D3DXMin.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	//m_CustomBoxVer[5] = { { D3DXMin.x,D3DXMax.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	//m_CustomBoxVer[6] = { { D3DXMax.x,D3DXMax.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	//m_CustomBoxVer[7] = { { D3DXMax.x,D3DXMin.y,D3DXMax.z },{ 1,1,1 },0x00ff00ff };
	//memcpy(pVBData2, m_CustomBoxVer, 8 * sizeof(CUSTOMVERTEX1));
	//m_BoxMesh->UnlockVertexBuffer();
	////g_pVB->Unlock();
	//m_BoxMesh->LockIndexBuffer(0, &pIBData);
	////g_pIB->Lock(0, 36 * sizeof(WORD), (void**)&pIBData, 0);
	//m_BoxIndex = new WORD[36];

	////前面 front side  顺时针
	//m_BoxIndex[0] = 0; m_BoxIndex[1] = 1; m_BoxIndex[2] = 2;
	//m_BoxIndex[3] = 0; m_BoxIndex[4] = 2; m_BoxIndex[5] = 3;
	////后面 back side   逆时针
	//m_BoxIndex[6] = 4; m_BoxIndex[7] = 6; m_BoxIndex[8] = 5;
	//m_BoxIndex[9] = 4; m_BoxIndex[10] = 7; m_BoxIndex[11] = 6;
	////左面 left side   顺时针
	//m_BoxIndex[12] = 4; m_BoxIndex[13] = 5; m_BoxIndex[14] = 1;
	//m_BoxIndex[15] = 4; m_BoxIndex[16] = 1; m_BoxIndex[17] = 0;
	////右面 left side   顺时针
	//m_BoxIndex[18] = 3; m_BoxIndex[19] = 2; m_BoxIndex[20] = 6;
	//m_BoxIndex[21] = 3; m_BoxIndex[22] = 6; m_BoxIndex[23] = 7;
	////顶面 top	 	   顺时针
	//m_BoxIndex[24] = 1; m_BoxIndex[25] = 5; m_BoxIndex[26] = 6;
	//m_BoxIndex[27] = 1; m_BoxIndex[28] = 6; m_BoxIndex[29] = 2;
	////底面 bottom      顺时针
	//m_BoxIndex[30] = 4; m_BoxIndex[31] = 0; m_BoxIndex[32] = 3;
	//m_BoxIndex[33] = 4; m_BoxIndex[34] = 3; m_BoxIndex[35] = 7;
	//memcpy(pIBData, m_BoxIndex, 36 * sizeof(WORD));//将数据从m_BoxIndex拷贝到pIBData指向的显存空间
	//m_BoxMesh->UnlockIndexBuffer();
	////g_pIB->Unlock();
	//D3DXComputeNormals(m_BoxMesh, NULL);

	//D3DXCreateSphere(m_pDeive, r, 20, 20, &m_pSphereMesh, NULL);

	
	//SetmatWorld();
	D3DXMATRIX MatRotX, MatRotY, MatRotZ, MatSoll, MatT;
	D3DXMatrixRotationX(&MatRotX, RoteX);
	D3DXMatrixRotationY(&MatRotY, RoteY);
	D3DXMatrixRotationZ(&MatRotZ, RoteZ);
	//D3DXMatrixTranslation(&MatT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&MatSoll, Scalex, Scaley, Scalez);
	matWorld = MatSoll * MatRotX*MatRotY*MatRotZ;
	D3DXMatrixInverse(&m_matInverse, NULL, &matWorld);
	
	


	return TRUE;
}
void  CPlayer::Draw()
{
	SetmatWorld();
	//D3DXMATRIX mat;
	//D3DXMATRIX mat2, MatSoll, MatT;
	////D3DXMatrixRotationX(&mat, 0);
	////D3DXMatrixRotationY(&mat2, 0);
	//D3DXMatrixIdentity(&mat);
	//D3DXMatrixIdentity(&mat2);
	//D3DXMatrixScaling(&MatSoll, Scalex, Scaley, Scalez);
	////D3DXMatrixTranslation(&MatT, m_vPos.x, m_vPos.y, m_vPos.z);
	//matWorld = MatSoll *matWorld;
	
	
	D3DXMATRIX MatRotX, MatRotY, MatRotZ, MatSoll, MatT;
	D3DXMatrixRotationX(&MatRotX, 0);
	D3DXMatrixRotationY(&MatRotY, RoteY);
	D3DXMatrixRotationZ(&MatRotZ, RoteZ);
	D3DXMatrixTranslation(&MatT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&MatSoll, Scalex, Scaley, Scalez);
	matWorld = MatSoll * MatRotX*MatRotY*/*MatRotZ**//*MatT**/matWorld;
	D3DXMatrixInverse(&m_matInverse, NULL, &matWorld);
	m_pDeive->SetTransform(D3DTS_WORLD, &matWorld);

	///***********************使用逆矩阵坐标系转换***********************/
	//D3DXVECTOR3 ppp = { 0,0,0 };
	//ppp = D3DXMax + GetPos();
	//D3DXVECTOR3 ppp1 = D3DXMax;
	//D3DXVECTOR3 ppp2 = D3DXMin;
	//D3DXMATRIX inver;
	//D3DXMatrixInverse(&inver, NULL, &matWorld);
	//D3DXVec3TransformCoord(&ppp1, &D3DXMax, &inver);
	//D3DXVec3TransformCoord(&ppp1, &ppp1, &matWorld);
	//ppp1 = ppp1 + GetPos();
	///***********************使用逆矩阵坐标系转换***********************/

	///***********************不使用逆矩阵坐标系转换***********************/
	//D3DXVECTOR3 ppp3 = D3DXMax;
	//D3DXMATRIX mat10,mat11,mat12;
	//D3DXMatrixIdentity(&mat10);
	//D3DXMatrixRotationX(&mat11, D3DX_PI / 2);
	//D3DXMatrixRotationY(&mat12, -D3DX_PI / 2);
	//mat10 = mat11*mat12;
	//D3DXMatrixTranslation(&mat10, m_vPos.x, m_vPos.y,  m_vPos.z);
	//D3DXVec3TransformCoord(&ppp3, &D3DXMax, &mat10);
	///***********************不使用逆矩阵坐标系转换***********************/
	/*m_pDeive->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pDeive->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDeive->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/

	/*m_pMeshDate->SetPos(m_vPos);
	m_pMeshDate->SetForwordDir(ForwordDir);
	m_pMeshDate->SetRightDir(RightDir);
	m_pMeshDate->SetUpDir(UpDir);*/
	m_pMeshDate->SetWorldMatrix(matWorld);
	m_pMeshDate->Draw();

	//m_pDeive->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//for (int i = 0; i < g_dwNumMaterail; i++)
	//{
	//	m_pDeive->SetTexture(0, g_vecTex[i]);
	//	m_Mesh->DrawSubset(i);
	//}
	m_pDeive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//m_pDeive->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDeive->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	D3DXMATRIX mat1;
	D3DXMatrixIdentity(&mat1);
	m_pDeive->SetTransform(D3DTS_WORLD, &mat1);
	D3DXVECTOR3 EndZ = ForwordDir * 40 * 3;
	D3DXVECTOR3 StartY = UpDir * 10 ;
	line[6] = { m_vPos  ,0xffff0000 };
	line[7] = { EndZ + m_vPos  ,0xffff0000 };
	line[0] = { m_vPos + StartY,0xffffff00 };
	line[1] = { EndZ + m_vPos+ StartY ,0xffffff00 };
	line[2] = { m_vPos - StartY,0xfff00f00 };
	line[3] = { EndZ + m_vPos - StartY ,0xff00ff00 };
	line[4] = { m_vPos + 2*StartY,0xffffffff };
	line[5] = { EndZ + m_vPos +2* StartY ,0xffffffff };
	m_pDeive->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	m_pDeive->DrawPrimitiveUP(D3DPT_LINELIST, 4, &line, sizeof(CUSTOMVERTEXLINE));

	D3DXVECTOR3  dir2;
	dir2 = D3DXVECTOR3(0, -1, 0);
	D3DXVec3Normalize(&dir2, &dir2);
	D3DXVECTOR3 endy = -UpDir * 40*2;
	D3DXVECTOR3 Front = ForwordDir * 10;
	D3DXVECTOR3 back = ForwordDir * -10;
	D3DXVECTOR3 YY = -dir2 * 0;
	start[0] = { m_vPos + YY ,0xffffff00 };
	start[1] = { endy + m_vPos + YY ,0xffffff00 };
	start[2] = { m_vPos + Front+ YY ,0xffffff00 };
	start[3] = { endy + m_vPos + Front+ YY ,0xffffff00 };
	start[4] = { m_vPos + back+ YY,0xffffff00 };
	start[5] = { endy + m_vPos + back+ YY ,0xffffff00 };
	m_pDeive->DrawPrimitiveUP(D3DPT_LINELIST, 1, &start, sizeof(CUSTOMVERTEXLINE));

	ZeroMemory(&g_Material, sizeof(g_Material));
	g_Material.Ambient.r = 0.0f;
	g_Material.Ambient.g = 0.0f;
	g_Material.Ambient.b = 1.0f;
	g_Material.Diffuse.r = g_Material.Diffuse.g = g_Material.Diffuse.b = 1.0f;
	//g_Material.Specular.r = g_Material.Specular.g = g_Material.Specular.b = 1.0f;
	//g_Material.Emissive.g = 1.0f;
	g_Material.Power = 50;
	m_pDeive->SetRenderState(D3DRS_SPECULARENABLE, true);//反射高亮
	m_pDeive->SetMaterial(&g_Material);
	//m_pDeive->SetRenderState(D3DRS_LIGHTING, FALSE);
	/*m_pDeive->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_BoxMesh->DrawSubset(0);*/
	m_pDeive->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//D3DXMatrixTranslation(&mat, pCenter.x, pCenter.y, pCenter.z);
	/*matWorld = matWorld*mat;
	m_pDeive->SetTransform(D3DTS_WORLD, &matWorld);
	m_pSphereMesh->DrawSubset(0);*/
	//m_pDeive->SetRenderState(D3DRS_LIGHTING, TRUE);
}
#include "stdafx.h"
#include "CMap.h"


CCMap::CCMap()
{
	m_lType = OB_TYPE_MAP;
}


CCMap::~CCMap()
{
	delete[]m_Index;
	delete[]m_CustomVer;
	delete MapHighImage;
}

void CCMap::CreateMap(DWORD row, DWORD col, DWORD width, DWORD height, D3DXVECTOR3 pos, DWORD color)
{
	m_pDeive = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResource("设备接口");
	D3DXCreateMeshFVF(row*col * 2, (row + 1)*(col + 1), D3DXMESH_32BIT, D3DXFVF_CUSTOMVERTEX2, m_pDeive, &m_Mesh);

	//m_pDeive->CreateVertexBuffer((row + 1)*(col + 1) * sizeof(CUSTOMVERTEX2), 0, D3DXFVF_CUSTOMVERTEX2, D3DPOOL_DEFAULT, &m_pVerBuff, 0);
	//m_pDeive->CreateIndexBuffer(row*col * 6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuff, 0);//D3DPOOL_MANAGER
	VertexNum = (row + 1)*(col + 1); // 顶点数组的个数
	IndexNum = row*col * 6; //矩形的个数*6顶点索引数组的个数
	D3DXVECTOR3 P = pos;
	void*  pVBData;
	void * pIBData;
	m_Mesh->LockVertexBuffer(0, &pVBData);
	//m_pVerBuff->Lock(0, (row + 1)*(col + 1) * sizeof(CUSTOMVERTEX2), &pVBData, 0);
	m_CustomVer = new CUSTOMVERTEX2[VertexNum];
	for (int i = 0; i < row + 1; i++)
	{
		for (int j = 0; j < col + 1; j++)
		{
			/*DWORD Color = MapHighImage->GetColor({ i,j });
			pos.y = Color & 0xff;
			if (pos.y > 20)
				color = 0x00ffffff;
			else
				color = 0xffffffff;
			pos.y =- 200;*/
			m_CustomVer[i*(col + 1) + j] = { pos,{ 0,0,0 },color ,
				D3DXVECTOR2(j*1.0f * 100 / col , i*1.0f * 100 / row),
				D3DXVECTOR2(j*1.0f * 100 / col , i*1.0f * 100 / row) };
			if (j == col)
			{
				pos.z -= height;
				pos.x = P.x;
			}
			else
				pos.x += width;

		}
	}
	/*for (int i = 0; i < row + 1; i++)
	{
		for (int j = 0; j < col + 1; j++)
		{
			if (i == 0 && j == 0)
			{
				D3DXVECTOR3 d3dxvect1 = m_CustomVer[i*(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
				D3DXVECTOR3 d3dxvect2 = m_CustomVer[(i + 1)*(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
				D3DXVECTOR3 d3dxvect3 = m_CustomVer[(i + 1)*(col + 1) + j].pos - m_CustomVer[(i + 1)*(col + 1) + j].pos;
				D3DXVECTOR3 normal1 = *D3DXVec3Cross(&normal1, &d3dxvect1, &d3dxvect2);
				D3DXVECTOR3 normal2 = *D3DXVec3Cross(&normal2, &d3dxvect2, &d3dxvect3);
				m_CustomVer[i*(col + 1) + j].normal = 0.5*(normal1 + normal2);
			}
			else
				if (i == row&&j == col)
				{
					D3DXVECTOR3 d3dxvect1 = m_CustomVer[(i - 1)*(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
					D3DXVECTOR3 d3dxvect2 = m_CustomVer[(i - 1)*(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
					D3DXVECTOR3 d3dxvect3 = m_CustomVer[i*(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
					D3DXVECTOR3 normal1 = *D3DXVec3Cross(&normal1, &d3dxvect1, &d3dxvect2);
					D3DXVECTOR3 normal2 = *D3DXVec3Cross(&normal2, &d3dxvect2, &d3dxvect3);
					m_CustomVer[i*(col + 1) + j].normal = 0.5*(normal1 + normal2);
				}
				else
					if (i == 0 && j == col)
					{
						D3DXVECTOR3 d3dxvect1 = m_CustomVer[(i + 1) *(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
						D3DXVECTOR3 d3dxvect2 = m_CustomVer[i *(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
						D3DXVECTOR3 normal = *D3DXVec3Cross(&normal, &d3dxvect1, &d3dxvect2);
						m_CustomVer[i*(col + 1) + j].normal = normal;
					}
					else
						if (i == row&&j == 0)
						{
							D3DXVECTOR3 d3dxvect1 = m_CustomVer[(i - 1) *(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
							D3DXVECTOR3 d3dxvect2 = m_CustomVer[i *(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
							D3DXVECTOR3 normal = *D3DXVec3Cross(&normal, &d3dxvect1, &d3dxvect2);
							m_CustomVer[i*(col + 1) + j].normal = normal;
						}
						else
							if (i == 0 && j != 0 && j != col)
							{
								D3DXVECTOR3 d3dxvect1 = m_CustomVer[i*(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
								D3DXVECTOR3 d3dxvect2 = m_CustomVer[(i + 1)*(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
								D3DXVECTOR3 d3dxvect3 = m_CustomVer[(i + 1)*(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
								D3DXVECTOR3 d3dxvect4 = m_CustomVer[i *(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
								D3DXVECTOR3 normal1 = *D3DXVec3Cross(&normal1, &d3dxvect1, &d3dxvect2);
								D3DXVECTOR3 normal2 = *D3DXVec3Cross(&normal2, &d3dxvect2, &d3dxvect3);
								D3DXVECTOR3 normal3 = *D3DXVec3Cross(&normal3, &d3dxvect3, &d3dxvect4);
								m_CustomVer[i*(col + 1) + j].normal = 1.0f / 3 * (normal1 + normal2 + normal3);
							}
							else
								if (i == row&&j != 0 && j != col)
								{
									D3DXVECTOR3 d3dxvect1 = m_CustomVer[i*(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
									D3DXVECTOR3 d3dxvect2 = m_CustomVer[(i - 1)*(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
									D3DXVECTOR3 d3dxvect3 = m_CustomVer[(i - 1)*(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
									D3DXVECTOR3 d3dxvect4 = m_CustomVer[i *(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
									D3DXVECTOR3 normal1 = *D3DXVec3Cross(&normal1, &d3dxvect1, &d3dxvect2);
									D3DXVECTOR3 normal2 = *D3DXVec3Cross(&normal2, &d3dxvect2, &d3dxvect3);
									D3DXVECTOR3 normal3 = *D3DXVec3Cross(&normal3, &d3dxvect3, &d3dxvect4);
									m_CustomVer[i*(col + 1) + j].normal = 1.0f / 3 * (normal1 + normal2 + normal3);
								}
								else
									if (j == 0 && i != 0 && i != row)
									{
										D3DXVECTOR3 d3dxvect1 = m_CustomVer[(i - 1)*(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
										D3DXVECTOR3 d3dxvect2 = m_CustomVer[i *(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
										D3DXVECTOR3 d3dxvect3 = m_CustomVer[(i + 1)*(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
										D3DXVECTOR3 d3dxvect4 = m_CustomVer[(i + 1) *(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
										D3DXVECTOR3 normal1 = *D3DXVec3Cross(&normal1, &d3dxvect1, &d3dxvect2);
										D3DXVECTOR3 normal2 = *D3DXVec3Cross(&normal2, &d3dxvect2, &d3dxvect3);
										D3DXVECTOR3 normal3 = *D3DXVec3Cross(&normal3, &d3dxvect3, &d3dxvect4);
										m_CustomVer[i*(col + 1) + j].normal = 1.0f / 3 * (normal1 + normal2 + normal3);
									}
									else
										if (j == col && i != 0 && i != row)
										{
											D3DXVECTOR3 d3dxvect1 = m_CustomVer[(i + 1)*(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect2 = m_CustomVer[i *(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect3 = m_CustomVer[(i - 1)*(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect4 = m_CustomVer[(i - 1) *(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 normal1 = *D3DXVec3Cross(&normal1, &d3dxvect1, &d3dxvect2);
											D3DXVECTOR3 normal2 = *D3DXVec3Cross(&normal2, &d3dxvect2, &d3dxvect3);
											D3DXVECTOR3 normal3 = *D3DXVec3Cross(&normal3, &d3dxvect3, &d3dxvect4);
											m_CustomVer[i*(col + 1) + j].normal = 1.0f / 3 * (normal1 + normal2 + normal3);
										}
										else
										{
											D3DXVECTOR3 d3dxvect1 = m_CustomVer[(i - 1)*(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect2 = m_CustomVer[i *(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect3 = m_CustomVer[(i + 1)*(col + 1) + j + 1].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect4 = m_CustomVer[(i + 1) *(col + 1) + j].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect5 = m_CustomVer[i *(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 d3dxvect6 = m_CustomVer[(i - 1) *(col + 1) + j - 1].pos - m_CustomVer[i*(col + 1) + j].pos;
											D3DXVECTOR3 normal1 = *D3DXVec3Cross(&normal1, &d3dxvect1, &d3dxvect2);
											D3DXVECTOR3 normal2 = *D3DXVec3Cross(&normal2, &d3dxvect2, &d3dxvect3);
											D3DXVECTOR3 normal3 = *D3DXVec3Cross(&normal3, &d3dxvect3, &d3dxvect4);
											D3DXVECTOR3 normal4 = *D3DXVec3Cross(&normal4, &d3dxvect4, &d3dxvect5);
											D3DXVECTOR3 normal5 = *D3DXVec3Cross(&normal5, &d3dxvect5, &d3dxvect6);
											D3DXVECTOR3 normal6 = *D3DXVec3Cross(&normal6, &d3dxvect6, &d3dxvect1);
											m_CustomVer[i*(col + 1) + j].normal = 1.0f / 6 * (normal1 + normal2 + normal3 + normal4 + normal5 + normal6);
										}
		}
	}*/
	memcpy(pVBData, m_CustomVer, VertexNum * sizeof(CUSTOMVERTEX2));
	m_Mesh->UnlockVertexBuffer();
	//m_pVerBuff->Unlock();
	//m_pIndexBuff->Lock(0, row*col * 6 * sizeof(WORD), &pIBData, 0);
	m_Mesh->LockIndexBuffer(0, &pIBData);
	m_Index = new DWORD[IndexNum];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			m_Index[(i*col + j) * 6]	 = i*(col + 1) + j;
			m_Index[(i*col + j) * 6 + 1] = i*(col + 1) + j + 1;
			m_Index[(i*col + j) * 6 + 2] = (i + 1)*(col + 1) + j + 1;
			m_Index[(i*col + j) * 6 + 3] = i*(col + 1) + j;
			m_Index[(i*col + j) * 6 + 4] = (i + 1)*(col + 1) + j + 1;
			m_Index[(i*col + j) * 6 + 5] = (i + 1)*(col + 1) + j;
		}
	}
	memcpy(pIBData, m_Index, IndexNum * sizeof(DWORD));
	//m_pIndexBuff->Unlock();
	m_Mesh->UnlockIndexBuffer();
	//D3DXCreateTextureFromFile(m_pDeive, "grass.jpg", &m_pText);
	////D3DXCreateTextureFromFile(m_pDeive, "grass.JPG", &g_pTex);
	//D3DXCreateTextureFromFile(m_pDeive, _T("地形石地01.dds"), &m_pText2);
	D3DXMatrixIdentity(&m_matInverse);
}

BOOL CCMap::Init(TiXmlElement *node)
{
	aa = 1;
	TiXmlElement* childnode = node->FirstChildElement("ResName");
	string name = childnode->GetText();
	MapHighImage = new CPicture;
	MapHighImage->Init(name);

	m_vPos = { -3000,0,700 };
	
	width = 40;
	height = 40;

	Width = 127 * aa * width;
	Height = 127 * aa * height;
	CreateMap(127* aa, 127* aa, width, height, m_vPos,0xffffffff);
	
	childnode = node->FirstChildElement("贴图1");
	name = childnode->GetText();
	D3DXCreateTextureFromFile(m_pDeive, name.c_str(), &m_pText);
	childnode = node->FirstChildElement("贴图2");
	name = childnode->GetText();
	D3DXCreateTextureFromFile(m_pDeive, name.c_str(), &m_pText2);

	return TRUE;
}

void CCMap::Draw()
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
	D3DXMatrixIdentity(&matWorld);
	m_pDeive->SetFVF(D3DXFVF_CUSTOMVERTEX2);
	m_pDeive->SetStreamSource(0, m_pVerBuff, 0, sizeof(CUSTOMVERTEX2));
	m_pDeive->SetIndices(m_pIndexBuff);
	m_pDeive->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDeive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDeive->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDDIFFUSEALPHA);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_pDeive->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDeive->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	m_pDeive->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_pDeive->SetTexture(0, m_pText);
	m_pDeive->SetTexture(1, m_pText2);
	m_pDeive->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDeive->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDeive->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	m_pDeive->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDeive->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDeive->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	static float a = 0;
	a += 0.01;
	mat._31 = a;
	/*m_pDeive->SetTransform(D3DTS_TEXTURE1, &mat);
	m_pDeive->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);*/
	//m_pDeive->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, VertexNum, 0, IndexNum / 3);
	m_pDeive->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			//裁剪模式为不裁剪return S_OK;
	//m_pDeive->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_Mesh->DrawSubset(0);
	m_pDeive->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDeive->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);//关闭颜色混合 图层1
	D3DXMatrixIdentity(&mat);
	m_pDeive->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//关闭颜色混合 图层2
	//m_pDeive->SetTransform(D3DTS_TEXTURE1, &mat);
	//m_pDeive->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);

}

DWORD CCMap::GetWidth()
{
	return Width;
}

DWORD CCMap::GetHeight()
{
	return Height;
}

D3DXVECTOR3 CCMap::GetPosY(D3DXVECTOR3 pos)
{
	DWORD row = (m_vPos.z - pos.z) / height;
	DWORD col = (pos.x - m_vPos.x) / width;
	D3DXVECTOR3 pt[4] = { m_CustomVer[row * (127 * aa + 1) + col].pos ,m_CustomVer[row * (127 * aa + 1) + col + 1].pos,m_CustomVer[(row + 1) * (127 * aa + 1) + col + 1].pos,m_CustomVer[(row + 1) * (127 * aa + 1) + col].pos };
	/*D3DXVECTOR3 a = pt[0];
	a = pt[1];
	a = pt[2];
	a = pt[3];*/
	float lengthx = (pos - pt[3]).x;
	float lengthz = (pos - pt[3]).z;
	float f = lengthx / width;
	float g = lengthz / height;
	if (f + g > 1)
	{
		f = 1 - f;
		g = 1 - g;
		D3DXVec3BaryCentric(&pos, &pt[1], &pt[0], &pt[2], f, g);
	}
	else
	{
		D3DXVec3BaryCentric(&pos, &pt[3], &pt[2], &pt[0], f, g);
	}
	return pos;
}

D3DXMATRIX CCMap::GetMatInverse()
{
	return m_matInverse;
}

LPD3DXMESH CCMap::GetMesh()
{
	return m_Mesh;
}

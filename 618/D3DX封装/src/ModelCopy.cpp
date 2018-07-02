#include "stdafx.h"
#include "ModelCopy.h"
#include "SceneManager.h"

CModelCopy::CModelCopy()
{
	m_lType = OB_TYPE_MODEL_COPY;
}


CModelCopy::~CModelCopy()
{

}

BOOL CModelCopy::Init(TiXmlElement* element)
{
	TiXmlElement *childNode = element->FirstChildElement("BindMesh");
	name = childNode->GetText();
	m_pBindModle = (CModel*)CSceneManager::GetInstance()->GetObjectByName(name);
	if (m_pBindModle)
	{
		childNode = element->FirstChildElement("Pos");
		m_vPos.x = atoi(childNode->Attribute("x"));
		m_vPos.y = atoi(childNode->Attribute("y"));
		m_vPos.z = atoi(childNode->Attribute("z"));

		childNode = element->FirstChildElement("Scale");
		Scalex = atof(childNode->Attribute("scalex"));
		Scaley = atof(childNode->Attribute("scaley"));
		Scalez = atof(childNode->Attribute("scalez"));

		childNode = element->FirstChildElement("Roate");
		RoteX = atof(childNode->Attribute("x"));
		RoteY = atof(childNode->Attribute("y"));
		RoteZ = atof(childNode->Attribute("z"));
		Roate = atoi(childNode->GetText());

		if (childNode = element->FirstChildElement("Translation"))
		{
			TranslationX = atof(childNode->Attribute("x"));
			TranslationY = atof(childNode->Attribute("y"));
			TranslationZ = atof(childNode->Attribute("z"));
			Translation = atoi(childNode->GetText());
		}
		D3DXMATRIX MatRotX, MatRotY, MatRotZ, MatSoll, MatT;
		D3DXMatrixRotationX(&MatRotX, RoteX);
		D3DXMatrixRotationY(&MatRotY, RoteY);
		D3DXMatrixRotationZ(&MatRotZ, RoteZ);

		D3DXMatrixTranslation(&MatT, m_vPos.x+1500, m_vPos.y, m_vPos.z);
		D3DXMatrixScaling(&MatSoll, Scalex, Scaley, Scalez);
		matWorld = MatSoll * MatRotX*MatRotY*MatRotZ*MatT;
		D3DXMatrixInverse(&m_matInverse, NULL, &matWorld);
		TranslationY1 = TranslationY;
		return TRUE;
	}else
	return FALSE;
}

void CModelCopy::Draw()
{
	
	
	if (Translation)
	{
		if (m_vPos.y >= 362)
			flag = false;
		if (m_vPos.y <= 120)
			flag = true;
		if (flag)
			m_vPos.y++;
		//TranslationY1 = TranslationY;
		else
			m_vPos.y--;
			//TranslationY1 = -TranslationY;
		//m_vPos.y += TranslationY1 * Scaley;
		//D3DXMatrixTranslation(&MatT, TranslationX, TranslationY1, TranslationZ);
		//matWorld = MatT * matWorld;
		D3DXMATRIX MatRotX, MatRotY, MatRotZ, MatSoll, MatT;
		D3DXMatrixRotationX(&MatRotX, RoteX);
		D3DXMatrixRotationY(&MatRotY, RoteY);
		D3DXMatrixRotationZ(&MatRotZ, RoteZ);

		D3DXMatrixTranslation(&MatT, m_vPos.x + 1500, m_vPos.y, m_vPos.z);
		D3DXMatrixScaling(&MatSoll, Scalex, Scaley, Scalez);
		matWorld = MatSoll * MatRotX*MatRotY*MatRotZ*MatT;
		D3DXMatrixInverse(&m_matInverse, NULL, &matWorld);
	}
	((CRenderObject*)m_pBindModle)->SetWorldMatrix(matWorld);
	m_pBindModle->Draw();
}

CModel * CModelCopy::GetCModel()
{
	return m_pBindModle;
}

D3DXMATRIX CModelCopy::GetMatInverse()
{

	return m_matInverse;
}

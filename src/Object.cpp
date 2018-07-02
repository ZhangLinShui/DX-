#include "stdafx.h"
#include "Object.h"

//构造函数
CObject::CObject()
{
	m_lType = OB_TYPE_NOTYPE;
	m_vPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vPos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//析构函数
CObject::~CObject()
{

}



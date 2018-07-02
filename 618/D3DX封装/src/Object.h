//���������еĺ�ͼ����Ⱦ��صĶ���Ļ���
//���������,�ƹ�,��Ⱦ�ľ�̬,��̬����
#pragma once

#include "EngineDef.h"
#include "Picture.h"
class CObject
{
public:

	//���캯��
	CObject();

	//��������
	virtual ~CObject();

	virtual void Draw() {}
	virtual BOOL Init(TiXmlElement *node) = 0;
	//���ö�����豸����
	void SetDevice(IDirect3DDevice9* pDevice)					{m_pDevice = pDevice;}

	//��ö�����豸����
	IDirect3DDevice9* GetDevice(void)							{return m_pDevice;}

	//��ȡ���������
	long GetType(void)											{return m_lType;}

	//���ö����λ��(���������ʵ��)
	virtual void SetPos(D3DXVECTOR3 pos)						{m_vPos = pos;}
	virtual void SetPos1(D3DXVECTOR3 pos)						{ m_vPos1 = pos; }
	virtual void SetPos(float posX, float posY, float posZ)		{ m_vPos.x = posX; m_vPos.y = posY; m_vPos.z = posZ; }
	virtual void SetPos1(float posX, float posY, float posZ)	{ m_vPos1.x = posX; m_vPos1.y = posY; m_vPos1.z = posZ; }
	virtual void ChangePos(D3DXVECTOR3 pos)
	{
		m_vPos += pos;
	}
	//��ö����λ��(���������ʵ��)
	virtual D3DXVECTOR3 GetPos(void)							
	{ 
		return m_vPos;
	}
	virtual D3DXVECTOR3 GetPos1(void)							
	{ 
		return m_vPos1; 
	}
protected:

	//Object������()
	long m_lType;

	//Object�����糡���е�λ��
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vPos1;
	//D3D�豸����
	IDirect3DDevice9* m_pDevice;
};

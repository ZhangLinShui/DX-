//场景上所有的和图形渲染相关的对象的基类
//包括摄像机,灯光,渲染的静态,动态物体
#pragma once

#include "EngineDef.h"
#include "Picture.h"
class CObject
{
public:

	//构造函数
	CObject();

	//析构函数
	virtual ~CObject();

	virtual void Draw() {}
	virtual BOOL Init(TiXmlElement *node) = 0;
	//设置对象的设备对象
	void SetDevice(IDirect3DDevice9* pDevice)					{m_pDevice = pDevice;}

	//获得对象的设备对象
	IDirect3DDevice9* GetDevice(void)							{return m_pDevice;}

	//获取对象的类型
	long GetType(void)											{return m_lType;}

	//设置对象的位置(子类可重新实现)
	virtual void SetPos(D3DXVECTOR3 pos)						{m_vPos = pos;}
	virtual void SetPos1(D3DXVECTOR3 pos)						{ m_vPos1 = pos; }
	virtual void SetPos(float posX, float posY, float posZ)		{ m_vPos.x = posX; m_vPos.y = posY; m_vPos.z = posZ; }
	virtual void SetPos1(float posX, float posY, float posZ)	{ m_vPos1.x = posX; m_vPos1.y = posY; m_vPos1.z = posZ; }
	virtual void ChangePos(D3DXVECTOR3 pos)
	{
		m_vPos += pos;
	}
	//获得对象的位置(子类可重新实现)
	virtual D3DXVECTOR3 GetPos(void)							
	{ 
		return m_vPos;
	}
	virtual D3DXVECTOR3 GetPos1(void)							
	{ 
		return m_vPos1; 
	}
protected:

	//Object的类型()
	long m_lType;

	//Object在世界场景中的位置
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vPos1;
	//D3D设备对象
	IDirect3DDevice9* m_pDevice;
};

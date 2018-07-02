//////////////////////////////////////////////////////////////////////////
//Name:GraphSystem.h

//游戏中的图形渲染系统
//所有的引擎中的对象都在这个类中协同工作
//所有的图形渲染逻辑都在这个类中定义
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "GUIManager.h"	
#include "SceneManager.h"

class CGraphSystem:public IObserver
{
public:

	//构造函数
	CGraphSystem();

	//析构函数
	~CGraphSystem();

	//初始化图形系统
	bool Init(void);

	//发送状态接口
	void Notify(IObservable* pObservable,IObject* Arg);

	//接收状态接口
	void Update(IObservable* pObservable,IObject* Arg);

	//渲染当前帧
	bool Render();

protected:

	//向场景管理器里注册Object,只在图形系统内部使用
	//void RegisterObjectToSceneMgr();

	//在图形系统中已经绑定了的场景上的对象
	map<string,CObject*>	m_mapAttachedObject;
	vector<CModelCopy*>		m_vecStaticModel;
	vector<CCharacter*>		m_vecMoster;
	CGUIManager* m_pObservableGUI;

	//保存在系统里面的观察者模式控制器,一个系统可以有多个控制器,用于触发不同的事件
	CSceneManager* m_pObservableScene;

public:
	
	//渲染GUI对象
	void RenderGUI(void);

	//设置D3D设备对象
	void SetDevice(IDirect3DDevice9* pDevice)		{m_pDevice = pDevice;}

	//获得图形系统的光标标示,来设定新的光标
	long GetCursor(void)							{return m_lCursor;}


protected:
	//需要渲染的GUI组件
	list<CComponent*> m_listGUIComponent;
	list<CComponent*>::iterator m_listGUIComponentIT;

private:

	//D3D设备对象
	IDirect3DDevice9	*m_pDevice;
	ID3DXSprite			*m_pSprite;
	//鼠标光标的类型
	long m_lCursor;
	CWater				*m_pWater;
	CCMap				*m_pMap;
	CPlayer				*m_pPlayer;
	CSky				* m_pSky;
	CHourse				* m_pHourse;
	CBridge				* m_pBridge;
	CModelCopy			*m_pMeshManager;


};

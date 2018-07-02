//////////////////////////////////////////////////////////////////////////
//Name:SceneManager.h

//场景管理器主要负责场景的创建和销毁
//场景管理器负责对象的初始化,读取LUA的场景初始化脚本文件
//场景管理器每帧将需要渲染的对象加入一个渲染队列
//然后图形系统输出需要渲染的对象
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Observer.h"
#include "Object.h"

class CSceneManager: public IObservable
{
public:
	//析构函数
	~CSceneManager();
	//取得全局唯一的"场景管理器"的实例
	static CSceneManager* GetInstance();

	//初始化"场景管理器"
	bool Init(string fileName);

	//释放"场景管理器"
	void Release(void);

	//销毁一个场景
	void DestroyScene(void);

	//创建一个对象
	CObject* CreateObject(long objecttype,string objectname);

	//销毁一个对象
	void DestroyObject(string objectname);

	//返回场景管理器的对象容器MAP
	//供各个系统调用
	map<string,CObject*> GetSceneObject()		{return m_mapObject;}

	//设置D3D设备对象
	void SetDevice(IDirect3DDevice9* pDevice)	{m_pDevice = pDevice;}

	//通过对象名获得对象实体的指针
	CObject* GetObjectByName(string ObjectName)	{return m_mapObject[ObjectName];}

private:

	//单件模式下构造函数是私有的
	CSceneManager();

	

	//全局唯一的"场景管理器"的实例
	static CSceneManager* m_Instance;

	//场景管理器中的所有的对象
	map<string,CObject*> m_mapObject;

	//控制器里的ImapObject对象
	ImapObject* m_ImapObject;

	//标示场景里面有多少个对象
	long m_lNumOfObject;

	//D3D设备对象
	IDirect3DDevice9* m_pDevice;
};

CSceneManager* GetSceneMgr();

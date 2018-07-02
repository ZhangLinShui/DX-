//////////////////////////////////////////////////////////////////////////
//Name:Observer.h
//观察者模式的3个基类
//在FUNK引擎中,所有的"管理器"负责控制对象的创建和销毁1
//"管理器"类就是从IObservable控制器基类中派生出来的
//所有的"系统"负责控制对象的逻辑
//"系统"就是从IObserver观察者基类中派生出来的
//观察者需要将自己注册给控制器,那么控制器就会把观察者需要的数据传递给观察者
//传递的数据就是从IObject数据资源基类中派生出来的
//////////////////////////////////////////////////////////////////////////

#pragma once
#include"stdafx.h"
#include "BaseInterface.h"
#include "Button.h"
#include "Frame.h"
#include "Picture.h"
#include "ItemBox.h"
#include "EditBox.h"
#include "CheckBox.h"
#include "ListBox.h"
#include "Component.h"
#include "Object.h"
#include "CMap.h"

#include "Camera.h"
#include "Player.h"
#include "Sky.h"
//#include"Clight.h"
#include "Water.h"
#include "Bridge.h"
#include "Hourse.h"
#include "Model.h"
#include "ModelCopy.h"
#include "MultiAnim.h"
#include "Character.h"

//数据资源
class IObject
{

};

//控制器(各管理器基类)的声明
class IObservable;

//观察者(各系统基类)
class IObserver
{
public:

	//观察者(各个系统)当数据资源发生改变后发送至控制器(各个管理器)
	virtual void Notify(IObservable* pObservable,IObject* Arg) = 0;

	//观察者(各个系统)接收到控制器发送过来的消息后进行消息处理时所调用的接口
	virtual void Update(IObservable* pObservable,IObject* Arg) = 0;
};

//控制器(各管理器基类)
class IObservable
{
public:

	//在控制器里添加一个观察者(系统把自己注册进某个管理器,这样管理器就可以往这个系统发送消息)
	bool RegisterObserver(IObserver* pObserver)
	{
		if(m_setObservers.find(pObserver) != m_setObservers.end())
		{
			return false;
		}
		m_setObservers.insert(pObserver);
		return true;
	}

	//在控制器里删除一个观察者
	bool RemoveObserver(IObserver* pObserver)
	{
		if(m_setObservers.find(pObserver) == m_setObservers.end())
		{
			return false;
		}
		m_setObservers.erase(pObserver);
		return true;
	}

	//通知注册了的观察者数据对象发生改变
	void NotifyObserver(IObject* pObject)
	{
		for(set<IObserver*>::iterator it = m_setObservers.begin() ; it != m_setObservers.end(); ++it)
		{
			(*it)->Update(this,pObject);
		}
	}

protected:

	//注册了的观察者的SET容器  map<,>
	set<IObserver*> m_setObservers;
};

//具象化了的数据资源ImapObject(在场景管理器中使用)
class ImapObject: public IObject
{
public:
	string ObjectName;	//对象的名称
	CObject* Object;	//对象的实体
};

//具象化了的数据资源IComponent
class IComponent : public IObject
{
public:
	string ComponentName;	//组件的名称
	CComponent* Component;	//组件的实体
};


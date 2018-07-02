//////////////////////////////////////////////////////////////////////////
//Name:Observer.h
//�۲���ģʽ��3������
//��FUNK������,���е�"������"������ƶ���Ĵ���������1
//"������"����Ǵ�IObservable����������������������
//���е�"ϵͳ"������ƶ�����߼�
//"ϵͳ"���Ǵ�IObserver�۲��߻���������������
//�۲�����Ҫ���Լ�ע���������,��ô�������ͻ�ѹ۲�����Ҫ�����ݴ��ݸ��۲���
//���ݵ����ݾ��Ǵ�IObject������Դ����������������
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

//������Դ
class IObject
{

};

//������(������������)������
class IObservable;

//�۲���(��ϵͳ����)
class IObserver
{
public:

	//�۲���(����ϵͳ)��������Դ�����ı������������(����������)
	virtual void Notify(IObservable* pObservable,IObject* Arg) = 0;

	//�۲���(����ϵͳ)���յ����������͹�������Ϣ�������Ϣ����ʱ�����õĽӿ�
	virtual void Update(IObservable* pObservable,IObject* Arg) = 0;
};

//������(������������)
class IObservable
{
public:

	//�ڿ����������һ���۲���(ϵͳ���Լ�ע���ĳ��������,�����������Ϳ��������ϵͳ������Ϣ)
	bool RegisterObserver(IObserver* pObserver)
	{
		if(m_setObservers.find(pObserver) != m_setObservers.end())
		{
			return false;
		}
		m_setObservers.insert(pObserver);
		return true;
	}

	//�ڿ�������ɾ��һ���۲���
	bool RemoveObserver(IObserver* pObserver)
	{
		if(m_setObservers.find(pObserver) == m_setObservers.end())
		{
			return false;
		}
		m_setObservers.erase(pObserver);
		return true;
	}

	//֪ͨע���˵Ĺ۲������ݶ������ı�
	void NotifyObserver(IObject* pObject)
	{
		for(set<IObserver*>::iterator it = m_setObservers.begin() ; it != m_setObservers.end(); ++it)
		{
			(*it)->Update(this,pObject);
		}
	}

protected:

	//ע���˵Ĺ۲��ߵ�SET����  map<,>
	set<IObserver*> m_setObservers;
};

//�����˵�������ԴImapObject(�ڳ�����������ʹ��)
class ImapObject: public IObject
{
public:
	string ObjectName;	//���������
	CObject* Object;	//�����ʵ��
};

//�����˵�������ԴIComponent
class IComponent : public IObject
{
public:
	string ComponentName;	//���������
	CComponent* Component;	//�����ʵ��
};


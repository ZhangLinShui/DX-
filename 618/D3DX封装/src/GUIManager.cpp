#include "stdafx.h"
#include "GUIManager.h"
#include "Button.h"
#include "CheckBox.h"
#include "EditBox.h"
#include "Frame.h"
#include "UIPicture.h"
#include "ItemBox.h"
#include "StaticText.h"
#include "ListBox.h"
//��̬��Ա�ĳ�ʼ��
CGUIManager* CGUIManager::m_Instance = NULL;


//��ȡȫ��Ψһ��GUI�������Ķ���
CGUIManager* CGUIManager::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new CGUIManager();
	}
	return m_Instance;
}

//���캯��
CGUIManager::CGUIManager()
{
	m_ImapComponent = new IComponent();
	m_pDevice = NULL;
}

//��������
CGUIManager::~CGUIManager()
{
	Release();
	SAFE_DELETE(m_ImapComponent);
}

//��ʼ��GUI������
bool CGUIManager::Init(string fileName)
{
	//���ز�����GUIϵͳ�Ľű�
	TiXmlDocument curFile(fileName.c_str());

	if (curFile.LoadFile())
	{
		TiXmlElement *root = curFile.FirstChildElement("UIManager");
		for (TiXmlElement * node = root->FirstChildElement("UIInterface"); node; node = node->NextSiblingElement("UIInterface"))
		{
			string xmlFileName = node->GetText();

			LoadPage(xmlFileName);
		}
	}
	return true;
}

//�ͷ�GUI������
void CGUIManager::Release()
{
	for (m_mapComponentIT = m_mapComponent.begin(); m_mapComponentIT != m_mapComponent.end(); ++m_mapComponentIT)
	{
		SAFE_DELETE(m_mapComponentIT->second);
	}
	m_mapComponent.clear();
	m_Instance = NULL;
}

//����һ��PAGE
bool CGUIManager::LoadPage(string PageName)
{
	TiXmlDocument curFile(PageName.c_str());

	if (curFile.LoadFile())
	{
		TiXmlElement *root = curFile.FirstChildElement("UIInterface");
		for (TiXmlElement * node = root->FirstChildElement("UIElement"); node; node = node->NextSiblingElement("UIElement"))
		{
			CComponent* component = nullptr;
			int type = atoi(node->Attribute("Type"));
			string name = node->Attribute("Name");
			string parentName = node->Attribute("ParentName");
			int childnum = atoi(node->Attribute("ParentID"));
			component = CreateComponent(type, name);

			if (!parentName.empty())
			{
				component->SetParent(m_mapComponent[parentName]);
				m_mapComponent[parentName]->AddChild(component, childnum);
			}
			else
				component->SetParent(nullptr);

			component->Init(node);

		}
	}
	return true;
}

//����һ��GUI���
CComponent* CGUIManager::CreateComponent(long ComponentType, string ComponentName)
{
	CComponent* component = NULL;

	switch (ComponentType)
	{
	case GUI_TYPE_BUTTON:
		component = new CButton();
		break;
	case GUI_TYPE_FRAME:
		component = new CFrame();
		break;
	case GUI_TYPE_PIC:
		component = new CUIPicture();
		break;
	case GUI_TYPE_ITEMBOX:
		component = new CItemBox();
		break;
	case GUI_TYPE_STATICTEXT:
		component = new CStaticText();
		break;
	case GUI_TYPE_EDITBOX:
		component = new CEditBox();
		break;
	case GUI_TYPE_CHECKBOX:
		component = new CCheckBox();
		break;
	case GUI_TYPE_LISTBOX:
		component = new CListBox();
		break;
	}

	//�����豸����
	component->SetDevice(m_pDevice);

	//���þ������
	component->SetSprite();

	m_mapComponent[ComponentName] = component;

	m_ImapComponent->ComponentName = ComponentName;
	m_ImapComponent->Component = component;

	//֪ͨͼ��ϵͳ����GUI�������Ⱦ����
	NotifyObserver(m_ImapComponent);

	return component;
}




//��������ƶ����¼���Ӧ
void CGUIManager::ProcessMouseMove(long x, long y)
{
	bool tempBeMoveTo = false;
	CComponent::m_BeingMovetoComponent = NULL;

	for (m_mapComponentIT = m_mapComponent.begin(); m_mapComponentIT != m_mapComponent.end(); ++m_mapComponentIT)
	{
		//�ж�����Ƿ�ɼ�
		if ((m_mapComponentIT->second)->IsVisible())
		{
			//�ж�����Ƿ��������
			(m_mapComponentIT->second)->ProcessMouseMove(x, y);
			//ֻҪ������κ�һ�������λ����
			if (CComponent::m_BeingMovetoComponent)
			{
				//OutputDebugString(CComponent::m_BeingMovetoComponent->GetName());
				//OutputDebugString("4444444444\n");
				//��ô�ͱ�ʾҪ����GUI��,�����ʱ����ΪTRUE�ʹ���GUI,FALSE�ʹ������������
				tempBeMoveTo = true;
			}
		}
	}


	//����ط��������жϵ�ǰ�����û����ִ��GUIϵͳ
	if (tempBeMoveTo)
	{
		CComponent::m_bProcessGUI = true;
	}
	else
	{
		CComponent::m_bProcessGUI = false;
		CComponent::m_BeingMovetoComponent = NULL;
	}

}

//�������������µ��¼���Ӧ
void CGUIManager::ProcessMouseLBDown(long x, long y)
{
	
}

//����������������¼���Ӧ
void CGUIManager::ProcessMouseLBUp(long x, long y)
{
	for (m_mapComponentIT = m_mapComponent.begin(); m_mapComponentIT != m_mapComponent.end(); ++m_mapComponentIT)
	{
		//�ж�����Ƿ�ɼ�
		if ((m_mapComponentIT->second)->IsVisible())
		{
			(m_mapComponentIT->second)->ProcessMouseLBUp(x, y);
		}
	}
}

//��������Ҽ����µ��¼���Ӧ
void CGUIManager::ProcessMouseRBDown(long x, long y)
{

}

//��������Ҽ�������¼���Ӧ
void CGUIManager::ProcessMouseRBUp(long x, long y)
{

}

//���������ֹ������¼���Ӧ
void CGUIManager::ProcessMouseWheel()
{

}

//���һ�������ָ��
//����Ϊ����������
CComponent* CGUIManager::GetComponentByName(string ComponentName)
{
	return m_mapComponent[ComponentName];
}

CGUIManager* GetGUIMgr()
{
	return CGUIManager::GetInstance();
}
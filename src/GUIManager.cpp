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
//静态成员的初始化
CGUIManager* CGUIManager::m_Instance = NULL;


//获取全局唯一的GUI管理器的对象
CGUIManager* CGUIManager::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new CGUIManager();
	}
	return m_Instance;
}

//构造函数
CGUIManager::CGUIManager()
{
	m_ImapComponent = new IComponent();
	m_pDevice = NULL;
}

//析构函数
CGUIManager::~CGUIManager()
{
	Release();
	SAFE_DELETE(m_ImapComponent);
}

//初始化GUI管理器
bool CGUIManager::Init(string fileName)
{
	//加载并编译GUI系统的脚本
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

//释放GUI管理器
void CGUIManager::Release()
{
	for (m_mapComponentIT = m_mapComponent.begin(); m_mapComponentIT != m_mapComponent.end(); ++m_mapComponentIT)
	{
		SAFE_DELETE(m_mapComponentIT->second);
	}
	m_mapComponent.clear();
	m_Instance = NULL;
}

//创建一个PAGE
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

//创建一个GUI组件
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

	//设置设备对象
	component->SetDevice(m_pDevice);

	//设置精灵对象
	component->SetSprite();

	m_mapComponent[ComponentName] = component;

	m_ImapComponent->ComponentName = ComponentName;
	m_ImapComponent->Component = component;

	//通知图形系统更新GUI对象的渲染队列
	NotifyObserver(m_ImapComponent);

	return component;
}




//处理鼠标移动的事件响应
void CGUIManager::ProcessMouseMove(long x, long y)
{
	bool tempBeMoveTo = false;
	CComponent::m_BeingMovetoComponent = NULL;

	for (m_mapComponentIT = m_mapComponent.begin(); m_mapComponentIT != m_mapComponent.end(); ++m_mapComponentIT)
	{
		//判断组件是否可见
		if ((m_mapComponentIT->second)->IsVisible())
		{
			//判断鼠标是否在组件上
			(m_mapComponentIT->second)->ProcessMouseMove(x, y);
			//只要鼠标在任何一个组件的位置上
			if (CComponent::m_BeingMovetoComponent)
			{
				//OutputDebugString(CComponent::m_BeingMovetoComponent->GetName());
				//OutputDebugString("4444444444\n");
				//那么就表示要处理GUI了,这个临时变量为TRUE就处理GUI,FALSE就处理摄像机控制
				tempBeMoveTo = true;
			}
		}
	}


	//这个地方就用来判断当前鼠标有没有在执行GUI系统
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

//处理鼠标左键按下的事件响应
void CGUIManager::ProcessMouseLBDown(long x, long y)
{
	
}

//处理鼠标左键弹起的事件响应
void CGUIManager::ProcessMouseLBUp(long x, long y)
{
	for (m_mapComponentIT = m_mapComponent.begin(); m_mapComponentIT != m_mapComponent.end(); ++m_mapComponentIT)
	{
		//判断组件是否可见
		if ((m_mapComponentIT->second)->IsVisible())
		{
			(m_mapComponentIT->second)->ProcessMouseLBUp(x, y);
		}
	}
}

//处理鼠标右键按下的事件响应
void CGUIManager::ProcessMouseRBDown(long x, long y)
{

}

//处理鼠标右键弹起的事件响应
void CGUIManager::ProcessMouseRBUp(long x, long y)
{

}

//处理鼠标滚轮滚动的事件响应
void CGUIManager::ProcessMouseWheel()
{

}

//获得一个组件的指针
//参数为这个组件名字
CComponent* CGUIManager::GetComponentByName(string ComponentName)
{
	return m_mapComponent[ComponentName];
}

CGUIManager* GetGUIMgr()
{
	return CGUIManager::GetInstance();
}
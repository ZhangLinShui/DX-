#include "stdafx.h"
#include "Frame.h"
 
//构造函数
CFrame::CFrame():CComponent()
{
	m_lType = GUI_TYPE_FRAME;
}

//析构函数
CFrame::~CFrame()
{

}

void CFrame::Init(TiXmlElement* element)
{
	CComponent::Init(element);
	this->SetPicture(element->FirstChildElement("FramePicture")->GetText());
}
//处理鼠标左键按下的事件响应
void CFrame::ProcessMouseLBDown(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//如果没有子组件
		if (m_mapChildren.empty())
		{
			//设置焦点组件
			CComponent::m_BeingDownComponent = this;
			//OutputDebugString(m_BeingDownComponent->GetName());
			//OutputDebugString("Down1111111\n");
		}
		//如果有子组件
		else
		{
			//遍历所有的子组件,判断鼠标有没有移动到他们上面
			for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
			{
				if ((m_mapChildrenIT->second) == m_BeingMovetoComponent)
				{
					return;
				}
			}
			//设置焦点组件
			CComponent::m_BeingDownComponent = this;
			//OutputDebugString(m_BeingDownComponent->GetName());
			//OutputDebugString("Down222222222\n");
		}
	}
}

//处理鼠标左键弹起的事件响应
void CFrame::ProcessMouseLBUp(long x,long y)
{
	//CComponent::m_BeDrag = false;
}

//处理鼠标移动的事件响应
void CFrame::ProcessMouseMove(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//如果没有子组件
		if (m_mapChildren.empty())
		{
			//设置焦点组件
			m_lState = COMPONENT_STATE_MOVETO;
			m_BeingMovetoComponent = this;

			//OutputDebugString(m_BeingDownComponent->GetName());
			//OutputDebugString("Down222222222\n");
		}
		//如果有子组件
		else
		{
			//遍历所有的子组件,判断鼠标有没有移动到他们上面
			for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
			{
				if ((m_mapChildrenIT->second) == m_BeingMovetoComponent)
				{
					return ;
				}
			}
			//设置焦点组件
			m_lState = COMPONENT_STATE_MOVETO;
			m_BeingMovetoComponent = this;

		}
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
		//.m_BeingMovetoComponent = NULL;
	} 
	//如果处于拖曳中
	//if (m_BeingMovetoComponent == this)
	//{
	///	SetPos(float(x),float(y));
	//}

}
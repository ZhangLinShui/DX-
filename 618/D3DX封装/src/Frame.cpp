#include "stdafx.h"
#include "Frame.h"
 
//���캯��
CFrame::CFrame():CComponent()
{
	m_lType = GUI_TYPE_FRAME;
}

//��������
CFrame::~CFrame()
{

}

void CFrame::Init(TiXmlElement* element)
{
	CComponent::Init(element);
	this->SetPicture(element->FirstChildElement("FramePicture")->GetText());
}
//�������������µ��¼���Ӧ
void CFrame::ProcessMouseLBDown(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//���û�������
		if (m_mapChildren.empty())
		{
			//���ý������
			CComponent::m_BeingDownComponent = this;
			//OutputDebugString(m_BeingDownComponent->GetName());
			//OutputDebugString("Down1111111\n");
		}
		//����������
		else
		{
			//�������е������,�ж������û���ƶ�����������
			for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
			{
				if ((m_mapChildrenIT->second) == m_BeingMovetoComponent)
				{
					return;
				}
			}
			//���ý������
			CComponent::m_BeingDownComponent = this;
			//OutputDebugString(m_BeingDownComponent->GetName());
			//OutputDebugString("Down222222222\n");
		}
	}
}

//����������������¼���Ӧ
void CFrame::ProcessMouseLBUp(long x,long y)
{
	//CComponent::m_BeDrag = false;
}

//��������ƶ����¼���Ӧ
void CFrame::ProcessMouseMove(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//���û�������
		if (m_mapChildren.empty())
		{
			//���ý������
			m_lState = COMPONENT_STATE_MOVETO;
			m_BeingMovetoComponent = this;

			//OutputDebugString(m_BeingDownComponent->GetName());
			//OutputDebugString("Down222222222\n");
		}
		//����������
		else
		{
			//�������е������,�ж������û���ƶ�����������
			for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
			{
				if ((m_mapChildrenIT->second) == m_BeingMovetoComponent)
				{
					return ;
				}
			}
			//���ý������
			m_lState = COMPONENT_STATE_MOVETO;
			m_BeingMovetoComponent = this;

		}
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
		//.m_BeingMovetoComponent = NULL;
	} 
	//���������ҷ��
	//if (m_BeingMovetoComponent == this)
	//{
	///	SetPos(float(x),float(y));
	//}

}
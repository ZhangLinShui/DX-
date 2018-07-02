#include "stdafx.h"
#include "Button.h"
#include "BaseInterface.h"
 
//���캯��
CButton::CButton():CComponent()
{
	//��ʾ�������Ϊ��ť�ؼ�
	m_lType = GUI_TYPE_BUTTON;
	m_pTexDefault = NULL;
	m_pTexDown = NULL;
	m_pTexMoveto = NULL;
	m_pTexNow = NULL;
	//��ǰ��״̬����ͨ״̬
	m_lState = COMPONENT_STATE_NORMAL;
}

void CButton::Init(TiXmlElement* element)
{
	CComponent::Init(element);
	this->SetTextureDefault(element->FirstChildElement("ButtonPictureDefault")->GetText());
	this->SetTextureMoveto(element->FirstChildElement("ButtonPictureMoveto")->GetText());
	this->SetTextureDown(element->FirstChildElement("ButtonPictureDown")->GetText());

	m_strFunctionName = element->FirstChildElement("EventProcName")->GetText();
}
//��������
CButton::~CButton()
{
	SAFE_RELEASE(m_pTexDefault);
	SAFE_RELEASE(m_pTexDown);
	SAFE_RELEASE(m_pTexMoveto);
	SAFE_RELEASE(m_pTexNow);
}

//�������
void CButton::Draw()
{
	//�����жϵ�ǰ�İ�ť״̬��ȷ��������ͼƬ����Ⱦ
	switch(m_lState)
	{
	case COMPONENT_STATE_NORMAL:
		m_pTexNow = m_pTexDefault;
		break;
	case COMPONENT_STATE_MOVETO:
		m_pTexNow = m_pTexMoveto;
		break;
	}

	//ͨ���ж��������Ƿ��¼�ʱ����Ӧ������Ϣ,������ͼƬ���л�
	if (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1:0))
	{
		if (CComponent::m_BeingMovetoComponent == this)
		{
			m_pTexNow = m_pTexDown;
		}
	}

	//����λ�þ���
	D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);

	//���ڼ��ص���TGAͼƬ,Ҫ��ALPHAͨ�����ܽ���͸����Ⱦ
	if (m_bAlpha)
	{
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		m_pSprite->Begin(0);
		m_pSprite->SetTransform(&m_matPos);
		m_pSprite->Draw(m_pTexNow,NULL,NULL,NULL,0xffffffff);
		m_pSprite->End();
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
	} 
	else
	{
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		m_pSprite->Begin(0);
		m_pSprite->SetTransform(&m_matPos);
		m_pSprite->Draw(m_pTexNow,NULL,NULL,NULL,0xffffffff);
		m_pSprite->End();
	}
}

//������̵��¼���Ӧ
void CButton::ProcessKeyEvent(char key)
{
	//�������ļ��������BUTTON�Ŀ�ݼ���ͬ
	if (key == m_cHotKey)
	{
		//ִ��BUTTON��Ӧ���¼�
		this->DoEvent();
	}
}

//��������ƶ����¼���Ӧ
void CButton::ProcessMouseMove(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//���������Ѿ����ڰ���״̬
		if (m_lState == COMPONENT_STATE_DOWN)
		{
			return;
		}
		else
		{
			m_lState = COMPONENT_STATE_MOVETO;
		}
		m_BeingMovetoComponent = this;
		//OutputDebugString(m_BeingMovetoComponent->GetName());
		//OutputDebugString("33333333\n");
		//m_BeingDownComponent = this;
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
}

//�������������µ��¼���Ӧ
void CButton::ProcessMouseLBDown(long x,long y)
{
	//�жϴ����X,Y�����Ƿ������������
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//���ð�ť��״̬ΪCOMPONENT_STATE_MOVETO
		m_lState = COMPONENT_STATE_DOWN;
		CComponent::m_BeingDownComponent = this;
		
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
}

//����������������¼���Ӧ
void CButton::ProcessMouseLBUp(long x,long y)
{
	//�жϴ����X,Y�����Ƿ������������
	if (x >= m_BeingDownComponent->GetRect().left && x <= m_BeingDownComponent->GetRect().right && y >= m_BeingDownComponent->GetRect().top && y <= m_BeingDownComponent->GetRect().bottom)
	{
		//���ð�ť��״̬ΪCOMPONENT_STATE_MOVETO
		m_lState = COMPONENT_STATE_MOVETO;

		//ִ�а�ť��Ӧ���¼�
		this->DoEvent();
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
	CComponent::m_BeingDownComponent = NULL;
	CComponent::m_BeingMovetoComponent = this;
}

////��������Ҽ����µ��¼���Ӧ
//void CButton::ProcessMouseRBDown(long x,long y)
//{
//	//�жϴ����X,Y�����Ƿ������������
//	if (m_ptPos.x >= m_Rect.left && m_ptPos.x <= m_Rect.right && m_ptPos.y >= m_Rect.top && m_ptPos.y <= m_Rect.bottom)
//	{
//		//���ð�ť��״̬ΪCOMPONENT_STATE_MOVETO
//		m_lState = COMPONENT_STATE_MOVETO;
//	}
//}

////��������Ҽ�������¼���Ӧ
//void CButton::ProcessMouseRBUp(long x,long y)
//{
//	//�жϴ����X,Y�����Ƿ������������
//	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
//	{
//		//���ð�ť��״̬ΪCOMPONENT_STATE_MOVETO
//		m_lState = COMPONENT_STATE_MOVETO;
//	}
//}

////���������ֹ������¼���Ӧ
//void CButton::ProcessMouseWheel()
//{
//	//�жϴ����X,Y�����Ƿ������������
//	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
//	{
//		//���ð�ť��״̬ΪCOMPONENT_STATE_MOVETO
//		m_lState = COMPONENT_STATE_MOVETO;
//	}
//}

//���ÿ�ݼ�
void CButton::SetHotKey(char CHotKey)
{
	m_cHotKey = CHotKey;
}

//��ť����Ӧ�ľ�����¼�(�û�����ĺ���)
void CButton::DoEvent()
{
	if (m_strFunctionName.empty())
	{
		return;
	}
	else
	{
		DoGlobeEvent(m_strFunctionName);
	}

}

//���ð�ť����Ӧ�ľ�����¼�(LUA����),����Ĳ�����LUA�ű��еĺ�����
void CButton::SetEvent(string FunctionName)
{
	m_strFunctionName = FunctionName;
}


//�ֱ����3��״̬�µ�ͼƬ��Դ
void CButton::SetTextureDefault(string TexDefault)
{
	HRESULT hr;
	//����Ĭ��״̬�µ�ͼƬ
	hr = D3DXCreateTextureFromFileEx(m_pDevice,TexDefault.c_str(),D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,D3DCOLOR_RGBA(0,0,0, 255),NULL,NULL,&m_pTexDefault);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf,"���������Դ%sʧ��",TexDefault.c_str());
		MessageBox(hWnd,buf,"����",MB_OK);
	}
}

void CButton::SetTextureMoveto(string TexMoveto)
{
	HRESULT hr;
	//�����ƶ���״̬�µ�ͼƬ
	hr = D3DXCreateTextureFromFileEx(m_pDevice,TexMoveto.c_str(),D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,D3DCOLOR_RGBA(0,0,0, 255),NULL,NULL,&m_pTexMoveto);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf,"���������Դ%sʧ��",TexMoveto.c_str());
		MessageBox(hWnd,buf,"����",MB_OK);
	}
}

void CButton::SetTextureDown(string TexDown)
{
	HRESULT hr;
	//���ذ���״̬�µ�ͼƬ
	hr = D3DXCreateTextureFromFileEx(m_pDevice,TexDown.c_str(),D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,D3DCOLOR_RGBA(0,0,0, 255),NULL,NULL,&m_pTexDown);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf,"���������Դ%sʧ��",TexDown.c_str());
		MessageBox(hWnd,buf,"����",MB_OK);
	}
}
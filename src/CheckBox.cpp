#include "stdafx.h"
#include "CheckBox.h"
 
//���캯��
CCheckBox::CCheckBox()
: CComponent()
, m_pCheckCursorTex(NULL)
, m_bShowCheckCursor(false)
, m_strFunctionName("")
{
	m_lType = GUI_TYPE_CHECKBOX;
	m_vCursorLeftUpPos.x = 0.0f;
	m_vCursorLeftUpPos.y = 0.0f;
	m_vCursorScale.x = 1.0f;
	m_vCursorScale.y = 1.0f;
}

//��������
CCheckBox::~CCheckBox()
{

}

//����"��"����
bool CCheckBox::SetCheckCursorPic(string filename)
{
	HRESULT hr = S_OK;
	hr = D3DXCreateTextureFromFile(m_pDevice,filename.c_str(),&m_pCheckCursorTex);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"����ѡ�������ʧ��","����ѡ�������ʧ��",MB_OK);
		return false;
	}
	return true;
}

//�������
void CCheckBox::Draw(void)
{
	if(m_pPic==NULL)
	{
		return;
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
		m_pSprite->Draw(m_pPic,NULL,NULL,NULL,0xffffffff);
		m_pSprite->End();
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
	} 
	else
	{
		m_pSprite->Begin(0);
		m_pSprite->SetTransform(&m_matPos);
		m_pSprite->Draw(m_pPic,NULL,NULL,NULL,0xffffffff);
		m_pSprite->End();
	}

	//������˹�
	if (m_bShowCheckCursor)
	{
		D3DXMATRIX matCursor;
		D3DXMatrixTransformation2D(&matCursor,NULL,0,&m_vCursorScale,NULL,0,&m_vCursorLeftUpPos);

		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		m_pSprite->Begin(0);
		m_pSprite->SetTransform(&matCursor);
		m_pSprite->Draw(m_pCheckCursorTex,NULL,NULL,NULL,0xffffffff);
		m_pSprite->End();
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
	}
}

//��������ƶ����¼���Ӧ
void CCheckBox::ProcessMouseMove(long x,long y)
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
	}
}

//�������������µ��¼���Ӧ
void CCheckBox::ProcessMouseLBDown(long x,long y)
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
void CCheckBox::ProcessMouseLBUp(long x,long y)
{
	//�жϴ����X,Y�����Ƿ������������
	if (x >= m_BeingDownComponent->GetRect().left && x <= m_BeingDownComponent->GetRect().right && y >= m_BeingDownComponent->GetRect().top && y <= m_BeingDownComponent->GetRect().bottom)
	{
		//���ð�ť��״̬ΪCOMPONENT_STATE_MOVETO
		m_lState = COMPONENT_STATE_MOVETO;

		//����"��"�����Ƿ���ʾ(��֮ǰ��״̬�෴)
		m_bShowCheckCursor = !m_bShowCheckCursor;

		//ִ�а�ť��Ӧ���¼�
		this->DoEvent();
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
	CComponent::m_BeingDownComponent = NULL;
}

//���ð�ť����Ӧ�ľ�����¼�(LUA����),����Ĳ�����LUA�ű��еĺ�����
void CCheckBox::SetEvent(string FunctionName)
{
	m_strFunctionName = FunctionName;
}

//��ť����Ӧ�ľ�����¼�(�û�����ĺ���)
void CCheckBox::DoEvent()
{
	if (m_strFunctionName.empty())
	{
		return;
	}
	else
	{
	
	}

}

//�����α�����Ͻǵ�����
void CCheckBox::SetCursorLeftUpPos(D3DXVECTOR2 vPos)
{
	m_vCursorLeftUpPos = vPos;
}
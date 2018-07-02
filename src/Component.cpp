#include "stdafx.h"
#include "Component.h"

CComponent* CComponent::m_BeingMovetoComponent = NULL;
CComponent* CComponent::m_BeingDownComponent = NULL;
CComponent* CComponent::m_BeingWithMouseComponent = NULL;
bool CComponent::m_bProcessGUI = false;

//���캯��
CComponent::CComponent()
	:m_strName("")
	, m_lType(GUI_TYPE_NOTYPE)
	, m_bVisible(false)
	, m_pSprite(NULL)
	, m_bEventEnable(false)
	, m_pPic(NULL)
	, m_pParent(NULL)
	, m_bDrag(false)
	, m_bAlpha(false)
	, m_Alpha(0xffffffff)
	, m_pDevice(NULL)
{
	m_vScale.x = 1.0f;
	m_vScale.y = 1.0f;
	D3DXMatrixIdentity(&m_matPos);
}

//��������
CComponent::~CComponent()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pPic);
	m_pParent = NULL;
}

//Ϊ�����������,����һΪ�������,������Ϊ������ڸ�����е��������
void CComponent::AddChild(CComponent* pChild, long index)
{
	if (NULL != pChild)
	{
		m_mapChildren[index] = pChild;
		pChild->SetParent(this);
	}
}

//��������Ƿ�ɼ�(�ݹ����,���е������ҲҪ�����Ƿ�ɼ�)
void CComponent::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
	//�������
	if (!m_mapChildren.empty())
	{
		for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
		{
			(m_mapChildrenIT->second)->SetVisible(bVisible);
		}
	}
}

//���������λ��(���Ͻ�,ͨ���������)
void CComponent::SetPos(float OffsetX, float OffsetY)
{
	m_ptPos.x += OffsetX;
	m_ptPos.y += OffsetY;
	m_Rect.left = (long)m_ptPos.x;
	m_Rect.right = (long)m_ptPos.x + m_lWidth;
	m_Rect.top = (long)m_ptPos.y;
	m_Rect.bottom = (long)m_ptPos.y + m_lHeight;
	//�������
	if (!m_mapChildren.empty())
	{
		for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
		{
			(m_mapChildrenIT->second)->SetPos(OffsetX, OffsetY);
		}
	}
}

//��������ĳߴ�
void CComponent::SetSize(long width, long height)
{
	m_lWidth = width;
	m_lHeight = height;
	m_Rect.left = (long)m_ptPos.x;
	m_Rect.right = (long)m_ptPos.x + m_lWidth;
	m_Rect.top = (long)m_ptPos.y;
	m_Rect.bottom = (long)m_ptPos.y + m_lHeight;
}

//Ϊ��������������
void CComponent::AddMouseListener()
{

}

//Ϊ�����Ӽ��̼�����
void CComponent::AddKeyListener()
{

}

//�������
void CComponent::Draw()
{
	//OutputDebugString("Draw start\n");
	if (m_pPic == NULL)
	{
		return;
	}
	//����λ�þ���
	D3DXMatrixTransformation2D(&m_matPos, NULL, 0, &m_vScale, NULL, 0, &m_ptPos);

	//���ڼ��ص���TGAͼƬ,Ҫ��ALPHAͨ�����ܽ���͸����Ⱦ
	if (m_bAlpha)
	{
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pSprite->Begin(0);
		m_pSprite->SetTransform(&m_matPos);
		m_pSprite->Draw(m_pPic, NULL, NULL, NULL, 0xffffffff);
		m_pSprite->End();
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
	else
	{
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		m_pSprite->Begin(0);
		m_pSprite->SetTransform(&m_matPos);
		m_pSprite->Draw(m_pPic, NULL, NULL, NULL, 0xffffffff);
		m_pSprite->End();
	}
	//OutputDebugString("Draw end\n");
}

//��������,�����ַ���,ͨ����ȡ�����������,���߻�ȡ�������������
CComponent* CComponent::GetChild(string name)
{
	for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
	{
		if (strcmp(name.c_str(), (m_mapChildrenIT->second)->GetName()) == 0)
		{
			return m_mapChildrenIT->second;
		}
	}
	return NULL;
}
//��������,�����ַ���,ͨ����ȡ�����������,���߻�ȡ�������������
CComponent* CComponent::GetChild(long index)
{
	return m_mapChildren[index];
}

//��������¼�
void CComponent::ProcessKeyEvent(char key)
{

}

//��������ƶ��¼�
void CComponent::ProcessMouseMove(long x, long y)
{

}

//�������������µ��¼���Ӧ
void CComponent::ProcessMouseLBDown(long x, long y)
{

}

//����������������¼���Ӧ
void CComponent::ProcessMouseLBUp(long x, long y)
{

}

//��������Ҽ����µ��¼���Ӧ
void CComponent::ProcessMouseRBDown(long x, long y)
{

}

//��������Ҽ�������¼���Ӧ
void CComponent::ProcessMouseRBUp(long x, long y)
{

}

//���������ֹ������¼���Ӧ
void CComponent::ProcessMouseWheel()
{

}

//���������ͼƬ
void CComponent::SetPicture(string filename)
{
	HRESULT hr;
	//���ذ���״̬�µ�ͼƬ
	hr = D3DXCreateTextureFromFileEx(m_pDevice, filename.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DCOLOR_RGBA(0, 0, 0, 255), NULL, NULL, &m_pPic);
	if (FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf, "���������Դ%sʧ��", filename.c_str());
		MessageBox(hWnd, buf, "����", MB_OK);
		return;
	}
}

//���þ������(����ͼ��ʱ���õ�ID3DXSprite�ӿ�)
void CComponent::SetSprite()
{
	if (m_pDevice)
	{
		D3DXCreateSprite(m_pDevice, &m_pSprite);
	}
	else
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd, "��Ϸ�豸����û�д���,���Բ��ܴ����������", "��Ϸ�豸����û�д���,���Բ��ܴ����������", MB_OK);
	}
}
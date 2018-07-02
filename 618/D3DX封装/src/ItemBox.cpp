#include "stdafx.h"
#include "ItemBox.h"
 
//���캯��
CItemBox::CItemBox()
{
	m_ItemPic = NULL;
	m_ItemFramePic = NULL;
	m_bPicPicked = false;
	m_lType = GUI_TYPE_ITEMBOX;
	m_bWithMouseMove = false;
	m_strPicFile.clear();
}

//��������
CItemBox::~CItemBox()
{
	SAFE_RELEASE(m_ItemPic);
	SAFE_RELEASE(m_ItemFramePic);
}

//��������λ�ϵ�ͼƬ
bool CItemBox::ChangeItemPic(string filename)
{
	HRESULT hr;
	//��ͼƬ���ļ�·��Ϊ��ʱ,����Ʒ����ͼƬ���(����Ҫ��Ⱦ)
	if ("" == filename)
	{
		m_ItemPic = NULL;
		SAFE_RELEASE(m_ItemPic);
		m_strPicFile = filename;
		return true;
	}

	if (m_strPicFile == filename)
	{
		return true;
	}

	m_strPicFile = filename;
	SAFE_RELEASE(m_ItemPic);

	//������λ�ı߿��ͼƬ
	hr = D3DXCreateTextureFromFileEx(m_pDevice,filename.c_str(),m_lItemPicWidth,m_lItemPicHeight,0,D3DUSAGE_DYNAMIC,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,
		D3DX_DEFAULT,D3DX_DEFAULT,0xffffffff,NULL,NULL,&m_ItemPic);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd,"����ͼƬ��Դʧ��","����ͼƬ��Դʧ��",MB_OK);
		return false;
	}
	return true;
}

//��������ƶ�������ϵ�ʱ����λ�ı߿��ͼƬ
bool CItemBox::SetItemFramePic(string filename)
{
	HRESULT hr;
	SAFE_RELEASE(m_ItemFramePic);

	//������λ�ı߿��ͼƬ
	hr = D3DXCreateTextureFromFileEx(m_pDevice,filename.c_str(),m_lWidth,m_lHeight,0,D3DUSAGE_DYNAMIC,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,
		D3DX_DEFAULT,D3DX_DEFAULT,0xffffffff,NULL,NULL,&m_ItemFramePic);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd,"����ͼƬ��Դʧ��","����ͼƬ��Դʧ��",MB_OK);
		return false;
	}
	return true;
}

//�������
void CItemBox::Draw()
{
	//�����Ʒ����ͼ��������������״̬
	if (this == CComponent::m_BeingWithMouseComponent)
	{
		if (m_ItemFramePic && m_ItemPic)
		{
			//��Ⱦ�����λ�ı߿��Լ���λ�����ͼƬ

			//����λ�þ���
			D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);
			D3DXMatrixTransformation2D(&m_matWithMousePos,NULL,0,&m_vScale,NULL,0,&m_ptPosWithMouse);

			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			m_pSprite->Begin(0);

			//��Ⱦ������λ�ı߿��ͼƬ����λ�����ͼƬ
			m_pSprite->SetTransform(&m_matPos);
			m_pSprite->Draw(m_ItemFramePic,NULL,NULL,NULL,0xffffffff);
			m_pSprite->SetTransform(&m_matWithMousePos);
			m_pSprite->Draw(m_ItemPic,NULL,NULL,NULL,0xffffffff);

			m_pSprite->End();
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
		}

	}
	else
	{
		//�����λ��û��ͼƬ
		if (m_ItemPic == NULL)
		{
			//�������ƶ��������
			if (m_lState == COMPONENT_STATE_MOVETO)
			{
				//��Ⱦ�����λ�ı߿�

				if (m_ItemFramePic)
				{
					//����λ�þ���
					D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
					m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
					m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
					m_pSprite->Begin(0);
					m_pSprite->SetTransform(&m_matPos);
					//��Ⱦ������λ�ı߿��ͼƬ
					m_pSprite->Draw(m_ItemFramePic,NULL,NULL,NULL,0xffffffff);
					m_pSprite->End();
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
				}

			}
			else
			{
				//����Ҫ��Ⱦ
				return ;
			}
		}
		//�����λ����ͼƬ
		else
		{
			//�������ƶ��������
			if (m_lState == COMPONENT_STATE_MOVETO)
			{
				//��Ⱦ�����λ�ı߿��Լ���λ�����ͼƬ

				if (m_ItemFramePic && m_ItemPic)
				{
					//����λ�þ���
					D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);
					D3DXMatrixTransformation2D(&m_matItemPicPos,NULL,0,&m_vScale,NULL,0,&m_ptPosItemPic);

					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
					m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
					m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
					m_pSprite->Begin(0);

					//��Ⱦ������λ�ı߿��ͼƬ����λ�����ͼƬ
					m_pSprite->SetTransform(&m_matPos);
					m_pSprite->Draw(m_ItemFramePic,NULL,NULL,NULL,0xffffffff);
					m_pSprite->SetTransform(&m_matItemPicPos);
					m_pSprite->Draw(m_ItemPic,NULL,NULL,NULL,0xffffffff);

					m_pSprite->End();
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
				}
			}
			else
			{
				if (m_ItemPic)
				{
					//����λ�þ���
					D3DXMatrixTransformation2D(&m_matItemPicPos,NULL,0,&m_vScale,NULL,0,&m_ptPosItemPic);
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
					m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
					m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
					m_pSprite->Begin(0);
					m_pSprite->SetTransform(&m_matItemPicPos);
					//��Ⱦ������λ�ı߿��ͼƬ����λ�����ͼƬ

					m_pSprite->Draw(m_ItemPic,NULL,NULL,NULL,0xffffffff);

					m_pSprite->End();
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
				}
			}
		}
	}

}

//���������λ��(���Ͻ�,ͨ���������)
void CItemBox::SetPos(float OffsetX,float OffsetY)
{
	//�������������״̬,��ֻ��Ҫ�ƶ���Ʒ����ͼƬ�Ϳ�����
	if (CComponent::m_BeingWithMouseComponent)
	{
		m_ptPosWithMouse.x += OffsetX;
		m_ptPosWithMouse.y += OffsetY;
	}
	else
	{
		//��Ҫͬʱ�ı�߿��ͼƬ��λ��
		m_ptPos.x += OffsetX;
		m_ptPos.y += OffsetY;
		m_ptPosItemPic.x += OffsetX;
		m_ptPosItemPic.y += OffsetY;
		m_Rect.left = (long)m_ptPos.x;
		m_Rect.right = (long)m_ptPos.x + m_lWidth;
		m_Rect.top = (long)m_ptPos.y;
		m_Rect.bottom = (long)m_ptPos.y + m_lHeight;
	}
}

//�������������µ��¼���Ӧ
void CItemBox::ProcessMouseLBDown(long x,long y)
{

	//�ж��������û����Ʒ������������״̬
	if (!CComponent::m_BeingWithMouseComponent)
	{
		if (this->m_strPicFile != "")
		{
			m_bWithMouseMove = true;
			m_ptPosWithMouse.x = m_ptPosItemPic.x - 5.0f;
			m_ptPosWithMouse.y = m_ptPosItemPic.y - 5.0f;
			CComponent::m_BeingWithMouseComponent = this;
			CComponent::m_BeingDownComponent = this;
			CComponent::m_bProcessGUI = true;
		}
	}
	else
	{
		//������������Ʒ����ͼƬ
		string tempPicFile = this->GetItemPicFile();
		CItemBox* itemboxFrom = dynamic_cast<CItemBox*>(CComponent::m_BeingWithMouseComponent);
		this->ChangeItemPic(itemboxFrom->GetItemPicFile());
		itemboxFrom->ChangeItemPic(tempPicFile);
		m_bWithMouseMove = false;
		CComponent::m_BeingWithMouseComponent = NULL;
		CComponent::m_BeingDownComponent = NULL;
		CComponent::m_bProcessGUI = false;
	}
}
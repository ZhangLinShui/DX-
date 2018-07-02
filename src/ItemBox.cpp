#include "stdafx.h"
#include "ItemBox.h"
 
//构造函数
CItemBox::CItemBox()
{
	m_ItemPic = NULL;
	m_ItemFramePic = NULL;
	m_bPicPicked = false;
	m_lType = GUI_TYPE_ITEMBOX;
	m_bWithMouseMove = false;
	m_strPicFile.clear();
}

//析构函数
CItemBox::~CItemBox()
{
	SAFE_RELEASE(m_ItemPic);
	SAFE_RELEASE(m_ItemFramePic);
}

//更换换栏位上的图片
bool CItemBox::ChangeItemPic(string filename)
{
	HRESULT hr;
	//当图片的文件路径为空时,将物品栏的图片清空(不需要渲染)
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

	//加载栏位的边框的图片
	hr = D3DXCreateTextureFromFileEx(m_pDevice,filename.c_str(),m_lItemPicWidth,m_lItemPicHeight,0,D3DUSAGE_DYNAMIC,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,
		D3DX_DEFAULT,D3DX_DEFAULT,0xffffffff,NULL,NULL,&m_ItemPic);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd,"加载图片资源失败","加载图片资源失败",MB_OK);
		return false;
	}
	return true;
}

//设置鼠标移动到组件上的时候栏位的边框的图片
bool CItemBox::SetItemFramePic(string filename)
{
	HRESULT hr;
	SAFE_RELEASE(m_ItemFramePic);

	//加载栏位的边框的图片
	hr = D3DXCreateTextureFromFileEx(m_pDevice,filename.c_str(),m_lWidth,m_lHeight,0,D3DUSAGE_DYNAMIC,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,
		D3DX_DEFAULT,D3DX_DEFAULT,0xffffffff,NULL,NULL,&m_ItemFramePic);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd,"加载图片资源失败","加载图片资源失败",MB_OK);
		return false;
	}
	return true;
}

//绘制组件
void CItemBox::Draw()
{
	//如果物品栏的图标正处于鼠标跟随状态
	if (this == CComponent::m_BeingWithMouseComponent)
	{
		if (m_ItemFramePic && m_ItemPic)
		{
			//渲染这个栏位的边框以及栏位本身的图片

			//计算位置矩阵
			D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);
			D3DXMatrixTransformation2D(&m_matWithMousePos,NULL,0,&m_vScale,NULL,0,&m_ptPosWithMouse);

			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			m_pSprite->Begin(0);

			//渲染的是栏位的边框的图片和栏位本身的图片
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
		//如果栏位上没有图片
		if (m_ItemPic == NULL)
		{
			//如果鼠标移动到组件上
			if (m_lState == COMPONENT_STATE_MOVETO)
			{
				//渲染这个栏位的边框

				if (m_ItemFramePic)
				{
					//计算位置矩阵
					D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
					m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
					m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
					m_pSprite->Begin(0);
					m_pSprite->SetTransform(&m_matPos);
					//渲染的是栏位的边框的图片
					m_pSprite->Draw(m_ItemFramePic,NULL,NULL,NULL,0xffffffff);
					m_pSprite->End();
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
				}

			}
			else
			{
				//不需要渲染
				return ;
			}
		}
		//如果栏位上有图片
		else
		{
			//如果鼠标移动到组件上
			if (m_lState == COMPONENT_STATE_MOVETO)
			{
				//渲染这个栏位的边框以及栏位本身的图片

				if (m_ItemFramePic && m_ItemPic)
				{
					//计算位置矩阵
					D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);
					D3DXMatrixTransformation2D(&m_matItemPicPos,NULL,0,&m_vScale,NULL,0,&m_ptPosItemPic);

					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
					m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
					m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
					m_pSprite->Begin(0);

					//渲染的是栏位的边框的图片和栏位本身的图片
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
					//计算位置矩阵
					D3DXMatrixTransformation2D(&m_matItemPicPos,NULL,0,&m_vScale,NULL,0,&m_ptPosItemPic);
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
					m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
					m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
					m_pSprite->Begin(0);
					m_pSprite->SetTransform(&m_matItemPicPos);
					//渲染的是栏位的边框的图片和栏位本身的图片

					m_pSprite->Draw(m_ItemPic,NULL,NULL,NULL,0xffffffff);

					m_pSprite->End();
					m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
				}
			}
		}
	}

}

//设置组件的位置(左上角,通过相对坐标)
void CItemBox::SetPos(float OffsetX,float OffsetY)
{
	//如果处于鼠标跟随状态,则只需要移动物品栏的图片就可以了
	if (CComponent::m_BeingWithMouseComponent)
	{
		m_ptPosWithMouse.x += OffsetX;
		m_ptPosWithMouse.y += OffsetY;
	}
	else
	{
		//需要同时改变边框和图片的位置
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

//处理鼠标左键按下的事件响应
void CItemBox::ProcessMouseLBDown(long x,long y)
{

	//判断如果现在没有物品栏处于鼠标跟随状态
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
		//交换这两个物品栏的图片
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
#include "stdafx.h"
#include "CheckBox.h"
 
//构造函数
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

//析构函数
CCheckBox::~CCheckBox()
{

}

//加载"打钩"纹理
bool CCheckBox::SetCheckCursorPic(string filename)
{
	HRESULT hr = S_OK;
	hr = D3DXCreateTextureFromFile(m_pDevice,filename.c_str(),&m_pCheckCursorTex);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"加载选择框纹理失败","加载选择框纹理失败",MB_OK);
		return false;
	}
	return true;
}

//绘制组件
void CCheckBox::Draw(void)
{
	if(m_pPic==NULL)
	{
		return;
	}

	//计算位置矩阵
	D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);

	//由于加载的是TGA图片,要打开ALPHA通道才能进行透明渲染
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

	//如果打了勾
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

//处理鼠标移动的事件响应
void CCheckBox::ProcessMouseMove(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//如果该组件已经处于按下状态
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

//处理鼠标左键按下的事件响应
void CCheckBox::ProcessMouseLBDown(long x,long y)
{
	//判断传入的X,Y坐标是否在组件区域内
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		//设置按钮的状态为COMPONENT_STATE_MOVETO
		m_lState = COMPONENT_STATE_DOWN;
		CComponent::m_BeingDownComponent = this;
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
}

//处理鼠标左键弹起的事件响应
void CCheckBox::ProcessMouseLBUp(long x,long y)
{
	//判断传入的X,Y坐标是否在组件区域内
	if (x >= m_BeingDownComponent->GetRect().left && x <= m_BeingDownComponent->GetRect().right && y >= m_BeingDownComponent->GetRect().top && y <= m_BeingDownComponent->GetRect().bottom)
	{
		//设置按钮的状态为COMPONENT_STATE_MOVETO
		m_lState = COMPONENT_STATE_MOVETO;

		//设置"打钩"纹理是否显示(与之前的状态相反)
		m_bShowCheckCursor = !m_bShowCheckCursor;

		//执行按钮对应的事件
		this->DoEvent();
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
	CComponent::m_BeingDownComponent = NULL;
}

//设置按钮所对应的具体的事件(LUA函数),传入的参数是LUA脚本中的函数名
void CCheckBox::SetEvent(string FunctionName)
{
	m_strFunctionName = FunctionName;
}

//按钮所对应的具体的事件(用户定义的函数)
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

//设置游标的左上角的坐标
void CCheckBox::SetCursorLeftUpPos(D3DXVECTOR2 vPos)
{
	m_vCursorLeftUpPos = vPos;
}
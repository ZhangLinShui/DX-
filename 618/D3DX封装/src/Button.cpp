#include "stdafx.h"
#include "Button.h"
#include "BaseInterface.h"
 
//构造函数
CButton::CButton():CComponent()
{
	//标示组件类型为按钮控件
	m_lType = GUI_TYPE_BUTTON;
	m_pTexDefault = NULL;
	m_pTexDown = NULL;
	m_pTexMoveto = NULL;
	m_pTexNow = NULL;
	//当前的状态是普通状态
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
//析构函数
CButton::~CButton()
{
	SAFE_RELEASE(m_pTexDefault);
	SAFE_RELEASE(m_pTexDown);
	SAFE_RELEASE(m_pTexMoveto);
	SAFE_RELEASE(m_pTexNow);
}

//绘制组件
void CButton::Draw()
{
	//首先判断当前的按钮状态以确定用哪张图片来渲染
	switch(m_lState)
	{
	case COMPONENT_STATE_NORMAL:
		m_pTexNow = m_pTexDefault;
		break;
	case COMPONENT_STATE_MOVETO:
		m_pTexNow = m_pTexMoveto;
		break;
	}

	//通过判断鼠标左键是否按下及时的相应按下消息,并进行图片的切换
	if (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1:0))
	{
		if (CComponent::m_BeingMovetoComponent == this)
		{
			m_pTexNow = m_pTexDown;
		}
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

//处理键盘的事件响应
void CButton::ProcessKeyEvent(char key)
{
	//如果捕获的键盘输入和BUTTON的快捷键相同
	if (key == m_cHotKey)
	{
		//执行BUTTON对应的事件
		this->DoEvent();
	}
}

//处理鼠标移动的事件响应
void CButton::ProcessMouseMove(long x,long y)
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
		//OutputDebugString(m_BeingMovetoComponent->GetName());
		//OutputDebugString("33333333\n");
		//m_BeingDownComponent = this;
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
}

//处理鼠标左键按下的事件响应
void CButton::ProcessMouseLBDown(long x,long y)
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
void CButton::ProcessMouseLBUp(long x,long y)
{
	//判断传入的X,Y坐标是否在组件区域内
	if (x >= m_BeingDownComponent->GetRect().left && x <= m_BeingDownComponent->GetRect().right && y >= m_BeingDownComponent->GetRect().top && y <= m_BeingDownComponent->GetRect().bottom)
	{
		//设置按钮的状态为COMPONENT_STATE_MOVETO
		m_lState = COMPONENT_STATE_MOVETO;

		//执行按钮对应的事件
		this->DoEvent();
	}
	else
	{
		m_lState = COMPONENT_STATE_NORMAL;
	}
	CComponent::m_BeingDownComponent = NULL;
	CComponent::m_BeingMovetoComponent = this;
}

////处理鼠标右键按下的事件响应
//void CButton::ProcessMouseRBDown(long x,long y)
//{
//	//判断传入的X,Y坐标是否在组件区域内
//	if (m_ptPos.x >= m_Rect.left && m_ptPos.x <= m_Rect.right && m_ptPos.y >= m_Rect.top && m_ptPos.y <= m_Rect.bottom)
//	{
//		//设置按钮的状态为COMPONENT_STATE_MOVETO
//		m_lState = COMPONENT_STATE_MOVETO;
//	}
//}

////处理鼠标右键弹起的事件响应
//void CButton::ProcessMouseRBUp(long x,long y)
//{
//	//判断传入的X,Y坐标是否在组件区域内
//	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
//	{
//		//设置按钮的状态为COMPONENT_STATE_MOVETO
//		m_lState = COMPONENT_STATE_MOVETO;
//	}
//}

////处理鼠标滚轮滚动的事件响应
//void CButton::ProcessMouseWheel()
//{
//	//判断传入的X,Y坐标是否在组件区域内
//	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
//	{
//		//设置按钮的状态为COMPONENT_STATE_MOVETO
//		m_lState = COMPONENT_STATE_MOVETO;
//	}
//}

//设置快捷键
void CButton::SetHotKey(char CHotKey)
{
	m_cHotKey = CHotKey;
}

//按钮所对应的具体的事件(用户定义的函数)
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

//设置按钮所对应的具体的事件(LUA函数),传入的参数是LUA脚本中的函数名
void CButton::SetEvent(string FunctionName)
{
	m_strFunctionName = FunctionName;
}


//分别加载3个状态下的图片资源
void CButton::SetTextureDefault(string TexDefault)
{
	HRESULT hr;
	//加载默认状态下的图片
	hr = D3DXCreateTextureFromFileEx(m_pDevice,TexDefault.c_str(),D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,D3DCOLOR_RGBA(0,0,0, 255),NULL,NULL,&m_pTexDefault);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf,"加载组件资源%s失败",TexDefault.c_str());
		MessageBox(hWnd,buf,"错误",MB_OK);
	}
}

void CButton::SetTextureMoveto(string TexMoveto)
{
	HRESULT hr;
	//加载移动到状态下的图片
	hr = D3DXCreateTextureFromFileEx(m_pDevice,TexMoveto.c_str(),D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,D3DCOLOR_RGBA(0,0,0, 255),NULL,NULL,&m_pTexMoveto);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf,"加载组件资源%s失败",TexMoveto.c_str());
		MessageBox(hWnd,buf,"错误",MB_OK);
	}
}

void CButton::SetTextureDown(string TexDown)
{
	HRESULT hr;
	//加载按下状态下的图片
	hr = D3DXCreateTextureFromFileEx(m_pDevice,TexDown.c_str(),D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,D3DCOLOR_RGBA(0,0,0, 255),NULL,NULL,&m_pTexDown);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf,"加载组件资源%s失败",TexDown.c_str());
		MessageBox(hWnd,buf,"错误",MB_OK);
	}
}
#include "stdafx.h"
#include "Component.h"

CComponent* CComponent::m_BeingMovetoComponent = NULL;
CComponent* CComponent::m_BeingDownComponent = NULL;
CComponent* CComponent::m_BeingWithMouseComponent = NULL;
bool CComponent::m_bProcessGUI = false;

//构造函数
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

//析构函数
CComponent::~CComponent()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pPic);
	m_pParent = NULL;
}

//为组件添加子组件,参数一为组件对象,参数二为子组件在父组件中的索引序号
void CComponent::AddChild(CComponent* pChild, long index)
{
	if (NULL != pChild)
	{
		m_mapChildren[index] = pChild;
		pChild->SetParent(this);
	}
}

//设置组件是否可见(递归调用,所有的子组件也要设置是否可见)
void CComponent::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
	//有子组件
	if (!m_mapChildren.empty())
	{
		for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
		{
			(m_mapChildrenIT->second)->SetVisible(bVisible);
		}
	}
}

//设置组件的位置(左上角,通过相对坐标)
void CComponent::SetPos(float OffsetX, float OffsetY)
{
	m_ptPos.x += OffsetX;
	m_ptPos.y += OffsetY;
	m_Rect.left = (long)m_ptPos.x;
	m_Rect.right = (long)m_ptPos.x + m_lWidth;
	m_Rect.top = (long)m_ptPos.y;
	m_Rect.bottom = (long)m_ptPos.y + m_lHeight;
	//有子组件
	if (!m_mapChildren.empty())
	{
		for (m_mapChildrenIT = m_mapChildren.begin(); m_mapChildrenIT != m_mapChildren.end(); ++m_mapChildrenIT)
		{
			(m_mapChildrenIT->second)->SetPos(OffsetX, OffsetY);
		}
	}
}

//设置组件的尺寸
void CComponent::SetSize(long width, long height)
{
	m_lWidth = width;
	m_lHeight = height;
	m_Rect.left = (long)m_ptPos.x;
	m_Rect.right = (long)m_ptPos.x + m_lWidth;
	m_Rect.top = (long)m_ptPos.y;
	m_Rect.bottom = (long)m_ptPos.y + m_lHeight;
}

//为组件添加鼠标监听器
void CComponent::AddMouseListener()
{

}

//为组件添加键盘监听器
void CComponent::AddKeyListener()
{

}

//绘制组件
void CComponent::Draw()
{
	//OutputDebugString("Draw start\n");
	if (m_pPic == NULL)
	{
		return;
	}
	//计算位置矩阵
	D3DXMatrixTransformation2D(&m_matPos, NULL, 0, &m_vScale, NULL, 0, &m_ptPos);

	//由于加载的是TGA图片,要打开ALPHA通道才能进行透明渲染
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

//获得子组件,有两种方法,通过获取子组件的名称,或者获取子组件的索引号
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
//获得子组件,有两种方法,通过获取子组件的名称,或者获取子组件的索引号
CComponent* CComponent::GetChild(long index)
{
	return m_mapChildren[index];
}

//处理键盘事件
void CComponent::ProcessKeyEvent(char key)
{

}

//处理鼠标移动事件
void CComponent::ProcessMouseMove(long x, long y)
{

}

//处理鼠标左键按下的事件响应
void CComponent::ProcessMouseLBDown(long x, long y)
{

}

//处理鼠标左键弹起的事件响应
void CComponent::ProcessMouseLBUp(long x, long y)
{

}

//处理鼠标右键按下的事件响应
void CComponent::ProcessMouseRBDown(long x, long y)
{

}

//处理鼠标右键弹起的事件响应
void CComponent::ProcessMouseRBUp(long x, long y)
{

}

//处理鼠标滚轮滚动的事件响应
void CComponent::ProcessMouseWheel()
{

}

//设置组件的图片
void CComponent::SetPicture(string filename)
{
	HRESULT hr;
	//加载按下状态下的图片
	hr = D3DXCreateTextureFromFileEx(m_pDevice, filename.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DCOLOR_RGBA(0, 0, 0, 255), NULL, NULL, &m_pPic);
	if (FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		char buf[100] = "";
		sprintf(buf, "加载组件资源%s失败", filename.c_str());
		MessageBox(hWnd, buf, "错误", MB_OK);
		return;
	}
}

//设置精灵对象(绘制图形时候用的ID3DXSprite接口)
void CComponent::SetSprite()
{
	if (m_pDevice)
	{
		D3DXCreateSprite(m_pDevice, &m_pSprite);
	}
	else
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd, "游戏设备对象没有创建,所以不能创建精灵对象", "游戏设备对象没有创建,所以不能创建精灵对象", MB_OK);
	}
}
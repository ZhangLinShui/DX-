#include "stdafx.h"
#include "StaticText.h"
 
//构造函数
CStaticText::CStaticText()
{
	m_pFont = NULL;
	m_strOutputText.clear();
	m_lCharHeight = 0;
	m_lCharWidth = 0;
	m_FontColor = 0xffffffff;
	m_dwAlignStyle = DT_LEFT;
	m_lType = GUI_TYPE_STATICTEXT;
}

//析构函数
CStaticText::~CStaticText()
{
	SAFE_RELEASE(m_pFont);
}

//设置输出文字的宽度和高度(当创建一个静态文字组件后,这个接口是必须实现的)
bool CStaticText::SetCharWidthAndHeight(long lCharWidth,long lCharHeight)
{
	HRESULT hr;
	m_lCharHeight = lCharHeight;
	m_lCharWidth = lCharWidth;

	//创建一个字体对象,用于显示文字
	hr = D3DXCreateFont(m_pDevice,m_lCharHeight,m_lCharWidth,10,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE ,"黑体",&m_pFont);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd,"初始化字体失败","初始化字体失败",MB_OK);
		return false;
	}
	return true;
}

//渲染文字
void CStaticText::Draw(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->DrawText(NULL,m_strOutputText.c_str(),-1,&m_Rect,m_dwAlignStyle | DT_TOP,m_FontColor);
	}
}
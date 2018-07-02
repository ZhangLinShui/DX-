#include "stdafx.h"
#include "StaticText.h"
 
//���캯��
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

//��������
CStaticText::~CStaticText()
{
	SAFE_RELEASE(m_pFont);
}

//����������ֵĿ�Ⱥ͸߶�(������һ����̬���������,����ӿ��Ǳ���ʵ�ֵ�)
bool CStaticText::SetCharWidthAndHeight(long lCharWidth,long lCharHeight)
{
	HRESULT hr;
	m_lCharHeight = lCharHeight;
	m_lCharWidth = lCharWidth;

	//����һ���������,������ʾ����
	hr = D3DXCreateFont(m_pDevice,m_lCharHeight,m_lCharWidth,10,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE ,"����",&m_pFont);
	if(FAILED(hr))
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd,"��ʼ������ʧ��","��ʼ������ʧ��",MB_OK);
		return false;
	}
	return true;
}

//��Ⱦ����
void CStaticText::Draw(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->DrawText(NULL,m_strOutputText.c_str(),-1,&m_Rect,m_dwAlignStyle | DT_TOP,m_FontColor);
	}
}
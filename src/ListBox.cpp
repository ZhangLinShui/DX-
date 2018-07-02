#include "stdafx.h"
#include "ListBox.h"
 
//构造函数
CListBox::CListBox()
: CComponent()
, m_pScroll(NULL)
, m_pUp(NULL)
, m_pDown(NULL)
, m_strAllText("")
, m_pFont(NULL)
, m_lMaxByteInRaw(0)
, m_lMaxRaw(0)
, m_lRawNow(0)
, m_lFontType(DT_TOP)
{
	m_lType = GUI_TYPE_LISTBOX;
	m_strAllText = "";
}

//析构函数
CListBox::~CListBox()
{
	SAFE_RELEASE(m_pFont);
}

//绘制组件
void CListBox::Draw()
{
	if(m_pPic==NULL)
	{
		return;
	}
	//计算位置矩阵
	D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	m_pSprite->Begin(0);
	m_pSprite->SetTransform(&m_matPos);
	m_pSprite->Draw(m_pPic,NULL,NULL,NULL,0xffffffff);
	m_pSprite->End();
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
	
	//渲染文字
	if (m_pFont)
	{
		m_pFont->DrawText(NULL,
			m_strAllText.c_str(),
			(int)strlen(m_strAllText.c_str()),
			&m_Rect,
			m_lFontType | DT_WORDBREAK,
			D3DCOLOR_XRGB(255,255,255));
	}
}

//处理鼠标移动的事件响应
void CListBox::ProcessMouseMove(long x,long y)
{
	
}

////处理鼠标左键按下的事件响应
//void CListBox::ProcessMouseLBDown(long x,long y)
//{
//
//}

//设置ListBox所对应的滚动条本体的Button
void CListBox::SetListBoxScrollButton(CButton* pScroll)
{
	pScroll->SetParent(this);
	this->AddChild(pScroll,1);
}

//设置ListBox所对应的滚动条的向上的Button
void CListBox::SetListBoxUpButton(CButton* pUp)
{
	pUp->SetParent(this);
	this->AddChild(pUp,2);
}

//设置ListBox所对应的滚动条的向下的Button
void CListBox::SetListBoxDownButton(CButton* pDown)
{
	pDown->SetParent(this);
	this->AddChild(pDown,3);
}

//设置每一行可容纳的最大字节数
void CListBox::SetMaxByteInRaw(void)
{
	m_lMaxByteInRaw = m_lWidth / 12;
}

//设置最大行数
void CListBox::SetMaxRaw(void)
{
	m_lMaxRaw = m_lHeight / 20;
}

//往ListBox里添加一条字符串
void CListBox::AppendString(string strNew)
{
	m_lRawNow ++;
	//判断当前的字符串行数有没有大于最大的行数
	if (m_lRawNow > m_lMaxRaw)
	{
		//设置字体的绘制方式为底部对齐
		m_lFontType = DT_BOTTOM;

		//将m_strAllText中的最前面的以\n结尾的字符串取出来
		//这个string就是顶部多出的字符
		//将顶部多出的字符压入m_stackFront栈中
		long lNumBack = m_stackBack.size();
		//if (lNumBack == 0)
		//{
		//	long pos = m_strAllText.find('\n');
		//	m_stackFront.push(m_strAllText.substr(0,pos));
		//	m_strAllText.erase(0,pos+1);
		//}
		for (long i = 0 ; i < lNumBack; i++)
		{
			long pos = m_strAllText.find('\n');
			m_stackFront.push(m_strAllText.substr(0,pos));
			m_strAllText.erase(0,pos+1);
			string strBack = m_stackBack.top();
			m_stackBack.pop();
			//strBack = strBack;
			m_strAllText = m_strAllText + strBack;
		}
		m_strAllText = m_strAllText + strNew;
		long pos = m_strAllText.find('\n');
		m_stackFront.push(m_strAllText.substr(0,pos));
		m_strAllText.erase(0,pos+1);
	}
	else
	{
		m_strAllText = m_strAllText + strNew;
	}
}

//设置ListBox的字体
void CListBox::SetFont()
{
	//创建一个字体对象
	HRESULT hr;
	hr = D3DXCreateFont(m_pDevice,20,8,10,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,"幼圆",&m_pFont);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"创建字体失败","创建字体失败",MB_OK);
	}
}

//设置字体绘制的格式(对齐方式)
void CListBox::SetDrawingFontType(long lType)
{
	m_lFontType = lType;
}

//获取字体绘制的格式(对齐方式)
long CListBox::GetDrawingFontType()
{
	return m_lFontType;
}

//从m_stackFront中弹出若干条字符串到m_strAllText
void CListBox::PopStringFromStackFront(long n)
{
	//从保存的m_stackFront字符串中弹出一个字符串
	if (m_stackFront.empty())
	{
		return;
	}
	string strFront = m_stackFront.top();
	m_stackFront.pop();
	//把两部分字符串拼接
	strFront = strFront + "\n";
	m_strAllText = strFront + m_strAllText;
	//将m_strAllText中的最后面的以\n结尾的字符取出来
	//这个string就是顶部多出的字符
	//将顶部多出的字符压入m_stackFront栈中
	long pos = m_strAllText.rfind('\n',m_strAllText.size()-2);
	long lastpos = m_strAllText.size();
	m_stackBack.push(m_strAllText.substr(pos+1,lastpos-1));
	m_strAllText.erase(pos+1,lastpos);
}

//从m_stackBack中弹出若干条字符串到m_strAllText
void CListBox::PopStringFromStackBack(long n)
{
	if (m_stackBack.empty())
	{
		return;
	}
	//从保存的m_stackBack字符串中弹出一个字符串
	string strBack = m_stackBack.top();
	m_stackBack.pop();
	//把两部分字符串拼接
	m_strAllText = m_strAllText + strBack;
	
	long pos = m_strAllText.find('\n');
	m_stackFront.push(m_strAllText.substr(0,pos));
	m_strAllText.erase(0,pos+1);
	
}

//清空ListBox
void CListBox::Clear()
{
	m_strAllText.clear();
	while (!m_stackFront.empty())
	{
		m_stackFront.pop();
	}
	while (!m_stackBack.empty())
	{
		m_stackBack.pop();
	}
	m_lRawNow = 0;
	m_lFontType = DT_TOP;
}
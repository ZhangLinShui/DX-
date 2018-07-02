#include "stdafx.h"
#include "EditBox.h"
 
bool CEditBox::m_bShowCursor = false;

//构造函数
CEditBox::CEditBox()
{
	m_lType = GUI_TYPE_EDITBOX;
	m_bActive = false;
	m_nowPutIn.clear();
	m_Password.clear();
	m_pFont = NULL;
	m_MousePt.x = 0 ;
	m_MousePt.y = 0 ;
	m_pTextureCursor = NULL;		//游标的贴图
	m_vCursorLeftUpPos = D3DXVECTOR2(15.0f,40.0f);		//游标的左上角坐标
	m_vCursorScale = D3DXVECTOR2(1.0f,1.0f);			//游标的显示比例

	//字符可以显示的区域,左上角确定,右下角为整个屏幕,其实用不到
	m_PutInRect.bottom = 768;
	m_PutInRect.left = (long)m_vCursorLeftUpPos.x;
	m_PutInRect.right = 1024;
	m_PutInRect.top = (long)m_vCursorLeftUpPos.y;

	m_lCharHeight = 20;		//每个字符的高度所占的像素
	m_lCharWidth = 8;		//每个字符的宽度所占的像素
	m_lMaxInput = 23;		//最大的输入数量为23个字符

	m_bPasswordType = false;

	m_strResponseEnterEvent.clear();

	//创建一个定时器,用来控制游标的闪烁
	SetTimer(GetActiveWindow(),100,500,TimerProc);
}

//创建字体,用于显示文字
bool CEditBox::SetFont(void)
{
	//创建一个字体对象
	HRESULT hr;

	hr = D3DXCreateFont(m_pDevice,m_lCharHeight,m_lCharWidth,10,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,"幼圆",&m_pFont);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"创建字体失败","创建字体失败",MB_OK);
	}
	return true;
}

//加载游标的纹理
bool CEditBox::SetCursorTex(string texFileName)
{	
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(m_pDevice,texFileName.c_str(),&m_pTextureCursor);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"加载编辑框纹理错误","加载编辑框纹理错误",MB_OK);
		return false;
	}
	return true;
}

//析构函数
CEditBox::~CEditBox()
{

}

//绘制组件
void CEditBox::Draw()
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

	//如果激活了
	if (CComponent::m_BeingDownComponent == this)
	{
		//处理用户的输入
		//HandlePutIn();

		//并且如果需要渲染游标
		if (m_bShowCursor)
		{
			SetCursorPos();
			D3DXMATRIX matCursor;
			D3DXMatrixTransformation2D(&matCursor,NULL,0,&m_vCursorScale,NULL,0,&m_vCursorLeftUpPos);

			m_pSprite->Begin(0);
			m_pSprite->SetTransform(&matCursor);
			m_pSprite->Draw(m_pTextureCursor,NULL,NULL,NULL,0xffffffff);
			m_pSprite->End();
		}
	}

	//渲染文字部分
	if (m_bPasswordType)
	{
		//将当前输入的密码在渲染前赋值给m_Password,并对m_Password进行转换
		m_Password = m_nowPutIn;
		for (string::iterator it = m_Password.begin(); it != m_Password.end(); it++)
		{
			(*it) = '*';
		}
		m_pFont->DrawText(NULL,					
			m_Password.c_str(),					//文本内容
			(int)strlen(m_Password.c_str()),	//文本长度
			&m_PutInRect,						//文本的显示区域,使用窗口坐标
			DT_LEFT,							//显示格式:左对齐
			D3DCOLOR_XRGB(100,100,100));		//文本颜色:白色
	}
	else
	{
		m_pFont->DrawText(NULL,
			m_nowPutIn.c_str(),
			(int)strlen(m_nowPutIn.c_str()),
			&m_PutInRect,
			DT_LEFT,
			D3DCOLOR_XRGB(100,100,100));
	}
}

//处理鼠标移动的事件响应
void CEditBox::ProcessMouseMove(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		m_BeingMovetoComponent = this;
	}
}

//处理鼠标左键按下的事件响应
void CEditBox::ProcessMouseLBDown(long x,long y)
{
	//判断传入的X,Y坐标是否在组件区域内
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		m_bActive = true;
		CComponent::m_BeingDownComponent = this;
	}
	else
	{
		m_bActive = false;
	}
}

//往当前的保存的字符串后面添加一个字符
void CEditBox::AddChar(char cChar)
{
	//如果输入的是退格键
	if (cChar == VK_BACK)
	{
		
		if (!m_nowPutIn.empty())
		{
			//如果最后一位字符大于0,说明是英文字符,只向后退一格
			if (m_nowPutIn[m_nowPutIn.size()-1] > 0)
			{
				m_nowPutIn = m_nowPutIn.substr(0,m_nowPutIn.length()-1);
			}
			//如果最后一位字符小于0,说明是中文字符,要向后退二格
			else
			{
				m_nowPutIn = m_nowPutIn.substr(0,m_nowPutIn.length()-2);
			}
			
		}
		return;
	}
	if (cChar == VK_SHIFT || cChar == VK_CAPITAL || cChar == VK_TAB)
	{
		return ;
	}
	//如果输入的是回车
	if (cChar == VK_RETURN)
	{
		//响应ENTER键的事件
		DoResponseKeyEnter();
	}
	else
	{
		//如果字符串数超过最大字符,就不处理非BACKSPACE的字符输入
		if ((long)m_nowPutIn.length() <= m_lMaxInput && m_nowPutIn.length() >= 0)
		{
			//如果输入的是数字,就直接输出
			if (cChar >= '0' && cChar <= '9')
			{
				m_nowPutIn.push_back(cChar);
			}
			//如果输入的是字母
			else
			{
				//if (GetAsyncKeyState(VK_CAPITAL) & 0x01)
				//{
				//	m_nowPutIn.push_back(cChar);
				//}
				//else
				//{
					if (GetAsyncKeyState(VK_SHIFT))
					{
						m_nowPutIn.push_back(cChar);
					}
					else
					{
						m_nowPutIn.push_back(cChar);
					}
				//}
			}

		}
	}
	//return m_nowPutIn;
}

//往当前的保存的字符串后面添加一串字符串
void CEditBox::AddString(string str)
{
	m_nowPutIn = m_nowPutIn + str;
}

//在用户输入字符后响应
string CEditBox::HandlePutIn(void)
{
	//如果字符串数超过最大字符,就不处理非BACKSPACE的字符输入
	if ((long)m_nowPutIn.length() <= m_lMaxInput && m_nowPutIn.length() >= 0)
	{
		if (GetAsyncKeyState(0x41))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('A');
			}
			else
			{
				m_nowPutIn.push_back('a');
			}
		}
		if (GetAsyncKeyState(0x42))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('B');
			}
			else
			{
				m_nowPutIn.push_back('b');
			}
		}
		if (GetAsyncKeyState(0x43))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('C');
			}
			else
			{
				m_nowPutIn.push_back('c');
			}
		}
		if (GetAsyncKeyState(0x44))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('D');
			}
			else
			{
				m_nowPutIn.push_back('d');
			}
		}
		if (GetAsyncKeyState(0x45))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('E');
			}
			else
			{
				m_nowPutIn.push_back('e');
			}
		}
		if (GetAsyncKeyState(0x46))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('F');
			}
			else
			{
				m_nowPutIn.push_back('f');
			}
		}
		if (GetAsyncKeyState(0x47))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('G');
			}
			else
			{
				m_nowPutIn.push_back('g');
			}
		}
		if (GetAsyncKeyState(0x48))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('H');
			}
			else
			{
				m_nowPutIn.push_back('h');
			}
		}
		if (GetAsyncKeyState(0x49))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('I');
			}
			else
			{
				m_nowPutIn.push_back('i');
			}
		}
		if (GetAsyncKeyState(0x4A))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('J');
			}
			else
			{
				m_nowPutIn.push_back('j');
			}
		}
		if (GetAsyncKeyState(0x4B))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('K');
			}
			else
			{
				m_nowPutIn.push_back('k');
			}
		}
		if (GetAsyncKeyState(0x4C))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('L');
			}
			else
			{
				m_nowPutIn.push_back('l');
			}
		}
		if (GetAsyncKeyState(0x4D))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('M');
			}
			else
			{
				m_nowPutIn.push_back('m');
			}
		}
		if (GetAsyncKeyState(0x4E))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('N');
			}
			else
			{
				m_nowPutIn.push_back('n');
			}
		}
		if (GetAsyncKeyState(0x4F))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('O');
			}
			else
			{
				m_nowPutIn.push_back('o');
			}
		}
		if (GetAsyncKeyState(0x50))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('P');
			}
			else
			{
				m_nowPutIn.push_back('p');
			}
		}
		if (GetAsyncKeyState(0x51))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('Q');
			}
			else
			{
				m_nowPutIn.push_back('q');
			}
		}
		if (GetAsyncKeyState(0x52))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('R');
			}
			else
			{
				m_nowPutIn.push_back('r');
			}
		}
		if (GetAsyncKeyState(0x53))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('S');
			}
			else
			{
				m_nowPutIn.push_back('s');
			}
		}
		if (GetAsyncKeyState(0x54))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('T');
			}
			else
			{
				m_nowPutIn.push_back('t');
			}
		}
		if (GetAsyncKeyState(0x55))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('U');
			}
			else
			{
				m_nowPutIn.push_back('u');
			}
		}
		if (GetAsyncKeyState(0x56))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('V');
			}
			else
			{
				m_nowPutIn.push_back('v');
			}
		}
		if (GetAsyncKeyState(0x57))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('W');
			}
			else
			{
				m_nowPutIn.push_back('w');
			}
		}
		if (GetAsyncKeyState(0x58))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('X');
			}
			else
			{
				m_nowPutIn.push_back('x');
			}
		}
		if (GetAsyncKeyState(0x59))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('Y');
			}
			else
			{
				m_nowPutIn.push_back('y');
			}
		}
		if (GetAsyncKeyState(0x5A))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('Z');
			}
			else
			{
				m_nowPutIn.push_back('z');
			}
		}
		if (GetAsyncKeyState(0x30))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('0');
			}
			else
			{
				m_nowPutIn.push_back('0');
			}
		}
		if (GetAsyncKeyState(0x31))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('1');
			}
			else
			{
				m_nowPutIn.push_back('1');
			}
		}
		if (GetAsyncKeyState(0x32))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('2');
			}
			else
			{
				m_nowPutIn.push_back('2');
			}
		}
		if (GetAsyncKeyState(0x33))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('3');
			}
			else
			{
				m_nowPutIn.push_back('3');
			}
		}
		if (GetAsyncKeyState(0x34))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('4');
			}
			else
			{
				m_nowPutIn.push_back('4');
			}
		}
		if (GetAsyncKeyState(0x35))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('5');
			}
			else
			{
				m_nowPutIn.push_back('5');
			}
		}
		if (GetAsyncKeyState(0x36))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('6');
			}
			else
			{
				m_nowPutIn.push_back('6');
			}
		}
		if (GetAsyncKeyState(0x37))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('7');
			}
			else
			{
				m_nowPutIn.push_back('7');
			}
		}
		if (GetAsyncKeyState(0x38))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('8');
			}
			else
			{
				m_nowPutIn.push_back('8');
			}
		}
		if (GetAsyncKeyState(0x39))
		{
			if (GetAsyncKeyState(VK_CAPITAL))
			{
				m_nowPutIn.push_back('9');
			}
			else
			{
				m_nowPutIn.push_back('9');
			}
		}

	}
	if (GetAsyncKeyState(VK_BACK))
	{
		m_nowPutIn = m_nowPutIn.substr(0,m_nowPutIn.length()-1);
	}
	return m_nowPutIn;
}

//在渲染的过程中根据文本框输入的字数的多少来设定游标的位置
void CEditBox::SetCursorPos(void)
{
	m_vCursorLeftUpPos.x = (float)(m_lCursorPos + m_lCharWidth * strlen(m_nowPutIn.c_str()));
}

//设置游标的左上角的坐标
void CEditBox::SetCursorLeftUpPos(D3DXVECTOR2 vPos)
{
	m_vCursorLeftUpPos = vPos;
	m_lCursorPos = (long)m_vCursorLeftUpPos.x;
	m_PutInRect.left = (long)m_vCursorLeftUpPos.x;
	m_PutInRect.top = (long)m_vCursorLeftUpPos.y - 8.0f;
}

//编辑框响应Enter的事件
void CEditBox::SetResponseKeyEnter(string strEnterEvent)
{
	m_strResponseEnterEvent = strEnterEvent;
}

//响应ENTER键的事件
void CEditBox::DoResponseKeyEnter()
{
	if (m_strResponseEnterEvent.empty())
	{
		return;
	}
	else
	{
		
	}
}

//设置编辑框是否被激活
void CEditBox::SetActive(bool bActive)
{
	m_bActive = bActive;
	//如果处于激活状态,就设置这个组件为按下的组件
	if (m_bActive)
	{
		CComponent::m_BeingDownComponent = this;
	}
}
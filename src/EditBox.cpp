#include "stdafx.h"
#include "EditBox.h"
 
bool CEditBox::m_bShowCursor = false;

//���캯��
CEditBox::CEditBox()
{
	m_lType = GUI_TYPE_EDITBOX;
	m_bActive = false;
	m_nowPutIn.clear();
	m_Password.clear();
	m_pFont = NULL;
	m_MousePt.x = 0 ;
	m_MousePt.y = 0 ;
	m_pTextureCursor = NULL;		//�α����ͼ
	m_vCursorLeftUpPos = D3DXVECTOR2(15.0f,40.0f);		//�α�����Ͻ�����
	m_vCursorScale = D3DXVECTOR2(1.0f,1.0f);			//�α����ʾ����

	//�ַ�������ʾ������,���Ͻ�ȷ��,���½�Ϊ������Ļ,��ʵ�ò���
	m_PutInRect.bottom = 768;
	m_PutInRect.left = (long)m_vCursorLeftUpPos.x;
	m_PutInRect.right = 1024;
	m_PutInRect.top = (long)m_vCursorLeftUpPos.y;

	m_lCharHeight = 20;		//ÿ���ַ��ĸ߶���ռ������
	m_lCharWidth = 8;		//ÿ���ַ��Ŀ����ռ������
	m_lMaxInput = 23;		//������������Ϊ23���ַ�

	m_bPasswordType = false;

	m_strResponseEnterEvent.clear();

	//����һ����ʱ��,���������α����˸
	SetTimer(GetActiveWindow(),100,500,TimerProc);
}

//��������,������ʾ����
bool CEditBox::SetFont(void)
{
	//����һ���������
	HRESULT hr;

	hr = D3DXCreateFont(m_pDevice,m_lCharHeight,m_lCharWidth,10,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,"��Բ",&m_pFont);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"��������ʧ��","��������ʧ��",MB_OK);
	}
	return true;
}

//�����α������
bool CEditBox::SetCursorTex(string texFileName)
{	
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(m_pDevice,texFileName.c_str(),&m_pTextureCursor);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"���ر༭���������","���ر༭���������",MB_OK);
		return false;
	}
	return true;
}

//��������
CEditBox::~CEditBox()
{

}

//�������
void CEditBox::Draw()
{
	if(m_pPic==NULL)
	{
		return;
	}

	//����λ�þ���
	D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);

	//���ڼ��ص���TGAͼƬ,Ҫ��ALPHAͨ�����ܽ���͸����Ⱦ
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

	//���������
	if (CComponent::m_BeingDownComponent == this)
	{
		//�����û�������
		//HandlePutIn();

		//���������Ҫ��Ⱦ�α�
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

	//��Ⱦ���ֲ���
	if (m_bPasswordType)
	{
		//����ǰ�������������Ⱦǰ��ֵ��m_Password,����m_Password����ת��
		m_Password = m_nowPutIn;
		for (string::iterator it = m_Password.begin(); it != m_Password.end(); it++)
		{
			(*it) = '*';
		}
		m_pFont->DrawText(NULL,					
			m_Password.c_str(),					//�ı�����
			(int)strlen(m_Password.c_str()),	//�ı�����
			&m_PutInRect,						//�ı�����ʾ����,ʹ�ô�������
			DT_LEFT,							//��ʾ��ʽ:�����
			D3DCOLOR_XRGB(100,100,100));		//�ı���ɫ:��ɫ
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

//��������ƶ����¼���Ӧ
void CEditBox::ProcessMouseMove(long x,long y)
{
	if (x >= m_Rect.left && x <= m_Rect.right && y >= m_Rect.top && y <= m_Rect.bottom)
	{
		m_BeingMovetoComponent = this;
	}
}

//�������������µ��¼���Ӧ
void CEditBox::ProcessMouseLBDown(long x,long y)
{
	//�жϴ����X,Y�����Ƿ������������
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

//����ǰ�ı�����ַ����������һ���ַ�
void CEditBox::AddChar(char cChar)
{
	//�����������˸��
	if (cChar == VK_BACK)
	{
		
		if (!m_nowPutIn.empty())
		{
			//������һλ�ַ�����0,˵����Ӣ���ַ�,ֻ�����һ��
			if (m_nowPutIn[m_nowPutIn.size()-1] > 0)
			{
				m_nowPutIn = m_nowPutIn.substr(0,m_nowPutIn.length()-1);
			}
			//������һλ�ַ�С��0,˵���������ַ�,Ҫ����˶���
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
	//���������ǻس�
	if (cChar == VK_RETURN)
	{
		//��ӦENTER�����¼�
		DoResponseKeyEnter();
	}
	else
	{
		//����ַ�������������ַ�,�Ͳ������BACKSPACE���ַ�����
		if ((long)m_nowPutIn.length() <= m_lMaxInput && m_nowPutIn.length() >= 0)
		{
			//��������������,��ֱ�����
			if (cChar >= '0' && cChar <= '9')
			{
				m_nowPutIn.push_back(cChar);
			}
			//������������ĸ
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

//����ǰ�ı�����ַ����������һ���ַ���
void CEditBox::AddString(string str)
{
	m_nowPutIn = m_nowPutIn + str;
}

//���û������ַ�����Ӧ
string CEditBox::HandlePutIn(void)
{
	//����ַ�������������ַ�,�Ͳ������BACKSPACE���ַ�����
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

//����Ⱦ�Ĺ����и����ı�������������Ķ������趨�α��λ��
void CEditBox::SetCursorPos(void)
{
	m_vCursorLeftUpPos.x = (float)(m_lCursorPos + m_lCharWidth * strlen(m_nowPutIn.c_str()));
}

//�����α�����Ͻǵ�����
void CEditBox::SetCursorLeftUpPos(D3DXVECTOR2 vPos)
{
	m_vCursorLeftUpPos = vPos;
	m_lCursorPos = (long)m_vCursorLeftUpPos.x;
	m_PutInRect.left = (long)m_vCursorLeftUpPos.x;
	m_PutInRect.top = (long)m_vCursorLeftUpPos.y - 8.0f;
}

//�༭����ӦEnter���¼�
void CEditBox::SetResponseKeyEnter(string strEnterEvent)
{
	m_strResponseEnterEvent = strEnterEvent;
}

//��ӦENTER�����¼�
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

//���ñ༭���Ƿ񱻼���
void CEditBox::SetActive(bool bActive)
{
	m_bActive = bActive;
	//������ڼ���״̬,������������Ϊ���µ����
	if (m_bActive)
	{
		CComponent::m_BeingDownComponent = this;
	}
}
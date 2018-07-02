#include "stdafx.h"
#include "ListBox.h"
 
//���캯��
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

//��������
CListBox::~CListBox()
{
	SAFE_RELEASE(m_pFont);
}

//�������
void CListBox::Draw()
{
	if(m_pPic==NULL)
	{
		return;
	}
	//����λ�þ���
	D3DXMatrixTransformation2D(&m_matPos,NULL,0,&m_vScale,NULL,0,&m_ptPos);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	m_pSprite->Begin(0);
	m_pSprite->SetTransform(&m_matPos);
	m_pSprite->Draw(m_pPic,NULL,NULL,NULL,0xffffffff);
	m_pSprite->End();
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
	
	//��Ⱦ����
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

//��������ƶ����¼���Ӧ
void CListBox::ProcessMouseMove(long x,long y)
{
	
}

////�������������µ��¼���Ӧ
//void CListBox::ProcessMouseLBDown(long x,long y)
//{
//
//}

//����ListBox����Ӧ�Ĺ����������Button
void CListBox::SetListBoxScrollButton(CButton* pScroll)
{
	pScroll->SetParent(this);
	this->AddChild(pScroll,1);
}

//����ListBox����Ӧ�Ĺ����������ϵ�Button
void CListBox::SetListBoxUpButton(CButton* pUp)
{
	pUp->SetParent(this);
	this->AddChild(pUp,2);
}

//����ListBox����Ӧ�Ĺ����������µ�Button
void CListBox::SetListBoxDownButton(CButton* pDown)
{
	pDown->SetParent(this);
	this->AddChild(pDown,3);
}

//����ÿһ�п����ɵ�����ֽ���
void CListBox::SetMaxByteInRaw(void)
{
	m_lMaxByteInRaw = m_lWidth / 12;
}

//�����������
void CListBox::SetMaxRaw(void)
{
	m_lMaxRaw = m_lHeight / 20;
}

//��ListBox�����һ���ַ���
void CListBox::AppendString(string strNew)
{
	m_lRawNow ++;
	//�жϵ�ǰ���ַ���������û�д�����������
	if (m_lRawNow > m_lMaxRaw)
	{
		//��������Ļ��Ʒ�ʽΪ�ײ�����
		m_lFontType = DT_BOTTOM;

		//��m_strAllText�е���ǰ�����\n��β���ַ���ȡ����
		//���string���Ƕ���������ַ�
		//������������ַ�ѹ��m_stackFrontջ��
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

//����ListBox������
void CListBox::SetFont()
{
	//����һ���������
	HRESULT hr;
	hr = D3DXCreateFont(m_pDevice,20,8,10,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,"��Բ",&m_pFont);
	if (FAILED(hr))
	{
		MessageBox(GetActiveWindow(),"��������ʧ��","��������ʧ��",MB_OK);
	}
}

//����������Ƶĸ�ʽ(���뷽ʽ)
void CListBox::SetDrawingFontType(long lType)
{
	m_lFontType = lType;
}

//��ȡ������Ƶĸ�ʽ(���뷽ʽ)
long CListBox::GetDrawingFontType()
{
	return m_lFontType;
}

//��m_stackFront�е����������ַ�����m_strAllText
void CListBox::PopStringFromStackFront(long n)
{
	//�ӱ����m_stackFront�ַ����е���һ���ַ���
	if (m_stackFront.empty())
	{
		return;
	}
	string strFront = m_stackFront.top();
	m_stackFront.pop();
	//���������ַ���ƴ��
	strFront = strFront + "\n";
	m_strAllText = strFront + m_strAllText;
	//��m_strAllText�е���������\n��β���ַ�ȡ����
	//���string���Ƕ���������ַ�
	//������������ַ�ѹ��m_stackFrontջ��
	long pos = m_strAllText.rfind('\n',m_strAllText.size()-2);
	long lastpos = m_strAllText.size();
	m_stackBack.push(m_strAllText.substr(pos+1,lastpos-1));
	m_strAllText.erase(pos+1,lastpos);
}

//��m_stackBack�е����������ַ�����m_strAllText
void CListBox::PopStringFromStackBack(long n)
{
	if (m_stackBack.empty())
	{
		return;
	}
	//�ӱ����m_stackBack�ַ����е���һ���ַ���
	string strBack = m_stackBack.top();
	m_stackBack.pop();
	//���������ַ���ƴ��
	m_strAllText = m_strAllText + strBack;
	
	long pos = m_strAllText.find('\n');
	m_stackFront.push(m_strAllText.substr(0,pos));
	m_strAllText.erase(0,pos+1);
	
}

//���ListBox
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
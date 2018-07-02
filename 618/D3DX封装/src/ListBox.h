//////////////////////////////////////////////////////////////////////////
//Name:ListBox.h
//��Ϸ�����е��б�����
//����������Ϸ�е������
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Button.h"

class CListBox : public CComponent
{
public:

	//���캯��
	CListBox();

	//��������
	~CListBox();

	//�������
	void Draw();

	//��������ƶ����¼���Ӧ
	void ProcessMouseMove(long x,long y);

	////�������������µ��¼���Ӧ
	//void ProcessMouseLBDown(long x,long y);

	//����ListBox����Ӧ�Ĺ����������Button
	void SetListBoxScrollButton(CButton* pScroll);

	//����ListBox����Ӧ�Ĺ����������ϵ�Button
	void SetListBoxUpButton(CButton* pUp);

	//����ListBox����Ӧ�Ĺ����������µ�Button
	void SetListBoxDownButton(CButton* pDown);

	//����ÿһ�п����ɵ�����ֽ���
	//�������ؼ�ͼƬ�Ŀ�ȳ����ַ��Ŀ��
	void SetMaxByteInRaw(void);

	//�����������
	//�������ؼ�ͼƬ�ĸ߶ȳ����ַ��ĸ߶�
	void SetMaxRaw(void);

	//��ListBox�����һ���ַ���
	void AppendString(string strNew);

	//����ListBox������
	void SetFont();

	//����������Ƶĸ�ʽ(���뷽ʽ)
	void SetDrawingFontType(long lType);

	//��ȡ������Ƶĸ�ʽ(���뷽ʽ)
	long GetDrawingFontType();

	//��m_stackFront�е����������ַ�����m_strAllText
	void PopStringFromStackFront(long n);

	//��m_stackBack�е����������ַ�����m_strAllText
	void PopStringFromStackBack(long n);

	//���ListBox
	void Clear();

protected:

	//�����������Button
	CButton* m_pScroll;

	//���������ϵ�Button
	CButton* m_pUp;

	//���������µ�Button
	CButton* m_pDown;

	//ListBox�������ı����ַ�������
	string m_strAllText;

	//D3D�������ָ��
	ID3DXFont* m_pFont;

	//ListBox��ÿһ�п����ɵ�����ֽ���
	long m_lMaxByteInRaw;

	//ListBox���������
	long m_lMaxRaw;

	//��ǰ�ַ�����ռ������
	long m_lRawNow;

	//�������ֵĶ��뷽ʽ
	long m_lFontType;

	//��LISTBOX��ʵ�ʵ���������ListBox����ʾ�����������
	//���泬�������ݾͱ������m_stackFrontջ��
	stack<string> m_stackFront;

	stack<string> m_stackBack;
	
};

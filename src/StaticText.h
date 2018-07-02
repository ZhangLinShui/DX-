//ר��������ʾ���ֵ����

#pragma once
#include "Component.h"

class CStaticText : public CComponent
{
public:

	//���캯��
	CStaticText();

	//��������
	~CStaticText();

	//����������ֵĿ�Ⱥ͸߶�(������һ����̬���������,����ӿ��Ǳ���ʵ�ֵ�)
	bool SetCharWidthAndHeight(long lCharWidth,long lCharHeight);	

	//����������ֵ���ɫ
	void SetCharColor(DWORD color)									{m_FontColor = color;}

	//������������ֵ�����
	void SetOutputText(string str)									{m_strOutputText = str;}

	//��Ⱦ����
	void Draw(void);

	//��������������ھ��������еĶ��뷽ʽ
	void SetAlignStyle(DWORD style)									{m_dwAlignStyle = style;}						

	//����������ֵĸ߶�
	//void SetCharHeight(long lCharHeight)			{m_lCharHeight = lCharHeight;}

	//����������ֵľ�������
	//void SetTextRect(long left,long top,long right,long bottom);



protected:

	//D3D�������
	ID3DXFont* m_pFont;

	//��������ֵ�����
	string m_strOutputText;

	//����ĸ߶�
	long m_lCharHeight;

	//����Ŀ��
	long m_lCharWidth;

	//�������ɫ
	D3DCOLOR m_FontColor;

	//����������ھ��������ڵĶ��뷽ʽ
	DWORD m_dwAlignStyle;


};

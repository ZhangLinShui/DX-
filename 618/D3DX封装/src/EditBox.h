////////////////////////////////////////////////////////////////////////////
//Name:EditBox.h

//�ı������ؼ�
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Component.h"

class CEditBox : public CComponent
{
public:

	//���캯��
	CEditBox();

	//��������
	~CEditBox();

	//�������
	void Draw();

	//��������ƶ����¼���Ӧ
	void ProcessMouseMove(long x,long y);

	//�������������µ��¼���Ӧ
	void ProcessMouseLBDown(long x,long y);

	//���û������ַ�����Ӧ
	string HandlePutIn(void);

	//����ǰ�ı�����ַ����������һ���ַ�
	void AddChar(char cChar);

	//����ǰ�ı�����ַ����������һ���ַ���
	void AddString(string str);

	//����Ⱦ�Ĺ����и����ı�������������Ķ������趨�α��λ��
	void SetCursorPos(void);

	//��ʱ���Ļص�����,���ڿ����α����˸
	static void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)	{m_bShowCursor = !m_bShowCursor;}

	//����m_nowPutIn�������(�ַ���),�����PAGE��
	const char* GetInputString(void)		{return m_nowPutIn.c_str();}

	//�����ַ��Ŀ��
	void SetCharWidth(long lWidth)		{m_lCharWidth = lWidth;}

	//�����ַ��ĸ߶�
	void SetCharHeight(long lHeight)	{m_lCharHeight = lHeight;}

	//���ñ༭���Ƿ񱻼���
	void SetActive(bool bActive);

	//�����α�����Ͻǵ�����
	void SetCursorLeftUpPos(D3DXVECTOR2 vPos);	

	//������������������ַ�������
	void SetMaxInput(long lMaxInput)			{m_lMaxInput = lMaxInput;}

	//��ʾ�ñ༭���ǲ����������������
	void SetBePasswordType(bool bPasswordType)	{m_bPasswordType = bPasswordType;}

	//�����α������
	bool SetCursorTex(string texFileName);

	//��������,������ʾ����
	bool SetFont(void);

	//���EditBox������
	void Clear(void)		{m_nowPutIn.clear();}

	//���ñ༭����ӦENTER����LUA������
	void SetResponseKeyEnter(string strKey);

	//��ӦENTER�����¼�
	void DoResponseKeyEnter();

	//�ж��������û�б�����
	bool GetBeActive(void)		{return m_bActive;}

protected:

	//�ж�������Ƿ񱻼���,�����˲ſ�������
	bool m_bActive;

	//D3DFont�ӿ�ָ��,��������ַ�
	ID3DXFont* m_pFont;

	//�������������
	string m_nowPutIn;

	//���ڽ��ַ���ת����"*",��������������,��ʵ�ʵĶ�Ӧֵ���Ǳ�����m_nowPutIn��
	string m_Password;

	//������������ľ�������
	RECT m_PutInRect;

	//����λ��
	POINT m_MousePt;

	//�α������
	IDirect3DTexture9* m_pTextureCursor;

	//�α�����Ͻ�����
	D3DXVECTOR2 m_vCursorLeftUpPos;

	//�α����ʾ�����ű���
	D3DXVECTOR2 m_vCursorScale;

	//�α���л�
	static bool m_bShowCursor;

	//�α��λ��
	long m_lCursorPos;

	//�ַ��ĸ߶�
	long m_lCharHeight;

	//�ַ��Ŀ��
	long m_lCharWidth;

	//�ַ���������������
	long m_lMaxInput;

	//EditBox�ĵ������
	RECT m_ClickedRegion;

	//��ʾ�˸�EditBox�ؼ��ǲ����������������
	bool m_bPasswordType;

	//��ӦENTER����LUA������
	string m_strResponseEnterEvent;
};

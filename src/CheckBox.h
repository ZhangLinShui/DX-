//////////////////////////////////////////////////////////////////////////
//Name:CheckBox.h

//Desc:
//ѡ���ؼ�
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Component.h"

class CCheckBox : public CComponent
{
public:

	//���캯��
	CCheckBox();

	//��������
	~CCheckBox();

	//����"��"����
	bool SetCheckCursorPic(string filename);

	//�������
	void Draw(void);

	//��������ƶ����¼���Ӧ
	void ProcessMouseMove(long x,long y);

	//�������������µ��¼���Ӧ
	void ProcessMouseLBDown(long x,long y);

	//����������������¼���Ӧ
	void ProcessMouseLBUp(long x,long y);

	//���ð�ť����Ӧ�ľ�����¼�(LUA����),����Ĳ�����LUA�ű��еĺ�����
	void SetEvent(string FunctionName);

	//ִ�а�ť����Ӧ�ľ�����¼�
	void DoEvent();

	//�����α�����Ͻǵ�����
	void SetCursorLeftUpPos(D3DXVECTOR2 vPos);	

	//��õ�ǰѡ����Ƿ��Ѿ���ѡ
	bool GetBeChecked(void)							{return m_bShowCheckCursor;}

	//���õ�ǰѡ����Ƿ�ѡ
	void SetBeChecked(bool bChecked)				{m_bShowCheckCursor = bChecked;}

protected:

	//"��"����
	IDirect3DTexture9* m_pCheckCursorTex;

	//�Ƿ���ʾ"��"����
	bool m_bShowCheckCursor;

	//��ť����Ӧ�ľ�����¼��ĺ�����
	string m_strFunctionName;

	//�α�����Ͻ�����
	D3DXVECTOR2 m_vCursorLeftUpPos;

	//�α����ʾ�����ű���
	D3DXVECTOR2 m_vCursorScale;
};

//��ť�ؼ�
//��CComponent������������

#pragma once
#include "Component.h"


class CButton:public CComponent
{

public:

	//���캯��
	CButton();

	//��������
	~CButton();

	void Init(TiXmlElement* element);
	//�������
	void Draw();

	//������̵��¼���Ӧ
	void ProcessKeyEvent(char key);

	//��������ƶ����¼���Ӧ
	void ProcessMouseMove(long x,long y);

	//�������������µ��¼���Ӧ
	void ProcessMouseLBDown(long x,long y);

	//����������������¼���Ӧ
	void ProcessMouseLBUp(long x,long y);

	////��������Ҽ����µ��¼���Ӧ
	//void ProcessMouseRBDown(long x,long y);

	////��������Ҽ�������¼���Ӧ
	//void ProcessMouseRBUp(long x,long y);

	////���������ֹ������¼���Ӧ
	//void ProcessMouseWheel();


	//ִ�а�ť����Ӧ�ľ�����¼�
	void DoEvent();

	//���ÿ�ݼ�
	void SetHotKey(char CHotKey);

	//���ð�ť����Ӧ�ľ�����¼�(LUA����),����Ĳ�����LUA�ű��еĺ�����
	void SetEvent(string FunctionName);

	//�ֱ����3��״̬�µ�ͼƬ��Դ
	void SetTextureDefault(string TexDefault);
	void SetTextureMoveto(string TexMoveto);
	void SetTextureDown(string TexDown);

protected:

	//��ͨ״̬�µİ�ťͼƬ
	IDirect3DTexture9* m_pTexDefault;

	//������ƶ�����ť��ʱ��Ӧ�İ�ťͼƬ
	IDirect3DTexture9* m_pTexMoveto;

	//����갴��ȥʱ��Ӧ�İ�ťͼƬ
	IDirect3DTexture9* m_pTexDown;

	//��ǰ״̬�µİ�ťͼƬ(��Ⱦ��ͼƬ)
	IDirect3DTexture9* m_pTexNow;

	//��ݼ�
	char m_cHotKey;

	//��ť����Ӧ�ľ�����¼��ĺ�����
	string m_strFunctionName;

};

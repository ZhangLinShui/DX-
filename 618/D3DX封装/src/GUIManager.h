//GUIϵͳ�Ĺ�����,ȫ��һ��ʵ��,ʹ�õ���ģʽ
//���е�COMPONENTʵ���������ʾ,����,��Ϣ��Ӧ����GUI������ͳһ����
//���GUIϵͳ�ǻ���LUA��,һ��PAGE��Ӧ��һ��LUA����
//PAGE��λ��,��Ӧ�����ȶ����Ǽ򵥵�����,���ǻ��ڰ��˵�C++����

#pragma once
#include "Observer.h"

#include "Component.h"
class CGUIManager : public IObservable
{
public:
	//��������
	~CGUIManager();
	//ȡ��ȫ��Ψһ��"GUI������"��ʵ��
	static CGUIManager* GetInstance();

	//��ʼ��"GUI������"
	bool Init(string fileName);

	//�ͷ�"GUI������"
	void Release(void);

	//����һ��PAGE,����Ϊִ�еĺ���
	bool LoadPage(string filename);

	//����һ��GUI���
	CComponent* CreateComponent(long ComponentType, string ComponentName);

	////����GUI��ص������¼�
	//void ProcessGUIEvent(long x, long y);

	//������̵��¼���Ӧ
	void ProcessKeyEvent(char key);

	//��������ƶ����¼���Ӧ
	void ProcessMouseMove(long x, long y);

	////�������������µ��¼���Ӧ
	void ProcessMouseLBDown(long x,long y);

	//����������������¼���Ӧ
	void ProcessMouseLBUp(long x,long y);

	//��������Ҽ����µ��¼���Ӧ
	void ProcessMouseRBDown(long x,long y);

	//��������Ҽ�������¼���Ӧ
	void ProcessMouseRBUp(long x,long y);

	//���������ֹ������¼���Ӧ
	void ProcessMouseWheel();

	//���һ�������ָ��
	//����Ϊ����������
	CComponent* GetComponentByName(string ComponentName);

	//�����豸����
	void SetDevice(IDirect3DDevice9* pDevice) { m_pDevice = pDevice; }
	IDirect3DDevice9* GetDevice() { return m_pDevice; }
	void SetIsDraw(bool IsDraw){IsDrawAll = IsDraw;}
	bool GetIsDraw() { return IsDrawAll; }

	
private:

	//����ģʽ�¹��캯����˽�е�
	CGUIManager();

	

	//ȫ��Ψһ��"����������"��ʵ��
	static CGUIManager* m_Instance;

	//GUI�������е����е�GUI�������
	map<string,CComponent*> m_mapComponent;
	map<string,CComponent*>::iterator m_mapComponentIT;

	//map<string,CBaseInterface*>m_mapInterface
	//���������IComponent����,���ڴ��䵽ͼ��ϵͳ��Ⱦ
	IComponent* m_ImapComponent;

	//��һ֡������λ��
	long m_lXOld;
	long m_lYOld;

	//��һ֡����λ�õ�ƫ����
	long m_lXOffset;
	long m_lYOffset;

	//D3D�豸����
	IDirect3DDevice9* m_pDevice;

	bool IsDrawAll=false;//�������з���Ļ��ƣ���ʼUI������Ϸ���ٻ��ƣ�
	

};

//CGUIManager* GetGUIMgr();

//////////////////////////////////////////////////////////////////////////
//Name:SceneManager.h

//������������Ҫ���𳡾��Ĵ���������
//�����������������ĳ�ʼ��,��ȡLUA�ĳ�����ʼ���ű��ļ�
//����������ÿ֡����Ҫ��Ⱦ�Ķ������һ����Ⱦ����
//Ȼ��ͼ��ϵͳ�����Ҫ��Ⱦ�Ķ���
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Observer.h"
#include "Object.h"

class CSceneManager: public IObservable
{
public:
	//��������
	~CSceneManager();
	//ȡ��ȫ��Ψһ��"����������"��ʵ��
	static CSceneManager* GetInstance();

	//��ʼ��"����������"
	bool Init(string fileName);

	//�ͷ�"����������"
	void Release(void);

	//����һ������
	void DestroyScene(void);

	//����һ������
	CObject* CreateObject(long objecttype,string objectname);

	//����һ������
	void DestroyObject(string objectname);

	//���س����������Ķ�������MAP
	//������ϵͳ����
	map<string,CObject*> GetSceneObject()		{return m_mapObject;}

	//����D3D�豸����
	void SetDevice(IDirect3DDevice9* pDevice)	{m_pDevice = pDevice;}

	//ͨ����������ö���ʵ���ָ��
	CObject* GetObjectByName(string ObjectName)	{return m_mapObject[ObjectName];}

private:

	//����ģʽ�¹��캯����˽�е�
	CSceneManager();

	

	//ȫ��Ψһ��"����������"��ʵ��
	static CSceneManager* m_Instance;

	//�����������е����еĶ���
	map<string,CObject*> m_mapObject;

	//���������ImapObject����
	ImapObject* m_ImapObject;

	//��ʾ���������ж��ٸ�����
	long m_lNumOfObject;

	//D3D�豸����
	IDirect3DDevice9* m_pDevice;
};

CSceneManager* GetSceneMgr();

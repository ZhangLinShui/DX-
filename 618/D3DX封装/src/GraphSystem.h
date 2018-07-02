//////////////////////////////////////////////////////////////////////////
//Name:GraphSystem.h

//��Ϸ�е�ͼ����Ⱦϵͳ
//���е������еĶ������������Эͬ����
//���е�ͼ����Ⱦ�߼�����������ж���
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "GUIManager.h"	
#include "SceneManager.h"

class CGraphSystem:public IObserver
{
public:

	//���캯��
	CGraphSystem();

	//��������
	~CGraphSystem();

	//��ʼ��ͼ��ϵͳ
	bool Init(void);

	//����״̬�ӿ�
	void Notify(IObservable* pObservable,IObject* Arg);

	//����״̬�ӿ�
	void Update(IObservable* pObservable,IObject* Arg);

	//��Ⱦ��ǰ֡
	bool Render();

protected:

	//�򳡾���������ע��Object,ֻ��ͼ��ϵͳ�ڲ�ʹ��
	//void RegisterObjectToSceneMgr();

	//��ͼ��ϵͳ���Ѿ����˵ĳ����ϵĶ���
	map<string,CObject*>	m_mapAttachedObject;
	vector<CModelCopy*>		m_vecStaticModel;
	vector<CCharacter*>		m_vecMoster;
	CGUIManager* m_pObservableGUI;

	//������ϵͳ����Ĺ۲���ģʽ������,һ��ϵͳ�����ж��������,���ڴ�����ͬ���¼�
	CSceneManager* m_pObservableScene;

public:
	
	//��ȾGUI����
	void RenderGUI(void);

	//����D3D�豸����
	void SetDevice(IDirect3DDevice9* pDevice)		{m_pDevice = pDevice;}

	//���ͼ��ϵͳ�Ĺ���ʾ,���趨�µĹ��
	long GetCursor(void)							{return m_lCursor;}


protected:
	//��Ҫ��Ⱦ��GUI���
	list<CComponent*> m_listGUIComponent;
	list<CComponent*>::iterator m_listGUIComponentIT;

private:

	//D3D�豸����
	IDirect3DDevice9	*m_pDevice;
	ID3DXSprite			*m_pSprite;
	//����������
	long m_lCursor;
	CWater				*m_pWater;
	CCMap				*m_pMap;
	CPlayer				*m_pPlayer;
	CSky				* m_pSky;
	CHourse				* m_pHourse;
	CBridge				* m_pBridge;
	CModelCopy			*m_pMeshManager;


};

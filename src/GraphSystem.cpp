#include "stdafx.h"
#include "GraphSystem.h"
//#include "Collide.h"
 
//���캯��
CGraphSystem::CGraphSystem()
	:
	m_pObservableScene(NULL), m_pDevice(NULL)
{
	m_mapAttachedObject.clear();
	
}

//��������
CGraphSystem::~CGraphSystem()
{
	m_mapAttachedObject.clear();
}

//����״̬�ӿ�
void CGraphSystem::Notify(IObservable* pObservable, IObject* Arg)
{

}

//����״̬�ӿ�
void CGraphSystem::Update(IObservable* pObservable, IObject* Arg)
{

	//�������ǳ���������
	if (m_pObservableScene == pObservable)
	{
		//�������Ϊ��
		if (!((ImapObject*)Arg)->Object)
		{
			return;
		}

		m_mapAttachedObject[((ImapObject*)Arg)->ObjectName] = ((ImapObject*)Arg)->Object;

		long objecttype = ((ImapObject*)Arg)->Object->GetType();
		CModelCopy *temp;
		CCharacter *temp1;
		switch (objecttype)
		{
		case OB_TYPE_NOTYPE:
			break;
		case OB_TYPE_MAP:
			m_pMap=(CCMap*) ((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_PLAYER:
			m_pPlayer= (CPlayer*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_SKY:
			m_pSky = (CSky*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_WATER:
			m_pWater = (CWater*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_HOURSE:
			//m_pHourse = (CHourse*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_BRIDGE:
			m_pBridge = (CBridge*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_MODEL_COPY:
			temp = (CModelCopy*)((ImapObject*)Arg)->Object;
			m_vecStaticModel.push_back(temp);
			break;
		case OB_TYPE_MONSTER:
			temp1 = (CCharacter*)((ImapObject*)Arg)->Object;
			m_vecMoster.push_back(temp1);
			break;
	
		}
		
	}
	//��������GUI������
	else if (m_pObservableGUI == pObservable)
	{
		m_listGUIComponent.push_back((((IComponent*)Arg)->Component));
	}
}

//��ʼ��ͼ��ϵͳ
bool CGraphSystem::Init()
{
	//�ڳ�����������ע���Լ�
	m_pObservableScene = CSceneManager::GetInstance();
	m_pObservableScene->RegisterObserver(this);

	m_pObservableGUI = CGUIManager::GetInstance();
	m_pObservableGUI->RegisterObserver(this);

	m_pSprite =(LPD3DXSPRITE) CPlatform::GetsinglenPtr()->FindResourceA("����ӿ�");
	return true;
}


//��Ⱦ��ǰ֡
bool CGraphSystem::Render()
{
	//��պ�̨������
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(88, 88, 88)/* 0xffffffff*/, 1.0f, 0);
	m_pDevice->BeginScene();
	//��ȾUI
	this->RenderGUI();

	//�ж���Ϸ״̬
	EnvMgrState GameState =*(EnvMgrState*) CPlatform::GetsinglenPtr()->FindResourceA("��Ϸ״̬");

	switch(GameState)
	{
	case ENV_GAME:
		{
			m_pMap->Draw();
			m_pPlayer->Draw();
			m_pSky->Draw();
			//m_pHourse->Draw();
			m_pBridge->Draw();

			vector<CModelCopy*>::iterator it1 = m_vecStaticModel.begin();
			for (; it1 != m_vecStaticModel.end(); it1++)
			{
				(*it1)->Draw();
			}
			vector<CCharacter*>::iterator it = m_vecMoster.begin();
			for (; it != m_vecMoster.end(); it++)
			{
				(*it)->Draw();
			}

			//m_pWater->Draw();//ˮ��� �������ܺ�������ģ��һ�𰢶������
		}
	}
	m_pDevice->EndScene();

	//����ǰ��̨������
	m_pDevice->Present(NULL, NULL, NULL, NULL);

	return true;
}


//��ȾGUI����
void CGraphSystem::RenderGUI(void)
{
	for (m_listGUIComponentIT = m_listGUIComponent.begin(); m_listGUIComponentIT != m_listGUIComponent.end();)
	{
		CComponent *temp = *m_listGUIComponentIT;
		//�ж�����Ƿ�ɼ�
		if ((*m_listGUIComponentIT)->IsVisible())
		{
			//��ȾGUI���
			(*m_listGUIComponentIT)->Draw();

			CComponent *temp = *m_listGUIComponentIT;
			////����������Ǵ��ڸ�������ƶ�״̬,�ǾͰ�������ÿ֡�����Ⱦ,�������Ϸ�
			if (CComponent::m_BeingWithMouseComponent == (*m_listGUIComponentIT))
			{
				CComponent *temp = *m_listGUIComponentIT;
				m_listGUIComponent.erase(m_listGUIComponentIT++);
				m_listGUIComponent.push_back(temp);
				continue;
			}
		}
		m_listGUIComponentIT++;
	}
}


#include "stdafx.h"
#include "GraphSystem.h"
//#include "Collide.h"
 
//构造函数
CGraphSystem::CGraphSystem()
	:
	m_pObservableScene(NULL), m_pDevice(NULL)
{
	m_mapAttachedObject.clear();
	
}

//析构函数
CGraphSystem::~CGraphSystem()
{
	m_mapAttachedObject.clear();
}

//发送状态接口
void CGraphSystem::Notify(IObservable* pObservable, IObject* Arg)
{

}

//接收状态接口
void CGraphSystem::Update(IObservable* pObservable, IObject* Arg)
{

	//控制器是场景控制器
	if (m_pObservableScene == pObservable)
	{
		//如果对象为空
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
	//控制器是GUI管理器
	else if (m_pObservableGUI == pObservable)
	{
		m_listGUIComponent.push_back((((IComponent*)Arg)->Component));
	}
}

//初始化图形系统
bool CGraphSystem::Init()
{
	//在场景管理器中注册自己
	m_pObservableScene = CSceneManager::GetInstance();
	m_pObservableScene->RegisterObserver(this);

	m_pObservableGUI = CGUIManager::GetInstance();
	m_pObservableGUI->RegisterObserver(this);

	m_pSprite =(LPD3DXSPRITE) CPlatform::GetsinglenPtr()->FindResourceA("精灵接口");
	return true;
}


//渲染当前帧
bool CGraphSystem::Render()
{
	//清空后台缓存区
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(88, 88, 88)/* 0xffffffff*/, 1.0f, 0);
	m_pDevice->BeginScene();
	//渲染UI
	this->RenderGUI();

	//判断游戏状态
	EnvMgrState GameState =*(EnvMgrState*) CPlatform::GetsinglenPtr()->FindResourceA("游戏状态");

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

			//m_pWater->Draw();//水最后画 这样才能和其他的模型一起阿尔法混合
		}
	}
	m_pDevice->EndScene();

	//交换前后台缓冲区
	m_pDevice->Present(NULL, NULL, NULL, NULL);

	return true;
}


//渲染GUI对象
void CGraphSystem::RenderGUI(void)
{
	for (m_listGUIComponentIT = m_listGUIComponent.begin(); m_listGUIComponentIT != m_listGUIComponent.end();)
	{
		CComponent *temp = *m_listGUIComponentIT;
		//判断组件是否可见
		if ((*m_listGUIComponentIT)->IsVisible())
		{
			//渲染GUI组件
			(*m_listGUIComponentIT)->Draw();

			CComponent *temp = *m_listGUIComponentIT;
			////如果这个组件是处于跟随鼠标移动状态,那就把它放在每帧最后渲染,处于最上方
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


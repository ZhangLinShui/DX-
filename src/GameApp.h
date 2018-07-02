#pragma once

#include "SceneManager.h"
#include"GUIManager.h"
#include "GraphSystem.h"
#include "InputSystem.h"
class CGameApp
{
public:
	//全局唯一的CGameApp对象实例的指针
	static CGameApp* GetInstance();

	//游戏启动,完成所有的初始化工作,并进入游戏循环
	bool Go();
	
	//获得图形系统对象指针
	CGraphSystem* GetGraph() { return m_GraphSys; }

	//获得输入系统对象指针
	CInputSystem* GetInput() { return m_InputSys; }

	//获得D3D设备对象
	IDirect3DDevice9* GetDevice() { return m_pDevice; }
protected:
	
	//////////////////////////////////////////////////////////////////////////
	//游戏初始化相关接口
	//////////////////////////////////////////////////////////////////////////


	//创建游戏主窗口
	bool CreateGameWindow(void);
	
	//初始化D3D程序
	bool InitD3D(void);

	//初始化管理器
	bool InitManager(void);

	//初始化各个系统
	bool InitSystem(void);

	bool InitPlatform();
	void Update(float fcote);
	//////////////////////////////////////////////////////////////////////////
	//全局的一些成员
	//////////////////////////////////////////////////////////////////////////

	//全局的应用程序实例句柄
	HINSTANCE m_hInstance;

	//全局的应用程序窗口句柄
	HWND m_hWnd;

	//全局的消息结构体
	MSG m_msg;

	//全局的光标句柄
	HCURSOR m_hCursorNormal;
	HCURSOR m_hCursorAtk;
	HCURSOR m_hCursorPick;
	HCURSOR m_hCursorNPCTalk;

	//D3D对象
	IDirect3D9* m_pD3D;

	//D3D设备对象
	IDirect3DDevice9* m_pDevice;

	//D3D设备对象的参数
	D3DPRESENT_PARAMETERS m_d3dpp;

	ID3DXSprite*        m_pSprite = NULL;	//精灵接口指针
	ID3DXFont*			m_pFont = NULL;	//字体接口
	ID3DXLine*			m_pLine = NULL;


	//图形系统的对象指针
	CGraphSystem* m_GraphSys;

	//输入系统的对象指针
	CInputSystem* m_InputSys;

	//窗口宽高
	DWORD m_dwWinWidth;
	DWORD m_dwWinHeight;

	
	EnvMgrState m_emEnvState;
private:
	
	~CGameApp();
	CGameApp();
	//全局唯一的CGameApp对象实例的指针
	static CGameApp* m_Instance;
	
};

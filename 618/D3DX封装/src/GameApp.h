#pragma once

#include "SceneManager.h"
#include"GUIManager.h"
#include "GraphSystem.h"
#include "InputSystem.h"
class CGameApp
{
public:
	//ȫ��Ψһ��CGameApp����ʵ����ָ��
	static CGameApp* GetInstance();

	//��Ϸ����,������еĳ�ʼ������,��������Ϸѭ��
	bool Go();
	
	//���ͼ��ϵͳ����ָ��
	CGraphSystem* GetGraph() { return m_GraphSys; }

	//�������ϵͳ����ָ��
	CInputSystem* GetInput() { return m_InputSys; }

	//���D3D�豸����
	IDirect3DDevice9* GetDevice() { return m_pDevice; }
protected:
	
	//////////////////////////////////////////////////////////////////////////
	//��Ϸ��ʼ����ؽӿ�
	//////////////////////////////////////////////////////////////////////////


	//������Ϸ������
	bool CreateGameWindow(void);
	
	//��ʼ��D3D����
	bool InitD3D(void);

	//��ʼ��������
	bool InitManager(void);

	//��ʼ������ϵͳ
	bool InitSystem(void);

	bool InitPlatform();
	void Update(float fcote);
	//////////////////////////////////////////////////////////////////////////
	//ȫ�ֵ�һЩ��Ա
	//////////////////////////////////////////////////////////////////////////

	//ȫ�ֵ�Ӧ�ó���ʵ�����
	HINSTANCE m_hInstance;

	//ȫ�ֵ�Ӧ�ó��򴰿ھ��
	HWND m_hWnd;

	//ȫ�ֵ���Ϣ�ṹ��
	MSG m_msg;

	//ȫ�ֵĹ����
	HCURSOR m_hCursorNormal;
	HCURSOR m_hCursorAtk;
	HCURSOR m_hCursorPick;
	HCURSOR m_hCursorNPCTalk;

	//D3D����
	IDirect3D9* m_pD3D;

	//D3D�豸����
	IDirect3DDevice9* m_pDevice;

	//D3D�豸����Ĳ���
	D3DPRESENT_PARAMETERS m_d3dpp;

	ID3DXSprite*        m_pSprite = NULL;	//����ӿ�ָ��
	ID3DXFont*			m_pFont = NULL;	//����ӿ�
	ID3DXLine*			m_pLine = NULL;


	//ͼ��ϵͳ�Ķ���ָ��
	CGraphSystem* m_GraphSys;

	//����ϵͳ�Ķ���ָ��
	CInputSystem* m_InputSys;

	//���ڿ��
	DWORD m_dwWinWidth;
	DWORD m_dwWinHeight;

	
	EnvMgrState m_emEnvState;
private:
	
	~CGameApp();
	CGameApp();
	//ȫ��Ψһ��CGameApp����ʵ����ָ��
	static CGameApp* m_Instance;
	
};

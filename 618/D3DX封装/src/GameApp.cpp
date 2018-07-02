#include "stdafx.h"
#include <timeapi.h>
#include "D3DX��װ.h"
#include "GameApp.h"

class CGameApp;


//��̬������ֵ
CGameApp* CGameApp::m_Instance = NULL;
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT downPos;
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		CGameApp::GetInstance()->GetInput()->PushMouseKey(LOWORD(lParam), HIWORD(lParam), MOUSE_NONE);
		break;

		//����������
	case WM_LBUTTONUP:
		if (GetCapture() == GetActiveWindow())
		{
			SetCapture(0);
		}
		CGameApp::GetInstance()->GetInput()->PushMouseKey(LOWORD(lParam), HIWORD(lParam), MOUSE_LB_UP);
		CGameApp::GetInstance()->GetInput()->SetLeftButtonDown(false);
		break;

		//����������
	case WM_LBUTTONDOWN:
		SetCapture(GetActiveWindow());
		CGameApp::GetInstance()->GetInput()->PushMouseKey(LOWORD(lParam), HIWORD(lParam), MOUSE_LB_DOWN);
		CGameApp::GetInstance()->GetInput()->SetLeftButtonDown(true);
		break;
	case  WM_MOUSEWHEEL:
		SetCapture(GetActiveWindow());
		CGameApp::GetInstance()->GetInput()->PushMouseKey(LOWORD(lParam), HIWORD(lParam), MOUSE_MB_WHEEL);
		CGameApp::GetInstance()->GetInput()->SetMiddleButtonDown(true);
		break;
	case WM_KEYDOWN:
		CGameApp::GetInstance()->GetInput()->KeyMessageProc(wParam, true);

		break;
	case WM_KEYUP:
		CGameApp::GetInstance()->GetInput()->KeyMessageProc(wParam, false);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

bool CGameApp::CreateGameWindow(void)
{
	m_hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	WNDCLASS wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hCursor = LoadCursorFromFile(_T("res/Arrow.cur"));
	//wc1.hIcon = LoadIcon(hInstance, (LPCWSTR)"../bin/res/��è.ico");//��ȡexe�ļ�ͼ�����exe����ʱ���Ͻǵ�ͼ��
	wnd.hIcon = (HICON)LoadImage(m_hInstance, _T("../bin/res/��è.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	//wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance = m_hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = _T("d3d");
	wnd.lpszMenuName = NULL/*MAKEINTRESOURCEA(IDC_D3DX)*/;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	//ע�ᴰ������
	RegisterClass(&wnd);

	RECT rc = { 0,0,1400,800 };
	AdjustWindowRect(&rc, WS_POPUP | WS_OVERLAPPEDWINDOW, false);
	//��������
	m_hWnd = CreateWindow(_T("d3d"), _T("D3DX��װ"), WS_POPUP | WS_OVERLAPPEDWINDOW, 200, 20, rc.right - rc.left, rc.bottom - rc.top, 0, 0, m_hInstance, NULL);
	if (!m_hWnd)
	{
		return false;
	}
	RECT rc1;
	GetClientRect(m_hWnd, &rc1);
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}



bool CGameApp::InitD3D(void)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//����ڴ�
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;							//��̨�����ʽ
	d3dpp.hDeviceWindow = m_hWnd;										//�豸���ھ��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//˫����(��̨����)
	d3dpp.Windowed = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;						//������ȸ�ʽ
	d3dpp.EnableAutoDepthStencil = true;								//�Ƿ�������ȸ�ʽ
	
	//D3DCREATE_HARDWARE_VERTEXPROCESSING   D3DCREATE_SOFTWARE_VERTEXPROCESSING
	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDevice);
	//SetRenderState()���û���״̬
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);					//�رչ���
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			//�ü�ģʽΪ���ü�return S_OK;
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//����Ϊ�߿�
	
	D3DXCreateSprite(m_pDevice, &m_pSprite);
	D3DXCreateFontA(m_pDevice, 20, 20, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, "����", &m_pFont);

	D3DXCreateLine(m_pDevice, &m_pLine);
	
	
	return true;
}

bool CGameApp::InitPlatform()
{
	CPlatform::GetsinglenPtr()->AddResource("���ھ��", m_hWnd);
	CPlatform::GetsinglenPtr()->AddResource("ʵ�����", m_hInstance);
	CPlatform::GetsinglenPtr()->AddResource("���ڿ��", &m_dwWinWidth);
	CPlatform::GetsinglenPtr()->AddResource("���ڸ߶�", &m_dwWinHeight);
	CPlatform::GetsinglenPtr()->AddResource("�豸�ӿ�", m_pDevice);


	CPlatform::GetsinglenPtr()->AddResource("����ӿ�", m_pSprite);
	CPlatform::GetsinglenPtr()->AddResource("����ӿ�", m_pFont);
	CPlatform::GetsinglenPtr()->AddResource("���߽ӿ�", m_pLine);

	CPlatform::GetsinglenPtr()->AddResource("��Ϸ״̬", &m_emEnvState);

	return true;
}

void CGameApp::Update(float fcote)
{
	m_InputSys->InputProc();
}

bool CGameApp::InitManager(void)
{
	CGUIManager::GetInstance()->SetDevice(m_pDevice);
	if (!CGUIManager::GetInstance()->Init("./UI/GUI.txt"))
	{
		return false;
	}
	CSceneManager::GetInstance()->SetDevice(m_pDevice);
	if (!CSceneManager::GetInstance()->Init("./res/Object/MyObject.xml"))
	{
		return false;
	}
	return true;
}

bool CGameApp::InitSystem(void)
{
	m_GraphSys = new CGraphSystem();
	m_InputSys = new CInputSystem();

	m_GraphSys->SetDevice(m_pDevice);
	m_GraphSys->Init();

	m_InputSys->Init();
	return true;
}

CGameApp* CGameApp::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new CGameApp();
	}
	return m_Instance;
}

bool CGameApp::Go()
{

	//������Ϸ������,����ʧ����ֱ���˳�
 	if (!CreateGameWindow())
	{
		MessageBox(m_hWnd, _T("������Ϸ����ʧ��"), _T("������Ϸ����ʧ��"), MB_OK);
		return false;
	}
	//��ʼ��D3D����
	if (!InitD3D())
	{
		return false;
	}

	if (!InitPlatform())
	{
		return false;
	}

	//��ʼ��ϵͳ
	if (!InitSystem())
	{
		return false;
	}
	//��ʼ��������
	if (!InitManager())
	{
		return false;
	}

	long GameState = 0;

	//��Ϸѭ��
	while (TRUE)
	{
		if (PeekMessage(&m_msg, 0, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT)
				break;
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		else
		{
			static float fPreTime = static_cast<float>(timeGetTime());
			float fCurrentTime = static_cast<float>(timeGetTime());
			float fElapsedTime = (fCurrentTime - fPreTime)*0.001f;
			fPreTime = fCurrentTime;


			Update(fElapsedTime);
			m_GraphSys->Render();

		}
	}
	delete CGameApp::GetInstance();
	return true;
}

CGameApp::CGameApp()
	: m_hInstance(0)
	, m_hWnd(0)
	, m_hCursorNormal(0)
	, m_hCursorAtk(0)
	, m_hCursorPick(0)
	, m_hCursorNPCTalk(0)
	, m_pD3D(NULL)
	, m_pDevice(NULL)
	//, m_GraphSys(NULL)
	//, m_InputSys(NULL)
	//, m_dwFrameCount(0)
	//, m_fFrameCost(0)
{
	ZeroMemory(&m_msg, sizeof(m_msg));
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

	m_emEnvState = ENV_LOGIN;
	m_dwWinWidth = 1400;
	m_dwWinHeight = 800;
}

CGameApp::~CGameApp()
{
}

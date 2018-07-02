// D3DX封装.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GameApp.h"




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CGameApp::GetInstance()->Go();
	return 1;
}





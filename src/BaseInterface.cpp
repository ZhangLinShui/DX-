#include "stdafx.h"
#include "BaseInterface.h"
#include "GUIManager.h"
#include"SceneManager.h"
 
CBaseInterface::CBaseInterface()
{
}


CBaseInterface::~CBaseInterface()
{
}
void LoginConnect();
void LoginQuit();

void DoGlobeEvent(string name)
{
	if (name == "LoginConnect")
	{
		LoginConnect();

		
	}
	if (name == "LoginQuit")
	{
		LoginQuit();
	}
	
	if (name == "OutGame")
	{
		LoginQuit();
	}
	
}
void LoginConnect()
{
	
	CGUIManager::GetInstance()->GetComponentByName("FrameLongin")->SetVisible(false);
	
	*(EnvMgrState*)CPlatform::GetsinglenPtr()->FindResourceA("сно╥в╢л╛") = ENV_GAME;


	
}

void LoginQuit()
{
	PostQuitMessage(0);
}


#include "stdafx.h"
#include "InputSystem.h"

//构造函数
CInputSystem::CInputSystem()
{
	m_lX = 0;
	m_lY = 0;
	m_lOldX = 0;
	m_lOldY = 0;
	m_bLeftDown = false;
	m_bRightDown = false;
	m_bMiddleDown = false;
	m_lDelta = 0;
	m_pObservableScene = NULL;

	ZeroMemory(m_cKeyBuffer, sizeof(m_cKeyBuffer));
}

//析构函数
CInputSystem::~CInputSystem()
{
	while (m_queueMouseKey.size() != 0)
	{
		tagMouseKey* p = m_queueMouseKey.front();
		m_queueMouseKey.pop();
		SAFE_DELETE(p);
	}
}

//初始化
bool CInputSystem::Init()
{
	m_pObservableScene = CSceneManager::GetInstance();
	m_pObservableScene->RegisterObserver(this);

	return true;
}

//发送状态接口
void CInputSystem::Notify(IObservable* pObservable, IObject* Arg)
{

}

//接收状态接口
void CInputSystem::Update(IObservable *pObservable, IObject *Arg)
{
	//如果对象为空
	if (!((ImapObject*)Arg)->Object)
	{
		return;
	}

	if (pObservable == m_pObservableScene)
	{
		//如果对象为空
		if (!((ImapObject*)Arg)->Object)
		{

			return;
		}
		long objecttype = ((ImapObject*)Arg)->Object->GetType();
		CModelCopy *temp;
		CCharacter *temp1;
		switch (objecttype)
		{
		case OB_TYPE_NOTYPE:
			break;
		case OB_TYPE_PLAYER:
			m_pPlayer = (CPlayer*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_CAMERA:
			m_pCamera = (CCamera*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_SKY:
			m_pSky = (CSky*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_MAP:
			m_pMap = (CCMap*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_Light:
			//m_pLight = (CLight*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_BRIDGE:
			m_pBridge = (CBridge*)((ImapObject*)Arg)->Object;
			break;
		case OB_TYPE_HOURSE:
			m_pHourse = (CHourse*)((ImapObject*)Arg)->Object;
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
}

//这个函数里的操作都是基于窗口消息的
bool CInputSystem::MouseMessageProc()
{

	if (m_queueMouseKey.size() == 0)
	{
		return false;
	}
	POINT P2;
	GetCursorPos(&P2);
	tagMouseKey* p = m_queueMouseKey.front();
	m_lX = p->lX;
	m_lY = p->lY;

	m_fOffsetX = (m_lX - m_lOldX);
	m_fOffsetY = (m_lY - m_lOldY);
	EnvMgrState GameState = *(EnvMgrState*)CPlatform::GetsinglenPtr()->FindResourceA("游戏状态");
	if (GameState)
	{

		if (GetKeyState(VK_RBUTTON) & 0x8000)
		{
			if (m_fOffsetX)
			{
				float angleY = m_fOffsetX*0.01;
				cameraAngleY += m_fOffsetX*0.01;
				//AngleY += m_fOffsetX*0.01;
				D3DXMATRIX matRot;
				D3DXMatrixRotationY(&matRot, angleY);
				D3DXVec3TransformNormal(&dir, &m_pCamera->GetForwordDir(), &matRot);
				m_pCamera->SetForwordDir(dir);
				D3DXVec3TransformNormal(&dir, &m_pCamera->GetRightDir(), &matRot);
				m_pCamera->SetRightDir(dir);
				D3DXVec3TransformNormal(&dir, &m_pCamera->GetUpDir(), &matRot);
				m_pCamera->SetUpDir(dir);
				m_fOffsetX = 0;
			}
			if (m_fOffsetY)
			{
				float angleX = m_fOffsetY*0.01;
				cameraAngleX += m_fOffsetY*0.01;
				//AngleY -= m_fOffsetX*0.01;
				D3DXMATRIX matRot;
				D3DXMatrixRotationAxis(&matRot, &m_pCamera->GetRightDir(), angleX);
				D3DXVec3TransformNormal(&dir, &m_pCamera->GetForwordDir(), &matRot);
				m_pCamera->SetForwordDir(dir);
				D3DXVec3TransformNormal(&dir, &m_pCamera->GetUpDir(), &matRot);
				m_pCamera->SetUpDir(dir);
				m_fOffsetY = 0;
			}
		}
		if (GetKeyState(VK_LBUTTON)&0x8000)
		{
			bLButtonDown = true;
			if (!cameraAngleY)
			{
				if (m_fOffsetX)
				{
					float angleY = m_fOffsetX*0.01;
					//cameraAngleY += m_fOffsetX *0.01;
					D3DXMATRIX matRot;
					D3DXMatrixRotationY(&matRot, angleY);
					D3DXVec3TransformNormal(&dir, &m_pCamera->GetForwordDir(), &matRot);
					m_pCamera->SetForwordDir(dir);
					D3DXVec3TransformNormal(&dir, &m_pCamera->GetRightDir(), &matRot);
					m_pCamera->SetRightDir(dir);
					D3DXVec3TransformNormal(&dir, &m_pCamera->GetUpDir(), &matRot);
					m_pCamera->SetUpDir(dir);

					D3DXVec3TransformNormal(&dir, &m_pPlayer->GetForwordDir(), &matRot);
					m_pPlayer->SetForwordDir(dir);

					D3DXVec3TransformNormal(&dir, &m_pPlayer->GetCurrentDir(), &matRot);
					m_pPlayer->SetCurrentDir(dir);

					D3DXVec3TransformNormal(&dir, &m_pPlayer->GetRightDir(), &matRot);
					m_pPlayer->SetRightDir(dir);
					D3DXVec3TransformNormal(&dir, &m_pPlayer->GetUpDir(), &matRot);
					m_pPlayer->SetUpDir(dir);
					m_fOffsetX = 0;
				}
				if (m_fOffsetY)
				{
					float angleX = m_fOffsetY*0.01;
					AngleY += m_fOffsetY * 0.01;
					D3DXMATRIX matRot;
					D3DXMatrixRotationAxis(&matRot, &m_pCamera->GetRightDir(), angleX);
					D3DXVec3TransformNormal(&dir, &m_pCamera->GetForwordDir(), &matRot);
					m_pCamera->SetForwordDir(dir);
					D3DXVec3TransformNormal(&dir, &m_pCamera->GetUpDir(), &matRot);
					m_pCamera->SetUpDir(dir);

					/*D3DXVec3TransformNormal(&dir, &m_pPlayer->GetForwordDir(), &matRot);
					m_pPlayer->SetForwordDir(dir);*/

					/*D3DXVec3TransformNormal(&dir, &m_pPlayer->GetCurrentDir(), &matRot);
					m_pPlayer->SetCurrentDir(dir);*/

					/*D3DXVec3TransformNormal(&dir, &m_pPlayer->GetUpDir(), &matRot);
					m_pPlayer->SetUpDir(dir);*/
					m_fOffsetY = 0;
				}
			}
		}
		else
			bLButtonDown = false;
		if ((bLButtonDown || bCubeMove) && cameraAngleY)
		{
			bAjustCamera = true;
		}
	}
	m_lOldX = m_lX;
	m_lOldY = m_lY;

	
	//仅判断鼠标移动
	if (!m_bLeftDown && !m_bRightDown)
	{
		//判断有没有物品栏处于鼠标跟随状态
		if (CComponent::m_BeingWithMouseComponent)
		{
			CComponent::m_BeingWithMouseComponent->SetPos((m_fOffsetX), m_fOffsetY);
		}
		//执行GUI系统事件,检测鼠标在不在GUI组件上
		CGUIManager::GetInstance()->ProcessMouseMove(m_lX, m_lY);
	}

	switch (p->lKey)
	{
		//鼠标移动消息
	case MOUSE_NONE:

		//如果目前的状态为处理GUI事件的话
		if (CComponent::m_bProcessGUI)
		{
			//判断当前鼠标左键有没有按下
			if (m_bLeftDown)
			{
				if (CComponent::m_BeingDownComponent)
				{
					//判断该组件能不能拖曳
					if (CComponent::m_BeingDownComponent->BeDrag() && !CComponent::m_BeingWithMouseComponent)
					{
						//如果可以拖曳,就使用SetPos这个接口设置位置(参数是X,Y的偏移量)
						CComponent::m_BeingDownComponent->SetPos((m_fOffsetX), m_fOffsetY);
						//CComponent::m_BeingWithMouseComponent->SetPos((m_fOffsetX*0.25f),m_fOffsetY*0.005f);
						break;
					}
					//如果有物品栏处于鼠标跟随移动状态的话
					if (CComponent::m_BeingWithMouseComponent)
					{
						CComponent::m_BeingWithMouseComponent->SetPos((m_fOffsetX), m_fOffsetY);
					}
				}
			}
		}
		break;
		//鼠标左键按下消息
	case MOUSE_LB_DOWN:
		//先判断鼠标的位置
		CGUIManager::GetInstance()->ProcessMouseMove(m_lX,m_lY);
		//如果鼠标位置正处于某个组件上
		if (CComponent::m_bProcessGUI)
		{
			if (CComponent::m_BeingMovetoComponent)
			{
				CComponent::m_BeingMovetoComponent->ProcessMouseLBDown(m_lX, m_lY);
				break;
			}
		}
		break;
	case MOUSE_LB_UP:
		//如果有组件被按下
		if (CComponent::m_BeingDownComponent)
		{
			CComponent::m_BeingDownComponent->ProcessMouseLBUp(m_lX, m_lY);
		}
		CComponent::m_bProcessGUI = false;

		//设置鼠标的位置,并显示鼠标
		//SetCursorPos(m_PtMouseDown.x,m_PtMouseDown.y);
		//ShowCursor(TRUE);
		break;

	}

	m_queueMouseKey.pop();
	SAFE_DELETE(p);

	return true;
}

void CInputSystem::PushMouseKey(long lMouseX, long lMouseY, long lValue)
{
	//如果正在执行GUI系统的操作的话就不需要继续
	tagMouseKey* p = new tagMouseKey;
	p->lX = lMouseX;
	p->lY = lMouseY;
	p->lKey = lValue;
	m_queueMouseKey.push(p);

}

bool CInputSystem::KeyMessageProc(DWORD keyValue,bool b)
{
	m_cKeyBuffer[keyValue] = b;

	return true;
}


//判断用户按键函数
bool CInputSystem::IsKeyPressed(long key)
{

	if (m_cKeyBuffer[key])
	{
		return true;
	}
	return false;
}
void CInputSystem::InputProc()
{
	this->MouseMessageProc();
	EnvMgrState GameState = *(EnvMgrState*)CPlatform::GetsinglenPtr()->FindResourceA("游戏状态");
	if (GameState)
	{
		PlayerMove();

		//m_pCamera->SetPos(m_pPlayer->GetPos() - m_pCamera->GetForwordDir()*m_pCamera->GetCamareToObjectDist());
		/*vector<CModelCopy*>::iterator it = m_vecStaticModel.begin();
		for (; it != m_vecStaticModel.end(); it++)
		{
			D3DXVECTOR3 pos = (*it)->GetPos();
			if (D3DXVec3Length(&(m_pPlayer->GetPos() - pos)) < 800)
			{
				SetCamera(*it);
			}
			else
				m_pCamera->SetPos(m_pPlayer->GetPos() - m_pCamera->GetForwordDir()*m_pCamera->GetCamareToObjectDist());

		}*/
		m_pCamera->SetPos(m_pPlayer->GetPos() - m_pCamera->GetForwordDir()*m_pCamera->GetCamareToObjectDist());

		m_pCamera->SetCamera();
	}
}

void CInputSystem::PlayerMove()
{
	static bool flag1 = false;
	static D3DXVECTOR3 posTemp, posTemp1;
	static DWORD preTime = GetTickCount();
	DWORD curTime = GetTickCount();
	D3DXVECTOR3 dirX = { 1,0,0 };
	static float Speed = 5;
	D3DXVECTOR3 start, start1;
	D3DXVECTOR3 dir = m_pPlayer->GetCurrentDir();
	D3DXVec3Normalize(&dir, &dir);
	D3DXVECTOR3 pos;
	D3DXMATRIX matInverse = m_pPlayer->GetMatInverse();


	if (IsKeyPressed(' ') && !flag1)
	{
		isDown = false;
		flag = true;
		flag1 = true;
		t = 0; s = 0;
		posTemp = m_pPlayer->GetPos();
	}
	 if (IsKeyPressed('W'))
	{
		pos = m_pPlayer->GetPos() + dir * Speed;
		if (!HitTestAABBCModelCopy(pos, dir, start1))//检测是否前进
		{
			m_pPlayer->ChangePos(dir*Speed);
			m_pPlayer->SetAnimation(MT_WALK);
		}
		if (!HitTestAABBCModelCopy1(m_pPlayer->GetPos(), start))//检测Y值
		{
			start = m_pMap->GetPosY(m_pPlayer->GetPos());
		}
		bCubeMove = true;
	}
	 if (IsKeyPressed('S'))
	{
		pos = m_pPlayer->GetPos() - dir * Speed;
		if (!HitTestAABBCModelCopy(pos, -dir, start1))
		{

			m_pPlayer->ChangePos(-dir * Speed);
			m_pPlayer->SetAnimation(MT_WALK);
		}
		if (!HitTestAABBCModelCopy1(m_pPlayer->GetPos(), start))
		{ 
			start = m_pMap->GetPosY(m_pPlayer->GetPos());
		}
		bCubeMove = true;
	}
	
	if (!IsKeyPressed(' '))
	{
		flag1 = false;
	}
	D3DXVECTOR3 Temppos;
	if (flag)
	{
		if (!isDown)
		{
			t += 0.2;
			s = v0_speed*t - 0.5*acc*t*t;
			float v = v0_speed - acc * t;
			if (v < 0.000001)
			{
				isDown = true;
				t = 0;
			}
			D3DXVECTOR3 dir = { 0,1,0 };
			posTemp.x = m_pPlayer->GetPos().x;
			posTemp.z = m_pPlayer->GetPos().z;
			Temppos = dir*s;
			start = Temppos + posTemp;
		}
		else
		{
			float s2 = 0;
			t += 0.2;
			s2 = s - 0.5*acc*t*t;
			posTemp.x = m_pPlayer->GetPos().x;
			posTemp.z = m_pPlayer->GetPos().z;
			D3DXVECTOR3 dir = { 0,1,0 };
			Temppos = dir * s2;
			Temppos= Temppos + posTemp;
			D3DXVECTOR3 FreeLength = dir * 0.5*acc*t*t;
			if (!HitTestAABBCModelCopy1(Temppos, start))
			{
				float a = D3DXVec3Length(&(m_pPlayer->GetPos() - m_pMap->GetPosY(m_pPlayer->GetPos())));
				float b = D3DXVec3Length(&FreeLength);
				//if (D3DXVec3Length(&(m_pPlayer->GetPos() - m_pMap->GetPosY(m_pPlayer->GetPos()))) < 0.000001)
				if (m_pPlayer->GetPos().y - m_pMap->GetPosY(m_pPlayer->GetPos()).y < 0.000001)
				{
					start = m_pMap->GetPosY(m_pPlayer->GetPos());
					t = 0;
					s = 0;
					s2 = 0;
					flag = false;
					isDown = false;
				}
				else
					start = Temppos;
			}
			else
			{
				t = 0;
				s = 0;
				s2 = 0;
				flag = false;
				isDown = false;
			}
		}
		m_pPlayer->SetPos(start);
	}
	else
	{
		if (!HitTestAABBCModelCopy1(m_pPlayer->GetPos(), start) &&
			m_pPlayer->GetPos().y - m_pMap->GetPosY(m_pPlayer->GetPos()).y > 0.000001 && !Freedom)
		{
			posTemp1 = m_pPlayer->GetPos();
			Freedom = true;
		}
		if(Freedom)
		{
			float s2 = 0;
			t += 0.2;
			s2 = s - 0.5*acc*t*t;
			posTemp1.x = m_pPlayer->GetPos().x;
			posTemp1.z = m_pPlayer->GetPos().z;
			D3DXVECTOR3 dir = { 0,1,0 };
			Temppos = dir * s2;
			Temppos = Temppos + posTemp1;
			if (!HitTestAABBCModelCopy1(Temppos, start))
			{
				//if (D3DXVec3Length(&(m_pPlayer->GetPos() - m_pMap->GetPosY(m_pPlayer->GetPos()))) > 0.000001)
				if (m_pPlayer->GetPos().y - m_pMap->GetPosY(m_pPlayer->GetPos()).y < 0.000001)
				{
					start = m_pMap->GetPosY(m_pPlayer->GetPos());
					t = 0;
					s = 0;
					s2 = 0;
					Freedom = false;
				}
				else
					start = Temppos;
			}
			else
			{
				t = 0;
				s = 0;
				s2 = 0;
				Freedom = false;
			}
		}
		if (!HitTestAABBCModelCopy1(m_pPlayer->GetPos(), start))
		{
			if (m_pPlayer->GetPos().y - m_pMap->GetPosY(m_pPlayer->GetPos()).y < 0.000001)
			{
				start = m_pMap->GetPosY(m_pPlayer->GetPos());
			}
		}
		
		bCubeMove = false;
		//start.y = start.y + 30;
		m_pPlayer->SetPos(start);
	}
	if (!IsKeyPressed('W')&& !IsKeyPressed('S')&& !IsKeyPressed(' '))
	{
		m_pPlayer->SetAnimation(MT_STAY);
	}
	static float aa = 0.01;
	if (bAjustCamera)
	{
		if (cameraAngleY)
		{
			if (fabs(cameraAngleY) > 6.28)
			{
				int a = fabs(cameraAngleY) / 6.28;
				if (cameraAngleY > 0)
					cameraAngleY -= a*6.28;
				else
					cameraAngleY += a*6.28;
			}

			if (cameraAngleY > 3.14)
			{
				cameraAngleY = -6.28 + cameraAngleY;
			}
			if (cameraAngleY < -3.14)
			{
				cameraAngleY = 6.28 + cameraAngleY;
			}
			
			static float speed = aa;
			if (cameraAngleY > aa)
				speed = -aa;
			else if (cameraAngleY < -aa)
				speed = aa;
			else
			{
				cameraAngleY = 0;
				speed = 0;
			}
			cameraAngleY += speed;
			D3DXMATRIX matRot;
			D3DXMatrixRotationY(&matRot, speed);
			D3DXVec3TransformNormal(&dir, &m_pCamera->GetForwordDir(), &matRot);
			m_pCamera->SetForwordDir(dir);
			D3DXVec3TransformNormal(&dir, &m_pCamera->GetRightDir(), &matRot);
			m_pCamera->SetRightDir(dir);
			D3DXVec3TransformNormal(&dir, &m_pCamera->GetUpDir(), &matRot);
			m_pCamera->SetUpDir(dir);
		}
		if (cameraAngleX)
		{
			if (fabs(cameraAngleX) > 6.28)
			{
				int a = fabs(cameraAngleX) / 6.28;
				if (cameraAngleX > 0)
					cameraAngleX -= a*6.28;
				else
					cameraAngleX += a*6.28;
			}

			if (cameraAngleX > 3.14)
			{
				cameraAngleX = -6.28 + cameraAngleY;
			}
			if (cameraAngleX < -3.14)
			{
				cameraAngleX = 6.28 + cameraAngleY;
			}
			static float speed = aa;
			if (cameraAngleX > aa)
				speed = -aa;
			else if (cameraAngleX < -aa)
				speed = aa;
			else
			{
				cameraAngleX = 0;
				speed = 0;
			}
			cameraAngleX += speed;
			D3DXMATRIX matRot;
			D3DXMatrixRotationAxis(&matRot, &m_pCamera->GetRightDir(), speed);
			D3DXVec3TransformNormal(&dir, &m_pCamera->GetForwordDir(), &matRot);
			m_pCamera->SetForwordDir(dir);
			D3DXVec3TransformNormal(&dir, &m_pCamera->GetRightDir(), &matRot);
			m_pCamera->SetRightDir(dir);
			D3DXVec3TransformNormal(&dir, &m_pCamera->GetUpDir(), &matRot);
			m_pCamera->SetUpDir(dir);
		}
		if (!cameraAngleX && !cameraAngleY)
		{
			bAjustCamera = false;
		}
	}
}
void CInputSystem::MapMove()
{
	
}
bool CInputSystem::IsDrop(D3DXVECTOR3 pos, CModelCopy*it, D3DXVECTOR3 &start)
{
	BOOL IsHit;
	DWORD faceIndec;
	float u, v, dist;
	D3DXVECTOR3  dir2,ppos;
	D3DXMATRIX matInverse = it->GetMatInverse();

	dir2 = D3DXVECTOR3(0, -1, 0);
	D3DXVECTOR3 YY = -dir2 * 15;
	ppos = pos + YY;
	D3DXVec3TransformCoord(&ppos, &ppos, &matInverse);
	D3DXVec3TransformNormal(&dir2, &dir2, &matInverse);
	D3DXVec3Normalize(&dir2, &dir2);
	D3DXIntersect(it->GetCModel()->GetMesh(), &ppos, &dir2, &IsHit, &faceIndec, &u, &v, &dist, NULL, NULL);
	D3DXVECTOR3 dist00 = ppos + dist * dir2;
	D3DXVec3TransformCoord(&ppos, &ppos, &it->GetmatWorld());
	D3DXVec3TransformCoord(&dist00, &dist00, &it->GetmatWorld());
	D3DXVECTOR3 dist01 = ppos - dist00-YY;
	float a = D3DXVec3Length(&dist01);
	if (IsHit && D3DXVec3Length(&dist01) < 0.2 * 40)
	{
		start = dist00;
		return true;
	}
	return false;
}

bool CInputSystem::IsCanMove(D3DXVECTOR3 pos, D3DXVECTOR3 dirZ, CModelCopy*it)
{
	BOOL IsHit;
	float distence;
	DWORD faceIndec;
	float u, v;
	D3DXVECTOR3  dir2 = dirZ;
	D3DXMATRIX matInverse;
	matInverse = it->GetMatInverse();
	D3DXVECTOR3 TempY = m_pPlayer->GetUpDir() * 15;
	D3DXVECTOR3 StartY[4];
	for (int i = 0; i < 4; ++i)
	{
		StartY[i] = pos + (i+1)*TempY;
		D3DXVec3TransformCoord(&StartY[i], &StartY[i], &matInverse);//坐标转换
		D3DXVec3TransformNormal(&dir2, &dir2, &matInverse);//向量转换
		D3DXVec3Normalize(&dir2, &dir2);
		D3DXIntersect(it->GetCModel()->GetMesh(), &StartY[i], &dir2, &IsHit, &faceIndec, &u, &v, &distence, nullptr, nullptr);
		D3DXVECTOR3 dist00 = StartY[i] + distence * dir2;
		D3DXVec3TransformCoord(&StartY[i], &StartY[i], &it->GetmatWorld());
		D3DXVec3TransformCoord(&dist00, &dist00, &it->GetmatWorld());
		D3DXVECTOR3 dist01 = StartY[i] - dist00;
		float a = D3DXVec3Length(&dist01);
		if (IsHit && D3DXVec3Length(&dist01) < 0.2 * 40)
		{
			return true;
		}
	}
	return false;
}
void CInputSystem::SetCamera(CModelCopy*it)
{
	D3DXVECTOR3 pos, pos2;
	pos = it->GetPos();
	if (D3DXVec3Length(&(m_pPlayer->GetPos() - pos)) < 800)
	{
		BOOL bHit;
		DWORD faceIndec;
		float u, v, dist;
		D3DXVECTOR3 start, dir2 = -m_pCamera->GetForwordDir();
		D3DXMATRIX matInverse = it->GetMatInverse();
		start = m_pPlayer->GetPos() + D3DXVECTOR3{ 0,10,0 };
		D3DXVec3TransformCoord(&start, &start, &matInverse);
		D3DXVec3TransformNormal(&dir2, &dir2, &matInverse);
		D3DXVec3Normalize(&dir2, &dir2);
		D3DXIntersect(it->GetCModel()->GetMesh(), &start, &dir2, &bHit, &faceIndec, &u, &v, &dist, NULL, NULL);
		if (bHit&&dist < m_pCamera->GetCamareToObjectDist())
		{
			start += dist*dir2;
			
			D3DXVec3TransformCoord(&start, &start, &it->GetmatWorld());
			m_pCamera->SetPos(start);
			return;
		}
		/*	else
		m_pCamera->SetPos(m_pPlayer->GetPos() - m_pCamera->GetForwordDir()*m_pCamera->GetCamareToObjectDist());*/
	}
	BOOL bHit;
	DWORD faceIndec;
	float u, v, dist;
	D3DXVECTOR3 start, dir2 = -m_pCamera->GetForwordDir();
	D3DXMATRIX matInverse = m_pMap->GetMatInverse();
	start = m_pPlayer->GetPos() + D3DXVECTOR3{ 0,10,0 };
	D3DXVec3TransformCoord(&start, &start, &matInverse);
	D3DXVec3TransformNormal(&dir2, &dir2, &matInverse);
	D3DXVec3Normalize(&dir2, &dir2);
	D3DXIntersect(m_pMap->GetMesh(), &start, &dir2, &bHit, &faceIndec, &u, &v, &dist, NULL, NULL);
	if (bHit&&dist < m_pCamera->GetCamareToObjectDist())
	{
		start += dist*dir2;
		D3DXVec3TransformCoord(&start, &start, &m_pMap->GetmatWorld());
		m_pCamera->SetPos(start);
	}
	
}
bool CInputSystem::HitTestAABBCModelCopy(D3DXVECTOR3 pos,D3DXVECTOR3 dirZ, D3DXVECTOR3 &start)
{
	vector<CModelCopy*>::iterator it = m_vecStaticModel.begin();
	for (; it != m_vecStaticModel.end(); it++)
	{
		/******************以下写OBB碰撞**********************/
		BOOL bHit;
		DWORD faceIndec;
		float u, v, dist;
		D3DXVECTOR3  dir2;
		D3DXMATRIX matInverse = (*it)->GetMatInverse();

		D3DXVECTOR3 TempY = m_pPlayer->GetUpDir() * 15;
		D3DXVECTOR3 StartY[4];
		for (int i = 0; i < 4; ++i)
		{
			StartY[i] = pos + (i + 1)*TempY;
			dir2 = dirZ;
			D3DXVec3Normalize(&dir2, &dir2);
			/*D3DXVECTOR3 YY = -dir2 * 0;
			start = pos + YY;*/
			D3DXVec3TransformCoord(&StartY[i], &StartY[i], &matInverse);
			D3DXVec3TransformNormal(&dir2, &dir2, &matInverse);//向量转换
			D3DXIntersect((*it)->GetCModel()->GetBoxMesh(), &StartY[i], &dir2, &bHit, &faceIndec, &u, &v, &dist, NULL, NULL);
			if (bHit)
			{
				if (IsCanMove(pos, dirZ, *it))
					return true;
			}
		}
	}
	return false;
}

bool CInputSystem::HitTestAABBCModelCopy1(D3DXVECTOR3 pos, D3DXVECTOR3 &start)
{
	vector<CModelCopy*>::iterator it = m_vecStaticModel.begin();
	for (; it != m_vecStaticModel.end(); it++)
	{
		BOOL bHit;
		DWORD faceIndec;
		float u, v, dist;
		D3DXVECTOR3  dir2, ppos;
		D3DXMATRIX matInverse = (*it)->GetMatInverse(); 
		dir2 = D3DXVECTOR3(0, -1, 0);
		D3DXVec3Normalize(&dir2, &dir2);
		D3DXVECTOR3 YY = -dir2 * 15;
		ppos = pos + YY;
		D3DXVec3TransformCoord(&ppos, &ppos, &matInverse);
		D3DXVec3TransformNormal(&dir2, &dir2, &matInverse);//向量转换
		
		D3DXIntersect((*it)->GetCModel()->GetBoxMesh(), &ppos, &dir2, &bHit, &faceIndec, &u, &v, &dist, NULL, NULL);
		if (bHit)
		{
			//if (m_pPlayer->GetPos().y - (*it)->GetPos().y > 0.2*40)
  				if (IsDrop(pos, *it, start))
					return true;
		}
	}
	return false;
}

bool CInputSystem::HitTestAABBCharacter()
{
	vector<CCharacter*>::iterator it = m_vecMoster.begin();
	for (; it != m_vecMoster.end(); it++)
	{
		//以下写OBB碰撞
		if (D3DXVec3Length(&(m_pPlayer->GetPos() - (*it)->GetPos())) < 50)
		{
			
			return true;
		}
		
	}
	return false;
}

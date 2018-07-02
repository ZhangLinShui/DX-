//////////////////////////////////////////////////////////////////////////
//Name:InputSystem.h
//所有的主玩家的操作都封装在了这个类中
//以及所有和主玩家有关的对象的操作
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "SceneManager.h"
#include "GUIManager.h"
#include "GraphSystem.h"

//鼠标消息的结构体
struct tagMouseKey
{
	long lX, lY;
	long lKey;
};

//鼠标类,对游戏进行基本的控制
class CInputSystem : public IObserver
{

public:

	//构造函数
	CInputSystem();

	//析构函数
	~CInputSystem();

	//初始化系统
	bool Init();

	//发送状态接口
	void Notify(IObservable* pObservable, IObject* Arg);

	//接收状态接口
	void Update(IObservable* pObservable, IObject* Arg);

protected:

	//保存在系统里面的观察值模式控制器
	CSceneManager* m_pObservableScene;

	//鼠标控制部分

private:

	bool m_bLeftDown;
	bool m_bRightDown;
	bool m_bMiddleDown;

	long m_lX;
	long m_lY;
	long m_lOldX;
	long m_lOldY;
	float m_fOffsetX;
	float m_fOffsetY;
	long m_lDelta;


private:

	//鼠标消息队列
	queue<tagMouseKey*> m_queueMouseKey;
	//模型对象数组
	vector<CModelCopy*>		m_vecStaticModel;
	vector<CCharacter*>		m_vecMoster;
public:

	long GetMouseX(void) { return m_lX; }
	long GetMouseY(void) { return m_lY; }
	long GetOldMouseX(void) { return m_lOldX; }
	long GetOldMouseY(void) { return m_lOldY; }
	long GetMouseOffsetX(void) { return m_lX - m_lOldX; }
	long GetMouseOffsetY(void) { return m_lY - m_lOldY; }

	bool IsLeftButtonDown(void) { return m_bLeftDown; }
	bool IsRightButtonDown(void) { return m_bRightDown; }
	bool IsMiddleButtonDown(void) { return m_bMiddleDown; }

	void SetLeftButtonDown(bool bdown) { m_bLeftDown = bdown; }
	void SetRightButtonDown(bool bdown) { m_bRightDown = bdown; }
	void SetMiddleButtonDown(bool bdown) { m_bMiddleDown = bdown; }
	void SetMouseWheelDelta(long delta) { m_lDelta = delta; }

	long GetWheelDelta() { return m_lDelta; }

public:

	//处理鼠标消息
	bool MouseMessageProc();
	void PushMouseKey(long lMouseX, long lMouseY, long lValue);
	

	void PlayerMove();
	void MapMove();
	void InputProc();
	//键盘部分
public:

	//判断用户按键函数
	bool IsKeyPressed(long);
	bool KeyMessageProc(DWORD keyValue,bool b);
protected:
	//键盘缓冲区
	char m_cKeyBuffer[256];

	//需要控制的对象
private:
	D3DXVECTOR3 dir;
	float cameraAngleY;
	float AngleY;
	float cameraAngleX;
	bool bLButtonDown;
	bool bAjustCamera;
	bool bCubeMove;
	CPlayer			* m_pPlayer;
	CSky			* m_pSky;
	CBridge			*m_pBridge;
	CCamera			*m_pCamera;
	CCMap			*m_pMap;
	CHourse			*m_pHourse;

	/**************跳跃*****************/
	bool flag = false;
	bool isDown = false;
	float s = 0;
	float v = 0;
	float acc = 10;//重力
	float t = 0;//时间
	float v0_speed = 50;//初速度
	float H = (v0_speed*v0_speed) / (2 * acc);//条约的最大高度
	/**************跳跃*****************/

	/************自由下落***************/
	bool Freedom = false;
	/************自由下落***************/



public:
		bool IsDrop(D3DXVECTOR3 pos,CModelCopy*it, D3DXVECTOR3 &start);
		bool IsCanMove(D3DXVECTOR3 pos, D3DXVECTOR3 dir, CModelCopy*);
		void SetCamera(CModelCopy*);
		bool HitTestAABBCModelCopy(D3DXVECTOR3 pos,D3DXVECTOR3 dir, D3DXVECTOR3 &start);
		bool HitTestAABBCModelCopy1(D3DXVECTOR3 pos, D3DXVECTOR3 &start);
		bool HitTestAABBCharacter();	
};

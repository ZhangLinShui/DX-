//////////////////////////////////////////////////////////////////////////
//Name:InputSystem.h
//���е�����ҵĲ�������װ�����������
//�Լ����к�������йصĶ���Ĳ���
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "SceneManager.h"
#include "GUIManager.h"
#include "GraphSystem.h"

//�����Ϣ�Ľṹ��
struct tagMouseKey
{
	long lX, lY;
	long lKey;
};

//�����,����Ϸ���л����Ŀ���
class CInputSystem : public IObserver
{

public:

	//���캯��
	CInputSystem();

	//��������
	~CInputSystem();

	//��ʼ��ϵͳ
	bool Init();

	//����״̬�ӿ�
	void Notify(IObservable* pObservable, IObject* Arg);

	//����״̬�ӿ�
	void Update(IObservable* pObservable, IObject* Arg);

protected:

	//������ϵͳ����Ĺ۲�ֵģʽ������
	CSceneManager* m_pObservableScene;

	//�����Ʋ���

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

	//�����Ϣ����
	queue<tagMouseKey*> m_queueMouseKey;
	//ģ�Ͷ�������
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

	//���������Ϣ
	bool MouseMessageProc();
	void PushMouseKey(long lMouseX, long lMouseY, long lValue);
	

	void PlayerMove();
	void MapMove();
	void InputProc();
	//���̲���
public:

	//�ж��û���������
	bool IsKeyPressed(long);
	bool KeyMessageProc(DWORD keyValue,bool b);
protected:
	//���̻�����
	char m_cKeyBuffer[256];

	//��Ҫ���ƵĶ���
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

	/**************��Ծ*****************/
	bool flag = false;
	bool isDown = false;
	float s = 0;
	float v = 0;
	float acc = 10;//����
	float t = 0;//ʱ��
	float v0_speed = 50;//���ٶ�
	float H = (v0_speed*v0_speed) / (2 * acc);//��Լ�����߶�
	/**************��Ծ*****************/

	/************��������***************/
	bool Freedom = false;
	/************��������***************/



public:
		bool IsDrop(D3DXVECTOR3 pos,CModelCopy*it, D3DXVECTOR3 &start);
		bool IsCanMove(D3DXVECTOR3 pos, D3DXVECTOR3 dir, CModelCopy*);
		void SetCamera(CModelCopy*);
		bool HitTestAABBCModelCopy(D3DXVECTOR3 pos,D3DXVECTOR3 dir, D3DXVECTOR3 &start);
		bool HitTestAABBCModelCopy1(D3DXVECTOR3 pos, D3DXVECTOR3 &start);
		bool HitTestAABBCharacter();	
};

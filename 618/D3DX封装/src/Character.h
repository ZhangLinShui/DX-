#pragma once
#include "RenderObject.h"

#include "MultiAnim.h"
enum enMotionType { MT_STAY, MT_WALK, MT_ATTACK, MT_BEHIT, MT_DIEING, MT_DEAD };
#define MOVE_TRANSITION_TIME 0.25		//ƽ���任ʱ��
class CCharacter:public CRenderObject
{

public:
	CCharacter(void);
	~CCharacter(void);
	BOOL Init(TiXmlElement* element);
	void Draw();
	void Update(float fElapsedTime);
	
	// �л���������
	void ChangeMotionType(enMotionType enType);
	
	// AABB
	D3DXVECTOR3		m_vMax;
	D3DXVECTOR3		m_vMin;

	// ������ײ����ָ�Ϊ��ײ״̬λ��
	D3DXVECTOR3		m_vOldPos;
	enMotionType	m_enMotionType;	// ��������



	friend class CMultiAnim;
private:


	virtual void    UpdateFrames(LPD3DXFRAME pFrame, D3DXMATRIX* pmxBase);
	virtual void    DrawFrames(LPD3DXFRAME pFrame);
	virtual void    DrawMeshFrame(LPD3DXFRAME pFrame);

public:

	DWORD CCharacter::GetPlayTime();

	//CMultiAnim*		GetMultiAnim();
	//void            GetAnimController(LPD3DXANIMATIONCONTROLLER* ppAC);


	void			SetAnimationByName(string name, DWORD dwControlPlayTime = 0, bool bSmooth = true);
	virtual HRESULT AdvanceTime(DOUBLE dTimeDelta, ID3DXAnimationCallbackHandler* pCH, D3DXMATRIX mat);
protected:

	float			m_fMoveSpeed;		// �ƶ��ٶ�
	CMultiAnim* m_pMultiAnim;
	LPD3DXANIMATIONCONTROLLER m_pAC;
	DWORD m_dwCurrentTrack;
	string m_strNowAnimationName;

	/// ��ǰ�����趨���Ŵ���(0Ϊ�ظ�����)
	DWORD					m_dwControlPlayTime;
	/// ��ǰʱ�� 
	float					m_fTimeCurrent;
	/// ��ǰ�������Ŵ���
	DWORD					m_dwPlayTime;
	/// ��ǰ��������ʱ��
	float					m_fFrameTime;
	/// ��ǰ�����ܲ���ʱ��
	double					m_lfTotalFrameTime;
	string					Modedata;

	float					RoteX, RoteY, RoteZ, Roate;
};

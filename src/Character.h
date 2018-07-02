#pragma once
#include "RenderObject.h"

#include "MultiAnim.h"
enum enMotionType { MT_STAY, MT_WALK, MT_ATTACK, MT_BEHIT, MT_DIEING, MT_DEAD };
#define MOVE_TRANSITION_TIME 0.25		//平滑变换时间
class CCharacter:public CRenderObject
{

public:
	CCharacter(void);
	~CCharacter(void);
	BOOL Init(TiXmlElement* element);
	void Draw();
	void Update(float fElapsedTime);
	
	// 切换动作类型
	void ChangeMotionType(enMotionType enType);
	
	// AABB
	D3DXVECTOR3		m_vMax;
	D3DXVECTOR3		m_vMin;

	// 用于碰撞检测后恢复为碰撞状态位置
	D3DXVECTOR3		m_vOldPos;
	enMotionType	m_enMotionType;	// 动作类型



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

	float			m_fMoveSpeed;		// 移动速度
	CMultiAnim* m_pMultiAnim;
	LPD3DXANIMATIONCONTROLLER m_pAC;
	DWORD m_dwCurrentTrack;
	string m_strNowAnimationName;

	/// 当前动作设定播放次数(0为重复播放)
	DWORD					m_dwControlPlayTime;
	/// 当前时间 
	float					m_fTimeCurrent;
	/// 当前动作播放次数
	DWORD					m_dwPlayTime;
	/// 当前动画播放时间
	float					m_fFrameTime;
	/// 当前动画总播放时间
	double					m_lfTotalFrameTime;
	string					Modedata;

	float					RoteX, RoteY, RoteZ, Roate;
};

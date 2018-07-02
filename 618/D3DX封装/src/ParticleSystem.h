/********************************************************************
	created:	2007/03/26
	created:	26:3:2007   9:46
	filename: 	ParticleSystem.h
	author:		������
	
	purpose:	������������������ࡣ��������ۺ������࣬ʹ�����ӳض�̬
				�������Ӷ����������
	changelog:	2007/04/30	����Clone�������Է������ɶ������
*********************************************************************/

#pragma once
#include <vector>
#include <list>
#include <map>
using namespace std;
#include "ParticleEmitter.h"
#include "ParticleAffector.h"
#include "tinyxml\tinyxml.h"
#include "Camera.h"

/** �����࣬����һ������ʵ��
*/
class Particle
{
public:
	/// ���
	float m_fWidth;
	/// �߶�
	float m_fHeight;
	//���ӳߴ��Ƿ��б仯
	bool m_bOwnDimension;
	/// ��ǰ��ɫ��ͨ��ָ������ɫ��
	DWORD m_Color;
	/// λ��
	D3DXVECTOR3		m_vPosition;
	/// �����г��ȵķ��򣬰����ٶȣ�
	D3DXVECTOR3		m_vDirection;
	/// ���ܴ���ʱ��
	float m_fTimeToLive;
	/// �ܹ�����ʱ��
	float m_fTotalTimeToLive;

	/// ��ǰ����ת����
	float m_fRotation;		
	/// ���ȣ���ת���ٶ�
	float m_fRotationSpeed;	

	Particle();
	void SetDimension(float width, float height);
};

/** ����������
*/
enum BillboardType
{
	/// ��Զ���������
	BT_POINT,
	/// �������ӵķ��з����������m_vDirection
	BT_ORIENT_SELF,
	/// ���Ź̶�����m_CommonDirection�����������Ź̶�������ת�����������
	BT_ORIENT_COMMON_DIRECTION,
	/// ��ֱ�̶�����m_CommonDirection������������޹أ� ���û�ָ���ķ���m_CommonUp����
	BT_PERPENDICULAR_COMMON_DIRECTION,
};

/** �������������������ϵ
*/
enum ParticleCoordinateSystem
{
	/// �������ռ�
	PCS_WORLD,
	/// ��Ա��ؿռ�
	PCS_LOCAL
};

/** �������ָ࣬һ�ž�����ͬ������ͬ��Ⱦ״̬������
	@remarks
		��ʹ��ͬһ�����������һ�����ύ��D3D����������޶ȵļ�����Ⱦ״̬
		�л��������ȾЧ�ʡ�
	@par
		ͬһ�����ӿ���ͳһ�����ڴ棬�Լ��ٶ�̬�������������ɵ�Ч����ʧ��
		�ڴ���Ƭ��
	@par
		�������������֪ʶ�㣺����ϵͳ��VertexBuffer��IndexBufferʹ�ã�����
		����֪ʶ���������㣬STL��list��vector������ʹ�á�Alpha Blending��Ӧ�á�
*/
class ParticleGroup
{
public:
	/// ���Ӷ���
	class ParticleVertex
	{
	public:
		D3DXVECTOR3 pos;
		DWORD diffuse;
		float tu, tv;

		enum
		{
			FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1
		};
	};

	typedef std::vector<Particle*> ParticlePool;
	typedef std::list<Particle*> ParticleActiveList;
	typedef std::list<Particle*> ParticleFreeList;
	/** ���ӳ�
		@remarks
			Ԥ�ȷ���m_uiPoolSize�����ӣ���ÿ�δ�������ʱ������Ҫ��̬�����ڴ�
			������new����ֻ��Ҫ�����ӳ���ȡ��һ��û��ʹ�ù�������ָ�롣
	*/
	ParticlePool m_ParticlePool;
	///�����ӳ����ѱ�ʹ�õ����Ӷ���
	ParticleActiveList m_ActiveParticles;
	///�����ӳ���δ��ʹ�õ����Ӷ���
	ParticleFreeList m_FreeParticles;

	///�����ӳش�С��������������ͬʱ���ڵ�������Ŀ
	unsigned int m_uiPoolSize;
	///�����Ķ�����Ŀ�����������Billboard�����ֵΪm_uiPoolSize*4
	unsigned int m_uiMaxNumVertices;
	///������������Ŀ�����������Billboard�����ֵΪm_uiPoolSize*2
	unsigned int m_uiMaxNumIndices;

	typedef std::vector<ParticleEmitter*> ParticleEmitterVector;
	typedef std::vector<ParticleAffector*> ParticleAffectorVector;
	/// ����������
	ParticleEmitterVector m_Emitters;
	/// Ч��������
	ParticleAffectorVector m_Affectors;

	/// Vertex Buffer
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	/// Index Buffer
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	/// ���ӵ�Ĭ�Ͽ��
	float m_fDefaultWidth;
	///�����ӵ�Ĭ�ϸ߶�
	float m_fDefaultHeight;

	/// ������
	string m_TextureName;
	LPDIRECT3DTEXTURE9 m_pTexture;
	/// �����볡���Ļ�Ϸ�ʽ
	SceneBlendType m_SceneBlendType;
	/// ����������
	int m_iSide;
	int m_iNumFrame;
	float m_fTexDelta;
	float m_fTexAnimDuration;
	bool m_bAnimationTexture;
	bool m_bRotationTexture;

	bool m_bEnable;

	/// ���������������ķ�ʽ
	BillboardType m_BillboardType;
	/// ��m_BillboardTypeΪBT_ORIENT_COMMON_DIRECTIONʱ��������Ϊ����ָ��ķ���
	D3DXVECTOR3 m_CommonDirection;
	/// ��m_BillboardTypeΪBT_PERPENDICULAR_COMMON_DIRECTIONʱ����������m_CommonDirection�������ӵ�x, y��
	D3DXVECTOR3 m_CommonUp;

	/// ��������������������ϵ
	ParticleCoordinateSystem m_CoordinateSystem;

	LPDIRECT3DDEVICE9 m_pDevice;
	/// ��ǰ�������ָ��
	CCamera *m_pCamera;
	D3DXVECTOR3 m_vCamDir;
	D3DXVECTOR3 m_vCamRight;
	D3DXVECTOR3 m_vCamUp;
	/// ����屾������ϵ��x�ᣬ����������ϵ�еķ���
	D3DXVECTOR3	m_vBillboardX;
	/// ����屾������ϵ��y�ᣬ����������ϵ�еķ���
	D3DXVECTOR3	m_vBillboardY;
	/// ������ĸ����е�����꣬����ڽ���������ϵԭ���Ƶ������ԭ�������ϵ
	D3DXVECTOR3 m_vLeftOff;
	D3DXVECTOR3 m_vRightOff;
	D3DXVECTOR3 m_vTopOff;
	D3DXVECTOR3 m_vBottomOff;
	float m_fLeft;
	float m_fRight;
	float m_fTop;
	float m_fBottom;
	D3DXVECTOR3 m_vOffset[4];

	/// �Ƿ���2D����
	bool m_b2DParticle;
	/// ��������2D�������Ե���������������ʹ��ƽ��ͶӰ����
	CCamera m_2DCamera;
	D3DXMATRIX matOldView;
	D3DXMATRIX matOldProj;
	/// ������Ϊ2D����ʱ����Ҫ�û����ô˾��������������ŷ�λ
	D3DXMATRIX m_2DTransform;

	ParticleGroup();
	virtual ~ParticleGroup();

	/** �������ӳش�С
		@remarks
			Ϊ�˱���Ƶ��С�ڴ���䣬ʹ�����ӳ�Ԥ�ȷ������Ӷ�����ÿ�δ�������ʱ��
			����Ҫ��̬�����ڴ棨����new����ֻ��Ҫ�����ӳ���ȡ��һ��û��ʹ�ù���
			����ָ�롣
		@par
			�������ӳصĴ�С����VertexBuffer��IndexBuffer������Ӧ�����ؽ��ⴴ��
			D3D��Դ�Ĳ���ѡ��
		@param
			uiPoolSize ���ӳش�С��ͬһʱ�̣��������Ŷ���ͬʱ���ڵ����Ӳ��ᳬ��
			����ֵ��
	*/
	void SetPoolSize( unsigned int uiPoolSize );

	/** �����ӳ���ȡ��һ��δʹ�õ�����ָ�롣
		@returns
			����ɹ����򷵻�һ���Ϸ�������ָ�롣
		@par
			���ʧ�ܣ��򷵻�NULL��
	*/
	Particle *CreateParticle();
	ParticleActiveList::iterator DeleteParticle( ParticleActiveList::iterator &i );
	void ClearParticle();
	UINT GetNumParticles();

	/// ����һ��������
	ParticleEmitter *CreateEmitter( string &name );
	/// ����һ��������
	void AddEmitter( ParticleEmitter *pe );
	/// ����һ��Ч����
	ParticleAffector *CreateAffector( string &name );
	/// ����һ��Ч����
	void AddAffector( ParticleAffector *pa );

	void SetTexAnimDuration( float fDuration );
	/// ����������ɫ�볡����ɫ�Ļ�Ϸ�ʽ
	void SetSceneBlendType( SceneBlendType sbt );

	/// 
	void SetEnable( bool bEnable );
	bool GetEnable() { return m_bEnable; };
	void SetTexture( LPSTR pName );
	void Init( LPDIRECT3DDEVICE9 pDevice );
	///������ʱ������������������ԣ�ͬʱ����VertexBuffer��IndexBuffer
	void Update( float fElapsedTime, CCamera &cam );
	///�����ú��ʵ���Ⱦ״̬����Ⱦ����
	void Render();


	/** Clone�µ�ʵ��
		@remarks
			Ϊ�˱���ÿ�ζ�������Դ������xml�ļ����˴�ѡ��Ԥ�ȼ������е�����xml�ļ���
			��Ϊģ�塣ÿ�δ�������ʱ��ʹ��Clone��������ģ������ʵ����
		@param 
			p ��ҪClone����ʵ��
		@param
			bDeepCopyTexture �Ƿ��������Ĭ��Ϊfalse������ֱ��copy����ָ��
			������������ԣ�trueΪ���¼����������¼�������������ԡ�
	*/
	void Clone( ParticleGroup *p );

	///����ȡ�����ļ�
	bool Load( LPCSTR pName );
	bool Save( LPSTR pName );
protected:
	/**���������ӳش�С����VB��IB����������ǹ����Ļ�����ֵΪm_uiPoolSize*4
	*/
	void _CreateBuffers();

	/** ����ʱ�������ӵ�����
		@remarks
			�������������������ָ���m_ActiveParticlesɾ����ͬʱ���뵽
			m_FreeParticles�
	*/
	void _LiveOrDead( float fElapsedTime );
	/**���������е�Ч�������������ӵ�����
	*/
	void _TriggerAffectors(float fElapsedTime);
	/**���������ӵ�λ��
	*/
	void _ApplyMotion( float fElapsedTime );
	/**���������еķ������������µ�����
	*/
	void _TriggerEmitters( float fElapsedTime );
	/** �������ӵ�x,y������������ϵ�µķ���
		@remarks
			������������������ķ�ʽm_BillboardType��ͬ������m_vBillboardX��
			m_vBillboardY��
	*/
	void _GenBillboardAxis(Particle *p = NULL);
	void _GenVertexOffset(float fWidth, float fHeight);
	/** ���VB��IB
	*/
	void _FillBuffers();

public:
	HRESULT InvalidateDeviceObjects(void);
	HRESULT RestoreDeviceObjects(void);
};

typedef map<string, ParticleGroup*> ParticleGroupMap;
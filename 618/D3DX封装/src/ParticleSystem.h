/********************************************************************
	created:	2007/03/26
	created:	26:3:2007   9:46
	filename: 	ParticleSystem.h
	author:		任晓宇
	
	purpose:	定义粒子类和粒子团类。粒子团类聚合粒子类，使用粒子池动态
				管理粒子对象的生死。
	changelog:	2007/04/30	加入Clone函数，以方便生成多个对象。
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

/** 粒子类，代表一个粒子实体
*/
class Particle
{
public:
	/// 宽度
	float m_fWidth;
	/// 高度
	float m_fHeight;
	//粒子尺寸是否有变化
	bool m_bOwnDimension;
	/// 当前颜色（通常指顶点颜色）
	DWORD m_Color;
	/// 位置
	D3DXVECTOR3		m_vPosition;
	/// 方向（有长度的方向，包含速度）
	D3DXVECTOR3		m_vDirection;
	/// 还能存活的时间
	float m_fTimeToLive;
	/// 总共存活的时间
	float m_fTotalTimeToLive;

	/// 当前的旋转弧度
	float m_fRotation;		
	/// 弧度，旋转的速度
	float m_fRotationSpeed;	

	Particle();
	void SetDimension(float width, float height);
};

/** 公告板的类型
*/
enum BillboardType
{
	/// 永远面向摄像机
	BT_POINT,
	/// 沿着粒子的飞行方向，粒子类的m_vDirection
	BT_ORIENT_SELF,
	/// 沿着固定方向（m_CommonDirection），总是沿着固定方向旋转，面向摄像机
	BT_ORIENT_COMMON_DIRECTION,
	/// 垂直固定方向（m_CommonDirection），与摄像机无关， 由用户指定的方向m_CommonUp决定
	BT_PERPENDICULAR_COMMON_DIRECTION,
};

/** 粒子物理计算的相对坐标系
*/
enum ParticleCoordinateSystem
{
	/// 相对世界空间
	PCS_WORLD,
	/// 相对本地空间
	PCS_LOCAL
};

/** 粒子团类，指一团具有相同纹理、相同渲染状态的粒子
	@remarks
		将使用同一张纹理的粒子一次性提交给D3D，可以最大限度的减少渲染状态
		切换，提高渲染效率。
	@par
		同一团粒子可以统一分配内存，以减少动态分配大量粒子造成的效率损失和
		内存碎片。
	@par
		此类包括了如下知识点：粒子系统，VertexBuffer、IndexBuffer使用，基本
		物理知识，向量运算，STL中list、vector容器的使用、Alpha Blending的应用。
*/
class ParticleGroup
{
public:
	/// 粒子顶点
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
	/** 粒子池
		@remarks
			预先分配m_uiPoolSize个粒子，在每次创建粒子时，不需要动态分配内存
			（调用new），只需要从粒子池中取出一个没有使用过的粒子指针。
	*/
	ParticlePool m_ParticlePool;
	///　粒子池中已被使用的粒子对象
	ParticleActiveList m_ActiveParticles;
	///　粒子池中未被使用的粒子对象
	ParticleFreeList m_FreeParticles;

	///　粒子池大小，此粒子团最大可同时存在的粒子数目
	unsigned int m_uiPoolSize;
	///　最大的顶点数目，如果粒子是Billboard，则此值为m_uiPoolSize*4
	unsigned int m_uiMaxNumVertices;
	///　最大的索引数目，如果粒子是Billboard，则此值为m_uiPoolSize*2
	unsigned int m_uiMaxNumIndices;

	typedef std::vector<ParticleEmitter*> ParticleEmitterVector;
	typedef std::vector<ParticleAffector*> ParticleAffectorVector;
	/// 发射器数组
	ParticleEmitterVector m_Emitters;
	/// 效果器数组
	ParticleAffectorVector m_Affectors;

	/// Vertex Buffer
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	/// Index Buffer
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	/// 粒子的默认宽度
	float m_fDefaultWidth;
	///　粒子的默认高度
	float m_fDefaultHeight;

	/// 纹理名
	string m_TextureName;
	LPDIRECT3DTEXTURE9 m_pTexture;
	/// 粒子与场景的混合方式
	SceneBlendType m_SceneBlendType;
	/// 纹理动画参数
	int m_iSide;
	int m_iNumFrame;
	float m_fTexDelta;
	float m_fTexAnimDuration;
	bool m_bAnimationTexture;
	bool m_bRotationTexture;

	bool m_bEnable;

	/// 公告板面向摄像机的方式
	BillboardType m_BillboardType;
	/// 当m_BillboardType为BT_ORIENT_COMMON_DIRECTION时，此向量为粒子指向的方向。
	D3DXVECTOR3 m_CommonDirection;
	/// 当m_BillboardType为BT_PERPENDICULAR_COMMON_DIRECTION时，此向量和m_CommonDirection决定粒子的x, y轴
	D3DXVECTOR3 m_CommonUp;

	/// 进行粒子运算的相对坐标系
	ParticleCoordinateSystem m_CoordinateSystem;

	LPDIRECT3DDEVICE9 m_pDevice;
	/// 当前摄像机的指针
	CCamera *m_pCamera;
	D3DXVECTOR3 m_vCamDir;
	D3DXVECTOR3 m_vCamRight;
	D3DXVECTOR3 m_vCamUp;
	/// 公告板本地坐标系的x轴，在世界坐标系中的方向
	D3DXVECTOR3	m_vBillboardX;
	/// 公告板本地坐标系的y轴，在世界坐标系中的方向
	D3DXVECTOR3	m_vBillboardY;
	/// 公告板四个边中点的坐标，相对于将世界坐标系原点移到公告板原点的坐标系
	D3DXVECTOR3 m_vLeftOff;
	D3DXVECTOR3 m_vRightOff;
	D3DXVECTOR3 m_vTopOff;
	D3DXVECTOR3 m_vBottomOff;
	float m_fLeft;
	float m_fRight;
	float m_fTop;
	float m_fBottom;
	D3DXVECTOR3 m_vOffset[4];

	/// 是否是2D粒子
	bool m_b2DParticle;
	/// 用来计算2D粒子属性的摄像机，上摄像机使用平等投影矩阵
	CCamera m_2DCamera;
	D3DXMATRIX matOldView;
	D3DXMATRIX matOldProj;
	/// 当粒子为2D粒子时，需要用户设置此矩阵来控制粒子团方位
	D3DXMATRIX m_2DTransform;

	ParticleGroup();
	virtual ~ParticleGroup();

	/** 设置粒子池大小
		@remarks
			为了避免频繁小内存分配，使用粒子池预先分配粒子对象。在每次创建粒子时，
			不需要动态分配内存（调用new），只需要从粒子池中取出一个没有使用过的
			粒子指针。
		@par
			根据粒子池的大小创建VertexBuffer、IndexBuffer，这里应该着重讲解创建
			D3D资源的参数选择。
		@param
			uiPoolSize 粒子池大小。同一时刻，该粒子团对象同时存在的粒子不会超过
			此数值。
	*/
	void SetPoolSize( unsigned int uiPoolSize );

	/** 从粒子池中取出一个未使用的粒子指针。
		@returns
			如果成功，则返回一个合法的粒子指针。
		@par
			如果失败，则返回NULL。
	*/
	Particle *CreateParticle();
	ParticleActiveList::iterator DeleteParticle( ParticleActiveList::iterator &i );
	void ClearParticle();
	UINT GetNumParticles();

	/// 创建一个发射器
	ParticleEmitter *CreateEmitter( string &name );
	/// 增加一个发射器
	void AddEmitter( ParticleEmitter *pe );
	/// 创建一个效果器
	ParticleAffector *CreateAffector( string &name );
	/// 增加一个效果器
	void AddAffector( ParticleAffector *pa );

	void SetTexAnimDuration( float fDuration );
	/// 设置粒子颜色与场景颜色的混合方式
	void SetSceneBlendType( SceneBlendType sbt );

	/// 
	void SetEnable( bool bEnable );
	bool GetEnable() { return m_bEnable; };
	void SetTexture( LPSTR pName );
	void Init( LPDIRECT3DDEVICE9 pDevice );
	///　根据时间差、摄像机计算粒子属性，同时更新VertexBuffer、IndexBuffer
	void Update( float fElapsedTime, CCamera &cam );
	///　设置合适的渲染状态，渲染粒子
	void Render();


	/** Clone新的实例
		@remarks
			为了避免每次都加载资源，解析xml文件。此处选择预先加载所有的粒子xml文件，
			做为模板。每次创建粒子时会使用Clone函数根据模板做出实例。
		@param 
			p 需要Clone出的实例
		@param
			bDeepCopyTexture 是否深拷贝纹理，默认为false，代表直接copy纹理指针
			和纹理相关属性，true为重新加载纹理并重新计算纹理相关属性。
	*/
	void Clone( ParticleGroup *p );

	///　读取粒子文件
	bool Load( LPCSTR pName );
	bool Save( LPSTR pName );
protected:
	/**　根据粒子池大小创建VB、IB，如果粒子是公告板的话，此值为m_uiPoolSize*4
	*/
	void _CreateBuffers();

	/** 根据时间差处理粒子的生死
		@remarks
			如果粒子死亡，则将粒子指针从m_ActiveParticles删除，同时加入到
			m_FreeParticles里。
	*/
	void _LiveOrDead( float fElapsedTime );
	/**　触发所有的效果器，更新粒子的属性
	*/
	void _TriggerAffectors(float fElapsedTime);
	/**　计算粒子的位置
	*/
	void _ApplyMotion( float fElapsedTime );
	/**　触发所有的发射器，创建新的粒子
	*/
	void _TriggerEmitters( float fElapsedTime );
	/** 计算粒子的x,y轴在世界坐标系下的方向
		@remarks
			根据粒子面向摄像机的方式m_BillboardType不同，计算m_vBillboardX、
			m_vBillboardY。
	*/
	void _GenBillboardAxis(Particle *p = NULL);
	void _GenVertexOffset(float fWidth, float fHeight);
	/** 填充VB、IB
	*/
	void _FillBuffers();

public:
	HRESULT InvalidateDeviceObjects(void);
	HRESULT RestoreDeviceObjects(void);
};

typedef map<string, ParticleGroup*> ParticleGroupMap;
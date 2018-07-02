/********************************************************************
created:	2007/03/26
created:	26:3:2007   9:46
filename: 	ParticleEmitter.h
author:		任晓宇

purpose:	定义粒子发射器类。
changelog:	2007/04/30	加入Clone函数，以方便生成多个对象。
*********************************************************************/
#pragma once

class Particle;
class ParticleGroup;
class TiXmlElement;

/** 粒子发射器，决定粒子的初始属性
	@remarks
		发射器的抽象类，定义了大部分发射器的共有属性和抽象接口。不同的
		发射器类提供不同的实现。
	@par
		由于发射器种类很多，这里最好使用工厂模式来设计。此实现并没有使用
		工厂模式。教师可以在讲解发射器时介绍一下设计模式的概念。
*/
class ParticleEmitter
{
public:
	string m_Type;
	/// 发射率。每秒钟发射粒子的个数，允许为小数
	float m_fEmissionRate;
	/// 上一帧计算粒子数目的小数部分，当m_fEmissionRate为小数时，此参数可以避免发射不出粒子的情况。
	float m_fRemainder;
	/// 粒子团在本地空间中的位置
	D3DXVECTOR3 m_vPosition;
	/// 粒子团在本地空间中的方向
	D3DXVECTOR3 m_vDirection;
	/// Up向量，用来辅助产生随机向量
	D3DXVECTOR3 m_vUp;
	/** 发射角
		@remarks
			已知发射器的位置、方向，和此角度，可以得到一个以发射器方向为中心轴
			的锥体。粒子的发射方向等于该锥体内穿过发射器位置的一条射线。
	*/
	float m_fAngle;
	/// “最小生存期”。粒子生存期由“最小生存期”和“最大生存期”之间的随机值决定。不允许为负数。
	float m_fMinTTL;
	/// “最大生存期”。粒子生存期由“最小生存期”和“最大生存期”之间的随机值决定。不允许为负数。
	float m_fMaxTTL;
	/// “最小速度”。粒子的速率由“最小速度”和“最大速度”之间的随机值决定。
	float m_fMinSpeed;
	/// “最大速度”。粒子的速率由“最小速度”和“最大速度”之间的随机值决定。
	float m_fMaxSpeed;
	/// “起始颜色”，粒子的顶点色等于“起始颜色”到“结束颜色”间的随机值。
	DWORD m_dwStartColor;
	/// “结束颜色”，粒子的顶点色等于“起始颜色”到“结束颜色”间的随机值。
	DWORD m_dwEndColor;

	/// 由发射到停止发射之间的时间
	float				m_fDurationMin;		
	float				m_fDurationMax;		
	float				m_fDurationRemain;	
	/// 由停止发射到再次发射之间的时间
	float				m_fRepeatDelayMin;	
	float				m_fRepeatDelayMax;
	float				m_fRepeatDelayRemain;

	bool m_bEnable;

	ParticleGroup *m_pParent;

	ParticleEmitter(ParticleGroup *pParent);
	virtual ~ParticleEmitter();

	
	/** 设置发射器的方向
		@param
			dir 发射器方向
	*/
	void SetDirection( D3DXVECTOR3 &dir );

	void SetDuration(float min, float max);
	void SetRepeatDelay(float min, float max);

	void SetEnable( bool bEnable );

	/** 初始化提供粒子对象的属性
		@param
			p 需要初始化的粒子对象指针
	*/
	virtual void InitParticle( Particle *p );
	/** 根据发射率和时间差返回发射粒子的数目
	*/
	virtual unsigned int GenEmissionCount( float fElapsedTime );
	/** 产生粒子生存生存期
	*/
	virtual float _GenEmissionTTL();

	/** 在发射器指定的范围内产生粒子位置
		@param
			destVector 输出参数，保存粒子位置
	*/
	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
	
	/** 产生粒子方向（归一化的）
		@param
			destVector 输出参数，保存粒子方向
	*/
	virtual void _GenEmissionDirection( D3DXVECTOR3 &destVector );

	/** 产生粒子速度
		@param
			destVector 输出参数，乘过粒子速度常量
	*/
	virtual void _GenEmissionSpeed( D3DXVECTOR3 &destVector );

	/** 产生粒子顶点色
		@param
			color 输出参数，保存粒子顶点色
	*/
	virtual void _GenEmissionColor( DWORD &color );

	void _InitDurationRepeat(void);

	virtual bool Load( TiXmlElement *pElemEmitter );
	virtual bool Save( TiXmlElement *pElemEmitter );

	virtual void Clone( ParticleEmitter *pe );
};

/** 从某一点发射粒子的发射器
*/
class PointEmitter : public ParticleEmitter
{
public:
	PointEmitter(ParticleGroup *pParent);
	virtual ~PointEmitter();

};

/** 范围发射器的抽象类，在某一区域内发射粒子
*/
class AreaEmitter : public ParticleEmitter
{
public:
	AreaEmitter(ParticleGroup *pParent);
	virtual ~AreaEmitter();

	/// x,y,z三个方向的长度
	D3DXVECTOR3 m_vSize;
	D3DXVECTOR3 m_vXRange;
	D3DXVECTOR3 m_vYRange;
	D3DXVECTOR3 m_vZRange;

	void SetSize( float x, float y, float z );
	virtual bool Load( TiXmlElement *pElemEmitter );
	virtual bool Save( TiXmlElement *pElemEmitter );

	virtual void Clone( ParticleEmitter *pe );
};

/** 盒子发射器，可以实现粒子在　立方体、长方体、面、线　上发射的效果。
*/
class BoxEmitter : public AreaEmitter
{
public:
	BoxEmitter(ParticleGroup *pParent);
	virtual ~BoxEmitter();

	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
};

/** 椭圆发射器
*/
class EllipsoidEmitter : public AreaEmitter
{
public:
	EllipsoidEmitter(ParticleGroup *pParent);
	virtual ~EllipsoidEmitter();
	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
};

/** 环发射器
*/
class RingEmitter : public AreaEmitter
{
public:
	RingEmitter(ParticleGroup *pParent);
	virtual ~RingEmitter();
	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
	void SetInnerSize( float x, float y );
	virtual void Clone( ParticleEmitter *pe );
	virtual bool Load( TiXmlElement *pElemEmitter );
	virtual bool Save( TiXmlElement *pElemEmitter );

	/// 内环x方向的长度
	float m_fInnerX;
	/// 内环y方向的长度
	float m_fInnerY;
};

/** 空心椭圆发射器
*/
class HollowEllipsoidEmitter : public AreaEmitter
{
public:
	HollowEllipsoidEmitter(ParticleGroup *pParent);
	virtual ~HollowEllipsoidEmitter();
	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
	virtual void InitParticle( Particle *p );
	void SetInnerSize( float x, float y, float z );
	virtual void Clone( ParticleEmitter *pe );

	/// 内环x,y,z三个方向的长度
	D3DXVECTOR3 m_vInnerSize;
};


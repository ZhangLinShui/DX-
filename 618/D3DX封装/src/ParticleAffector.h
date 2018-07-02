/********************************************************************
created:	2007/03/26
created:	26:3:2007   9:46
filename: 	ParticleAffector.h
author:		任晓宇

purpose:	定义粒子效果器类。
changelog:	2007/04/30	加入Clone函数，以方便生成多个对象。
			2007/05/09	为ScaleAffector加入缩放大小限制，以避免fElapsedTime过大
						导致粒子大小突变，降低填充率和帧率。
*********************************************************************/
#pragma once

class ParticleGroup;

/** 粒子效果器，动态改变粒子的属性
	@remarks
		效果器的纯虚基类。和发射器不同，效果器没有共同的属性，此类定义了大部分效果器
		需要实现的抽象接口。不同的效果器类提供不同的属性和实现。
	@par
		由于效果器种类很多，这里最好使用工厂模式来设计。此实现并没有使用
		工厂模式。教师可以在讲解发射器时介绍一下设计模式的概念。
*/
class ParticleAffector
{
public:
	ParticleAffector(ParticleGroup *pParent);
	virtual ~ParticleAffector();
	/** 新粒子发射时调用此函数初始化粒子属性。
	*/
	virtual void InitParticle( Particle *p );
	/** 每帧调用此函数影响粒子属性。
	*/
	virtual void AffectParticle(float fElapsedTime) = 0;
	/** 读取粒子文件初始化此affector
 	*/
	virtual bool Load( TiXmlElement *pElemAffector )=0;
	/** 向文件中存储粒子信息
	*/
	virtual bool Save( TiXmlElement *pElemAffector );

	virtual HRESULT InvalidateDeviceObjects() { return S_OK; }
	virtual HRESULT RestoreDeviceObjects() { return S_OK; }

	virtual void Clone( ParticleAffector *pe ) = 0;

	ParticleGroup *m_pParent;
	string m_Type;
};

/** 线性外力效果器
	@remarks
		动态改变粒子的m_vDirection属性，可以实现各种外力效果。比如重力、风力。
*/
class LinearForceAffector : public ParticleAffector
{
public:
	LinearForceAffector(ParticleGroup *pParent);
	virtual ~LinearForceAffector();
	virtual void AffectParticle(float fElapsedTime);
	virtual bool Load( TiXmlElement *pElemAffector );
	virtual bool Save( TiXmlElement *pElemAffector );
	virtual void Clone( ParticleAffector *pe );

	D3DXVECTOR3 m_vForceVector;
};

/** 颜色衰减效果器
	@remarks
		动态改变粒子的顶点色，可以实现渐隐效果。
*/
class ColorFadeAffector : public ParticleAffector
{
public:
	ColorFadeAffector(ParticleGroup *pParent);
	virtual ~ColorFadeAffector();
	virtual void AffectParticle(float fElapsedTime);
	virtual bool Load( TiXmlElement *pElemAffector );
	virtual bool Save( TiXmlElement *pElemAffector );
	virtual void Clone( ParticleAffector *pe );

	int m_iR;
	int m_iG;
	int m_iB;
};

/** 颜色图效果器
	@remarks
		使用一张贴图指定粒子在生存期间的颜色变化，比颜色衰减效果器更容易控制
		复杂的颜色变化。
*/
class ColorImageAffector : public ParticleAffector
{
public:
	ColorImageAffector(	ParticleGroup *pParent, LPDIRECT3DDEVICE9 pDevice );
	virtual ~ColorImageAffector();
	virtual void InitParticle( Particle *p );
	virtual void AffectParticle(float fElapsedTime);
	void SetImageName( LPSTR pName );

	virtual bool Load( TiXmlElement *pElemAffector );
	virtual bool Save( TiXmlElement *pElemAffector );
	virtual void Clone( ParticleAffector *pe );

	string  m_strImageName;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DDEVICE9 m_pDevice;
	BYTE *m_pColorBuffer;
	UINT m_uiWidth;
	UINT m_uiPitch;
};

/** 旋转效果器
	@remarks
		动态改变每个粒子的纹理坐标，实现旋转效果
*/
class RotationAffector : public ParticleAffector
{
public:
	RotationAffector( ParticleGroup *pParent );
	virtual ~RotationAffector();

	virtual void InitParticle( Particle *p );
	virtual void AffectParticle(float fElapsedTime);

	virtual bool Load( TiXmlElement *pElemAffector );
	virtual bool Save( TiXmlElement *pElemAffector );
	virtual void Clone( ParticleAffector *pe );

public:
	float m_fRotationSpeedRangeStart;
	float m_fRotationSpeedRangeEnd;
	float m_fRotationRangeStart;
	float m_fRotationRangeEnd;
};



/** 缩放效果器
	@remarks
		动态改变粒子大小，默认情况下，一个ParticleGroup内所有粒子都是相同大小的，
		这样粒子大小只需计算一次。如果每个粒子大小不同，则需在LogicFrame中计算每个
		粒子的大小。
*/
class ScaleAffector : public ParticleAffector
{
public:
	ScaleAffector( ParticleGroup *pParent );
	virtual ~ScaleAffector();
	virtual void InitParticle( Particle *p );
	virtual void AffectParticle(float fElapsedTime);

	virtual bool Load( TiXmlElement *pElemAffector );
	virtual bool Save( TiXmlElement *pElemAffector );
	virtual void Clone( ParticleAffector *pe );

public:
	float m_fScaleAdj;
	float m_fMaxSize;
};


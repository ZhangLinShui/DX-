/********************************************************************
created:	2007/03/26
created:	26:3:2007   9:46
filename: 	ParticleEmitter.h
author:		������

purpose:	�������ӷ������ࡣ
changelog:	2007/04/30	����Clone�������Է������ɶ������
*********************************************************************/
#pragma once

class Particle;
class ParticleGroup;
class TiXmlElement;

/** ���ӷ��������������ӵĳ�ʼ����
	@remarks
		�������ĳ����࣬�����˴󲿷ַ������Ĺ������Ժͳ���ӿڡ���ͬ��
		���������ṩ��ͬ��ʵ�֡�
	@par
		���ڷ���������ܶ࣬�������ʹ�ù���ģʽ����ơ���ʵ�ֲ�û��ʹ��
		����ģʽ����ʦ�����ڽ��ⷢ����ʱ����һ�����ģʽ�ĸ��
*/
class ParticleEmitter
{
public:
	string m_Type;
	/// �����ʡ�ÿ���ӷ������ӵĸ���������ΪС��
	float m_fEmissionRate;
	/// ��һ֡����������Ŀ��С�����֣���m_fEmissionRateΪС��ʱ���˲������Ա��ⷢ�䲻�����ӵ������
	float m_fRemainder;
	/// �������ڱ��ؿռ��е�λ��
	D3DXVECTOR3 m_vPosition;
	/// �������ڱ��ؿռ��еķ���
	D3DXVECTOR3 m_vDirection;
	/// Up�������������������������
	D3DXVECTOR3 m_vUp;
	/** �����
		@remarks
			��֪��������λ�á����򣬺ʹ˽Ƕȣ����Եõ�һ���Է���������Ϊ������
			��׶�塣���ӵķ��䷽����ڸ�׶���ڴ���������λ�õ�һ�����ߡ�
	*/
	float m_fAngle;
	/// ����С�����ڡ��������������ɡ���С�����ڡ��͡���������ڡ�֮������ֵ������������Ϊ������
	float m_fMinTTL;
	/// ����������ڡ��������������ɡ���С�����ڡ��͡���������ڡ�֮������ֵ������������Ϊ������
	float m_fMaxTTL;
	/// ����С�ٶȡ������ӵ������ɡ���С�ٶȡ��͡�����ٶȡ�֮������ֵ������
	float m_fMinSpeed;
	/// ������ٶȡ������ӵ������ɡ���С�ٶȡ��͡�����ٶȡ�֮������ֵ������
	float m_fMaxSpeed;
	/// ����ʼ��ɫ�������ӵĶ���ɫ���ڡ���ʼ��ɫ������������ɫ��������ֵ��
	DWORD m_dwStartColor;
	/// ��������ɫ�������ӵĶ���ɫ���ڡ���ʼ��ɫ������������ɫ��������ֵ��
	DWORD m_dwEndColor;

	/// �ɷ��䵽ֹͣ����֮���ʱ��
	float				m_fDurationMin;		
	float				m_fDurationMax;		
	float				m_fDurationRemain;	
	/// ��ֹͣ���䵽�ٴη���֮���ʱ��
	float				m_fRepeatDelayMin;	
	float				m_fRepeatDelayMax;
	float				m_fRepeatDelayRemain;

	bool m_bEnable;

	ParticleGroup *m_pParent;

	ParticleEmitter(ParticleGroup *pParent);
	virtual ~ParticleEmitter();

	
	/** ���÷������ķ���
		@param
			dir ����������
	*/
	void SetDirection( D3DXVECTOR3 &dir );

	void SetDuration(float min, float max);
	void SetRepeatDelay(float min, float max);

	void SetEnable( bool bEnable );

	/** ��ʼ���ṩ���Ӷ��������
		@param
			p ��Ҫ��ʼ�������Ӷ���ָ��
	*/
	virtual void InitParticle( Particle *p );
	/** ���ݷ����ʺ�ʱ���ط������ӵ���Ŀ
	*/
	virtual unsigned int GenEmissionCount( float fElapsedTime );
	/** ������������������
	*/
	virtual float _GenEmissionTTL();

	/** �ڷ�����ָ���ķ�Χ�ڲ�������λ��
		@param
			destVector �����������������λ��
	*/
	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
	
	/** �������ӷ��򣨹�һ���ģ�
		@param
			destVector ����������������ӷ���
	*/
	virtual void _GenEmissionDirection( D3DXVECTOR3 &destVector );

	/** ���������ٶ�
		@param
			destVector ����������˹������ٶȳ���
	*/
	virtual void _GenEmissionSpeed( D3DXVECTOR3 &destVector );

	/** �������Ӷ���ɫ
		@param
			color ����������������Ӷ���ɫ
	*/
	virtual void _GenEmissionColor( DWORD &color );

	void _InitDurationRepeat(void);

	virtual bool Load( TiXmlElement *pElemEmitter );
	virtual bool Save( TiXmlElement *pElemEmitter );

	virtual void Clone( ParticleEmitter *pe );
};

/** ��ĳһ�㷢�����ӵķ�����
*/
class PointEmitter : public ParticleEmitter
{
public:
	PointEmitter(ParticleGroup *pParent);
	virtual ~PointEmitter();

};

/** ��Χ�������ĳ����࣬��ĳһ�����ڷ�������
*/
class AreaEmitter : public ParticleEmitter
{
public:
	AreaEmitter(ParticleGroup *pParent);
	virtual ~AreaEmitter();

	/// x,y,z��������ĳ���
	D3DXVECTOR3 m_vSize;
	D3DXVECTOR3 m_vXRange;
	D3DXVECTOR3 m_vYRange;
	D3DXVECTOR3 m_vZRange;

	void SetSize( float x, float y, float z );
	virtual bool Load( TiXmlElement *pElemEmitter );
	virtual bool Save( TiXmlElement *pElemEmitter );

	virtual void Clone( ParticleEmitter *pe );
};

/** ���ӷ�����������ʵ�������ڡ������塢�����塢�桢�ߡ��Ϸ����Ч����
*/
class BoxEmitter : public AreaEmitter
{
public:
	BoxEmitter(ParticleGroup *pParent);
	virtual ~BoxEmitter();

	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
};

/** ��Բ������
*/
class EllipsoidEmitter : public AreaEmitter
{
public:
	EllipsoidEmitter(ParticleGroup *pParent);
	virtual ~EllipsoidEmitter();
	virtual void _GenEmissionPosition( D3DXVECTOR3 &destVector );
};

/** ��������
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

	/// �ڻ�x����ĳ���
	float m_fInnerX;
	/// �ڻ�y����ĳ���
	float m_fInnerY;
};

/** ������Բ������
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

	/// �ڻ�x,y,z��������ĳ���
	D3DXVECTOR3 m_vInnerSize;
};


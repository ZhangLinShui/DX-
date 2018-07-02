#include "stdafx.h"
#include "ParticleEmitter.h"

#define new VNEW


ParticleEmitter::ParticleEmitter(ParticleGroup *pParent) :
m_pParent(pParent),
m_Type(""),
m_fEmissionRate(10.f),
m_fRemainder(0.f),
m_vPosition(0.f, 0.f, 0.f),
m_vDirection(0.f, 1.f, 0.f),
m_fAngle(0.f),
m_fMinTTL(0.f),
m_fMaxTTL(0.f),
m_fMinSpeed(0.f),
m_fMaxSpeed(0.f),
m_dwStartColor(0xffffffff),
m_dwEndColor(0xffffffff),
m_bEnable(true),
m_fDurationMin(0.f),
m_fDurationMax(0.f),		
m_fDurationRemain(0.f),
m_fRepeatDelayMin(0.f),
m_fRepeatDelayMax(0.f),
m_fRepeatDelayRemain(0.f)
{
}
ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::SetDirection( D3DXVECTOR3 &dir )
{
	if( m_vDirection != dir )
	{
		m_vDirection = dir;
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		Vec3Perpendicular( m_vUp, m_vDirection );
		D3DXVec3Normalize(&m_vUp, &m_vUp);
	}
}
void ParticleEmitter::SetDuration(float min, float max)
{
	m_fDurationMin = min;
	m_fDurationMax = max;
	_InitDurationRepeat();
}
void ParticleEmitter::SetRepeatDelay(float min, float max)
{
	m_fRepeatDelayMin = min;
	m_fRepeatDelayMax = max;
	_InitDurationRepeat();
}
void ParticleEmitter::SetEnable( bool bEnable )
{
	m_bEnable = bEnable;
	_InitDurationRepeat();
}

void ParticleEmitter::InitParticle( Particle *p )
{
	assert(p);

	_GenEmissionPosition( p->m_vPosition );
	_GenEmissionDirection( p->m_vDirection );
	_GenEmissionSpeed( p->m_vDirection );
	_GenEmissionColor( p->m_Color );
	p->m_fTotalTimeToLive = p->m_fTimeToLive = _GenEmissionTTL();
}

unsigned int ParticleEmitter::GenEmissionCount( float fElapsedTime )
{
	unsigned int uiRequested = 0;
	if( m_bEnable )
	{
		m_fRemainder += m_fEmissionRate * fElapsedTime;
		uiRequested = static_cast<unsigned int>(m_fRemainder);
		m_fRemainder -= uiRequested;


		// Check duration
		if (m_fDurationMax)
		{
			m_fDurationRemain -= fElapsedTime;
			if (m_fDurationRemain <= 0) 
			{
				// Disable, duration is out (takes effect next time)
				SetEnable(false);
			}
		}
		return uiRequested;
	}
	else
	{
		// Check repeat
		if (m_fRepeatDelayMax)
		{
			m_fRepeatDelayRemain -= fElapsedTime;
			if (m_fRepeatDelayRemain <= 0)
			{
				// Enable, repeat delay is out (takes effect next time)
				SetEnable(true);
			}
		}
		return 0;
	}
}

float ParticleEmitter::_GenEmissionTTL()
{
	if( m_fMinTTL == m_fMaxTTL )
	{
		return m_fMinTTL;
	}
	else
	{
		return m_fMinTTL + ( m_fMaxTTL - m_fMinTTL ) * UnitRandom();
	}
}

void ParticleEmitter::_GenEmissionPosition( D3DXVECTOR3 &destVector )
{
	destVector = m_vPosition;
}
void ParticleEmitter::_GenEmissionDirection( D3DXVECTOR3 &destVector )
{
	if( m_fAngle == 0.f )
	{
		destVector = m_vDirection;
	}
	else
	{
		float rand=UnitRandom();
		float fAngle = m_fAngle * rand;
		RandomDeviant( destVector, m_vDirection, fAngle );
	}
}
void ParticleEmitter::_GenEmissionSpeed( D3DXVECTOR3 &destVector )
{
	float fSpeedScalar = 0;
	if( m_fMinSpeed == m_fMaxSpeed )
	{
		fSpeedScalar = m_fMinSpeed;
	}
	else
	{
		fSpeedScalar = m_fMinSpeed + ( m_fMaxSpeed - m_fMinSpeed ) * UnitRandom();
	}
	destVector *= fSpeedScalar;
}
void ParticleEmitter::_GenEmissionColor( DWORD &color )
{
	if( m_dwStartColor == m_dwEndColor )
	{
		color = m_dwStartColor;
	}
	else
	{
		int fR, fG, fB, fA, fER, fEG, fEB, fEA;
		fA = COLOR_GETAVALUE( m_dwStartColor );
		fR = COLOR_GETRVALUE( m_dwStartColor );
		fG = COLOR_GETGVALUE( m_dwStartColor );
		fB = COLOR_GETBVALUE( m_dwStartColor );

		fEA = COLOR_GETAVALUE( m_dwEndColor );
		fER = COLOR_GETRVALUE( m_dwEndColor );
		fEG = COLOR_GETGVALUE( m_dwEndColor );
		fEB = COLOR_GETBVALUE( m_dwEndColor );

		fA = fA + static_cast<int>(( fEA - fA ) * UnitRandom());
		fR = fR + static_cast<int>(( fER - fR ) * UnitRandom());
		fG = fG + static_cast<int>(( fEG - fG ) * UnitRandom());
		fB = fB + static_cast<int>(( fEB - fB ) * UnitRandom());

		color = D3DCOLOR_ARGB( fA, fR, fG, fB );
	}
}

void ParticleEmitter::_InitDurationRepeat(void)
{
	if (m_bEnable)
	{
		if (m_fDurationMin == m_fDurationMax)
		{
			m_fDurationRemain = m_fDurationMin;
		}
		else
		{
			m_fDurationRemain = RangeRandom(m_fDurationMin, m_fDurationMax);
		}
	}
	else
	{
		// Reset repeat
		if (m_fRepeatDelayMin == m_fRepeatDelayMax)
		{
			m_fRepeatDelayRemain = m_fRepeatDelayMin;
		}
		else
		{
			m_fRepeatDelayRemain = RangeRandom(m_fRepeatDelayMax, m_fRepeatDelayMin);
		}

	}
}

bool ParticleEmitter::Load( TiXmlElement *pElemEmitter )
{
	TiXmlElement *pElem = NULL;
	string name;

	pElem = pElemEmitter->FirstChildElement( "角度" );
	name = pElem->GetText();
	m_fAngle = static_cast<float>(atof( name.c_str() ));

	pElem = pElemEmitter->FirstChildElement( "发射率" );
	name = pElem->GetText();
	m_fEmissionRate = static_cast<float>(atof( name.c_str() ));

	pElem = pElemEmitter->FirstChildElement( "最少生存期" );
	name = pElem->GetText();
	m_fMinTTL = static_cast<float>(atof( name.c_str() ));

	pElem = pElemEmitter->FirstChildElement( "最大生存期" );
	name = pElem->GetText();
	m_fMaxTTL = static_cast<float>(atof( name.c_str() ));

	pElem = pElemEmitter->FirstChildElement( "最小速度" );
	name = pElem->GetText();
	m_fMinSpeed = static_cast<float>(atof( name.c_str() ));

	pElem = pElemEmitter->FirstChildElement( "最大速度" );
	name = pElem->GetText();
	m_fMaxSpeed = static_cast<float>(atof( name.c_str() ));

	float a, r, g, b;
	pElem = pElemEmitter->FirstChildElement( "起始颜色" );
	r = static_cast<float>(atof( pElem->Attribute( "r" ) ));
	g = static_cast<float>(atof( pElem->Attribute( "g" ) ));
	b = static_cast<float>(atof( pElem->Attribute( "b" ) ));
	a = static_cast<float>(atof( pElem->Attribute( "a" ) ));
	m_dwStartColor = D3DCOLOR_COLORVALUE( r, g, b, a ); 

	pElem = pElemEmitter->FirstChildElement( "结束颜色" );
	r = static_cast<float>(atof( pElem->Attribute( "r" ) ));
	g = static_cast<float>(atof( pElem->Attribute( "g" ) ));
	b = static_cast<float>(atof( pElem->Attribute( "b" ) ));
	a = static_cast<float>(atof( pElem->Attribute( "a" ) ));
	m_dwEndColor = D3DCOLOR_COLORVALUE( r, g, b, a ); 


	float x, y, z;
	pElem = pElemEmitter->FirstChildElement( "方向" );
	x = static_cast<float>(atof( pElem->Attribute( "x" ) ));
	y = static_cast<float>(atof( pElem->Attribute( "y" ) ));
	z = static_cast<float>(atof( pElem->Attribute( "z" ) ));
	SetDirection( D3DXVECTOR3(x, y, z) );

	pElem = pElemEmitter->FirstChildElement( "位置" );
	x = static_cast<float>(atof( pElem->Attribute( "x" ) ));
	y = static_cast<float>(atof( pElem->Attribute( "y" ) ));
	z = static_cast<float>(atof( pElem->Attribute( "z" ) ));
	m_vPosition = D3DXVECTOR3(x, y, z);

	pElem = pElemEmitter->FirstChildElement( "持续发射最小时间" );
	name = pElem->GetText();
	m_fDurationMin = static_cast<float>(atof( name.c_str() ));

	pElem = pElemEmitter->FirstChildElement( "持续发射最大时间" );
	name = pElem->GetText();
	m_fDurationMax = static_cast<float>(atof( name.c_str() ));
	SetDuration( m_fDurationMin, m_fDurationMax );
	
	pElem = pElemEmitter->FirstChildElement( "反复发射间隔最小时间" );
	name = pElem->GetText();
	m_fRepeatDelayMin = static_cast<float>(atof( name.c_str() ));

	pElem = pElemEmitter->FirstChildElement( "反复发射间隔最大时间" );
	name = pElem->GetText();
	m_fRepeatDelayMax = static_cast<float>(atof( name.c_str() ));
	SetRepeatDelay( m_fRepeatDelayMin, m_fRepeatDelayMax );

	return true;
}
bool ParticleEmitter::Save( TiXmlElement *pElemEmitter )
{
	return true;
}
void ParticleEmitter::Clone( ParticleEmitter *pe )
{
	assert( pe );

	pe->m_fAngle = m_fAngle;
	pe->m_fEmissionRate = m_fEmissionRate;
	pe->m_fMinTTL = m_fMinTTL;
	pe->m_fMaxTTL = m_fMaxTTL;
	pe->m_fMinSpeed = m_fMinSpeed;
	pe->m_fMaxSpeed = m_fMaxSpeed;
	pe->m_dwStartColor = m_dwStartColor;
	pe->m_dwEndColor = m_dwEndColor;
	pe->SetDirection( m_vDirection );
	pe->m_vPosition = m_vPosition;

	pe->m_bEnable = m_bEnable;
	pe->SetDuration( m_fDurationMin, m_fDurationMax );
	pe->SetRepeatDelay( m_fRepeatDelayMin, m_fRepeatDelayMax );
}


// =====================================Point Emitter=======================
PointEmitter::PointEmitter(ParticleGroup *pParent) :
ParticleEmitter(pParent)
{
	m_Type = "点发射器";
}
PointEmitter::~PointEmitter()
{
}

// =====================================Area Emitter=======================
AreaEmitter::AreaEmitter(ParticleGroup *pParent) :
ParticleEmitter(pParent)
{

}
AreaEmitter::~AreaEmitter()
{

}
void AreaEmitter::SetSize( float x, float y, float z )
{
	m_vSize.x = x;
	m_vSize.y = y;
	m_vSize.z = z;

	D3DXVECTOR3 vRight;
	D3DXVec3Cross( &vRight, &m_vUp, &m_vDirection );

	D3DXVec3Normalize(&vRight,&vRight);
	m_vXRange = x * vRight * 0.5f;
	m_vYRange = y * m_vUp * 0.5f;
	m_vZRange = z * m_vDirection * 0.5f;

}
bool AreaEmitter::Load( TiXmlElement *pElemEmitter )
{
	ParticleEmitter::Load( pElemEmitter );

	TiXmlElement *pElem = NULL;
	string name;

	float x, y, z;
	pElem = pElemEmitter->FirstChildElement( "盒子大小" );
	x = static_cast<float>(atof( pElem->Attribute( "盒子宽度" ) ));
	y = static_cast<float>(atof( pElem->Attribute( "盒子高度" ) ));
	z = static_cast<float>(atof( pElem->Attribute( "盒子深度" ) ));

	SetSize( x, y, z );

	return true;
}
bool AreaEmitter::Save( TiXmlElement *pElemEmitter )
{
	return true;
}
void AreaEmitter::Clone( ParticleEmitter *pe )
{
	assert( pe );

	ParticleEmitter::Clone(pe);

	static_cast<AreaEmitter*>(pe)->SetSize( m_vSize.x, m_vSize.y, m_vSize.z );
}

// =====================================Box Emitter=======================
BoxEmitter::BoxEmitter(ParticleGroup *pParent) :
AreaEmitter(pParent)
{
	m_Type = "盒子发射器";
}
BoxEmitter::~BoxEmitter()
{

}
void BoxEmitter::_GenEmissionPosition( D3DXVECTOR3 &destVector )
{
	destVector = m_vPosition + SymmetricRandom() * m_vXRange + 
		SymmetricRandom() * m_vYRange + SymmetricRandom() * m_vZRange;
}
// =====================================Area Emitter=======================
EllipsoidEmitter::EllipsoidEmitter(ParticleGroup *pParent) :
AreaEmitter(pParent)
{
	m_Type = "椭圆发射器";
}
EllipsoidEmitter::~EllipsoidEmitter()
{

}
void EllipsoidEmitter::_GenEmissionPosition( D3DXVECTOR3 &destVector )
{
	float x, y, z;

	while(true)
	{
		x = SymmetricRandom();
		y = SymmetricRandom();
		z = SymmetricRandom();

		if( x*x + y*y + z*z <= 1 )
			break;
	}

	destVector = m_vPosition + 
		m_vXRange * x + m_vYRange * y + m_vZRange * z;

	//destVector = m_vPosition + SymmetricRandom() * m_vXRange + 
	//	SymmetricRandom() * m_vYRange + SymmetricRandom() * m_vZRange;
}

// =====================================Ring Emitter=======================
RingEmitter::RingEmitter(ParticleGroup *pParent) :
AreaEmitter(pParent)
{
	m_Type = "环发射器";
}
RingEmitter::~RingEmitter()
{

}
void RingEmitter::_GenEmissionPosition( D3DXVECTOR3 &destVector )
{
	float alpha = RangeRandom( 0.f, D3DX_PI*2.f );


	//float x = m_fInnerX + (1.f - m_fInnerX) * sinf( alpha );
	//float y = m_fInnerY + (1.f - m_fInnerY) * cosf( alpha );
	//float z = UnitRandom();
	float a = RangeRandom( m_fInnerX, 1.f );
	float b = RangeRandom( m_fInnerY, 1.f );
	float x = a * sinf(alpha);
	float y = b * cosf(alpha);
	float z = UnitRandom();


	destVector = m_vPosition + 
		m_vXRange * x + m_vYRange * y + m_vZRange * z;

}
void RingEmitter::SetInnerSize( float x, float y )
{
	assert( x > 0.f && x < 1.f && y > 0.f && y < 1.f );
	m_fInnerX = x;
	m_fInnerY = y;
}
void RingEmitter::Clone( ParticleEmitter *pe )
{
	assert( pe );

	AreaEmitter::Clone(pe);

	static_cast<RingEmitter*>(pe)->SetInnerSize( m_fInnerX, m_fInnerY );
}
bool RingEmitter::Load( TiXmlElement *pElemEmitter )
{
	AreaEmitter::Load( pElemEmitter );

	TiXmlElement *pElem = NULL;
	string name;

	pElem = pElemEmitter->FirstChildElement( "内环大小" );
	m_fInnerX = static_cast<float>(atof(pElem->Attribute("内环长度")));
	m_fInnerY = static_cast<float>(atof(pElem->Attribute("内环宽度")));

	SetInnerSize( m_fInnerX, m_fInnerY );

	return true;
}
bool RingEmitter::Save( TiXmlElement *pElemEmitter )
{
	return true;
}

// =====================================Hollow Ellipsoid Emitter=======================
HollowEllipsoidEmitter::HollowEllipsoidEmitter(ParticleGroup *pParent) :
AreaEmitter(pParent)
{
	m_Type = "空心椭圆发射器";
}
HollowEllipsoidEmitter::~HollowEllipsoidEmitter()
{
}
void HollowEllipsoidEmitter::_GenEmissionPosition( D3DXVECTOR3 &destVector )
{
	float alpha, beta, a, b, c, x, y, z;

	alpha = RangeRandom(0,D3DX_PI*2.f);
	beta  = RangeRandom(0,D3DX_PI);

	a = RangeRandom(m_vInnerSize.x,1.0);
	b = RangeRandom(m_vInnerSize.y,1.0);
	c = RangeRandom(m_vInnerSize.z,1.0);

	x = a * cosf(alpha) * sinf(beta);
	y = b * sinf(alpha) * sinf(beta);
	z = c * cosf(beta);

	destVector = m_vPosition + 
		+ x * m_vXRange + y * m_vYRange + z * m_vZRange;
}
void HollowEllipsoidEmitter::InitParticle( Particle *p )
{
	_GenEmissionPosition( p->m_vPosition );
	_GenEmissionDirection( p->m_vDirection );
	_GenEmissionSpeed( p->m_vDirection );
	_GenEmissionColor( p->m_Color );
	p->m_fTotalTimeToLive = p->m_fTimeToLive = _GenEmissionTTL();
}
void HollowEllipsoidEmitter::SetInnerSize( float x, float y, float z )
{
	m_vInnerSize.x = x;
	m_vInnerSize.y = y;
	m_vInnerSize.z = z;

}
void HollowEllipsoidEmitter::Clone( ParticleEmitter *pe )
{
	assert( pe );

	AreaEmitter::Clone(pe);

	static_cast<HollowEllipsoidEmitter*>(pe)->SetInnerSize( 
		m_vInnerSize.x, m_vInnerSize.y, m_vInnerSize.z );
}
#include "stdafx.h"
#include "ParticleAffector.h"

#define new VNEW

ParticleAffector::ParticleAffector(ParticleGroup *pParent) : 
m_pParent(pParent)
{
}
ParticleAffector::~ParticleAffector()
{
}

void ParticleAffector::InitParticle( Particle *p )
{
}


bool ParticleAffector::Save( TiXmlElement *pElemAffector )
{
	return true;
}

LinearForceAffector::LinearForceAffector(ParticleGroup *pParent) :
ParticleAffector(pParent)
{
	m_Type = "线性外力";
}
LinearForceAffector::~LinearForceAffector()
{
}
void LinearForceAffector::AffectParticle(float fElapsedTime)
{
	Particle *p = NULL;
	ParticleGroup::ParticleActiveList::iterator i = m_pParent->m_ActiveParticles.begin();
	for( ; i != m_pParent->m_ActiveParticles.end(); ++i )
	{
		p = (*i);
		p->m_vDirection += m_vForceVector * fElapsedTime;
	}
}
bool LinearForceAffector::Load( TiXmlElement *pElemAffector )
{
	TiXmlElement *pElem = NULL;
	string name;

	float x, y, z;
	pElem = pElemAffector->FirstChildElement( "外力" );
	x = static_cast<float>(atof( pElem->Attribute( "x" ) ));
	y = static_cast<float>(atof( pElem->Attribute( "y" ) ));
	z = static_cast<float>(atof( pElem->Attribute( "z" ) ));

	m_vForceVector.x = x;
	m_vForceVector.y = y;
	m_vForceVector.z = z;

	return true;
}
bool LinearForceAffector::Save( TiXmlElement *pElemAffector )
{
	return true;
}
void LinearForceAffector::Clone( ParticleAffector *pe )
{
	assert(pe);

	static_cast<LinearForceAffector*>(pe)->m_vForceVector = m_vForceVector;
}


ColorFadeAffector::ColorFadeAffector(ParticleGroup *pParent) :
ParticleAffector(pParent){
	m_Type = "颜色衰减";
}

ColorFadeAffector::~ColorFadeAffector()
{
}

void ColorFadeAffector::AffectParticle(float fElapsedTime)
{
	int r, g, b;
	Particle *p = NULL;
	ParticleGroup::ParticleActiveList::iterator i = m_pParent->m_ActiveParticles.begin();
	for( ; i != m_pParent->m_ActiveParticles.end(); ++i )
	{
		p = (*i);

		r = COLOR_GETRVALUE(p->m_Color);
		g = COLOR_GETGVALUE(p->m_Color);
		b = COLOR_GETBVALUE(p->m_Color);

		r += static_cast<int>(m_iR * fElapsedTime);
		g += static_cast<int>(m_iG * fElapsedTime);
		b += static_cast<int>(m_iB * fElapsedTime);

		if( r < 0 )
			r = 0;
		if( r > 255 )
			r = 255;
		if( g < 0 )
			g = 0;
		if( g > 255 )
			g = 255;
		if( b < 0 )
			b = 0;
		if( b > 255 )
			b = 255;

		p->m_Color = D3DCOLOR_ARGB( 255, r, g, b );

	}
}
bool ColorFadeAffector::Load( TiXmlElement *pElemAffector )
{
	TiXmlElement *pElem = NULL;
	string name;

	pElem = pElemAffector->FirstChildElement( "红色衰减值" );
	m_iR = atoi(pElem->GetText());
	pElem = pElemAffector->FirstChildElement( "绿色衰减值" );
	m_iG = atoi(pElem->GetText());
	pElem = pElemAffector->FirstChildElement( "蓝色衰减值" );
	m_iB = atoi(pElem->GetText());

	return true;
}
bool ColorFadeAffector::Save( TiXmlElement *pElemAffector )
{
	return true;
}
void ColorFadeAffector::Clone( ParticleAffector *pe )
{
	assert(pe);

	static_cast<ColorFadeAffector*>(pe)->m_iR = m_iR;
	static_cast<ColorFadeAffector*>(pe)->m_iG = m_iG;
	static_cast<ColorFadeAffector*>(pe)->m_iB = m_iB;
}


ColorImageAffector::ColorImageAffector(ParticleGroup *pParent,LPDIRECT3DDEVICE9 pDevice) :
ParticleAffector(pParent),
m_pDevice(pDevice),
m_pTexture(NULL),
m_pColorBuffer(NULL),
m_uiPitch(0),
m_uiWidth(0)
{
	m_Type = "颜色衰减图";
}

ColorImageAffector::~ColorImageAffector()
{
	SAFE_RELEASE( m_pTexture );
	SAFE_DELETE( m_pColorBuffer );
}

void ColorImageAffector::SetImageName( LPSTR pName )
{
	string strDDSName;
	m_strImageName = pName;
	strDDSName = pName;

	//strDDSName = ".//Resource//Texture//" + strDDSName;
	ChangeFileNameToDDS( strDDSName );
	//m_strImageName = ".//Resource//Texture//" + m_strImageName;

	if( FAILED(D3DXCreateTextureFromFileEx( m_pDevice, strDDSName.c_str(), D3DX_DEFAULT, 
											D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
											D3DX_FILTER_POINT, 0, 0, NULL, NULL, &m_pTexture )) )
	{
		if( FAILED(D3DXCreateTextureFromFileEx( m_pDevice, m_strImageName.c_str(), D3DX_DEFAULT, 
												D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
												D3DX_FILTER_POINT, 0, 0, NULL, NULL, &m_pTexture )) )
			return;
	}
	//D3DXCreateTextureFromFile( m_pDevice, 
	//	m_strImageName.c_str(), &m_pTexture );

	D3DSURFACE_DESC desc;
	m_pTexture->GetLevelDesc( 0, &desc );
	m_uiWidth = desc.Width;


	D3DLOCKED_RECT rect;
	m_pTexture->LockRect( 0, &rect, NULL, 0 );
	m_uiPitch = rect.Pitch;
	m_pColorBuffer = new BYTE[rect.Pitch];
	memcpy( m_pColorBuffer, rect.pBits, rect.Pitch );
	m_pTexture->UnlockRect(0);

}
void ColorImageAffector::InitParticle( Particle *p )
{
	UINT uiPosition = 0;
	float fB = m_pColorBuffer[ uiPosition + 0 ];
	float fG = m_pColorBuffer[ uiPosition + 1 ];
	float fR = m_pColorBuffer[ uiPosition + 2 ];
	float fA = m_pColorBuffer[ uiPosition + 3 ];
	p->m_Color = D3DCOLOR_ARGB( static_cast<int>(fA), static_cast<int>(fR), 
		static_cast<int>(fG), static_cast<int>(fB) );
}

void ColorImageAffector::AffectParticle(float fElapsedTime)
{
	float fA, fR, fG, fB, fTA, fTR, fTG, fTB ;

	Particle *p = NULL;
	ParticleGroup::ParticleActiveList::iterator i = m_pParent->m_ActiveParticles.begin();
	for( ; i != m_pParent->m_ActiveParticles.end(); ++i )
	{
		p = (*i);

		float fLiveTime = p->m_fTotalTimeToLive - p->m_fTimeToLive;
		float fIndex = m_uiWidth * fLiveTime / p->m_fTotalTimeToLive;
		UINT uiIndex = static_cast<UINT>( fIndex );
		UINT uiPosition = uiIndex * 4;

		float fT = fIndex - static_cast<float>(uiIndex);


		if( uiIndex < 0 )
		{
			uiPosition = 0;
			fB = m_pColorBuffer[ uiPosition + 0 ];
			fG = m_pColorBuffer[ uiPosition + 1 ];
			fR = m_pColorBuffer[ uiPosition + 2 ];
			fA = m_pColorBuffer[ uiPosition + 3 ];
		}
		else if( uiIndex >= m_uiWidth-1 )
		{
			uiPosition = (m_uiWidth - 1)*4;
			fB = m_pColorBuffer[ uiPosition + 0 ];
			fG = m_pColorBuffer[ uiPosition + 1 ];
			fR = m_pColorBuffer[ uiPosition + 2 ];
			fA = m_pColorBuffer[ uiPosition + 3 ];
		}
		else
		{
			fB = m_pColorBuffer[ uiPosition + 0 ];
			fG = m_pColorBuffer[ uiPosition + 1 ];
			fR = m_pColorBuffer[ uiPosition + 2 ];
			fA = m_pColorBuffer[ uiPosition + 3 ];

			fTB = m_pColorBuffer[ uiPosition + 4 ];
			fTG = m_pColorBuffer[ uiPosition + 5 ];
			fTR = m_pColorBuffer[ uiPosition + 6 ];
			fTA = m_pColorBuffer[ uiPosition + 7 ];

			fA = fTA * fT + fA * ( 1- fT );
			fR = fTR * fT + fR * ( 1- fT );
			fG = fTG * fT + fG * ( 1- fT );
			fB = fTB * fT + fB * ( 1- fT );
		}
		p->m_Color = D3DCOLOR_ARGB( static_cast<int>(fA), static_cast<int>(fR), 
			static_cast<int>(fG), static_cast<int>(fB) );
	}


}


bool ColorImageAffector::Load( TiXmlElement *pElemAffector )
{
	TiXmlElement *pElem = NULL;
	string name;

	pElem = pElemAffector->FirstChildElement( "衰减图" );
	SetImageName( const_cast<LPSTR>(pElem->GetText()) );

	return true;
}
bool ColorImageAffector::Save( TiXmlElement *pElemAffector )
{
	return true;
}
void ColorImageAffector::Clone( ParticleAffector *pe )
{
	assert(pe);

	ColorImageAffector *pColorImageAffector = static_cast<ColorImageAffector *>(pe);

	pColorImageAffector->m_strImageName = m_strImageName;
	pColorImageAffector->m_pTexture = m_pTexture;
	m_pTexture->AddRef();
	pColorImageAffector->m_uiWidth = m_uiWidth;

	pColorImageAffector->m_uiPitch = m_uiPitch;
	SAFE_DELETE(pColorImageAffector->m_pColorBuffer);
	pColorImageAffector->m_pColorBuffer = new BYTE[m_uiPitch];
	memcpy( pColorImageAffector->m_pColorBuffer, m_pColorBuffer, m_uiPitch );
}

//////////////////////////////////////////////////////////////////////////

RotationAffector::RotationAffector( ParticleGroup *pParent ) :
ParticleAffector(pParent),
m_fRotationSpeedRangeStart(0),
m_fRotationSpeedRangeEnd(0),
m_fRotationRangeStart(0),
m_fRotationRangeEnd(0)
{
	m_Type = "旋转";
}
RotationAffector::~RotationAffector()
{

}

void RotationAffector::InitParticle( Particle *p )
{
	p->m_fRotation = m_fRotationRangeStart + (UnitRandom() * 
		(m_fRotationRangeEnd - m_fRotationRangeStart));
	p->m_fRotationSpeed = m_fRotationSpeedRangeStart + (UnitRandom() * 
		(m_fRotationSpeedRangeEnd - m_fRotationSpeedRangeStart));

}
void RotationAffector::AffectParticle(float fElapsedTime)
{
	Particle *p = NULL;
	ParticleGroup::ParticleActiveList::iterator i = m_pParent->m_ActiveParticles.begin();
	for( ; i != m_pParent->m_ActiveParticles.end(); ++i )
	{
		p = (*i);
		p->m_fRotation = p->m_fRotation + fElapsedTime * p->m_fRotationSpeed;
	}
}

bool RotationAffector::Load( TiXmlElement *pElemAffector )
{
	TiXmlElement *pElem = NULL;
	string name;

	pElem = pElemAffector->FirstChildElement( "旋转范围起始角度" );
	m_fRotationRangeStart = static_cast<float>(atof(pElem->GetText()));

	pElem = pElemAffector->FirstChildElement( "旋转范围结束角度" );
	m_fRotationRangeEnd = static_cast<float>(atof(pElem->GetText()));

	pElem = pElemAffector->FirstChildElement( "旋转速度起始值" );
	m_fRotationSpeedRangeStart = static_cast<float>(atof(pElem->GetText()));

	pElem = pElemAffector->FirstChildElement( "旋转速度结束值" );
	m_fRotationSpeedRangeEnd = static_cast<float>(atof(pElem->GetText()));

	return true;
}
bool RotationAffector::Save( TiXmlElement *pElemAffector )
{
	return true;
}
void RotationAffector::Clone( ParticleAffector *pe )
{
	assert(pe);

	RotationAffector *pRotationAffector = static_cast<RotationAffector *>(pe);

	pRotationAffector->m_fRotationSpeedRangeStart = m_fRotationSpeedRangeStart;
	pRotationAffector->m_fRotationSpeedRangeEnd = m_fRotationSpeedRangeEnd;
	pRotationAffector->m_fRotationRangeStart = m_fRotationRangeStart;
	pRotationAffector->m_fRotationRangeEnd = m_fRotationRangeEnd;
}



ScaleAffector::ScaleAffector( ParticleGroup *pParent ) :
ParticleAffector(pParent),
m_fScaleAdj(0.f),
m_fMaxSize(10000.f)
{
	m_Type = "缩放";
}
ScaleAffector::~ScaleAffector()
{

}
void ScaleAffector::InitParticle( Particle *p )
{
	// 设置为false，第一次affectParticle时不需要计算缩放
	p->m_bOwnDimension = false;
}
void ScaleAffector::AffectParticle(float fElapsedTime)
{
	float ds;
	ds = m_fScaleAdj * fElapsedTime;

	float NewWide, NewHigh;

	Particle *p = NULL;
	ParticleGroup::ParticleActiveList::iterator i = m_pParent->m_ActiveParticles.begin();
	for( ; i != m_pParent->m_ActiveParticles.end(); ++i )
	{
		p = (*i);

		if( p->m_bOwnDimension == false ){
			p->SetDimension( m_pParent->m_fDefaultWidth, 
				m_pParent->m_fDefaultHeight );
		}
		else{
			if( p->m_fHeight == 0.f || p->m_fWidth == 0.f )
				continue;

			NewWide = p->m_fWidth + ds;
			NewHigh = p->m_fHeight + ds;

			if( NewHigh < 0.f || NewWide < 0.f )
				NewHigh = NewWide = 0.f;
			if( NewHigh > m_fMaxSize || NewWide > m_fMaxSize )
				NewHigh = NewWide = m_fMaxSize;

			p->SetDimension( NewWide, NewHigh );
		}
	}
}

bool ScaleAffector::Load( TiXmlElement *pElemAffector )
{
	TiXmlElement *pElem = NULL;
	string name;

	pElem = pElemAffector->FirstChildElement( "缩放值" );
	m_fScaleAdj = static_cast<float>(atof(pElem->GetText()));

	pElem = pElemAffector->FirstChildElement( "最大大小" );
	if(pElem)
	{
		m_fMaxSize = static_cast<float>(atof(pElem->GetText()));
	}

	return true;
}
bool ScaleAffector::Save( TiXmlElement *pElemAffector )
{
	return true;
}
void ScaleAffector::Clone( ParticleAffector *pe )
{
	assert(pe);

	ScaleAffector *pScaleAffector = static_cast<ScaleAffector *>(pe);

	pScaleAffector->m_fScaleAdj = m_fScaleAdj;
	pScaleAffector->m_fMaxSize = m_fMaxSize;
}

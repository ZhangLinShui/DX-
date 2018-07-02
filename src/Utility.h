/********************************************************************
	created:	2007/03/14
	created:	14:3:2007   15:03
	filename: 	Utility.h
	author:		������
	
	purpose:	��������
	changelog:	2007/05/09	Ϊ���Ż����󲿷�����ѹ��Ϊdds��ʽ���˴�����
							���ļ���׺��תΪdds�ĸ���������
*********************************************************************/

#pragma once


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef V
#define V(x)           { hr = x; }
#endif
#ifndef V_RETURN
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return hr; } }
#endif


#define COLOR_GETAVALUE( argb ) ( (BYTE)( ( argb ) >> 24 ) )
#define COLOR_GETRVALUE( argb ) ( (BYTE)( ( argb ) >> 16 ) )
#define COLOR_GETGVALUE( argb ) ( (BYTE)( ( argb ) >> 8 ) )
#define COLOR_GETBVALUE( argb ) ( (BYTE)( argb ) )

/** �볡����ϵ�����
*/
enum SceneBlendType
{
	/// ��͸��
	SBT_OPAQUE = 0,
	/// Alpha��͸��
	SBT_TRANSPARENT_ALPHA,
	/// ʹ��Դ��ɫ��Alpha���ӣ�ʵ�ְ�͸��
	SBT_TRANSPARENT_COLOR,
	/// �볡����ɫ��ӣ�ͨ����������
	SBT_ADD_COLOR,
	/// �볡����ɫ���,ͨ����������ԭ������ϸ��
	SBT_ADD_ALPHA,
	/// �볡����ɫ���
	SBT_MODULATE,
	/// �볡����ɫ��˵�2��
	SBT_MODULATE2,
	/// ʹ�ö���ɫ��Alphaͨ����ʵ�ְ�͸��
	SBT_TRANSPARENT_DIFFUSE,
	SBT_MAX_NUMBER,
};

/** ·������
	@remarks
		.x�ļ����е��ļ�������·�����˺������Խ�·��ȥ����
*/
inline void GetRealFileName( std::string &name )
{
	size_t pos = name.find_last_of( '/' );
	if( pos != std::string::npos )
	{
		name = name.substr( pos+1, name.size()-pos-1 );
		return;
	}
	pos = name.find_last_of( '\\' );
	if( pos != std::string::npos )
	{
		name = name.substr( pos+1, name.size()-pos-1 );
		return;
	}
}

/** �������������
*/
D3DXVECTOR3 Vec3Mutiply( const D3DXVECTOR3 &v1, const D3DXVECTOR3 &v2 );

/** ��һ�������ġ���ֱ������
*/
void Vec3Perpendicular( D3DXVECTOR3 &out, const D3DXVECTOR3 &src );

/** ��֪һ������һ�Ƕȶ�λ��׶�壬�󴩹�׶�嶥�㲢λ��׶���ڵ����������
	@param
		dir ��֪������׶�����
	@param
		fAngle ��֪�Ƕȣ��ᵽ׶��ĳһ�ߵĻ���
	@param
		result ���ؽ��������׶�嶥�㣬����λ��׶���ڵ�������

	������ӵķ��䷽����ڸ�׶���ڴ���������λ�õ�һ�����ߡ�
*/
void RandomDeviant( D3DXVECTOR3 &result, const D3DXVECTOR3 &dir, float fAngle );

/** ���ֵ�� 0-1
*/
float UnitRandom();

/** ���ֵ�� fLow-fHigh
*/
float RangeRandom(float fLow, float fHigh);

/** ���ֵ�� (-1) - (1)
*/
float SymmetricRandom();


void ChangeFileNameToDDS( string &name );

inline DWORD F2DW( FLOAT f )
{
	return *((DWORD*)&f); 
}
inline float DW2F( DWORD dw )
{
	return *((FLOAT*)&dw); 
}

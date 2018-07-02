#pragma  once
#include "Object.h"
class CPicture
{
public:
	CPicture(void);
	~CPicture(void);
	//初始化
	VOID Init(string name);
	//绘制函数
	VOID Draw(POINT destPos, POINT srcPos, WORD w, WORD h, POINT destPos1);

	//返回图片的长宽
	int GetWidth() { return m_wWidth; }
	int GetHeight() { return m_wHeight; }

	void SetRot(float rot) { m_fRot = rot; }
	void SetAlphaColor(DWORD color) { m_dwAlphaColor = color; }
	void SetAlphaBlend(DWORD color) { m_dwAlphaBlend = color; }

	void GetPictureColor();
	DWORD GetColor(POINT pos);

	void SetCenterPoint(D3DXVECTOR3 cp) { m_vCenterPoint = cp; }

	void SetBlock(float scaleX, float scaleY, float scaleZ)
	{
		ScaleX = scaleX;
		ScaleY = scaleY;
		ScaleZ = scaleZ;
	}
	void SetDepth(float z) { depth = z; }


	D3DXMATRIX GetmatWotld() { return matWorld; }
	D3DXMATRIX GetmatWotld1() { return matWorld1; }
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPDIRECT3DTEXTURE9 m_pTex;
	LPD3DXSPRITE		m_pSprite;
	DWORD m_dwAlphaBlend;
	DWORD m_dwAlphaColor;

	WORD    m_wWidth;
	WORD    m_wHeight;

	float m_fRot;
	D3DXVECTOR3 m_vCenterPoint;
	DWORD * m_pColorData;
	DWORD m_dwPitch;		//一行的字节数

	
	float ScaleX;
	float ScaleY;
	float ScaleZ;
	float depth;

	D3DXMATRIX matWorld, matRot, matT, sclMat;
	D3DXMATRIX matWorld1, matRot1, matT1, sclMat1;
};
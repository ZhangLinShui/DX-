#include "stdafx.h"
#include "Picture.h"

CPicture::CPicture(void)
{
	m_dwAlphaColor = 0;
	m_dwAlphaBlend = 0xffffffff;
	m_fRot = 0;
	m_vCenterPoint = D3DXVECTOR3(0, 0,0);
	m_pColorData = NULL;

	ScaleX = 1;
	ScaleY = 1;
	ScaleZ = 1;
}
CPicture::~CPicture(void)
{

}

VOID CPicture::Init(string name)
{
	m_pDevice = (LPDIRECT3DDEVICE9)CPlatform::GetsinglenPtr()->FindResourceA("设备接口");
	m_pSprite = (LPD3DXSPRITE)CPlatform::GetsinglenPtr()->FindResourceA("精灵接口");

	D3DXCreateTextureFromFileExA(m_pDevice, name.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, 
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, 0, m_dwAlphaColor, 0, 0, &m_pTex);

	D3DSURFACE_DESC desc;
	m_pTex->GetLevelDesc(0, &desc);
	this->m_wWidth = desc.Width;
	m_wHeight = desc.Height;
	GetPictureColor();
}

VOID CPicture::Draw(POINT destPos, POINT srcPos, WORD w, WORD h, POINT destPos1)
{
	
	//预判世界矩阵
	D3DXMatrixIdentity(&matWorld1);
	D3DXMatrixTranslation(&matT1, destPos1.x, destPos1.y, depth);
	D3DXMatrixRotationZ(&matRot1, m_fRot);
	D3DXMatrixScaling(&sclMat1, ScaleX, ScaleY, ScaleZ);
	matWorld1 = matRot1*sclMat1* matT1;


	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matT, destPos.x, destPos.y, depth);
	D3DXMatrixRotationZ(&matRot, m_fRot);
	D3DXMatrixScaling(&sclMat, ScaleX, ScaleY, ScaleZ);
	matWorld = matRot*sclMat* matT;

	RECT rc = { srcPos.x,srcPos.y,w+srcPos.x,h+srcPos.y };
	m_pSprite->SetTransform(&matWorld);

	D3DXVECTOR3 center = {w*m_vCenterPoint.x,h*m_vCenterPoint.y,0};
	m_pSprite->Draw(m_pTex, &rc, &center, NULL, m_dwAlphaBlend);


}



void CPicture::GetPictureColor()
{
	if (m_pTex)
	{
		m_pColorData = new DWORD[m_wWidth*m_wHeight];

		D3DLOCKED_RECT info;
		RECT rc = { 0,0,m_wWidth,m_wHeight };
		m_pTex->LockRect(0, &info, &rc, 0);

		m_pColorData = (DWORD*)info.pBits;
		m_dwPitch = info.Pitch;
		m_pTex->UnlockRect(0);
	}
}
DWORD CPicture::GetColor(POINT pos)
{
	return m_pColorData[pos.y*m_wWidth + pos.x];
}
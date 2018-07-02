#include "stdafx.h"
#include "UIPicture.h"
 
CUIPicture::CUIPicture():CComponent()
{
	m_lType = GUI_TYPE_PIC;
}

CUIPicture::~CUIPicture()
{

}
void CUIPicture::Init(TiXmlElement* element)
{
	CComponent::Init(element);
	this->SetPicture(element->FirstChildElement("Picture")->GetText());
}
//����ͼƬ
void CUIPicture::ChangePic(string filename)
{
	HRESULT hr;
	//OutputDebugString("ChangePic start\n");
	IDirect3DTexture9* pTemp = NULL;
	//���ͷ�COM����,��Ȼ������ڴ�й©
	//���ذ���״̬�µ�ͼƬ
	hr = D3DXCreateTextureFromFileEx(m_pDevice,filename.c_str(),m_lWidth,m_lHeight,0,D3DUSAGE_DYNAMIC,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,
		D3DX_DEFAULT,D3DX_DEFAULT,0xffffffff,NULL,NULL,&pTemp);
	if(FAILED(hr))	
	{
		HWND hWnd = GetActiveWindow();
		MessageBox(hWnd,"����ͼƬ��Դʧ��","����ͼƬ��Դʧ��",MB_OK);
	}
	if(pTemp!=NULL)
	{
		SAFE_RELEASE(m_pPic);
		m_pPic = pTemp;
		pTemp = NULL;
	}
	
	//OutputDebugString("ChangePic end\n");
}
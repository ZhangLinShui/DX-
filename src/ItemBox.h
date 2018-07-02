//���Ϸż���ͼ��,��Ʒͼ���С��λ
//������Frame�����,�����϶�,��CButton��������
#pragma once
#include "Button.h"
#include "UIPicture.h"

class CItemBox:public CButton
{
public:

	//���캯��
	CItemBox();

	//��������
	~CItemBox();

	//��������λ�ϵ�ͼƬ
	bool ChangeItemPic(string filename);

	//��������ƶ�������ϵ�ʱ����λ�ı߿��ͼƬ
	bool SetItemFramePic(string filename);

	//������λ��ͼƬ�Ĵ�С(����ֱ�ӵ������SetSize)
	void SetItemPicSize(long lWidth,long lHeight)				{ m_lItemPicWidth = lWidth;m_lItemPicHeight = lHeight;}

	//��������λ��ͼƬ�����Ͻǵ�����
	void SetItemPicPos(long left,long top)						{ m_ptPosItemPic.x = (float)left,m_ptPosItemPic.y = (float)top;}

	//�������
	void Draw();

	//���������λ��(���Ͻ�,ͨ���������)
	void SetPos(float OffsetX,float OffsetY);

	//�������������µ��¼���Ӧ
	void ProcessMouseLBDown(long x,long y);

	//�����Ʒ���ϵ�ͼƬ��·��
	string GetItemPicFile(void)									{return m_strPicFile;}



protected:

	//��λ�ϵ�ͼƬ
	IDirect3DTexture9* m_ItemPic;

	//��λ�ϵı߿��ͼƬ
	IDirect3DTexture9* m_ItemFramePic;

	//��λ�ϵ�ͼƬ�Ƿ����ʰȡ��
	bool m_bPicPicked;

	//��Ʒ���ϵ�ͼƬ�Ŀ�͸�
	long m_lItemPicWidth;
	long m_lItemPicHeight;

	//��Ʒ���ϵ�ͼƬ�����Ͻǵ�����
	D3DXVECTOR2 m_ptPosItemPic;

	//��Ʒ���ϵ�ͼƬ�ľ���
	D3DXMATRIX m_matItemPicPos;

	//����Ʒ����ͼ�괦���������ƶ�ʱ�����Ͻǵ�����
	D3DXVECTOR2 m_ptPosWithMouse;

	//����Ʒ����ͼ�괦���������ƶ�ʱ�ľ���
	D3DXMATRIX m_matWithMousePos;

	//��ʾ����Ʒ����ͼ�굱ǰ�Ƿ��ڸ�������ƶ�
	bool m_bWithMouseMove;

	//��Ʒ����ͼƬ��·��
	string m_strPicFile;




};

//可拖放技能图标,物品图标的小栏位
//包含在Frame组件中,可以拖动,从CButton类中派生
#pragma once
#include "Button.h"
#include "UIPicture.h"

class CItemBox:public CButton
{
public:

	//构造函数
	CItemBox();

	//析构函数
	~CItemBox();

	//更换换栏位上的图片
	bool ChangeItemPic(string filename);

	//设置鼠标移动到组件上的时候栏位的边框的图片
	bool SetItemFramePic(string filename);

	//设置栏位的图片的大小(可以直接调基类的SetSize)
	void SetItemPicSize(long lWidth,long lHeight)				{ m_lItemPicWidth = lWidth;m_lItemPicHeight = lHeight;}

	//设置制栏位的图片的左上角的坐标
	void SetItemPicPos(long left,long top)						{ m_ptPosItemPic.x = (float)left,m_ptPosItemPic.y = (float)top;}

	//绘制组件
	void Draw();

	//设置组件的位置(左上角,通过相对坐标)
	void SetPos(float OffsetX,float OffsetY);

	//处理鼠标左键按下的事件响应
	void ProcessMouseLBDown(long x,long y);

	//获得物品栏上的图片的路径
	string GetItemPicFile(void)									{return m_strPicFile;}



protected:

	//栏位上的图片
	IDirect3DTexture9* m_ItemPic;

	//栏位上的边框的图片
	IDirect3DTexture9* m_ItemFramePic;

	//栏位上的图片是否被鼠标拾取了
	bool m_bPicPicked;

	//物品栏上的图片的宽和高
	long m_lItemPicWidth;
	long m_lItemPicHeight;

	//物品栏上的图片的左上角的坐标
	D3DXVECTOR2 m_ptPosItemPic;

	//物品栏上的图片的矩阵
	D3DXMATRIX m_matItemPicPos;

	//当物品栏的图标处于鼠标跟随移动时的左上角的坐标
	D3DXVECTOR2 m_ptPosWithMouse;

	//当物品栏的图标处于鼠标跟随移动时的矩阵
	D3DXMATRIX m_matWithMousePos;

	//标示了物品栏的图标当前是否在跟随鼠标移动
	bool m_bWithMouseMove;

	//物品栏的图片的路径
	string m_strPicFile;




};

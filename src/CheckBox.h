//////////////////////////////////////////////////////////////////////////
//Name:CheckBox.h

//Desc:
//选择框控件
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Component.h"

class CCheckBox : public CComponent
{
public:

	//构造函数
	CCheckBox();

	//析构函数
	~CCheckBox();

	//加载"打钩"纹理
	bool SetCheckCursorPic(string filename);

	//绘制组件
	void Draw(void);

	//处理鼠标移动的事件响应
	void ProcessMouseMove(long x,long y);

	//处理鼠标左键按下的事件响应
	void ProcessMouseLBDown(long x,long y);

	//处理鼠标左键弹起的事件响应
	void ProcessMouseLBUp(long x,long y);

	//设置按钮所对应的具体的事件(LUA函数),传入的参数是LUA脚本中的函数名
	void SetEvent(string FunctionName);

	//执行按钮所对应的具体的事件
	void DoEvent();

	//设置游标的左上角的坐标
	void SetCursorLeftUpPos(D3DXVECTOR2 vPos);	

	//获得当前选择框是否已经勾选
	bool GetBeChecked(void)							{return m_bShowCheckCursor;}

	//设置当前选择框是否勾选
	void SetBeChecked(bool bChecked)				{m_bShowCheckCursor = bChecked;}

protected:

	//"打钩"纹理
	IDirect3DTexture9* m_pCheckCursorTex;

	//是否显示"打钩"纹理
	bool m_bShowCheckCursor;

	//按钮所对应的具体的事件的函数名
	string m_strFunctionName;

	//游标的左上角坐标
	D3DXVECTOR2 m_vCursorLeftUpPos;

	//游标的显示的缩放比例
	D3DXVECTOR2 m_vCursorScale;
};

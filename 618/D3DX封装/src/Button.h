//按钮控件
//从CComponent类中派生出来

#pragma once
#include "Component.h"


class CButton:public CComponent
{

public:

	//构造函数
	CButton();

	//析构函数
	~CButton();

	void Init(TiXmlElement* element);
	//绘制组件
	void Draw();

	//处理键盘的事件响应
	void ProcessKeyEvent(char key);

	//处理鼠标移动的事件响应
	void ProcessMouseMove(long x,long y);

	//处理鼠标左键按下的事件响应
	void ProcessMouseLBDown(long x,long y);

	//处理鼠标左键弹起的事件响应
	void ProcessMouseLBUp(long x,long y);

	////处理鼠标右键按下的事件响应
	//void ProcessMouseRBDown(long x,long y);

	////处理鼠标右键弹起的事件响应
	//void ProcessMouseRBUp(long x,long y);

	////处理鼠标滚轮滚动的事件响应
	//void ProcessMouseWheel();


	//执行按钮所对应的具体的事件
	void DoEvent();

	//设置快捷键
	void SetHotKey(char CHotKey);

	//设置按钮所对应的具体的事件(LUA函数),传入的参数是LUA脚本中的函数名
	void SetEvent(string FunctionName);

	//分别加载3个状态下的图片资源
	void SetTextureDefault(string TexDefault);
	void SetTextureMoveto(string TexMoveto);
	void SetTextureDown(string TexDown);

protected:

	//普通状态下的按钮图片
	IDirect3DTexture9* m_pTexDefault;

	//当鼠标移动到按钮上时对应的按钮图片
	IDirect3DTexture9* m_pTexMoveto;

	//当鼠标按下去时对应的按钮图片
	IDirect3DTexture9* m_pTexDown;

	//当前状态下的按钮图片(渲染的图片)
	IDirect3DTexture9* m_pTexNow;

	//快捷键
	char m_cHotKey;

	//按钮所对应的具体的事件的函数名
	string m_strFunctionName;

};

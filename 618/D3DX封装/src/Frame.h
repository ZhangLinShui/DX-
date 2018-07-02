//框架组件,一个PAGE有一个框架,所有的其中的控件都是它的子组件
//它控制了PAGE的显示和隐藏,也控制了PAGE的拖曳

#pragma once
#include "Component.h"

class CFrame : public CComponent
{
public:
	//构造函数
	CFrame();

	//析构函数
	~CFrame();

	void Init(TiXmlElement* element);
	//处理鼠标左键按下的事件响应
	void ProcessMouseLBDown(long x,long y);

	//处理鼠标左键弹起的事件响应
	void ProcessMouseLBUp(long x,long y);

	//处理鼠标移动的事件响应
	void ProcessMouseMove(long x,long y);

};

//GUI系统的管理器,全局一个实例,使用单件模式
//所有的COMPONENT实例对象的显示,操作,消息响应都由GUI管理器统一管理
//这个GUI系统是基于LUA的,一个PAGE对应了一个LUA函数
//PAGE的位置,相应函数等都不是简单的配置,而是基于绑定了的C++函数

#pragma once
#include "Observer.h"

#include "Component.h"
class CGUIManager : public IObservable
{
public:
	//析构函数
	~CGUIManager();
	//取得全局唯一的"GUI管理器"的实例
	static CGUIManager* GetInstance();

	//初始化"GUI管理器"
	bool Init(string fileName);

	//释放"GUI管理器"
	void Release(void);

	//创建一个PAGE,参数为执行的函数
	bool LoadPage(string filename);

	//创建一个GUI组件
	CComponent* CreateComponent(long ComponentType, string ComponentName);

	////处理GUI相关的所有事件
	//void ProcessGUIEvent(long x, long y);

	//处理键盘的事件响应
	void ProcessKeyEvent(char key);

	//处理鼠标移动的事件响应
	void ProcessMouseMove(long x, long y);

	////处理鼠标左键按下的事件响应
	void ProcessMouseLBDown(long x,long y);

	//处理鼠标左键弹起的事件响应
	void ProcessMouseLBUp(long x,long y);

	//处理鼠标右键按下的事件响应
	void ProcessMouseRBDown(long x,long y);

	//处理鼠标右键弹起的事件响应
	void ProcessMouseRBUp(long x,long y);

	//处理鼠标滚轮滚动的事件响应
	void ProcessMouseWheel();

	//获得一个组件的指针
	//参数为这个组件名字
	CComponent* GetComponentByName(string ComponentName);

	//设置设备对象
	void SetDevice(IDirect3DDevice9* pDevice) { m_pDevice = pDevice; }
	IDirect3DDevice9* GetDevice() { return m_pDevice; }
	void SetIsDraw(bool IsDraw){IsDrawAll = IsDraw;}
	bool GetIsDraw() { return IsDrawAll; }

	
private:

	//单件模式下构造函数是私有的
	CGUIManager();

	

	//全局唯一的"场景管理器"的实例
	static CGUIManager* m_Instance;

	//GUI管理器中的所有的GUI组件对象
	map<string,CComponent*> m_mapComponent;
	map<string,CComponent*>::iterator m_mapComponentIT;

	//map<string,CBaseInterface*>m_mapInterface
	//控制器里的IComponent对象,用于传输到图形系统渲染
	IComponent* m_ImapComponent;

	//上一帧的鼠标的位置
	long m_lXOld;
	long m_lYOld;

	//这一帧鼠标的位置的偏移量
	long m_lXOffset;
	long m_lYOffset;

	//D3D设备对象
	IDirect3DDevice9* m_pDevice;

	bool IsDrawAll=false;//控制所有方块的绘制；开始UI进入游戏后再绘制；
	

};

//CGUIManager* GetGUIMgr();

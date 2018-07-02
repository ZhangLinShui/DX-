//引擎模块,系统以及管理器的一些基本定义

#pragma once
//模型的包围和的八个顶点
struct CubePoints
{
	D3DXVECTOR3 FrontUp;
	D3DXVECTOR3 FrontDown;
	D3DXVECTOR3 FrontLeft;
	D3DXVECTOR3 FrontRight;
	D3DXVECTOR3 BackUp;
	D3DXVECTOR3 BackDown;
	D3DXVECTOR3 BackLeft;
	D3DXVECTOR3 BackRight;
};
//画线的点和颜色
struct CUSTOMVERTEXLINE {
	D3DXVECTOR3 start;
	DWORD		color;
};

enum MyEnum
{
	LEFT = 1,//人物方向
	RIGHT,
	UP
};
//场景中的对象的类型
enum ObjectType
{
	OB_TYPE_NOTYPE,				//无类型
	OB_TYPE_MAP,				//地图
	OB_TYPE_PLAYER,				//玩家
	OB_TYPE_NPC,				//NPC
	OB_TYPE_MONSTER,			//怪物
	OB_TYPE_CAMERA,			//相机
	OB_TYPE_SKY,			//天空
	OB_TYPE_Light,			//天空
	OB_TYPE_WATER,			//天空
	OB_TYPE_BRIDGE,			//天空
	OB_TYPE_HOURSE,			//天空
	OB_TYPE_MODEL,			//基础模型
	OB_TYPE_MODEL_COPY,		//可复用基础模型的类型
	OB_TYPE_ANIMATION_MESH,	//动画模型	
	OB_TYPE_PARTICLE		//粒子

};
//鼠标事件的枚举值
enum MOUSEEVENT
{
	MOUSE_NONE,
	MOUSE_LB_DOWN,				//左键按下
	MOUSE_LB_UP,				//左键弹起
	MOUSE_LB_DCLICK,			//左键双击

	MOUSE_RB_DOWN,				//右键按下
	MOUSE_RB_UP,				//右键弹起
	MOUSE_RB_DCLICK,			//右键双击

	MOUSE_MB_DOWN,				//中键按下
	MOUSE_MB_UP,				//中键弹起
	MOUSE_MB_DCLICK,			//中键双击

	MOUSE_MB_WHEEL,
};
//GUI组件的类型
enum GUIComponentType
{
	GUI_TYPE_NOTYPE,			//无类型
	GUI_TYPE_BUTTON,			//按钮控件
	GUI_TYPE_FRAME,				//框架控件
	GUI_TYPE_PIC,				//图片控件
	GUI_TYPE_ITEMBOX,			//物品栏
	GUI_TYPE_STATICTEXT,		//静态文字
	GUI_TYPE_EDITBOX,			//编辑框控件
	GUI_TYPE_CHECKBOX,			//选择框
	GUI_TYPE_LISTBOX,			//列表框
};

//环境管理器的状态
enum EnvMgrState
{
	ENV_LOGIN,					//登陆界面
	ENV_GAME,					//游戏状态
	ENV_OVER,					//游戏结束
};

//光标的图标标示
enum CursorType
{
	CURSOR_NORMAL	= 0,
	CURSOR_ATK		= 1,
	CURSOR_PICK		= 2,
	CURSOR_NPCTALK	= 3,

};


#define SAFE_DELETE(x)   if ((x)!=NULL){delete (x);(x)=NULL;}
#define SAFE_RELEASE(x)   if ((x)!=NULL){(x)->Release() ;(x)=NULL;}
#define SAFE_DELETE_ARRAY(x)   if ((x)!=NULL){delete[] (x);(x)=NULL;}
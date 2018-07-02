////////////////////////////////////////////////////////////////////////////
//Name:EditBox.h

//文本输入框控件
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Component.h"

class CEditBox : public CComponent
{
public:

	//构造函数
	CEditBox();

	//析构函数
	~CEditBox();

	//绘制组件
	void Draw();

	//处理鼠标移动的事件响应
	void ProcessMouseMove(long x,long y);

	//处理鼠标左键按下的事件响应
	void ProcessMouseLBDown(long x,long y);

	//在用户输入字符后响应
	string HandlePutIn(void);

	//往当前的保存的字符串后面添加一个字符
	void AddChar(char cChar);

	//往当前的保存的字符串后面添加一串字符串
	void AddString(string str);

	//在渲染的过程中根据文本框输入的字数的多少来设定游标的位置
	void SetCursorPos(void);

	//定时器的回调函数,用于控制游标的闪烁
	static void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)	{m_bShowCursor = !m_bShowCursor;}

	//返回m_nowPutIn里的数据(字符串),输出到PAGE里
	const char* GetInputString(void)		{return m_nowPutIn.c_str();}

	//设置字符的宽度
	void SetCharWidth(long lWidth)		{m_lCharWidth = lWidth;}

	//设置字符的高度
	void SetCharHeight(long lHeight)	{m_lCharHeight = lHeight;}

	//设置编辑框是否被激活
	void SetActive(bool bActive);

	//设置游标的左上角的坐标
	void SetCursorLeftUpPos(D3DXVECTOR2 vPos);	

	//设置允许输入的最大的字符串个数
	void SetMaxInput(long lMaxInput)			{m_lMaxInput = lMaxInput;}

	//标示该编辑框是不是用来输入密码的
	void SetBePasswordType(bool bPasswordType)	{m_bPasswordType = bPasswordType;}

	//加载游标的纹理
	bool SetCursorTex(string texFileName);

	//创建字体,用于显示文字
	bool SetFont(void);

	//清空EditBox的内容
	void Clear(void)		{m_nowPutIn.clear();}

	//设置编辑框响应ENTER键的LUA函数名
	void SetResponseKeyEnter(string strKey);

	//响应ENTER键的事件
	void DoResponseKeyEnter();

	//判断输入框有没有被激活
	bool GetBeActive(void)		{return m_bActive;}

protected:

	//判断输入框是否被激活,激活了才可以输入
	bool m_bActive;

	//D3DFont接口指针,用于输出字符
	ID3DXFont* m_pFont;

	//保存输入的文字
	string m_nowPutIn;

	//用于将字符串转换成"*",用来做密码的输出,但实际的对应值还是保存在m_nowPutIn里
	string m_Password;

	//用于文字输出的矩形区域
	RECT m_PutInRect;

	//鼠标的位置
	POINT m_MousePt;

	//游标的纹理
	IDirect3DTexture9* m_pTextureCursor;

	//游标的左上角坐标
	D3DXVECTOR2 m_vCursorLeftUpPos;

	//游标的显示的缩放比例
	D3DXVECTOR2 m_vCursorScale;

	//游标的切换
	static bool m_bShowCursor;

	//游标的位置
	long m_lCursorPos;

	//字符的高度
	long m_lCharHeight;

	//字符的宽度
	long m_lCharWidth;

	//字符的最大输入的数量
	long m_lMaxInput;

	//EditBox的点击区域
	RECT m_ClickedRegion;

	//表示了该EditBox控件是不是用来输入密码的
	bool m_bPasswordType;

	//响应ENTER键的LUA函数名
	string m_strResponseEnterEvent;
};

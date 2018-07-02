//////////////////////////////////////////////////////////////////////////
//Name:ListBox.h
//游戏界面中的列表框对象
//比如用于游戏中的聊天框
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Button.h"

class CListBox : public CComponent
{
public:

	//构造函数
	CListBox();

	//析构函数
	~CListBox();

	//绘制组件
	void Draw();

	//处理鼠标移动的事件响应
	void ProcessMouseMove(long x,long y);

	////处理鼠标左键按下的事件响应
	//void ProcessMouseLBDown(long x,long y);

	//设置ListBox所对应的滚动条本体的Button
	void SetListBoxScrollButton(CButton* pScroll);

	//设置ListBox所对应的滚动条的向上的Button
	void SetListBoxUpButton(CButton* pUp);

	//设置ListBox所对应的滚动条的向下的Button
	void SetListBoxDownButton(CButton* pDown);

	//设置每一行可容纳的最大字节数
	//用整个控件图片的宽度除以字符的宽度
	void SetMaxByteInRaw(void);

	//设置最大行数
	//用整个控件图片的高度除以字符的高度
	void SetMaxRaw(void);

	//往ListBox里添加一条字符串
	void AppendString(string strNew);

	//设置ListBox的字体
	void SetFont();

	//设置字体绘制的格式(对齐方式)
	void SetDrawingFontType(long lType);

	//获取字体绘制的格式(对齐方式)
	long GetDrawingFontType();

	//从m_stackFront中弹出若干条字符串到m_strAllText
	void PopStringFromStackFront(long n);

	//从m_stackBack中弹出若干条字符串到m_strAllText
	void PopStringFromStackBack(long n);

	//清空ListBox
	void Clear();

protected:

	//滚动条本体的Button
	CButton* m_pScroll;

	//滚动条向上的Button
	CButton* m_pUp;

	//滚动条向下的Button
	CButton* m_pDown;

	//ListBox中所有文本的字符串集合
	string m_strAllText;

	//D3D字体对象指针
	ID3DXFont* m_pFont;

	//ListBox的每一行可容纳的最大字节数
	long m_lMaxByteInRaw;

	//ListBox的最大行数
	long m_lMaxRaw;

	//当前字符串所占的行数
	long m_lRawNow;

	//绘制文字的对齐方式
	long m_lFontType;

	//当LISTBOX中实际的行数大于ListBox中显示的最大行数后
	//上面超出的数据就被存放在m_stackFront栈中
	stack<string> m_stackFront;

	stack<string> m_stackBack;
	
};

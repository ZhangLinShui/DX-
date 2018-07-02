//专门用于显示文字的组件

#pragma once
#include "Component.h"

class CStaticText : public CComponent
{
public:

	//构造函数
	CStaticText();

	//析构函数
	~CStaticText();

	//设置输出文字的宽度和高度(当创建一个静态文字组件后,这个接口是必须实现的)
	bool SetCharWidthAndHeight(long lCharWidth,long lCharHeight);	

	//设置输出文字的颜色
	void SetCharColor(DWORD color)									{m_FontColor = color;}

	//设置输出的文字的内容
	void SetOutputText(string str)									{m_strOutputText = str;}

	//渲染文字
	void Draw(void);

	//设置输出的文字在矩形区域中的对齐方式
	void SetAlignStyle(DWORD style)									{m_dwAlignStyle = style;}						

	//设置输出文字的高度
	//void SetCharHeight(long lCharHeight)			{m_lCharHeight = lCharHeight;}

	//设置输出文字的矩形区域
	//void SetTextRect(long left,long top,long right,long bottom);



protected:

	//D3D字体对象
	ID3DXFont* m_pFont;

	//输出的文字的内容
	string m_strOutputText;

	//字体的高度
	long m_lCharHeight;

	//字体的宽度
	long m_lCharWidth;

	//字体的颜色
	D3DCOLOR m_FontColor;

	//输出的文字在矩形区域内的对齐方式
	DWORD m_dwAlignStyle;


};

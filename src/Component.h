//GUI的所有组件的基类
//包括了BUTTON,EDITBOX,MENU,TAB等控件
//还有PAGE等

#pragma once

class CComponent
{
public:

	//组件的状态的枚举值
	enum ButtonState
	{
		COMPONENT_STATE_NORMAL = 0,
		COMPONENT_STATE_MOVETO = 1,
		COMPONENT_STATE_DOWN = 2,
	};

public:

	//构造函数
	CComponent();

	//析构函数
	virtual ~CComponent();

	//设置对象的设备对象
	void SetDevice(IDirect3DDevice9* pDevice)					{m_pDevice = pDevice;}

	//加载脚本
	virtual void Init(TiXmlElement* element)
	{
		this->SetVisible(atoi(element->FirstChildElement("Visible")->GetText()));
		this->SetDrag(atoi(element->FirstChildElement("DragEnable")->GetText()));
		this->SetEventEnable(atoi(element->FirstChildElement("EventEnable")->GetText()));

		this->SetName(element->FirstChildElement("ElementName")->GetText());
		m_ptPos.x = atoi(element->FirstChildElement("Pos")->Attribute("x"));
		m_ptPos.y = atoi(element->FirstChildElement("Pos")->Attribute("y"));


		m_lWidth = atoi(element->FirstChildElement("Size")->Attribute("width"));
		m_lHeight = atoi(element->FirstChildElement("Size")->Attribute("height"));

		m_Alpha = atoi(element->FirstChildElement("Alpha")->GetText());

		this->SetScale(D3DXVECTOR2(atof(element->FirstChildElement("Scale")->Attribute("scalex")), atof(element->FirstChildElement("Scale")->Attribute("scaley"))));
		m_Rect.left = m_ptPos.x;
		m_Rect.top = m_ptPos.y;
		m_Rect.right = m_ptPos.x + m_lWidth;
		m_Rect.bottom = m_ptPos.y + m_lHeight;
		
	}
	//为组件添加子组件,参数一为组件对象,参数二为子组件在父组件中的索引序号
	virtual void AddChild(CComponent* pChild,long index);

	//为组件添加鼠标监听器
	virtual void AddMouseListener();

	//为组件添加键盘监听器
	virtual void AddKeyListener();

	//绘制组件
	virtual void Draw();

	//获得子组件,有两种方法,通过获取子组件的名称,或者获取子组件的索引号
	CComponent* GetChild(string name);
	CComponent* GetChild(long index);

	//处理键盘的事件响应
	virtual void ProcessKeyEvent(char key);

	//处理鼠标移动的事件响应
	virtual void ProcessMouseMove(long x,long y);

	//处理鼠标左键按下的事件响应
	virtual void ProcessMouseLBDown(long x,long y);

	//处理鼠标左键弹起的事件响应
	virtual void ProcessMouseLBUp(long x,long y);

	//处理鼠标右键按下的事件响应
	virtual void ProcessMouseRBDown(long x,long y);

	//处理鼠标右键弹起的事件响应
	virtual void ProcessMouseRBUp(long x,long y);

	//处理鼠标滚轮滚动的事件响应
	virtual void ProcessMouseWheel();

	//设置组件的图片
	void SetPicture(string filename);

	//获得组件的类型
	long GetType(void)							{return m_lType;}
	void SetType(long type)						{ m_lType = type; }
	//获得组件所在客户区域的矩形
	RECT GetRect()								{return m_Rect;}

	//获得组件的宽度
	long GetWidth()								{return m_lWidth;}

	//获得组件的高度
	long GetHeight()							{return m_lHeight;}

	//获得组件在客户区域的矩形的左上角坐标
	D3DXVECTOR2 GetLeftTopPos()					{return m_ptPos;}

	//获得组件的名称
	const char* GetName()						{return m_strName.c_str();}

	//获得父组件对象
	CComponent* GetParent()						{return m_pParent;}

	//设置父组件对象
	void SetParent(CComponent* component)		{m_pParent = component;}

	//判断组件是否可以相应事件
	bool BeEventEnable()						{return m_bEventEnable;}

	//判断组件是否可见
	bool IsVisible()							{return m_bVisible;}

	//设置组件是否可见
	void SetVisible(bool bVisible);

	//设置组件是否可以相应事件
	void SetEventEnable(bool bEventEnable)		{m_bEventEnable = bEventEnable;}

	//设置组件的名字
	void SetName(string name)					{m_strName = name;}

	//设置组件的位置(左上角,通过绝对坐标)
	void SetPos(long x,long y)					{m_ptPos.x = (float)x;m_ptPos.y = (float)y;}

	//设置组件的位置(左上角,通过相对坐标)
	virtual void SetPos(float OffsetX,float OffsetY);

	//设置组件的尺寸
	void SetSize(long width,long height);		

	//设置是否可以拖曳
	void SetDrag(bool bDrag)					{m_bDrag = bDrag;}

	//判断组件是否可以拖曳
	bool BeDrag(void)							{return m_bDrag;}

	//设置组件透明度
	void SetAlpha(DWORD alpha)					{m_bAlpha = true;m_Alpha = alpha;}

	//获得组件透明度
	DWORD GetAlpha(void)							{return m_Alpha;}

	//设置组件的缩放比例
	void SetScale(D3DXVECTOR2 scale)			{m_vScale = scale;}

	//获取组件的缩放比例
	D3DXVECTOR2 GetScale(void)					{return m_vScale;}

	//设置精灵对象(绘制图形时候用的ID3DXSprite接口)
	void SetSprite();


protected:

	//组件的状态
	long m_lState;

	//组件的类型
	long m_lType;

	//组件的名字
	string m_strName;

	//判断组件是否可见
	bool m_bVisible;

	//组件在客户区域的矩形区域
	RECT m_Rect;

	//子组件的map容器,long是索引序列号
	map<long,CComponent*> m_mapChildren;
	map<long,CComponent*>::iterator m_mapChildrenIT;

	//d3d精灵对象
	ID3DXSprite* m_pSprite;

	//判断组件是否能响应事件
	bool m_bEventEnable;

	//d3d纹理对象,组件的图片
	IDirect3DTexture9* m_pPic;

	//组件的宽度
	long m_lWidth;

	//组件的高度
	long m_lHeight;

	//组件的左上角的坐标
	D3DXVECTOR2 m_ptPos;

	//组件的父组件
	CComponent* m_pParent;

	//组件能否拖曳
	bool m_bDrag;

	//组件是否允许ALPHA渲染
	bool m_bAlpha;

	//组件的ALPHA值
	DWORD m_Alpha;

	//组件的缩放比例
	D3DXVECTOR2 m_vScale;

	//组件的位置矩阵
	D3DXMATRIX m_matPos;

	//D3D设备对象
	IDirect3DDevice9* m_pDevice;

public:

	//鼠标移动到了哪个组件上
	static CComponent* m_BeingMovetoComponent;

	//哪个组件被按下
	static CComponent* m_BeingDownComponent;

	//哪个组件处于鼠标跟随状态(只有物品栏组件需要拖动)
	static CComponent* m_BeingWithMouseComponent;

	//判断是否在操作GUI
	static bool m_bProcessGUI;
};

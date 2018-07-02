//GUI����������Ļ���
//������BUTTON,EDITBOX,MENU,TAB�ȿؼ�
//����PAGE��

#pragma once

class CComponent
{
public:

	//�����״̬��ö��ֵ
	enum ButtonState
	{
		COMPONENT_STATE_NORMAL = 0,
		COMPONENT_STATE_MOVETO = 1,
		COMPONENT_STATE_DOWN = 2,
	};

public:

	//���캯��
	CComponent();

	//��������
	virtual ~CComponent();

	//���ö�����豸����
	void SetDevice(IDirect3DDevice9* pDevice)					{m_pDevice = pDevice;}

	//���ؽű�
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
	//Ϊ�����������,����һΪ�������,������Ϊ������ڸ�����е��������
	virtual void AddChild(CComponent* pChild,long index);

	//Ϊ��������������
	virtual void AddMouseListener();

	//Ϊ�����Ӽ��̼�����
	virtual void AddKeyListener();

	//�������
	virtual void Draw();

	//��������,�����ַ���,ͨ����ȡ�����������,���߻�ȡ�������������
	CComponent* GetChild(string name);
	CComponent* GetChild(long index);

	//������̵��¼���Ӧ
	virtual void ProcessKeyEvent(char key);

	//��������ƶ����¼���Ӧ
	virtual void ProcessMouseMove(long x,long y);

	//�������������µ��¼���Ӧ
	virtual void ProcessMouseLBDown(long x,long y);

	//����������������¼���Ӧ
	virtual void ProcessMouseLBUp(long x,long y);

	//��������Ҽ����µ��¼���Ӧ
	virtual void ProcessMouseRBDown(long x,long y);

	//��������Ҽ�������¼���Ӧ
	virtual void ProcessMouseRBUp(long x,long y);

	//���������ֹ������¼���Ӧ
	virtual void ProcessMouseWheel();

	//���������ͼƬ
	void SetPicture(string filename);

	//������������
	long GetType(void)							{return m_lType;}
	void SetType(long type)						{ m_lType = type; }
	//���������ڿͻ�����ľ���
	RECT GetRect()								{return m_Rect;}

	//�������Ŀ��
	long GetWidth()								{return m_lWidth;}

	//�������ĸ߶�
	long GetHeight()							{return m_lHeight;}

	//�������ڿͻ�����ľ��ε����Ͻ�����
	D3DXVECTOR2 GetLeftTopPos()					{return m_ptPos;}

	//������������
	const char* GetName()						{return m_strName.c_str();}

	//��ø��������
	CComponent* GetParent()						{return m_pParent;}

	//���ø��������
	void SetParent(CComponent* component)		{m_pParent = component;}

	//�ж�����Ƿ������Ӧ�¼�
	bool BeEventEnable()						{return m_bEventEnable;}

	//�ж�����Ƿ�ɼ�
	bool IsVisible()							{return m_bVisible;}

	//��������Ƿ�ɼ�
	void SetVisible(bool bVisible);

	//��������Ƿ������Ӧ�¼�
	void SetEventEnable(bool bEventEnable)		{m_bEventEnable = bEventEnable;}

	//�������������
	void SetName(string name)					{m_strName = name;}

	//���������λ��(���Ͻ�,ͨ����������)
	void SetPos(long x,long y)					{m_ptPos.x = (float)x;m_ptPos.y = (float)y;}

	//���������λ��(���Ͻ�,ͨ���������)
	virtual void SetPos(float OffsetX,float OffsetY);

	//��������ĳߴ�
	void SetSize(long width,long height);		

	//�����Ƿ������ҷ
	void SetDrag(bool bDrag)					{m_bDrag = bDrag;}

	//�ж�����Ƿ������ҷ
	bool BeDrag(void)							{return m_bDrag;}

	//�������͸����
	void SetAlpha(DWORD alpha)					{m_bAlpha = true;m_Alpha = alpha;}

	//������͸����
	DWORD GetAlpha(void)							{return m_Alpha;}

	//������������ű���
	void SetScale(D3DXVECTOR2 scale)			{m_vScale = scale;}

	//��ȡ��������ű���
	D3DXVECTOR2 GetScale(void)					{return m_vScale;}

	//���þ������(����ͼ��ʱ���õ�ID3DXSprite�ӿ�)
	void SetSprite();


protected:

	//�����״̬
	long m_lState;

	//���������
	long m_lType;

	//���������
	string m_strName;

	//�ж�����Ƿ�ɼ�
	bool m_bVisible;

	//����ڿͻ�����ľ�������
	RECT m_Rect;

	//�������map����,long���������к�
	map<long,CComponent*> m_mapChildren;
	map<long,CComponent*>::iterator m_mapChildrenIT;

	//d3d�������
	ID3DXSprite* m_pSprite;

	//�ж�����Ƿ�����Ӧ�¼�
	bool m_bEventEnable;

	//d3d�������,�����ͼƬ
	IDirect3DTexture9* m_pPic;

	//����Ŀ��
	long m_lWidth;

	//����ĸ߶�
	long m_lHeight;

	//��������Ͻǵ�����
	D3DXVECTOR2 m_ptPos;

	//����ĸ����
	CComponent* m_pParent;

	//����ܷ���ҷ
	bool m_bDrag;

	//����Ƿ�����ALPHA��Ⱦ
	bool m_bAlpha;

	//�����ALPHAֵ
	DWORD m_Alpha;

	//��������ű���
	D3DXVECTOR2 m_vScale;

	//�����λ�þ���
	D3DXMATRIX m_matPos;

	//D3D�豸����
	IDirect3DDevice9* m_pDevice;

public:

	//����ƶ������ĸ������
	static CComponent* m_BeingMovetoComponent;

	//�ĸ����������
	static CComponent* m_BeingDownComponent;

	//�ĸ��������������״̬(ֻ����Ʒ�������Ҫ�϶�)
	static CComponent* m_BeingWithMouseComponent;

	//�ж��Ƿ��ڲ���GUI
	static bool m_bProcessGUI;
};

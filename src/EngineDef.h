//����ģ��,ϵͳ�Լ���������һЩ��������

#pragma once
//ģ�͵İ�Χ�͵İ˸�����
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
//���ߵĵ����ɫ
struct CUSTOMVERTEXLINE {
	D3DXVECTOR3 start;
	DWORD		color;
};

enum MyEnum
{
	LEFT = 1,//���﷽��
	RIGHT,
	UP
};
//�����еĶ��������
enum ObjectType
{
	OB_TYPE_NOTYPE,				//������
	OB_TYPE_MAP,				//��ͼ
	OB_TYPE_PLAYER,				//���
	OB_TYPE_NPC,				//NPC
	OB_TYPE_MONSTER,			//����
	OB_TYPE_CAMERA,			//���
	OB_TYPE_SKY,			//���
	OB_TYPE_Light,			//���
	OB_TYPE_WATER,			//���
	OB_TYPE_BRIDGE,			//���
	OB_TYPE_HOURSE,			//���
	OB_TYPE_MODEL,			//����ģ��
	OB_TYPE_MODEL_COPY,		//�ɸ��û���ģ�͵�����
	OB_TYPE_ANIMATION_MESH,	//����ģ��	
	OB_TYPE_PARTICLE		//����

};
//����¼���ö��ֵ
enum MOUSEEVENT
{
	MOUSE_NONE,
	MOUSE_LB_DOWN,				//�������
	MOUSE_LB_UP,				//�������
	MOUSE_LB_DCLICK,			//���˫��

	MOUSE_RB_DOWN,				//�Ҽ�����
	MOUSE_RB_UP,				//�Ҽ�����
	MOUSE_RB_DCLICK,			//�Ҽ�˫��

	MOUSE_MB_DOWN,				//�м�����
	MOUSE_MB_UP,				//�м�����
	MOUSE_MB_DCLICK,			//�м�˫��

	MOUSE_MB_WHEEL,
};
//GUI���������
enum GUIComponentType
{
	GUI_TYPE_NOTYPE,			//������
	GUI_TYPE_BUTTON,			//��ť�ؼ�
	GUI_TYPE_FRAME,				//��ܿؼ�
	GUI_TYPE_PIC,				//ͼƬ�ؼ�
	GUI_TYPE_ITEMBOX,			//��Ʒ��
	GUI_TYPE_STATICTEXT,		//��̬����
	GUI_TYPE_EDITBOX,			//�༭��ؼ�
	GUI_TYPE_CHECKBOX,			//ѡ���
	GUI_TYPE_LISTBOX,			//�б��
};

//������������״̬
enum EnvMgrState
{
	ENV_LOGIN,					//��½����
	ENV_GAME,					//��Ϸ״̬
	ENV_OVER,					//��Ϸ����
};

//����ͼ���ʾ
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
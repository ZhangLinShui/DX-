//������,һ��PAGE��һ�����,���е����еĿؼ��������������
//��������PAGE����ʾ������,Ҳ������PAGE����ҷ

#pragma once
#include "Component.h"

class CFrame : public CComponent
{
public:
	//���캯��
	CFrame();

	//��������
	~CFrame();

	void Init(TiXmlElement* element);
	//�������������µ��¼���Ӧ
	void ProcessMouseLBDown(long x,long y);

	//����������������¼���Ӧ
	void ProcessMouseLBUp(long x,long y);

	//��������ƶ����¼���Ӧ
	void ProcessMouseMove(long x,long y);

};

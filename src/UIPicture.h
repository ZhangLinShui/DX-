//��ͨ��ͼƬ�ؼ�,��CComponent����������
#pragma once

#include "Component.h"

class CUIPicture : public CComponent
{

public:

	//���캯��
	CUIPicture();
	void Init(TiXmlElement* element);
	//��������
	~CUIPicture();

	//����ͼƬ
	void ChangePic(string filename);


};

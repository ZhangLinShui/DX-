//普通的图片控件,从CComponent中派生出来
#pragma once

#include "Component.h"

class CUIPicture : public CComponent
{

public:

	//构造函数
	CUIPicture();
	void Init(TiXmlElement* element);
	//析构函数
	~CUIPicture();

	//更换图片
	void ChangePic(string filename);


};

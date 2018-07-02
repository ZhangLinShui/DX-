//平台类，存储公共数据

#pragma once

class CPlatform:public Singleton<CPlatform>
{
public:
	void				AddResource(string key,void* res);//添加资源
	void				DelResource(string key);//删除指定的资源
	void*				FindResource(string key);//查找资源

protected:
	map<string,void*>		_mapPlat;//排序二叉树结构去保存资源
};



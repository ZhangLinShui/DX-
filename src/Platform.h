//ƽ̨�࣬�洢��������

#pragma once

class CPlatform:public Singleton<CPlatform>
{
public:
	void				AddResource(string key,void* res);//�����Դ
	void				DelResource(string key);//ɾ��ָ������Դ
	void*				FindResource(string key);//������Դ

protected:
	map<string,void*>		_mapPlat;//����������ṹȥ������Դ
};



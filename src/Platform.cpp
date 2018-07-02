#include "stdafx.h"

void	CPlatform::AddResource(string key, void *res)
{
	_mapPlat[key] = res;
}

void CPlatform::DelResource(string key)
{
	map<string,void*>::iterator it = _mapPlat.find(key);
	delete (it->second);
	_mapPlat.erase(it);
}

void*	CPlatform::FindResource(string key)
{
	map<string,void*>::iterator it = _mapPlat.find(key);
	return (it->second);
}
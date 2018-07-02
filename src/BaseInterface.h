#pragma once
class CBaseInterface
{
public:
	CBaseInterface();
	virtual ~CBaseInterface();
	
private:
	string m_strInterfaceName;
};

void DoGlobeEvent(string name);
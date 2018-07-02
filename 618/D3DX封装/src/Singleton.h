#pragma once
template<typename T>
class Singleton
{
protected:
	Singleton() {}
	~Singleton() {}
private:
	static T* singlenPtr;


public:
	static T* GetsinglenPtr()
	{
		if (!singlenPtr)
			singlenPtr = new T;
		return singlenPtr;
	}

};

template<typename T>
T*Singleton<T>::singlenPtr = nullptr;
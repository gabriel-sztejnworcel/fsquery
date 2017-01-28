
#ifndef CMEMGUARD_H
#define CMEMGUARD_H

#include <iostream>

template <typename T>
class CMemGuard
{
public:
	CMemGuard(T* ptr) : m_ptr(ptr) {}
	
	~CMemGuard()
	{
		if (m_ptr != nullptr)
		{
			free(m_ptr);
		}
	}
	
	T* Get()
	{
		return m_ptr;
	}

private:
	T* m_ptr;
};

#endif // CMEMGUARD_H

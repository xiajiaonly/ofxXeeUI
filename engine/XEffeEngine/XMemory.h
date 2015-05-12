#ifndef _JIA_XMEMORY_
#define _JIA_XMEMORY_

#include "string.h"
namespace XE{

namespace XMem
{
	template<typename T>
	inline void XDELETE(T *&p)
	{
		if (p == NULL) return;
		delete p;
		p = NULL;
	}
	template<typename T>
	inline void XDELETE_ARRAY(T *&p)
	{
		if (p == NULL) return;
		delete[] p;
		p = NULL;
	}
	template<typename T>
	inline T * createMem()
	{
		try
		{
			return new T;
		}
		catch (...)
		{
			return NULL;
		}
	}
	template<typename T>
	inline T * createArrayMem(int size)
	{
		if (size <= 0) return NULL;
		try
		{
			return new T[size];
		}
		catch (...)
		{
			return NULL;
		}
	}

	extern unsigned char *spliceData(unsigned char * baseBuff, int &baseLen, int &offset, const unsigned char * addBuff, int len);
}
}
#endif
#ifndef _JIA_XCIRCLEGROUP_
#define _JIA_XCIRCLEGROUP_

#include "XBasicClass.h"
#include "XOSDefine.h"
#ifdef XEE_OS_LINUX
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#endif
namespace XE{
template<class Type> class XCircleGroup
{
private:
    XBool m_isInited;
    int m_insertPoint;
    int m_popPoint;
    int m_buffSize;

    struct XElement
    {
        XBool isEnable;
        Type elementData;
    };
    XElement *m_pElement;
	pthread_mutex_t m_mutex;
    int m_mode;
private:
	XCircleGroup(const XCircleGroup & temp){}
public:
    XCircleGroup()
    :m_isInited(XFalse)
    ,m_insertPoint(0)
    ,m_popPoint(0)
    ,m_buffSize(0)
    ,m_pElement(NULL)
    ,m_mode(0)
    {}
	XBool init(int buffsize,int mode = 0)
	{
		if(m_isInited ||
			buffsize <= 0) return XFalse;
		m_insertPoint = 0;
		m_popPoint = 0;
		m_buffSize = buffsize;
		m_pElement = NULL;
		m_mode = mode;
		m_pElement = XMem::createArrayMem<XElement>(m_buffSize);
		if(m_pElement == NULL) return XFalse;

		for(int i = 0;i < m_buffSize;++ i)
		{
			m_pElement[i].isEnable = XFalse;
		}

		m_isInited = XTrue;
		return XTrue;
	}
	int insertOneElement(Type &element)
	{
		if(!m_isInited) return 0;
		pthread_mutex_lock(m_mutex);
		if(!m_pElement[m_insertPoint].isEnable)
		{
			m_pElement[m_insertPoint].elementData = element;
			m_pElement[m_insertPoint].isEnable = XTrue;
			++ m_insertPoint;
			if(m_insertPoint >= m_buffSize) m_insertPoint = 0;
			pthread_mutex_unlock(m_mutex);
			return 1;
		}else
		{

			if(m_mode == 0)
			{

				m_pElement[m_insertPoint].elementData = element;
				m_pElement[m_insertPoint].isEnable = XTrue;
				++ m_insertPoint;
				if(m_insertPoint >= m_buffSize) m_insertPoint = 0;
				++ m_popPoint;
				if(m_popPoint >= m_buffSize) m_popPoint = 0;
			}

			pthread_mutex_unlock(m_mutex);
			return 2;
		}
	}
	XBool popOneElement(Type &element)
	{
		if(!m_isInited) return XFalse;
		pthread_mutex_lock(m_mutex);
		if(m_pElement[m_popPoint].isEnable != 0)
		{
			element = m_pElement[m_popPoint].elementData;
			m_pElement[m_popPoint].isEnable = XFalse;
			++ m_popPoint;
			if(m_popPoint >= m_buffSize) m_popPoint = 0;
			pthread_mutex_unlock(m_mutex);
			return XTrue;
		}
		pthread_mutex_unlock(m_mutex);
		return XFalse;
	}
    XBool isEmpty() const
    {
        if(!m_isInited) return XTrue;
        return !m_pElement[m_popPoint].isEnable;
    }
	XBool isFull() const
	{
		if(!m_isInited) return XFalse;
		return m_pElement[m_insertPoint].isEnable;
	}
};
}
#endif


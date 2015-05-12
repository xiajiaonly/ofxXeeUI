#ifndef _JIA_XSMARTPOINTER_
#define _JIA_XSMARTPOINTER_

#include "stdio.h"
#include "XBasicFun.h"
namespace XE{

template<class T> class XSmartP;

template<class T> class XBackP
{
private:
    friend XSmartP<T>;
    T *m_p;
    size_t m_counter;
    XBackP(T *p)
		:m_p(p)
		,m_counter(1)
    {

    }
public:
    ~XBackP()
    {
        XMem::XDELETE(m_p);

    }
};

template<class T> class XSmartP
{
public:

    XSmartP(T *p)
		:m_backP(new XBackP<T>(p))
    {

    }
    XSmartP()
		:m_backP(new XBackP<T>(new T()))
    {

    }

    XSmartP(const XSmartP& temp)
		:m_backP(temp.m_backP)
    {
		++m_backP->m_counter;

    }

    XSmartP<T>& operator=(const XSmartP<T>&temp)
	{
		if(this == &temp) return *this;

		++temp.m_backP->m_counter;

		if (--m_backP->m_counter == 0)
		{
			XMem::XDELETE(m_backP);
		}
		m_backP = temp.m_backP;
		return *this;
	}

    ~XSmartP()
    {

		if (--m_backP->m_counter == 0)
		{
			XMem::XDELETE(m_backP);
		}
    }

    T *getPtr() const
    {
        return m_backP->m_p;
    }

    T getVal() const
    {
        return *m_backP->m_p;
    }
    void setVal(T val)
    {
        *m_backP->m_p = val;
    }
private:
    XBackP<T> *m_backP;
};

template<class T> class XSmartPArray;

template<class T> class XBackPArray
{
private:
    friend XSmartPArray<T>;
    T *m_p;
    size_t m_counter;
    XBackPArray(T p[])
		:m_p(p)
		,m_counter(1)
    {

    }
public:
    ~XBackPArray()
    {
        XMem::XDELETE_ARRAY(m_p);

    }
};

template<class T> class XSmartPArray
{
public:
	XSmartPArray()
		:m_backP(new XBackPArray<T>(new T[2]))
		,m_size(2)
	{

	}

    XSmartPArray(T p[],int size)
		:m_backP(new XBackPArray<T>(p))
		,m_size(size)
    {

    }
    XSmartPArray(int size)
		:m_backP(new XBackPArray<T>(new T[size]))
		,m_size(size)
    {

    }

    XSmartPArray(const XSmartPArray& temp)
		:m_backP(temp.m_backP)
		,m_size(temp.m_size)
    {
		++m_backP->m_counter;

    }

    XSmartPArray<T>& operator=(const XSmartPArray<T>&temp)
	{
		if(this == &temp) return *this;

		++temp.m_backP->m_counter;

		if (--m_backP->m_counter == 0)
		{
			XMem::XDELETE(m_backP);
		}
		m_backP = temp.m_backP;
		m_size = temp.m_size;
		return *this;
	}
 	T& operator[](int order)const
	{

		return m_backP->m_p[order];
	}
 	T& operator[](int order)
	{

		return m_backP->m_p[order];
	}

    ~XSmartPArray()
    {

		if (--m_backP->m_counter == 0)
		{
			XMem::XDELETE(m_backP);
		}
    }

    T *getPtr() const
    {
        return m_backP->m_p;
    }

    T getVal(int order) const
    {
		if(order < 0 || order >= m_size) order = 0;
		return m_backP->m_p[order];
    }
    void setVal(T val,int order)
    {
		if(order < 0 || order >= m_size) order = 0;
        m_backP->m_p[order] = val;
    }
private:
    XBackPArray<T> *m_backP;
	int m_size;
};
}
#endif
#ifndef _JIA_XSMOOTHLINE_
#define _JIA_XSMOOTHLINE_

#include "XBasicClass.h"
#include <deque>
namespace XE{
class XSmoothPoint
{
public:
	XVector2 m_position;
	float m_length;
	float m_percentage;
};
class XSmoothLine
{
protected:
	bool m_isInited;
	std::deque<XSmoothPoint *> m_points;
	int m_insertSum;
	float m_insertLength;

	virtual void release();
	virtual void pushAPoint(const XVector2 &p);
	virtual void updateData();
public:
	XSmoothLine()
		:m_isInited(false)
		,m_insertSum(1)
		,m_insertLength(1.0f)
	{}
	virtual ~XSmoothLine() {release();}
	virtual bool init(int insertSum,float insertLength);
	virtual void draw();
	virtual void addAPoint(const XVector2 & p);

	virtual int getPointSum() const {return m_points.size();}
	virtual void clear()
	{
		for(unsigned int i = 0;i < m_points.size();++ i)
		{
			XMem::XDELETE(m_points[i]);
		}
		m_points.clear();
	}
	virtual bool getIsEnd(){return m_points.size() <= 0;}
};
}
#endif
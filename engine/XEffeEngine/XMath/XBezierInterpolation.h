#ifndef _JIA_XBEZIERINTERPOLATION_
#define _JIA_XBEZIERINTERPOLATION_

#include "XOSDefine.h"
namespace XE{
class XBezierInterpolation
{
private:
	float m_p0;
	float m_p1;
	float m_p2;
	float m_p3;
public:
	float getBezierSplineValue(float temp);

	float m_curValue;
	float m_curPosition;
	float m_speed;
	XBool m_isEnd;
	void move(int timeDelay);
	XBezierInterpolation();
	void init(float p0,float p1,float p2,float p3);
	void reset();
};
inline void XBezierInterpolation::init(float p0,float p1,float p2,float p3)
{
	m_p0 = p0;
	m_p1 = p1;
	m_p2 = p2;
	m_p3 = p3;
}
inline void XBezierInterpolation::reset()
{
	m_curPosition = 0.0f;
	m_isEnd = XFalse;
	m_curValue = m_p0;
}
}
#endif
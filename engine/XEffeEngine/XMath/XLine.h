#ifndef _JIA_XLINE_
#define _JIA_XLINE_

#include "XBasicFun.h"
#include "XVector2.h"
namespace XE{

class XLine
{
private:
	XVector2 m_startPosition;
	XVector2 m_endPosition;
	XBool m_isEnable;
public:
	double A,B,C;
	double m_data0;
	double m_data1;
	double m_angle;
public:
	void set(const XVector2 &startPosition,const XVector2 &endPosition);
	void set(float startX,float startY,float endX,float endY);
	float getLineLength() const;
	float getLineAngle() const;
	XVector2 getStartPosition() const;
	XVector2 getEndPosition() const;
	void setStartPosition(const XVector2& startPosition);
	void setStartPosition(float x,float y);
	void setEndPosition(const XVector2& endPosition);
	void setEndPosition(float x,float y);
	XBool getIsEnable() const{return m_isEnable;}
	void setEnable(XBool temp){m_isEnable = temp;}
	XLine()
	:m_isEnable(XFalse)
	,A(0.0)
	,B(0.0)
	,C(0.0)
	,m_data0(0.0)
	,m_data1(0.0)
	,m_angle(0.0)
	,m_startPosition(0.0f,0.0f)
	,m_endPosition(1.0f,1.0f)
	{}
};
#if WITH_INLINE_FILE
#include "XLine.inl"
#endif
}
#endif
#ifndef _JIA_XWINDLINE_
#define _JIA_XWINDLINE_

#include "XSmoothLine.h"
namespace XE{
class XWindLine:public XSmoothLine
{
private:
	std::deque<float> m_pointsLife;
	float m_maxLife;
	float m_wRate;
	float m_aRate;
	XFColor m_color;

	virtual void release();
	virtual void pushAPoint(const XVector2 &p,float life);
public:

	bool init(int insertSum,float insertLength,float life,float w,float a);
	virtual void draw();
	virtual void addAPoint(const XVector2 & p);
	virtual void move(int stepTime);
	virtual void clear();
	XWindLine()
		:m_color(0.6f,0.6f,1.0f,1.0f)
	{}
	void setColor(const XFColor& c) {m_color = c;}
	XFColor getColor() {return m_color;}
};
#if WITH_INLINE_FILE
#include "XWindLine.inl"
#endif
}
#endif
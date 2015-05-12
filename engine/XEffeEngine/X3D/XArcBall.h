#ifndef _JIA_XARCBALL_
#define _JIA_XARCBALL_

#include "XBasicClass.h"
namespace XE{
class XArcBall
{
protected:
	bool m_isInited;
	XVector3 m_clickVector;
	XVector3 m_dragVector;
	float m_sizeWRate;
	float m_sizeHRate;

	void mapToSphere(const XVector2 &point,XVector3& vec) const;
public:
	XArcBall(float width,float height)
		:m_isInited(false)
	{
		setSize(width,height);
	}
	XArcBall()
		:m_isInited(false)
	{}
	~XArcBall() {};
	bool setSize(float w,float h)
	{
		if(w <= 1.0f || h <= 1.0f) return false;
		m_sizeWRate = 2.0f / (w - 1.0f);
		m_sizeHRate = 2.0f / (h - 1.0f);
		m_isInited = true;
		return true;
	}
	void click(const XVector2 &point){mapToSphere(point,m_clickVector);}
	void drag(const XVector2 &point,XVector4& rotate);
};
}
#endif
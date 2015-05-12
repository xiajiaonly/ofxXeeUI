#ifndef _JIA_XEQUIDISTANTITERPOLATION_
#define _JIA_XEQUIDISTANTITERPOLATION_

#include "XMath.h"
#include "XVector2.h"

#include <vector>
namespace XE{
class XEquidistantIterpolation
{
private:
	bool m_isFirstData;
	float m_upLength;
	XVector2 m_upPoint;
	float m_distance;
public:
	XEquidistantIterpolation()
		:m_isFirstData(true)
		, m_upLength(0.0f)
		, m_distance(10.0f)
	{}
	void setDistance(float d)
	{
		if (d <= 0) return;
		m_distance = d;
	}
	float getDistance() const { return m_distance; }
	void reset()
	{
		m_isFirstData = true;
		m_upLength = 0.0f;
	}
	void reset(const XVector2 &p)
	{
		m_upLength = 0.0f;
		m_isFirstData = false;
		m_upPoint = p;
	}

	std::vector<XVector2> calPoint(const XVector2 &p)
	{
		std::vector<XVector2> ret;
		calPoint(p,ret);
		return ret;
	}
	int calPoint(const XVector2 &p,std::vector<XVector2> &data);
};
}
#endif
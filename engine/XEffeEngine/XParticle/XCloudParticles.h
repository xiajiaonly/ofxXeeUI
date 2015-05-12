#ifndef _JIA_XCLOUDPARTICLES_
#define _JIA_XCLOUDPARTICLES_

#include "XParticle.h"
namespace XE{
class XCloudParticles
{
private:
	char m_isInited;
	char m_isEnd;
	char m_isSetEnd;

	float m_curCenterPoint;
	float m_maxCenterPoint;
	float m_minCenterPoint;
	float m_maxSize;
	float m_minSize;
	float m_curSize;
	float m_density;
	XRect m_liveArea;
	XVector2 m_speed;

	int m_maxAtomSum;
	XAloneParticles *m_atom;

	const XTexture *m_texture;

public:
	int init(float maxCenterPoint,float minCenterPoint,float maxSize,float minSize,
		float density,const XRect& liveArea,const XVector2& speed,int maxAtomSum,const XTexture *tex);
	void reset();
	void move(int timeDelay);
	void draw() const;
	void release();
	void setEnd();
	XCloudParticles();
};
inline void XCloudParticles::release()
{
	if(m_isInited == 0) return;
	XMem::XDELETE_ARRAY(m_atom);
	m_isInited = 0;
}

inline void XCloudParticles::setEnd()
{
	if(m_isInited == 0 ||
		m_isEnd != 0 ||
		m_isSetEnd != 0) return;
	m_isSetEnd = 1;
}
}
#endif
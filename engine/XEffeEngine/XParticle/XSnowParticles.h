#ifndef _JIA_XSNOWPARTICLES_
#define _JIA_XSNOWPARTICLES_

#include "XEchoParticles.h"
namespace XE{
class XSnowParticles
{
private:
	char m_isInited;
	char m_isEnd;
	char m_isSetEnd;

	XVector2 m_productArea;
	XRect m_liveArea;
	XVector2 m_flySpeed;

	int m_maxAtomSum;
	float m_snowDensity;

	XAloneParticles *m_atom;

	const XTexture *m_texture;

public:
	int init(const XVector2& productArea,const XRect& liveArea,const XVector2& flySpeed,
		int maxAtomSum,float snowDensity,const XTexture *texture);
	void reset();
	void move(int timeDelay);
	void draw() const;
	void release()
	{
		if(m_isInited == 0) return;
		XMem::XDELETE_ARRAY(m_atom);
		m_isInited = 0;
	}
	void setEnd()
	{
		if(m_isInited == 0 ||
			m_isEnd != 0 ||
			m_isSetEnd != 0) return;

		m_isSetEnd = 1;
	}
	XSnowParticles();
};
}
#endif
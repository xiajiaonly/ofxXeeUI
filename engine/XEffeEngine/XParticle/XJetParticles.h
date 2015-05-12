#ifndef _JIA_XJETPARTICLES_
#define _JIA_XJETPARTICLES_

#include "XEchoParticles.h"
namespace XE{
class XJetParticles
{
private:
	char m_isInited;
	char m_isEnd;
	char m_isSetEnd;

	float m_directionAngle;
	float m_jetAngle;
	float m_jetDensity;
	XVector2 m_curPosition;

	float m_initSpeed;

	XEchoParticles *m_atomBasic;
	XEchoParticles *m_atom;
	int m_maxAtomSum;
	int m_curAtomPoint;
	int m_timer;

	const XTexture *m_texture;

	const XTexture *m_textureAtom;

public:
	int init(const XVector2& position,float jetSpeed,float jetAngle,float jetDensity,
		const XTexture *texture,const XTexture *textureAton = NULL);
	void reset(const XVector2& position);
	void reset(float x,float y);
	void move(int timeDelay);
	void setPosition(const XVector2& position);
	void setPosition(float x,float y);
	void draw() const;
	void release();
	void setEnd();

	XJetParticles();
};

inline void XJetParticles::setEnd()
{
	if(m_isInited == 0 ||
		m_isEnd != 0 ||
		m_isSetEnd != 0) return;
	m_isSetEnd = 1;
	m_atomBasic->setEnd();
}

inline void XJetParticles::setPosition(const XVector2& position)
{
	if(m_isInited == 0 ||
		m_isEnd != 0) return;

	m_directionAngle = m_curPosition.getAngle(position);
	m_curPosition = position;
	m_atomBasic->setPosition(position);
}

inline void XJetParticles::setPosition(float x,float y)
{
	if(m_isInited == 0 ||
		m_isEnd != 0) return;

	m_directionAngle = m_curPosition.getAngle(x,y);
	m_curPosition.set(x,y);
	m_atomBasic->setPosition(x,y);
}
}
#endif
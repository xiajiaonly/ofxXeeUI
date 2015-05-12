#ifndef _JIA_XPARTICLE_
#define _JIA_XPARTICLE_

#include "../XBasicClass.h"
#include "../XSprite.h"
#include "../XBasicOpenGL.h"
namespace XE{

class XBasicParticle
{
public:
	char m_isEnable;

	XVector2 m_initPosition;
	XVector2 m_initSize;
	float m_initAngle;
	XFColor m_initColor;

	XVector2 m_dPosition;
	XVector2 m_dSize;
	float m_dAngle;
	XFColor m_dColor;

	XVector2 m_curPosition;
	XVector2 m_curSize;
	float m_curAngle;
	XFColor m_curColor;
	XBasicParticle()
		:m_isEnable(0)
	{}
	virtual~XBasicParticle(){}
};
enum
{
	STAGE_SLEEP,
	STAGE_MOVE,
	STAGE_STILL,
	STAGE_STEALTHY
};

class XParentParticle:public XBasicParticle
{
public:
	char m_stage;

	XParentParticle();
	virtual~XParentParticle(){}
};
class XAloneParticles:public XParentParticle
{
public:
	char m_isInited;
private:
	const XTexture *m_texture;

	int halfW;
	int halfH;
	int m_glListOrder;
public:
	int init(const XTexture *texture);
	void draw() const;
	XAloneParticles();

	void move(int timeDelay);
};
inline void XAloneParticles::move(int timeDelay)
{
	if(m_isInited == 0 ||
		m_stage == STAGE_SLEEP) return;

	m_curPosition += m_dPosition * (float)timeDelay;
}
}
#endif
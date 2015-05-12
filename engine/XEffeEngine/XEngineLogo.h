#ifndef _JIA_XENGINELOGO_
#define _JIA_XENGINELOGO_

#include "XSprite.h"
namespace XE{
class XEngineLogo
{
private:
	XResourcePosition m_resoursePosition;
	XBool m_isInited;
	XBool m_mode;
	XVector2 m_position;
	XSprite m_back;
	XSprite m_logoBack;
	XSprite m_logoLight;
	XSprite m_logoMiddle;
	XSprite m_logoTextX;
	XSprite m_logoTextE;
	XSprite m_logoTextEC;
	XSprite m_logoTextRE;

	int m_logoStage;
	float m_xAlpha;
	float m_xSize;
	float m_dxLight;
	float m_eAlpha;

	char m_stageFlag[8];

	void setPosition(const XVector2 &position);

public:
	XBool init(const XVector2 &position,XResourcePosition resoursePosition,XBool mode = true);
	void move(int timeDelay);
	void reset();
	void draw();
	XEngineLogo();
	~XEngineLogo();
	void setBackSize(const XVector2 &size);
	void setBackSize(float x,float y);

	void setSize(const XVector2 &size);
	XBool release();
	XBool getIsEnd();
};

inline void XEngineLogo::setPosition(const XVector2 &position)
{
	m_position = position;
}
inline void XEngineLogo::setBackSize(const XVector2 &size)
{
	m_back.setScale(size);
}
inline void XEngineLogo::setBackSize(float x,float y)
{
	m_back.setScale(x,y);
}
inline XBool XEngineLogo::getIsEnd()
{
	if(!m_isInited) return XFalse;
	return m_logoStage == -2;
}
}
#endif
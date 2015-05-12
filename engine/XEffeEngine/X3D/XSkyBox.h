#ifndef _JIA_XSKYBOX_
#define _JIA_XSKYBOX_

#include "XBasicFun.h"
#include "XTextureInformation.h"
#include "XCam.h"
namespace XE{

class XSkyBox
{
private:
	XBool m_isInited;
	XTextureData m_texture[6];
	float m_top;
	float m_bottom;
	float m_front;
	float m_back;
	float m_left;
	float m_right;
public:
	void setBox(float top,float bottom,float left,float right,float front,float back)
	{
		m_top = top;
		m_bottom = bottom;
		m_left = left;
		m_right = right;
		m_front = front;
		m_back = back;
	}

	XBool init(const char *filename,XResourcePosition resourcePosition = RESOURCE_SYSTEM_DEFINE);
	void draw();

	XSkyBox()
		:m_isInited(XFalse)
		,m_top(-100.0f)
		,m_bottom(100.0f)
		,m_front(100.0f)
		,m_back(-100.0f)
		,m_left(-100.0f)
		,m_right(100.0f)
	{}
	~XSkyBox() {release();}
	void release()
	{
		if(!m_isInited) return;
		m_isInited = XFalse;
	}
};
}
#endif

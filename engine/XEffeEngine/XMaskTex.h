#ifndef _JIA_XMASKTEX_
#define _JIA_XMASKTEX_

#include "XMath\XVector2.h"
#include "XMath\XRect.h"
#include "XOSDefine.h"
namespace XE{
class XMaskTex
{
private:
	XBool m_isInited;
	XVector2 m_sourcePixelSize;
	XVector2 m_curPixelSize;
	unsigned char * m_pixelData;

	XVector2 m_position;
	XVector2 m_scale;
	XRect m_rect;
public:
	XBool init(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	void setPosition(float x,float y)
	{
		m_position.set(x,y);
		m_rect.set(m_position.x,m_position.y,
			m_position.x + m_sourcePixelSize.x * m_scale.x,m_position.y + m_sourcePixelSize.y * m_scale.y);
	}
	void setPosition(const XVector2 &pos){setPosition(pos.x,pos.y);}
	void setScale(float x,float y)
	{
		m_scale.set(x,y);
		m_rect.set(m_position.x,m_position.y,
			m_position.x + m_sourcePixelSize.x * m_scale.x,m_position.y + m_sourcePixelSize.y * m_scale.y);
	}
	void setScale(const XVector2 &scale){setScale(scale.x,scale.y);}
	XBool getIsMask(float x,float y) const;
	XBool getIsMask(const XVector2 &pos) const{getIsMask(pos.x,pos.y);}

	XMaskTex()
		:m_isInited(XFalse)
		,m_pixelData(NULL)
		,m_position(0.0f,0.0f)
		,m_scale(1.0f,1.0f)
	{}
	~XMaskTex(){release();}
	void release()
	{
		if(!m_isInited) return;
		XMem::XDELETE_ARRAY(m_pixelData);

		m_isInited = XFalse;
	}
};
}
#endif

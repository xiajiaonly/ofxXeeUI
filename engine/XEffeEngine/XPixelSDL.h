#ifndef _JIA_XPIXELSDL_
#define _JIA_XPIXELSDL_

#include "XPixelCore.h"
#include "XBasicWindow.h"
namespace XE{
class XPixelSDL:public XPixelCore
{
public:
	XPixelSDL(){}
	virtual ~XPixelSDL() {release();}
	virtual void release()
	{
		if(!isInited) return;
		XMem::XDELETE_ARRAY(m_pPixels);
		isInited = false;
	}
	virtual unsigned char * getPixel() {return m_pPixels;}
	virtual int getWidth() const {return w;}
	virtual int getHeight() const {return h;}
	virtual XColorMode getColorMode() const {return m_colorMode;}
	virtual bool getIsInited() const {return isInited;}

	virtual bool load(const std::string &filename,XResourcePosition resPos = RESOURCE_SYSTEM_DEFINE);

	virtual bool fitNPot();
	virtual bool create(int width,int height,XColorMode mode = COLOR_RGB)
	{
		if(isInited ||
			width <= 0 || height <= 0) return false;
		w = width;
		h = height;
		m_colorMode = mode;

		switch(mode)
		{
		case COLOR_RGBA:
		case COLOR_BGRA:
			m_pPixels = XMem::createArrayMem<unsigned char>((w * h) << 2);
			break;
		case COLOR_RGB:
		case COLOR_BGR:
			m_pPixels = XMem::createArrayMem<unsigned char>(w * h * 3);
			break;
		case COLOR_GRAY:
			m_pPixels = XMem::createArrayMem<unsigned char>(w * h);
			break;
		default:
			return false;
			break;
		}
		if(m_pPixels == NULL) return false;

		isInited = true;
		return true;
	}
};
}
#endif
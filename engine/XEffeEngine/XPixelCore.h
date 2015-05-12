#ifndef _JIA_XPIXELCORE_
#define _JIA_XPIXELCORE_

#include <string>
#include "XBasicFun.h"
namespace XE{
enum XColorMode;

class XPixelCore
{
protected:
	unsigned char * m_pPixels;
	int w;
	int h;
	XColorMode m_colorMode;
	bool isInited;
public:
	XPixelCore()
		:isInited(false)
		,m_pPixels(NULL)
	{}
	virtual ~XPixelCore() {release();}
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

	virtual bool load(const std::string &filename,XResourcePosition resPos = RESOURCE_SYSTEM_DEFINE) = 0;

	virtual bool fitNPot() = 0;
	virtual bool create(int width,int height,XColorMode mode = COLOR_RGB) = 0;
};
template<typename T>
class XPixels
{
private:
	XPixelCore *m_pObj;
public:
	XPixels(){m_pObj = XMem::createMem<T>();}
	~XPixels(){XMem::XDELETE(m_pObj);}
	virtual void release() {m_pObj->release();}
	virtual unsigned char * getPixel() {return m_pObj->getPixel();}
	virtual int getWidth() const {return m_pObj->getWidth();}
	virtual int getHeight() const {return m_pObj->getHeight();}
	virtual XColorMode getColorMode() const {return m_pObj->getColorMode();}
	virtual bool getIsInited() const {return m_pObj->getIsInited();}

	virtual bool load(const std::string &filename,XResourcePosition resPos = RESOURCE_SYSTEM_DEFINE)
	{
		return m_pObj->load(filename,resPos);
	}

	virtual bool fitNPot() {return m_pObj->fitNPot();}
	virtual bool create(int width,int height,XColorMode mode = COLOR_RGB) {return m_pObj->create(width,height,mode);}
};
}
#endif
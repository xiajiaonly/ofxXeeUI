#ifndef _JIA_XWINDOWCORE_
#define _JIA_XWINDOWCORE_

#include "windows.h"
#include <string>
namespace XE{
class XWindowCore
{
public:
	virtual ~XWindowCore() {;}
	virtual bool createWindow(int width,int height,const char *windowTitle,int isFullScreen,int withFrame) = 0;
	virtual void setWindowTitle(const std::string &title) = 0;
	virtual void setCurcor(bool flag) = 0;
	virtual bool getCurcor() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual int mapKey(int key) = 0;
	virtual unsigned char *getWindowBuff() = 0;

};

namespace XEE
{
	extern bool	arbMultisampleSupported;
	extern int arbMultisampleFormat;

	extern bool initMultisample(HDC hdc);
}
}
#endif
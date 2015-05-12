#ifndef _JIA_XWINDOWGLUT_
#define _JIA_XWINDOWGLUT_

#include "XWindowCore.h"
#include <gl/glut.h>
namespace XE{
class XWindowGlut:public XWindowCore
{
protected:
	XWindowGlut()
		:m_isShowCurcor(true)
	{}
	XWindowGlut(const XWindowGlut&);
	XWindowGlut &operator= (const XWindowGlut&);
	virtual ~XWindowGlut() {}
public:
	static XWindowGlut& GetInstance()
	{
		static XWindowGlut m_instance;
		return m_instance;
	}
private:
	bool m_isShowCurcor;

public:
	virtual bool createWindow(int width,int height,const char *windowTitle,int isFullScreen,int withFrame);
	virtual void setWindowTitle(const std::string &title) {glutSetWindowTitle(title.c_str());}
	virtual void setCurcor(bool flag)
	{
		m_isShowCurcor = flag;
		glutSetCursor(flag);
	}
	virtual bool getCurcor(){return m_isShowCurcor;}
	virtual void release() {}
	virtual void update() {glutSwapBuffers();}
	virtual int mapKey(int key);
	virtual unsigned char *getWindowBuff(){return NULL;}

};
}
#endif
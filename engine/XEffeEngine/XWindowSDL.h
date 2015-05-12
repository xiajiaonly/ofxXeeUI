#ifndef _JIA_XWINDOWSDL_
#define _JIA_XWINDOWSDL_

#include "XWindowCore.h"
#include "XSDL.h"

#include "XStringFun.h"
namespace XE{
class XWindowSDL:public XWindowCore
{
protected:
	XWindowSDL()
		:m_screen(NULL)
	{}
	XWindowSDL(const XWindowSDL&);
	XWindowSDL &operator= (const XWindowSDL&);
	virtual ~XWindowSDL() {}

	SDL_Surface *m_screen;

public:
	static XWindowSDL& GetInstance()
	{
		static XWindowSDL m_instance;
		return m_instance;
	}
public:
	virtual bool createWindow(int width,int height,const char *windowTitle,int isFullScreen,int withFrame);
	virtual void setWindowTitle(const std::string &title) {SDL_WM_SetCaption(XString::ANSI2UTF8(title.c_str()).c_str(), NULL);}
	virtual void setCurcor(bool flag)
	{

		ShowCursor(flag);
	}
	virtual unsigned char *getWindowBuff()
	{
		if(m_screen == NULL) return NULL;
		return (unsigned char *)m_screen->pixels;
	}
	virtual bool getCurcor()
	{
		return SDL_ShowCursor(-1) == 1;
	}
	virtual void release()
	{
		SDL_FreeSurface(m_screen);
		SDL_Quit();
	}
	virtual void update()
	{

		SDL_GL_SwapBuffers();
	}
	virtual int mapKey(int key);

};
}
#endif
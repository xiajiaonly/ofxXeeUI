#ifndef _JIA_XWINDOWTITLE_
#define _JIA_XWINDOWTITLE_

#include "XControl/XControls.h"
#include "XControl/XDragObjectBase.h"
namespace XE{
class XWindowTitle:public XDragObjectBase
{
private:
	bool m_isInited;
	bool m_withText;
	XButton m_minSizeBtn;
	XButton m_exitBtn;
	XButton m_iconBtn;
	XFontUnicode m_titleFont;
	XRect m_titleRect;

	static void ctrlProc(void *,int,int);

	void (*m_winExitFun)(void *);
	void (*m_winMinFun)(void *);
	void * m_pClass;
public:
	bool init();
	void move(int){;}
	void draw();
	void setCallbackFun(void (*winExitFun)(void *),
		void (*winMinFun)(void *),void * pClass);
	void setWithText(bool b);
	void mouseProc(int x,int y,XMouseState mouseState){mouseEventProc(x,y,mouseState);}
	void release(){;}

	XWindowTitle()
		:m_isInited(false)
		,m_withText(true)
		,m_winExitFun(NULL)
		,m_winMinFun(NULL)
	{}
	~XWindowTitle(){release();}
private:
	virtual XBool getIsInDragRect(float x,float y){return m_titleRect.isInRect(x,y);}
	virtual XVector2 correctPos(const XVector2 &pos){return pos;}
public:
	virtual void setPosition(float x,float y){XEE::setWindowPos(x,y);}
	virtual XVector2 getPosition()const
	{
		int tmpX,tmpY;
		XEE::getWindowPos(tmpX,tmpY);
		return XVector2(tmpX,tmpY);
	}
};
#if WITH_INLINE_FILE
#include "XWindowTitle.inl"
#endif
}
#endif
#ifndef _JIA_XSUBWINDOW_
#define _JIA_XSUBWINDOW_

#include "XButton.h"
#include "XCtrlManagerBase.h"
#include "XDragObjectBase.h"
#include "XAutoShrinkBase.h"
namespace XE{

struct XSubWindowObj
{
	XControlBasic *obj;
	XVector2 pos;
	XVector2 scale;

};
class XSubWindow:public XControlBasic,public XDragObjectBase,public XAutoShrinkBase
{
public:
	enum XSubWindowState
	{
		STATE_NORMAL,
		STATE_MINISIZE,
	};
	enum XSubWindowType
	{
		TYPE_NORMAL,
		TYPE_NO_TITLE,
		TYPE_TOP,
	};
	enum XSubWindowEvent
	{
		SWD_STATE_CHANGE,
		SWD_LOSE_FOCUS,
		SWD_RELEASE,
	};
private:
	XBool m_isInited;
	XBool m_withTitle;
	XBool m_withBackGround;
	XSubWindowType m_windowType;
	XSubWindowState m_windowState;
	std::string m_titleString;
	XButton m_titleButton[3];

	XRect m_area;
	XFontUnicode m_titleFont;

	std::vector<XSubWindowObj> m_objects;
	static void ctrlProc(void *,int,int);

	void setMiniSize();
	void setNormalSize();
	void updateMouseRect();

	XCtrlManagerBase m_ctrlManager;
public:
	XSubWindow()
		:m_isInited(XFalse)
		,m_withTitle(XTrue)
		,m_titleString("SubWindow")
		,m_withBackGround(XTrue)
		,m_windowType(TYPE_NORMAL)
		,m_windowState(STATE_NORMAL)
	{
		m_ctrlType = CTRL_OBJ_SUBWINDOW;
	}
	~XSubWindow() {release();}
	void release();
	XBool initWithoutSkin(const XVector2 &area,const char * title);
protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *ch,int len){m_ctrlManager.insertChar(ch,len);}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return true;}
	void setLostFocus();
	void setFocus();
public:
	XBool setACopy(const XSubWindow &){}
	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	virtual XVector2 getPosition() const {return m_position;}

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	void setTitle(const char * title);
	void changeStage(XSubWindowState state);

	XBool addACtrlObj(XControlBasic *obj);
	int getObjectIndex(XControlBasic *obj);
private:
	virtual XBool getIsInDragRect(float x,float y);
	virtual XVector2 correctPos(const XVector2 &pos);

	virtual XShrinkDirection calShrinkDir();
	virtual XBool getIsInShrinkRect(){return m_curMouseRect.isInRect(m_curMousePosition);}
	virtual void updateShrinkPosition();

public:
	virtual XBool saveState(TiXmlNode &e);
	virtual XBool loadState(TiXmlNode *e);

};
#if WITH_INLINE_FILE
#include "XSubWindow.inl"
#endif
}
#endif
#ifndef _JIA_XTEXT_
#define _JIA_XTEXT_

#include "XControlBasic.h"
#include "../XBasicWindow.h"
namespace XE{
class XPropertyBox;
class XText:public XControlBasic
{
	friend XPropertyBox;
private:
	XBool m_isInited;
	XFontUnicode m_font;
public:
	XBool init(const XFontUnicode &font);
	XBool init() {return init(XEE::systemFont);}
	XBool init(const char * p)
	{
		if(!init(XEE::systemFont)) return XFalse;
		setString(p);
		return XTrue;
	}
	void setString(const char * str){m_font.setString(str);}
	void setMaxStrLen(int len){m_font.setMaxStrLen(len);}
	const char *getCaptionString() const {return m_font.getString();}
	XText()
		:m_isInited(XFalse)
	{
		m_ctrlType = CTRL_OBJ_TEXT;
	}
	~XText(){release();}
	void release();

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	using XObjectBasic::setScale;
	void setScale(float x,float y);
	void setTextColor(const XFColor& color){m_font.setColor(color);}
	XFColor getTextColor() const {return m_font.getColor();}
	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
protected:
	void draw();
	void drawUp(){};
	XBool mouseProc(float,float,XMouseState){return XFalse;}
	XBool keyboardProc(int,XKeyState){return XFalse;}
	void insertChar(const char *,int){;}
	XBool canGetFocus(float,float){return XFalse;}
	XBool canLostFocus(float,float){return XTrue;}
	void setLostFocus();
	XBool canBeChoose(){return XFalse;}
public:
	XBool isInRect(float x,float y){return m_font.isInRect(x,y);}
	XVector2 getBox(int order){return m_font.getBox(order);}
private:
	XText(const XText &temp);
	XText& operator = (const XText& temp);
};
#if WITH_INLINE_FILE
#include "XText.inl"
#endif
}
#endif
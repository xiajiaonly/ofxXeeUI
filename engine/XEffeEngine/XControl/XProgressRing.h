#ifndef _JIA_XPROGRESSRING_
#define _JIA_XPROGRESSRING_

#include "XControlBasic.h"
#include "XResourcePack.h"
#include "XResourceManager.h"
namespace XE{
class XProgressRing:public XControlBasic
{
private:
	XBool m_isInited;
	float m_r0;
	float m_r1;
	XBool m_withBG;
	XBool m_withText;
	XFontUnicode m_caption;
	XFColor m_textColor;

	float m_curValue;
public:
	XBool initWithoutSkin(float r0,float r1,const XFontUnicode &font,bool withBG = false,bool withText = true);
	XBool initWithoutSkin(float r0,float r1,bool withBG = false,bool withText = true)
	{
		return initWithoutSkin(r0,r1,XEE::systemFont,withBG,withText);
	}

	XProgressRing()
		:m_isInited(XFalse)
		,m_curValue(0.0f)
		,m_withText(XTrue)
		,m_withBG(XTrue)
		,m_textColor(1.0f,1.0f,1.0f,1.0f)
	{
		m_ctrlType = CTRL_OBJ_PROGRESSRING;
	}
	~XProgressRing(){release();}
	void release();

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	void setValue(float temp);
	float getValue() const{return m_curValue;}
protected:
	void draw();
	void drawUp(){};
	XBool mouseProc(float,float,XMouseState){return XTrue;}
	XBool keyboardProc(int,XKeyState){return XTrue;}
	void insertChar(const char *,int){;}
	XBool canGetFocus(float,float){return XFalse;}
	XBool canLostFocus(float,float){return XTrue;}
public:
	XBool setACopy(const XProgressRing &temp);

	void enable(){m_isEnable = XTrue;}
	void disable();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
private:
	XProgressRing(const XProgressRing &temp);
	XProgressRing& operator = (const XProgressRing& temp);
};
#if WITH_INLINE_FILE
#include "XProgressRing.inl"
#endif
}
#endif
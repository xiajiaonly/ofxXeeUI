#ifndef _JIA_XSLIDEREX_
#define _JIA_XSLIDEREX_

#include "XSlider.h"
namespace XE{
class XSliderEx:public XControlBasic,public XBasicOprate
{
private:
	XBool m_isInited;
	XSlider m_mainSld;
	XSlider m_secondarySld;
	XButton m_chooseBtn;

	int m_timer;
public:
	enum XSliderExEvent
	{
		SLDEX_INIT,
		SLDEX_RELEASE,
		SLDEX_MOUSE_ON,
		SLDEX_MOUSE_DOWN,
		SLDEX_MOUSE_UP,
		SLDEX_MOUSE_MOVE,
		SLDEX_VALUE_CHANGE,
	};
private:
	static void stateChangeProc(void *);
	static void ctrlProc(void*,int,int);
protected:
	void update(int stepTime);
	void draw();
	void drawUp(){;}
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}

public:
	XBool initWithoutSkin(const XRect& area,float max = 100.0f,float min = 0.0f,
		XSliderType type = SLIDER_TYPE_HORIZONTAL,const XVector2 &fontPosition = XVector2::zero);
	XBool initWithoutSkin(const XVector2& pixelSize,float max = 100.0f,float min = 0.0f,
		XSliderType type = SLIDER_TYPE_HORIZONTAL,const XVector2 &fontPosition = XVector2::zero)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),max,min,type,fontPosition);
	}
	XSliderEx()
		:m_isInited(XFalse)
		,m_timer(0)
	{
		m_ctrlType = CTRL_OBJ_SLIDEREX;
	}
	virtual ~XSliderEx(){release();}

	void release();

	XBool setFont(const char *caption,const XFontUnicode &font,float captionSize = 1.0f,const XVector2 &fontPosition = XVector2::zero);
	XBool setFont(const char *caption,const XVector2 &fontPosition)
	{
		return setFont(caption,XEE::systemFont,1.0f,fontPosition);
	}
	XBool setFont(const char *caption)
	{
		return m_mainSld.setFont(caption);
	}

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor& color){m_mainSld.setTextColor(color);}
	XFColor getTextColor() const {return m_mainSld.getTextColor();}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XBool setACopy(const XSliderEx &temp);

	void setCurValue(float temp);
	void setRange(float max,float min);

	void disable();
	void enable();
	void setVisible();
	void disVisible();
	float getCurValue() const;
	float getMaxValue() const;
	float getMinValue() const;

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XSliderEx(const XSliderEx &temp);
	XSliderEx& operator = (const XSliderEx& temp);

public:
	void setConnectVar(float * p) {m_mainSld.setConnectVar(p);}
	void disConnectVar() {m_mainSld.disConnectVar();}
public:
	void setOprateState(void * data);
	void *getOprateState() const;
	void releaseOprateStateData(void *p);
	virtual bool isSameState(void * data);
};
#if WITH_INLINE_FILE
#include "XSliderEx.inl"
#endif
}
#endif
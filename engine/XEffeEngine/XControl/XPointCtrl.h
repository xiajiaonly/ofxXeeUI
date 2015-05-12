#ifndef _JIA_XPOINTCTRL_
#define _JIA_XPOINTCTRL_

#include "XControlBasic.h"
namespace XE{
class XPointCtrl:public XControlBasic
{
private:
	static const int m_pointCtrlLineSum = 10;
	XBool m_isInited;

	XVector2 m_pixelSize;
	XVector2 m_truePixelSize;
	XFontUnicode m_font;
	char m_textStr[64];

	bool m_withFont;
	bool m_isDown;
	bool m_withRange;
	bool m_withMap;
	XRect m_range;
	XRect m_mapRange;
	XVector2 m_mapValue;

	void updateData();
public:
	enum XPointCtrlEvent
	{
		PITCTRL_DATA_CHANGE,
	};
private:
	XCtrlMode m_ctrlMode;
public:
	void setCtrlMode(XCtrlMode mode){m_ctrlMode = mode;}
	void setRange(float l,float t,float r,float b);
	void disRange(){m_withRange = false;}
	XVector2 getValue();
	void setValue(const XVector2 &value);
	void setMapRange(float l,float t,float r,float b);
	void disMapRange(){m_withMap = false;}
public:
	XBool init(const XVector2& position,const XFontUnicode *font = NULL);
	void draw();
	void drawUp(){;}

	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int,XKeyState){return XTrue;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	void insertChar(const char *,int){;}

	void disable();
	void enable(){m_isEnable = XTrue;}
	void release();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
	XBool setACopy(const XPointCtrl & temp);

	XPointCtrl()
		:m_isInited(XFalse)

		,m_withFont(false)
		,m_pixelSize(10.0f,10.0f)
		,m_isDown(false)
		,m_range(0.0f,0.0f,100.0f,100.0f)
		,m_withRange(false)
		,m_mapRange(0.0f,0.0f,100.0f,100.0f)
		,m_withMap(false)
		,m_mapValue(0.0f,0.0f)

		,m_ctrlMode(CTRL_MODE_SIMPLE)
	{
		m_ctrlType = CTRL_OBJ_POINTCTRL;
	}
	~XPointCtrl() {release();}

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		if(!XXml::addLeafNode(e,(m_ctrlName + "X").c_str(),XString::toString(getValue().x))) return XFalse;
		if(!XXml::addLeafNode(e,(m_ctrlName + "Y").c_str(),XString::toString(getValue().y))) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		XVector2 tmp;
		if(XXml::getXmlAsFloat(e,(m_ctrlName + "X").c_str(),tmp.x) == NULL) return XFalse;
		if(XXml::getXmlAsFloat(e,(m_ctrlName + "Y").c_str(),tmp.y) == NULL) return XFalse;
		setValue(tmp);
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XPointCtrl.inl"
#endif
}
#endif
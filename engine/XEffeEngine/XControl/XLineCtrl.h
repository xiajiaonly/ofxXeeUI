#ifndef _JIA_XLINECTRL_
#define _JIA_XLINECTRL_

#include "XControlBasic.h"
namespace XE{
class XLineCtrl:public XControlBasic
{
public:
	enum XLineCtrlType
	{
		LINE_CTRL_TYPEX_D,
		LINE_CTRL_TYPEX_U,
		LINE_CTRL_TYPE_Y_R,
		LINE_CTRL_TYPE_Y_L,
	};
private:
	static const int m_lineCtrlLineSum = 10;

	XVector2 m_pixelSize;
	XVector2 m_truePixelSize;
	XFontUnicode m_font;
	char m_textStr[64];

	XLineCtrlType m_type;
	XBool m_isInited;
	bool m_withFont;
	bool m_isDown;
	bool m_withRange;
	bool m_withMap;
	bool m_withString;
	XVector2 m_range;
	XVector2 m_mapRange;
	float m_mapValue;
	std::string m_showString;
	XFontUnicode m_stringFont;

	void updateData();
public:
	enum XLineCtrlEvent
	{
		LNCTRL_DATA_CHANGE,
	};

private:
	XCtrlMode m_ctrlMode;
public:
	void setString(const char * str);

	void setCtrlMode(XCtrlMode mode){m_ctrlMode = mode;}
	void setRange(float min,float max);
	void disRange(){m_withRange = false;}
	float getValue();
	void setValue(float value);
	void setMapRange(float min,float max);
	void disMapRange(){m_withMap = false;}
public:
	XBool init(const XVector2& position,XLineCtrlType type = LINE_CTRL_TYPEX_D,const XFontUnicode *font = NULL);
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
	XBool setACopy(const XLineCtrl & temp);

	XLineCtrl()
		:m_isInited(XFalse)

		,m_withFont(false)
		,m_pixelSize(10.0f,10.0f)
		,m_isDown(false)
		,m_type(LINE_CTRL_TYPEX_D)
		,m_range(0.0f,100.0f)
		,m_withRange(false)
		,m_withMap(false)
		,m_mapRange(0.0f,100.0f)
		,m_mapValue(0.0f)

		,m_ctrlMode(CTRL_MODE_SIMPLE)
		,m_withString(false)
	{
		m_ctrlType = CTRL_OBJ_LINECTRL;
	}
	~XLineCtrl(){release();}

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		if(!XXml::addLeafNode(e,m_ctrlName.c_str(),XString::toString(getValue()))) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		float tmp;
		if(XXml::getXmlAsFloat(e,m_ctrlName.c_str(),tmp) == NULL) return XFalse;
		setValue(tmp);
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XLineCtrl.inl"
#endif
}
#endif
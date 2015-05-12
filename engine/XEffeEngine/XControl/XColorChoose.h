#ifndef _JIA_XCOLORCHOOSE_
#define _JIA_XCOLORCHOOSE_
#include "XButton.h"
namespace XE{

class XColorChoose:public XControlBasic
{
public:
	enum XColorChooseType
	{
		TYPE_WITH_TEXT,
		TYPE_NO_TEXT,
	};
	enum XColorChooseEvent
	{
		CLC_COLOR_CHANGE,
	};
private:
	XBool m_isInited;
	XFColor m_curColor;
	XVector2 m_area;

	XFontUnicode m_font;
	XColorChooseType m_type;
	XBool m_needChooseColor;
public:
	void setType(XColorChooseType type){m_type = type;}
	XBool initWithoutSkin(const XVector2 &size,const XCColor &color);
protected:
	void draw();
	void drawUp(){}
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int,XKeyState){return XFalse;}
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y)
	{
		if(!m_isInited ||
			!m_isActive ||
			!m_isVisible ||
			!m_isEnable) return XFalse;
		return m_curMouseRect.isInRect(x,y);
	}
	XBool canLostFocus(float,float){return XTrue;}

public:
	void update(int stepTime);
	XColorChoose()
		:m_isInited(XFalse)
		,m_type(TYPE_WITH_TEXT)
		,m_needChooseColor(XFalse)
	{
		m_ctrlType = CTRL_OBJ_COLORCHOOSE;
	}
	~XColorChoose(){release();}
	void release();
private:
	XColorChoose(const XColorChoose &temp);
	XColorChoose& operator = (const XColorChoose& temp);
private:
	void updateColor();
public:
	XBool isInRect(float x,float y)
	{
		if(!m_isInited) return XFalse;
		return m_curMouseRect.isInRect(x,y);
	}
	XVector2 getBox(int order)
	{
		if(!m_isInited) return XVector2::zero;
		switch(order)
		{
		case 0:return XVector2(m_curMouseRect.left,m_curMouseRect.top);
		case 1:return XVector2(m_curMouseRect.right,m_curMouseRect.top);
		case 2:return XVector2(m_curMouseRect.right,m_curMouseRect.bottom);
		case 3:return XVector2(m_curMouseRect.left,m_curMouseRect.bottom);
		}
		return XVector2::zero;
	}

	using XObjectBasic::setPosition;
	void setPosition(float x,float y)
	{
		m_position.set(x,y);
		m_font.setPosition(m_position.x + 2 * m_scale.x,m_position.y + m_area.y * m_scale.y * 0.5f);
		m_curMouseRect.set(m_position.x,m_position.y,
			m_position.x + m_area.x * m_scale.x,m_position.y + m_area.y * m_scale.y);
	}

	using XObjectBasic::setScale;
	void setScale(float x,float y)
	{
		m_scale.set(x,y);
		m_font.setPosition(m_position.x + 2 * m_scale.x,m_position.y + m_area.y * m_scale.y * 0.5f);
		m_font.setScale(m_scale);
		m_curMouseRect.set(m_position.x,m_position.y,
			m_position.x + m_area.x * m_scale.x,m_position.y + m_area.y * m_scale.y);
	}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a){m_color.setColor(r,g,b,a);}
	void setAlpha(float a){m_color.setA(a);}

	XBool setACopy(const XColorChoose &temp);

	XFColor getCurColor() const {return m_curColor;}
	void setCurColor(const XFColor &c)
	{
		m_curColor = c;
		updateColor();
	}

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		XFColor tmp = getCurColor();
		if(!XXml::addLeafNode(e,(m_ctrlName + "R").c_str(),XString::toString(tmp.fR))) return XFalse;
		if(!XXml::addLeafNode(e,(m_ctrlName + "G").c_str(),XString::toString(tmp.fG))) return XFalse;
		if(!XXml::addLeafNode(e,(m_ctrlName + "B").c_str(),XString::toString(tmp.fB))) return XFalse;
		if(!XXml::addLeafNode(e,(m_ctrlName + "A").c_str(),XString::toString(tmp.fA))) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		XFColor tmp;
		if(XXml::getNextXmlAsFloat(e,(m_ctrlName + "R").c_str(),tmp.fR) == NULL) return XFalse;
		if(XXml::getNextXmlAsFloat(e,(m_ctrlName + "G").c_str(),tmp.fG) == NULL) return XFalse;
		if(XXml::getNextXmlAsFloat(e,(m_ctrlName + "B").c_str(),tmp.fB) == NULL) return XFalse;
		if(XXml::getNextXmlAsFloat(e,(m_ctrlName + "A").c_str(),tmp.fA) == NULL) return XFalse;
		setCurColor(tmp);
		return XTrue;
	}

};
}
#endif
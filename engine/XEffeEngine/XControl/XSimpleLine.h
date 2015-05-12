#ifndef _JIA_XSIMPLELINE_
#define _JIA_XSIMPLELINE_

#include "XControlBasic.h"
namespace XE{
enum XSimpleLineType
{
	SIMPLELINE_TYPE_VERTICAL,
	SIMPLELINE_TYPE_HORIZONTAL,
};
class XSimpleLine:public XControlBasic
{
private:
	XBool m_isInited;
	float m_lineLen;
	float m_lineWidth;
	XSimpleLineType m_type;
public:
	XBool init(float lineLen,float lineWidth = 0.5f,
		XSimpleLineType type = SIMPLELINE_TYPE_HORIZONTAL);

	void setLineLen(float lineLen){m_lineLen = lineLen;}
	float getLineLen() const {return m_lineLen;}
	void setLineWidth(float lineWidth){m_lineWidth = lineWidth;}
	float getLineWidth() const {return m_lineWidth;}
	void setLineType(XSimpleLineType type){m_type = type;}
	XSimpleLineType getLineType() const {return m_type;}

	XSimpleLine()
		:m_isInited(XFalse)
		,m_lineLen(100.0f)
		,m_lineWidth(1.0f)
		,m_type(SIMPLELINE_TYPE_HORIZONTAL)
	{
		m_ctrlType = CTRL_OBJ_SIMPLELINE;
	}
	~XSimpleLine(){release();}
	void release();

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor&){;}
	XFColor getTextColor() const {return XFColor::white;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a){m_color.setColor(r,g,b,a);}
	void setAlpha(float a){m_color.setA(a);}
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
	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
private:
	XSimpleLine(const XSimpleLine &temp);
	XSimpleLine& operator = (const XSimpleLine& temp);
};
#if WITH_INLINE_FILE
#include "XSimpleLine.inl"
#endif
}
#endif
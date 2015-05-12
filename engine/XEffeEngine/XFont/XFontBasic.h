#ifndef _JIA_XFONTBASIC_
#define _JIA_XFONTBASIC_

#include "XSprite.h"
namespace XE{

 enum XFontAlignmentModeX
{
	FONT_ALIGNMENT_MODE_X_LEFT,
	FONT_ALIGNMENT_MODE_X_MIDDLE,
	FONT_ALIGNMENT_MODE_X_RIGHT,
};
enum XFontAlignmentModeY
{
	FONT_ALIGNMENT_MODE_Y_UP,
	FONT_ALIGNMENT_MODE_Y_MIDDLE,
	FONT_ALIGNMENT_MODE_Y_DOWN,
};

class XFontBasic:public XObjectBasic
{
private:
	static const int m_stringMaxLength = 64;
protected:
	XBool m_isInited;
	XResourcePosition m_resoursePosition;
	XSprite m_sprite;
	char *m_string;
	int m_lineSum;
	int m_needShowTextSum;

	XBool m_needUpdateData;

	int m_maxStringLen;

	XFontAlignmentModeX m_alignmentModeX;
	XFontAlignmentModeY m_alignmentModeY;

	XBool m_withFBO;
	XBool m_needUpdateFBO;
	XFBO *m_pFbo;
	XSprite m_fboSprite;
public:
	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
	XFColor getColor() const {return m_sprite.getColor();}
protected:
	XBool m_isVisible;
public:
	void setVisible();
	void disVisible();
	XBool getVisible() const {return m_isVisible;}
protected:

	XRect m_clipRect;
	XBool m_isCliped;
public:
	void setClipRect(const XRect &temp){setClipRect(temp.left,temp.top,temp.right,temp.bottom);}
	void setClipRect(float left,float top,float right,float bottom);
	void disClip();

	void setAlignmentModeX(XFontAlignmentModeX mode);
	void setAlignmentModeY(XFontAlignmentModeY mode);
protected:
	float m_angle;
	float m_angleSin;
	float m_angleCos;

	float m_distance;
	float m_distanceY;

	XVector2 m_position;
	XVector2 m_setPosition;
	XVector2 m_rotateBasicPoint;

	XVector2 m_size;
	XVector2 m_scale;
public:

	void setDistance(float distance);
	void setDistance(float x,float y);
	void setAngle(float angle);
	float getAngle() const {return m_angle;}
	virtual const char * getString() const {return m_string;}

	using XObjectBasic::setScale;
	void setScale(float x,float y);
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	void setRotateBasePoint(float x,float y);

	XVector2 getTextSize() const {return m_size;}
	XVector2 getScale() const {return m_scale;}
	XVector2 getPosition() const {	return XVector2(m_position.x,m_position.y);}
protected:

	int m_maxPixelWidth;
	int m_maxPixelHeight;

	virtual void updateData() = 0;
public:
	int getMaxPixelWidth();
	int getMaxPixelHeight();

public:

	XFontBasic& operator = (const XFontBasic& temp);
	XBool setACopy(const XFontBasic &temp);
protected:
	XBool m_isPassword;
public:
	void setIsPassWord(XBool temp);
	XBool getIsPassword() const {return m_isPassword;}
protected:
	XFontBasic(int maxStrLen)
		:m_needUpdateData(XFalse)
		,m_alignmentModeX(FONT_ALIGNMENT_MODE_X_LEFT)
		,m_alignmentModeY(FONT_ALIGNMENT_MODE_Y_UP)
		,m_distance(0.0f)
		,m_distanceY(0.0f)
		,m_angle(0.0f)
		,m_angleSin(0.0f)
		,m_angleCos(1.0f)
		,m_position(0.0f,0.0f)
		,m_setPosition(0.0f,0.0f)
		,m_rotateBasicPoint(0.0f,0.0f)
		,m_scale(1.0f,1.0f)
		,m_isInited(XFalse)
		,m_maxPixelWidth(0)
		,m_maxPixelHeight(0)
		,m_lineSum(0)
		,m_needShowTextSum(0)
		,m_isVisible(XTrue)
		,m_isCliped(XFalse)
		,m_clipRect(0,0,0,0)
		,m_isPassword(XFalse)
		,m_withFBO(XFalse)

		,m_needUpdateFBO(XFalse)
		,m_pFbo(NULL)
	{
		if(maxStrLen < 2) m_maxStringLen = 2;
		else m_maxStringLen = maxStrLen;
		m_string = XMem::createArrayMem<char>(m_maxStringLen);
		m_string[0] = '\0';
	}
	XFontBasic()
		:m_needUpdateData(XFalse)
		,m_alignmentModeX(FONT_ALIGNMENT_MODE_X_LEFT)
		,m_alignmentModeY(FONT_ALIGNMENT_MODE_Y_UP)
		,m_distance(0.0f)
		,m_distanceY(0.0f)
		,m_angle(0.0f)
		,m_angleSin(0.0f)
		,m_angleCos(1.0f)
		,m_position(0.0f,0.0f)
		,m_setPosition(0.0f,0.0f)
		,m_rotateBasicPoint(0.0f,0.0f)
		,m_scale(1.0f,1.0f)
		,m_isInited(XFalse)
		,m_maxPixelWidth(0)
		,m_maxPixelHeight(0)
		,m_lineSum(0)
		,m_needShowTextSum(0)
		,m_isVisible(XTrue)
		,m_isCliped(XFalse)
		,m_clipRect(0,0,0,0)
		,m_isPassword(XFalse)
		,m_withFBO(XFalse)

		,m_needUpdateFBO(XFalse)
		,m_pFbo(NULL)
	{
		m_maxStringLen = m_stringMaxLength;
		m_string = XMem::createArrayMem<char>(m_maxStringLen);
		m_string[0] = '\0';
	}

	XFontBasic(const XFontBasic& temp);
public:
	XBool setString(const char *p);

	virtual ~XFontBasic()
	{
		XMem::XDELETE_ARRAY(m_string);
		if(m_pFbo != NULL) XMem::XDELETE(m_pFbo);
	}
	virtual void draw() = 0;
	virtual XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,XBool withFBO = XFalse) = 0;
	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
	virtual void setMaxStrLen(int maxStrLen) = 0;

};
#if WITH_INLINE_FILE
#include "XFontBasic.inl"
#endif
}
#endif
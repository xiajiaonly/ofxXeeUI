#ifndef _JIA_XBUTTONEX_
#define _JIA_XBUTTONEX_

#include "XButton.h"
namespace XE{
class XImageList;
class XButtonEx:public XControlBasic
{
	friend XImageList;
private:
	XBool m_isInited;
	XButtonState m_curButtonState;

	XFontUnicode m_caption;

	const XTextureData *m_buttonNormal;
	const XTextureData *m_buttonDown;
	const XTextureData *m_buttonOn;
	const XTextureData *m_buttonDisable;

	XSprite m_sprite;
	XVector2 m_textPosition;
	XVector2 m_textSize;
	XFColor m_textColor;
	XVector2 m_upMousePoint;
	XVector2 *m_pArea;
	XVector2 *m_pCurArea;
	int m_areaPointSum;

	int m_hotKey;
	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
	float *m_colorRate;
public:

	XBool init(const XVector2& position,
		const XVector2 *area,int pointSum,
		const XButtonSkin &tex,
		const char *caption,float captionSize,const XVector2 &captionPosition,
		const XFontUnicode &font);
	XBool initEx(const XVector2& position,
		const XButtonSkin &tex,
		const char *caption,float captionSize,
		const XFontUnicode &font);
	XBool initPlus(const char *path,
		const char *caption,float captionSize,
		const XFontUnicode &font,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const XVector2 *area,int pointSum,const char *caption,
		const XFontUnicode &font,const XVector2 &captionPosition,float captionSize = 1.0f);
	XBool initWithoutSkin(const XVector2 *area,int pointSum,const char *caption)
	{
		if(area == NULL || pointSum <= 0) return XFalse;
		XVector2 tmp(0.0f,0.0f);
		for(int i = 0;i < pointSum;++ i)
		{
			tmp += area[i];
		}
		tmp /= (float)(pointSum);
		initWithoutSkin(area,pointSum,caption,XEE::systemFont,tmp,1.0f);
	}

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
	void setLostFocus();
public:
	void setTexture(const XButtonSkin& tex);

	XBool setACopy(const XButtonEx &temp);

	XButtonEx();
	~XButtonEx(){release();}

	void setCaptionPosition(const XVector2& textPosition);
	void setCaptionPosition(float x,float y);
	void setCaptionSize(const XVector2& size);
	void setCaptionSize(float x,float y);
	void setCaptionText(const char *caption);
	const char *getCaptionString() const {return m_caption.getString();}
	void setHotKey(int hotKey);
	int getHotKey() const;
	void setState(XButtonState temp);
	XButtonState getState() const;
	void disable();
	void enable();
	void release();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XButtonEx(const XButtonEx &temp);
	XButtonEx& operator = (const XButtonEx& temp);

private:
	XMoveData m_actionMoveData;
	XVector2 m_oldPos;
	XVector2 m_oldSize;
	XVector2 m_centerPos;
	XMoveData m_lightMD;

public:
	enum XButtonExEvent
	{
		BTNEX_INIT,
		BTNEX_RELEASE,
		BTNEX_MOUSE_ON,
		BTNEX_MOUSE_DOWN,
		BTNEX_MOUSE_UP,
	};

};
#if WITH_INLINE_FILE
#include "XButtonEx.inl"
#endif
}
#endif
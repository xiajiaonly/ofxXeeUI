#ifndef _JIA_XGROUP_
#define _JIA_XGROUP_

#include "XButton.h"
namespace XE{

class XGroup:public XControlBasic
{
public:
	enum XGroupState
	{
		STATE_NORMAL,
		STATE_MINISIZE,
	};
private:
	static const int m_groupStateBtnSize = 32;
	XBool m_isInited;

	XRect m_rect;
	XRect m_drawRect;

	XFontUnicode m_caption;
	XVector2 m_textSize;

	XGroupState m_state;
	XButton m_stateBotton;
public:
	enum XGroupEvent
	{
		GRP_STATE_CHANGE,
	};
private:

	static void ctrlProc(void *,int,int);
	void updateData();
public:
	XBool init(const XVector2& position,
		const XRect &rect,
		const char *caption,const XFontUnicode &font,float captionSize = 1.0f);
	XBool initWithoutSkin(const XVector2& position,
		const XRect &rect,
		const char *caption) {return init(position,rect,caption,XEE::systemFont,1.0f);}
	XBool initWithoutSkin(const XVector2& position,
		const XVector2 &pixelSize,
		const char *caption)
	{
		return init(position,XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),
			caption,XEE::systemFont,1.0f);
	}
	void setState(XGroupState state);
	XGroupState getState(){return m_state;}

	void resetSize(const XVector2 &size);
public:
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	void insertChar(const char *,int){;}
	void setCaptionText(const char *caption);
protected:
	void draw();
	void drawUp()
	{

	}
	void update(int)
	{

	}
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	XBool canGetFocus(float,float){return XFalse;}
	XBool canLostFocus(float,float){return XTrue;}
public:
	void setLostFocus() {;}
	void disable()
	{
		m_isEnable = XFalse;
		m_isBeChoose = XFalse;
	}
	void enable(){m_isEnable = XTrue;}
	void release();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
	XBool setACopy(const XGroup & temp);

	void setVisible();
	void disVisible();

	XGroup()
		:m_isInited(XFalse)

		,m_state(STATE_NORMAL)

	{
		m_ctrlType = CTRL_OBJ_GROUP;
	}
	~XGroup(){release();}

private:
	XGroup(const XGroup &temp);
	XGroup& operator = (const XGroup& temp);
};
#if WITH_INLINE_FILE
#include "XGroup.inl"
#endif
}
#endif
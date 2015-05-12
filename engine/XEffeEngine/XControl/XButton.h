#ifndef _JIA_XBUTTON_
#define _JIA_XBUTTON_

#include "XControlBasic.h"
#include "XResourcePack.h"
#include "XResourceManager.h"
#include "../XBasicWindow.h"
#include "../XMath/XMoveData.h"

namespace XE{
enum XButtonState
{
	BUTTON_STATE_NORMAL,
	BUTTON_STATE_DOWN,
	BUTTON_STATE_ON,
	BUTTON_STATE_DISABLE
};
enum XButtonSymbol
{
	BTN_SYMBOL_NULL,
	BTN_SYMBOL_CIRCLE,
	BTN_SYMBOL_RECT,
	BTN_SYMBOL_CROSS,
	BTN_SYMBOL_TRIANGLE,
	BTN_SYMBOL_MASK_RIGHT,
	BTN_SYMBOL_MASK_WRONG,
	BTN_SYMBOL_LEFT,
	BTN_SYMBOL_RIGHT,
	BTN_SYMBOL_UP,
	BTN_SYMBOL_DOWN,
};

class XButtonSkin
{
private:
	XBool m_isInited;

	void releaseTex();
public:
	XTextureData *buttonNormal;
	XTextureData *buttonDown;
	XTextureData *buttonOn;
	XTextureData *buttonDisable;

	XRect m_mouseRect;
	XVector2 m_fontPosition;
	int m_areaPointSum;
	XVector2 *m_pArea;

	XButtonSkin();
	~XButtonSkin(){release();}
	XBool init(const char *normal,const char *down,const char *on,const char *disable,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};

class XCombo;
class XMouseRightButtonMenu;
class XDirectoryList;
class XGroup;
class XSliderEx;
class XPasswordPad;
class XTab;
class XCalendar;
class XButtonBar;
class XSubWindow;
class XButton:public XControlBasic
{
	friend XCombo;
	friend XMouseRightButtonMenu;
	friend XDirectoryList;
	friend XGroup;
	friend XSliderEx;
	friend XPasswordPad;
	friend XTab;
	friend XCalendar;
	friend XButtonBar;
	friend XSubWindow;
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

	int m_hotKey;

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
	XBool initProc(const XFontUnicode &font,const char *caption,float captionSize);
public:

	XBool init(const XVector2& position,
		const XRect& Area,
		const XButtonSkin &tex,
		const char *caption,const XFontUnicode &font,float captionSize,const XVector2 &textPosition);
	XBool initEx(const XVector2& position,
		const XButtonSkin &tex,
		const char *caption,const XFontUnicode &font,float captionSize = 1.0f);
	XBool initPlus(const char * path,const char *caption,const XFontUnicode &font,float captionSize = 1.0f,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const char *caption,const XFontUnicode &font,
		float captionSize,const XRect& area,const XVector2 &textPosition);
	XBool initWithoutSkin(const char *caption,const XFontUnicode &font,const XRect& area);
	XBool initWithoutSkin(const char *caption,const XRect& area) {return initWithoutSkin(caption,XEE::systemFont,area);}
	XBool initWithoutSkin(const char *caption,const XVector2& pixelSize)
	{
		return initWithoutSkin(caption,XEE::systemFont,XRect(0.0f,0.0f,pixelSize.x,pixelSize.y));
	}
	XBool initWithoutSkin(const char *caption,float width)
	{
		return initWithoutSkin(caption, XEE::systemFont, XRect(0.0f, 0.0f, width, MIN_FONT_CTRL_SIZE));
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
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
	void setLostFocus();
public:
	void setTexture(const XButtonSkin& tex);

	XBool setACopy(const XButton &temp);

	XButton();
	~XButton(){release();}
	void release();

	void setCaptionPosition(const XVector2& textPosition);
	void setCaptionPosition(float x,float y);
	void setCaptionSize(const XVector2& size);
	void setCaptionSize(float x,float y);
	void setCaptionText(const char *caption);
	void setCaptionAlignmentModeX(XFontAlignmentModeX x){m_caption.setAlignmentModeX(x);}
	void setCaptionAlignmentModeY(XFontAlignmentModeY y){m_caption.setAlignmentModeY(y);}
	const char *getCaptionString() const {return m_caption.getString();}
	void setHotKey(int hotKey);
	int getHotKey() const;
	void setState(XButtonState temp);
	XButtonState getState() const;
	void disable();
	void enable();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	void setWidth(int width);
	int getWidth()const{return m_mouseRect.getWidth();}
private:
	XButton(const XButton &temp);
	XButton& operator = (const XButton& temp);

private:
	XBool m_withNormalIcon;
	XSprite m_normalIcon;
	XBool m_withDisableIcon;
	XSprite m_disableIcon;
	XVector2 m_iconSize;
	XVector2 m_iconPosition;
public:
	void setNormalIcon(const char * filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void setNormalIcon(const XSprite &icon);
	void setDisableIcon(const char * filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void setDisableIcon(const XSprite &icon);
	void removeIcon();
	void setIconPosition(float x,float y);
	void setIconSize(float x,float y);
	void setIconSize(float x){setIconSize(x,x);}

private:
	XMoveData m_actionMoveData;
	XVector2 m_oldPos;
	XVector2 m_oldSize;
	XMoveData m_lightMD;
	XRect m_lightRect;
public:
protected:
	void update(int stepTime);

private:
	XButtonSymbol m_symbolType;
public:
	void setSymbol(XButtonSymbol type){m_symbolType = type;}
	XButtonSymbol getSymbol() const {return m_symbolType;}
	void disSymbol(){m_symbolType = BTN_SYMBOL_NULL;}

public:
	enum XButtonEvent
	{
		BTN_INIT,
		BTN_RELEASE,
		BTN_MOUSE_ON,
		BTN_MOUSE_DOWN,
		BTN_MOUSE_UP,
	};
};
#if WITH_INLINE_FILE
#include "XButton.inl"
#endif
}
#endif
#ifndef _JIA_XMOUSERIGHTBUTTONMENU_
#define _JIA_XMOUSERIGHTBUTTONMENU_

#include "XButton.h"
namespace XE{

typedef XButtonSkin XMouseRightButtonMenuSkin;
class XEdit;
class XMouseRightButtonMenu:public XControlBasic
{
	friend XEdit;
private:
	XBool m_isInited;
	XButton *m_menu;
	int m_menuSum;
	int m_curChoose;
	int m_lastChoose;
public:
	enum XMouseRightButtonMenuEvent
	{
		MRBM_CHOOSE_CHANGE,
		MRBM_CHOOSE_OVER,
	};

private:
	XRect m_allArea;
	XVector2 m_upMousePoint;

	XResourceInfo *m_resInfo;
public:

	XBool init(int menuSum,
		const XVector2& position,
		const XRect& Area,
		const XMouseRightButtonMenuSkin &tex,
		const XFontUnicode &font,float captionSize,const XVector2& textPosition);
	XBool initEx(int menuSum,
		const XVector2& position,
		const XMouseRightButtonMenuSkin &tex,
		const XFontUnicode &font,float captionSize = 1.0f);
	XBool initPlus(const char * path,int menuSum,
		const XFontUnicode &font,float captionSize = 1.0f,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(int menuSum,const XRect& area,
		const XFontUnicode &font,float captionSize, const XVector2& textPosition);
	XBool initWithoutSkin(int menuSum,const XRect& area,const XVector2& textPosition)
	{
		return initWithoutSkin(menuSum,area,XEE::systemFont,1.0f,textPosition);
	}
	XBool initWithoutSkin(int menuSum,const XVector2& pixelSize,const XVector2& textPosition)
	{
		return initWithoutSkin(menuSum,XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),
			XEE::systemFont,1.0f,textPosition);
	}
protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
public:
	void setCurChoose(int){;}
	XBool setACopy(const XMouseRightButtonMenu &temp);
public:
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	XMouseRightButtonMenu();
	~XMouseRightButtonMenu(){release();}

	int getLastChoose() const;
	void setCallbackFun(void (* funChooseChange)(void *,int),
		void (* funChooseOver)(void *,int),
		void *pClass = NULL);
	void setHotKey(int hotKey,int order);
	void setText(const char *temp,int order);
	void setTexture(const XMouseRightButtonMenuSkin &tex,int order);
	void release();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

private:
	XMouseRightButtonMenu(const XMouseRightButtonMenu &temp);
	XMouseRightButtonMenu& operator = (const XMouseRightButtonMenu& temp);
};
#if WITH_INLINE_FILE
#include "XMouseRightButtonMenu.inl"
#endif
}
#endif
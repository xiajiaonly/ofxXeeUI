#ifndef _JIA_XBUTTONBAR_
#define _JIA_XBUTTONBAR_

#include "XButton.h"
namespace XE{
struct XButtonBarCore
{
	XBool isEnable;
	int width;
	std::string name;
	XButton *button;
	XButtonBarCore()
		:button(NULL)
	{}
	~XButtonBarCore(){}
};
class XButtonBar:public XControlBasic
{
private:
	XBool m_isInited;
	float m_insertPoint;
	int m_barHeight;
	std::vector<XButtonBarCore> m_buttons;
public:
	XBool initWithoutSkin(int height = 32);
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	using XObjectBasic::setScale;
	void setScale(float x,float y);
	void setTextColor(const XFColor& color);
	XFColor getTextColor() const;

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	int getIndexByName(const std::string &name);
	XBool addAButton(const std::string &name,const std::string &caption = "");
	XBool addAButton(const std::string& name,int width,const std::string &caption = "");

	XBool setBtnEnable(const std::string &name);
	XBool setBtnDisable(const std::string &name);
	XBool setBtnCaption(const std::string &name,const std::string &caption);
	XBool setEventProc(const std::string &name,
		void (* eventProc)(void *,int,int),void *pClass = NULL);

	XBool setBtnNormalIcon(const std::string &name,const char * filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool setBtnNormalIcon(const std::string &name,const XSprite &icon);
	XBool setBtnDisableIcon(const std::string &name,const char * filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool setBtnDisableIcon(const std::string &name,const XSprite &icon);
	XBool removeBtnIcon(const std::string &name);
	XBool setBtnIconPosition(const std::string &name,float x,float y);
	XBool setBtnIconSize(const std::string &name,float x,float y);
	XBool setBtnIconSize(const std::string &name,float x){return setBtnIconSize(name,x,x);}

	int getBtnID(const std::string &name);
	XBool setBtnComment(const std::string &name,const std::string &comment);
	XBool setBtnHotKey(const std::string &name,int hotKey);
protected:
	void draw();
	void drawUp();
	void update(int stepTime);
public:
	void release();
	XButtonBar()
		:m_isInited(XFalse)
		,m_barHeight(32)
	{
		m_ctrlType = CTRL_OBJ_BTNBAR;
	}
	~XButtonBar() {release();}

	virtual XBool isInRect(float x,float y);
	virtual XVector2 getBox(int order);
	void disable();
	void enable();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}

private:
	XButtonBar(const XButtonBar &temp);
	XButtonBar& operator = (const XButtonBar& temp);
};
#if WITH_INLINE_FILE
#include "XButtonBar.inl"
#endif
}
#endif
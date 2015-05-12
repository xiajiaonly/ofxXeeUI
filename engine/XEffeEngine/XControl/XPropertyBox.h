#ifndef _JIA_XPROPERTYBOX_
#define _JIA_XPROPERTYBOX_

#include "XSlider.h"
#include "XText.h"
#include "XEdit.h"
#include "XCheck.h"
#include "XCombo.h"
namespace XE{

enum XPropertyLineType
{
	PROPERTY_BLANK,
	PROPERTY_TITLE,
	PROPERTY_EDIT,
	PROPERTY_CHECK,
	PROPERTY_COMBO,
};
class XPropertyLine
{
public:
	std::string name;
	XPropertyLineType type;
	XFontUnicode *pNameFont;
	XControlBasic *pCtrl;

	XBool getIsFocus();
	void setFocus(bool flag);
	XBool canLostFocus(float x,float y);
	XBool canGetFocus();
	void draw();
	void drawUp();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void update(int stepTime);
	void insertChar(const char *ch,int len);
	void disable();
	void enable();
	XPropertyLine()
		:type(PROPERTY_BLANK)
		,pNameFont(NULL)
		,pCtrl(NULL)
	{}
	void setAlpha(float a);
	void setColor(float r,float g,float b,float a);
};
class XPropertyBox:public XControlBasic
{
private:
	XBool m_isInited;

	XBool m_haveTitle;
	std::string m_titleStr;
	XText m_titleTxt;
	XFontUnicode m_font;

	float m_width;
	float m_nameWidth;
	int m_maxLineSum;

	XBool m_needShowSlider;
	XSlider m_slider;
	int m_curStartLineIndex;

	std::vector<XPropertyLine> m_propertyLines;

	void setCurStartLineIndex(unsigned int index);
public:
	void setTitle(const char * title);
	void disTitle();
	XBool initWithoutSkin(int width,int maxLineSum);
	void setNameWidth(int width);

protected:
	void draw();
	void drawUp();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *ch,int len);
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
	void setLostFocus();
public:
	XBool addAPropertyLine(const char * name,XPropertyLineType type,int menuSum = 0,int showMenuSum = 0);
	XBool setPropertyName(unsigned int index,const char * name);
	std::string getPropertyName(unsigned int index);
	XBool setPropertyCtrlPrama(unsigned int index,int prama);
	XBool setPropertyStr(unsigned int index,const char * str);
	std::string getPropertyStr(unsigned int index);
	XBool setPropertyValue(unsigned int index,float value);
	float getPropertyValue(unsigned int index);
	XBool setPropertyIndex(unsigned int index,int order);
	int getPropertyIndex(unsigned int index);
	XBool setPropertyState(unsigned int index,XBool state);
	XBool getPropertyState(unsigned int index);
	XBool setPropertyMenuStr(unsigned int index,int menuIndex,const char *str);
	void updateSliderState();

	XPropertyBox()
		:m_isInited(XFalse)
		,m_haveTitle(XFalse)

		,m_curStartLineIndex(0)
		,m_oldFocusIndex(-1)

	{
		m_ctrlType = CTRL_OBJ_PROPERTYBOX;
	}
	~XPropertyBox(){release();}
	void release();

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	static void ctrlProc(void*,int,int);

	void disable();
	void enable();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XPropertyBox(const XPropertyBox &temp);
	XPropertyBox& operator = (const XPropertyBox& temp);
protected:
	void update(int stepTime);
	void updateRect();
	int m_oldFocusIndex;

	void moveFocus(bool flag);

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;

		TiXmlElement elmNode(m_ctrlName.c_str());
		XBool flag = XTrue;
		for(unsigned int i = 0;i < m_propertyLines.size();++ i)
		{
			if(m_propertyLines[i].pCtrl != NULL &&
				!m_propertyLines[i].pCtrl->saveState(elmNode)) flag = XFalse;
		}
		if(e.InsertEndChild(elmNode) == NULL) flag = XFalse;
		return flag;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;

		TiXmlNode * keyNode = e->FirstChildElement(m_ctrlName.c_str());
		if(keyNode == NULL) return XFalse;
		XBool flag = XTrue;
		for(unsigned int i = 0;i < m_propertyLines.size();++ i)
		{
			if(m_propertyLines[i].pCtrl != NULL &&
				!m_propertyLines[i].pCtrl->loadState(keyNode)) flag = XFalse;
		}
		return flag;
	}

};
#if WITH_INLINE_FILE
#include "XPropertyBox.inl"
#endif
}
#endif
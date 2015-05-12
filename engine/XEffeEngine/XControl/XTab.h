#ifndef _JIA_XTAB_
#define _JIA_XTAB_

#include "XButton.h"
#include "XCtrlManagerBase.h"
namespace XE{
#define TAB_MODE (2)

#define TAB_TITLE_HEIGHT (MIN_FONT_CTRL_SIZE)

struct XTabObject
{
	XBool isEnable;
	XBool isVisible;
	std::string srcTitle;
	std::string title;
	std::vector<XControlBasic *> objs;
	XFontUnicode *pFont;

	XBool needDraw;
	int len;
	int offset;
	std::vector<XVector2> pos;
	std::vector<XVector2> size;
	XTabObject()
		:isEnable(XTrue)
		,isVisible(XTrue)
		,pFont(NULL)
	{}

public:
	virtual XBool saveState(TiXmlNode &e);
	virtual XBool loadState(TiXmlNode *e);

};

class XTab:public XControlBasic
{
private:
	static const int m_tabTitleDistance = 3;
	static const int m_tabBtnWidth = 20;

	XRect m_titleRect;

	XBool m_isInited;
	XBool m_withoutTex;

	XButton m_leftBtn;
	XButton m_rightBtn;
	XFColor m_textColor;

	std::vector<XTabObject> m_tabObjects;

	int m_curChooseTabIndex;
	int m_curStartTabIndex;
	int m_maxTitleLen;
	float m_curTextWidth;
	XFontUnicode m_texFont;

	void updateTitle();
	void updateBtnState();
	void updateObjState(bool flag = true);
	static void ctrlProc(void*,int,int);

	std::string m_curChooseTabStr;
public:
	enum XTabEvent
	{
		TAB_CHOOSE,
	};
	std::string getCurChooseTabStr(){return m_curChooseTabStr;}

public:
	XBool initWithoutSkin(const XRect &rect,const XFontUnicode &font);
	XBool initWithoutSkin(const XRect &rect) {return initWithoutSkin(rect,XEE::systemFont);}
	XBool initWithoutSkin(const XVector2 &pixelSize)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),XEE::systemFont);
	}

protected:
	void draw();
	void drawUp();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int,XKeyState);
#if TAB_MODE == 2
	void insertChar(const char *ch,int len){m_ctrlManager.insertChar(ch,len);}
#else
	void insertChar(const char *,int){;}
#endif
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
	void setLostFocus();

public:
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XBool setTabStr(const char *str,unsigned int index);
	XBool setTabsStr(const char *str);
	std::string getTabStr(unsigned int index);
	std::string getTabsStr();
	int getTabIndexByTitle(const std::string &title) const;
	void addATab(const std::string &title);
	void clearAllObj();
	void addObjToTab(XControlBasic *obj,unsigned int index);
	void addObjToTab(XControlBasic *obj,const std::string &title);
	void setTabVisible(bool flag,int index);
	void setTabVisible(bool flag,const std::string &title);
	XBool getTabVisible(unsigned int index) const;
	XBool getTabVisible(const std::string &title) const;
	void setTabEnable(bool flag,unsigned int index);
	void setTabEnable(bool flag,const std::string &title);
	XBool getTabEnable(unsigned int index) const;
	XBool getTabEnable(const std::string &title) const;

	void delObjFromTab(XControlBasic *obj,int index);
	void delObjFromTab(XControlBasic *obj,const std::string &title);
	void clearObjFromTab(int index);
	void clearObjFromTab(const std::string &title);

	XTab()
		:m_isInited(XFalse)
		,m_withoutTex(XTrue)
		,m_curChooseTabIndex(0)
		,m_curStartTabIndex(0)

	{
		m_ctrlType = CTRL_OBJ_TAB;
	}
	~XTab(){release();}
	void release();

	void disable();
	void enable();
	void setVisible();
	void disVisible();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XTab(const XTab &temp);
	XTab& operator = (const XTab& temp);

private:
	XMoveData m_actionMoveData;
	int m_oldChooseTabIndex;
	void startAction();
	void update(int stepTime);

public:
	virtual XBool saveState(TiXmlNode &e);
	virtual XBool loadState(TiXmlNode *e);

#if TAB_MODE == 2
	XCtrlManagerBase m_ctrlManager;
#endif

};
#if WITH_INLINE_FILE
#include "XTab.inl"
#endif
}
#endif
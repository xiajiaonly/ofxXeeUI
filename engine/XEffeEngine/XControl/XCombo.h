#ifndef _JIA_XCOMBO_
#define _JIA_XCOMBO_

#include "XButton.h"
namespace XE{

class XComboSkin
{
private:
	XBool m_isInited;
	void releaseTex();
public:
	XTextureData *comboInputNormal;
	XTextureData *comboInputDisable;
	XButtonSkin downButtonTex;
	XButtonSkin downMenuUpButtonTex;
	XButtonSkin downMenuButtonTex;
	XButtonSkin downMenuDownButtonTex;

	XRect m_mouseRect;

	XComboSkin();
	~XComboSkin() {release();}
	XBool init(const char *inputNormal,const char *inputDisable,
		const char *downButtonNormal,const char *downButtonOn,const char *downButtonDown,const char *downButtonDisable,
		const char *downMenuUpNormal,const char *downMenuUpOn,const char *downMenuUpDown,const char *downMenuUpDisable,
		const char *downMenuNormal,const char *downMenuOn,const char *downMenuDown,const char *downMenuDisable,
		const char *downMenuDownNormal,const char *downMenuDownOn,const char *downMenuDownDown,const char *downMenuDownDisable,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};

#define DEFAULT_COMBO_BT_SIZE (MIN_FONT_CTRL_SIZE)
#define DEFAULT_COMBO_MN_HEIGHT (MIN_FONT_CTRL_SIZE)

class XPropertyLine;
class XCombo:public XControlBasic
{
	friend XPropertyLine;
private:

	static const int m_comboLeftDistance = 5;
	static const int m_comboTopDistance = 0;

	static const int m_defaultComboUDHeight = 24;

	XBool m_isInited;
	XBool m_isDrawDownMenu;
	XBool m_withoutTex;

	bool m_isDraw;
	XMoveData m_actionMoveData;

	const XTextureData *m_comboInputNormal;
	const XTextureData *m_comboInputDisable;

	int m_curMenuSum;
	int m_menuSum;
	int m_menuDrawSum;
	int m_menuStartDrawOrder;
	int m_menuTextWidth;
	int m_captionTextWidth;

	int m_curChooseOrder;

	XSprite m_sprite;
	XFontUnicode m_caption;
	XVector2 m_textSize;
	XFColor m_textColor;

	std::string m_menuData;

	XButton *m_buttom;

	void updateString();
	void changeDownMenuState();

	static void funCtrlProc(void*,int,int);

	XRect m_inputArea;
	XRect m_downButtonArea;
	XRect m_downMenuUpArea;
	XRect m_downMenuArea;
	XRect m_downMenuDownArea;
	XRect m_allArea;

	XResourceInfo *m_resInfo;
public:
	XBool init(const XComboSkin &tex,
		const XVector2& position,
		const XRect& inputArea,
		const XRect& downButtonArea,
		const XRect& downMenuUpArea,
		const XRect& downMenuArea,
		const XRect& downMenuDownArea,
		int menuSum,
		int drawMenuSum,
		const XFontUnicode &font,
		float fontSize = 1.0f);
	XBool initEx(const XComboSkin &tex,
		const XVector2& position,
		int menuSum,
		int drawMenuSum,
		const XFontUnicode &font,
		float fontSize = 1.0f);
	XBool initPlus(const char * path,
		int menuSum,
		int drawMenuSum,
		const XFontUnicode &font,
		float fontSize = 1.0f,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	XBool initWithoutSkin(int inputLen,
		int menuSum,
		int drawMenuSum,
		const XFontUnicode &font,
		float fontSize = 1.0f);
	XBool initWithoutSkin(int inputLen,
		int menuSum,
		int drawMenuSum)
	{
		return initWithoutSkin(inputLen,menuSum,drawMenuSum,XEE::systemFont,1.0f);
	}

protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float x,float y);
public:
	int getCurChooseOrder() {return m_curChooseOrder;}
	std::string getCurChooseMenu();
	XBool setCurChooseOrder(int index);
	XBool setMenuStr(const char *str,int order);
	XBool setMenuStr(const char *str);
	std::string getMenuStr() const;
	std::string getMenuStr(int order);

	bool resetMenuSum(int menuSum,int showMenuSum);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XBool setACopy(const XCombo &temp);
	void release();
	XCombo();
	~XCombo(){release();}

	void disable();
	void enable();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	void setInputLen(int len);
	int getInputLen()const{return m_inputArea.getWidth();}
private:
	XCombo(const XCombo &temp);
	XCombo& operator = (const XCombo& temp);
public:
	enum XComboEvent
	{
		CMB_DATA_CHANGE,
	};

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		int tmp = getCurChooseOrder();
		if(!XXml::addLeafNode(e,m_ctrlName.c_str(),XString::toString(tmp))) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		int tmp;
		if(XXml::getXmlAsInt(e,m_ctrlName.c_str(),tmp) == NULL) return XFalse;
		setCurChooseOrder(tmp);
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XCombo.inl"
#endif
}
#endif
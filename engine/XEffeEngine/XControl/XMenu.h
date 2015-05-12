#ifndef _JIA_XMENU_
#define _JIA_XMENU_

#include "XControlBasic.h"
#include "../XBasicWindow.h"
namespace XE{

enum XMenuType
{
	MENU_TYPE_VERTICAL,
	MENU_TYPE_HORIZONTA,
};
class XMenuItem;
class XMenuGroup
{
public:
	XVector2 m_insertPos;
	int m_width;
	XMenuType m_type;
	XMenuItem *m_parent;
	std::vector<XMenuItem *> m_items;
	void draw();
	XMenuGroup()
		:m_width(-1)
		,m_type(MENU_TYPE_HORIZONTA)
		,m_parent(NULL)
		,m_chooseIndex(-1)
	{}
	~XMenuGroup()
	{
		for(unsigned int i = 0;i < m_items.size();++ i)
		{
			XMem::XDELETE(m_items[i]);
		}
		m_items.clear();
	}
	void setOpen();
	void disOpen();
	XBool isInRect(float x,float y);
	XMenuItem * getItem(float x,float y);
	XMenuItem * getItemByNameInGroup(const std::string &name);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	void postPross();
	void updatePos();
	void updateSize();
	void updateColor();
	void setHotChooseActive(XBool flag);
	XMenuItem *getItemByHotChooseKey(char k);
	XMenuItem *getItemByHotKey(char k);
	void setAllCallBackFun(void (*callbackFun)(void *,const std::string &),void *p);

	int m_chooseIndex;
	void addIndex();
	void desIndex();
	void initIndex(XBool orderFlag = XTrue);
	void resetChoose();
	void openChoose();
	void closeChoose();
	XBool setChooseItem(const XMenuItem *it);
	XMenuItem *getChooseItem();

};
enum XMenuItemType
{
	MENU_ITEM_TYPE_BTN,
	MENU_ITEM_TYPE_CHK,
	MENU_ITEM_TYPE_DLT,
};
class XMenuItem
{
public:
	static const int m_maxMenuItemLength = 1024;

	int m_levelIndex;
	XVector2 m_position;
	XVector2 m_scaleSize;
	XVector2 m_size;
	XMenuGroup *m_owner;
	XMenuGroup *m_child;
	std::string m_originalName;
	std::string m_showName;
	XMenuItemType m_type;
	XBool m_isOpen;
	XBool m_isChecked;
	XFColor m_color;

	void setCheckState(XBool state);
	void setString(const std::string &name);
	void setPosition(float x,float y);
	void setScale(float x,float y);
	void setColor(const XFColor &c);

	XFontUnicode m_font;
	XBool m_isEnable;
	XBool m_isVisible;
	XBool m_isMouseOn;
	XBool mouseProc(float x,float y,XMouseState mouseState);

	XBool m_withIcon;
	XSprite m_spriteIcon;
	XBool setIcon(const char *filename,XResourcePosition res = RESOURCE_SYSTEM_DEFINE);
	void disIcon();

	char m_hotKey;
	char m_hotChooseKey;
	XBool m_isHotChooseActive;
	XBool setHotKey(char k);
	XBool setHotChooseKey(char k);
	XMenuItem *getItemByHotKey(char k);
	XMenuItem *getItemByHotChooseKey(char k);
	void setHotChooseActive(XBool flag);

private:
	void (*m_callbackFun)(void *pClass,const std::string &pos);
	void *m_pClass;
public:
	XMenuItem()
		:m_owner(NULL)
		,m_child(NULL)
		,m_isOpen(XFalse)
		,m_position(0.0f,0.0f)
		,m_scaleSize(1.0f,1.0f)
		,m_size(0.0f,0.0f)
		,m_callbackFun(NULL)
		,m_pClass(NULL)
		,m_isEnable(XTrue)
		,m_isVisible(XTrue)
		,m_isMouseOn(XFalse)
		,m_levelIndex(0)
		,m_type(MENU_ITEM_TYPE_BTN)
		,m_withIcon(XFalse)
		,m_hotKey(-1)
		,m_hotChooseKey(-1)
		,m_isHotChooseActive(XFalse)
		,m_color(1.0f,1.0f,1.0f,1.0f)
	{}
	~XMenuItem(){XMem::XDELETE(m_child);}
	void draw();
	void setCallbackFun(void (*callbackFun)(void *,const std::string &),void *p);
	void setAllCallBackFun(void (*callbackFun)(void *,const std::string &),void *p);
	void beTriggered();
	std::string getFullStr() const;

	XBool init(const std::string &name,const XFontUnicode &font,float fontsize,XMenuGroup *owner,XMenuItemType type = MENU_ITEM_TYPE_BTN);
	void setOpen();
	void disOpen();
	XBool isInRect(float x,float y);
	XMenuItem * getItem(float x,float y);
	void postPross();
	void updateStr();
	void resetChoose();
};
class XMenu:public XControlBasic
{
private:
	XBool m_isInited;
	XMenuItem m_rootItem;
	XMenuType m_type;

	XFontUnicode m_font;
	float m_fontSize;

	XBool m_isClicked;
	XMenuItem *m_oldChooseItem;
	XBool m_needPostProcess;

	void postProcess();
	std::string m_curChooseMenuStr;
	static void ctrlProc(void *,const std::string &);
public:
	enum XMenuEvent
	{
		MNU_CHOOSE,
	};
	std::string getCurChooseMenuStr(){return m_curChooseMenuStr;}
public:

	XBool addAItem(const std::string &pos,const std::string &name,int width = -1,XMenuItemType type = MENU_ITEM_TYPE_BTN);
	XBool getCheckState(const std::string &pos);
	XBool setCheckState(const std::string &pos,XBool state);
	XBool setDisable(const std::string &pos);
	XBool setEnable(const std::string &pos);
	XBool getEnable(const std::string &pos);
	XBool setMenuItemStr(const std::string &pos,const std::string &name);
	XBool setItemIcon(const std::string &pos,const char *filename,XResourcePosition res = RESOURCE_SYSTEM_DEFINE);
	XBool setHotKey(const std::string &pos,char k);
	char getHotKey(const std::string &pos);
	XBool setHotChooseKey(const std::string &pos,char k);
	char getHotChooseKey(const std::string &pos);
	XMenuItem * getItemByName(const std::string &name);
	std::string getItemFullStr(const XMenuItem * it);
private:
	XMenuItem * getItemFromGroup(char *p,XMenuGroup *g);
	XBool getIsPath(XMenuItem *s,XMenuItem *d);

	XBool m_hotChooseKeyIsActive;

	void closeAll();
public:

	XBool initWithoutSkin(const XFontUnicode &font,float captionSize = 1.0f,XMenuType type = MENU_TYPE_HORIZONTA);
	XBool initWithoutSkin(XMenuType type = MENU_TYPE_HORIZONTA) {return initWithoutSkin(XEE::systemFont,1.0f,type);}
protected:
	void draw();
	void drawUp(){};
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);

	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
	void setLostFocus();
public:
	XMenu()
		:m_isInited(XFalse)
		,m_isClicked(XFalse)
		,m_oldChooseItem(NULL)
		,m_needPostProcess(XFalse)
		,m_hotChooseKeyIsActive(XFalse)
		,m_type(MENU_TYPE_HORIZONTA)
	{
		m_ctrlType = CTRL_OBJ_MENU;
	}
	~XMenu(){release();}
	void release();

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return XFColor::white;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XBool isInRect(float x,float y) {return m_rootItem.isInRect(x,y);}
	XVector2 getBox(int order);

private:
	XMenu(const XMenu &temp);
	XMenu& operator = (const XMenu& temp);
};
#if WITH_INLINE_FILE
#include "XMenu.inl"
#endif
}
#endif
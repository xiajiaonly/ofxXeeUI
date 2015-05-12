#ifndef _JIA_XCONTROLBASIC_
#define _JIA_XCONTROLBASIC_

#include "../XBasicClass.h"
#include "../XMouseAndKeyBoardDefine.h"
#include "../XObjectBasic.h"
#include "../XFont/XFontUnicode.h"
#include "../XSprite.h"
#include "../XFont/XNumberEx.h"
#include "XComment.h"
#include "../XXml.h"
#include "XCtrlColorStyle.h"
namespace XE{
#define MIN_FONT_CTRL_SIZE (XEE::windowData.systemFontSize + 2.0f)

enum XCtrlMode
{
	CTRL_MODE_SIMPLE,
	CTRL_MODE_NORMAL,
	CTRL_MODE_COMPLETE,
};
enum XCtrlObjType
{
	CTRL_OBJ_NULL,
	CTRL_OBJ_BUTTON,
	CTRL_OBJ_BUTTONEX,
	CTRL_OBJ_CHECK,
	CTRL_OBJ_EDIT,
	CTRL_OBJ_MOUSERIGHTBUTTONMENU,
	CTRL_OBJ_SLIDER,
	CTRL_OBJ_RADIOS,
	CTRL_OBJ_PROGRESS,
	CTRL_OBJ_MUTITEXT,
	CTRL_OBJ_MUTILIST,
	CTRL_OBJ_COMBO,
	CTRL_OBJ_DIRECTORYLIST,
	CTRL_OBJ_GROUP,
	CTRL_OBJ_POINTCTRL,
	CTRL_OBJ_LINECTRL,
	CTRL_OBJ_SLIDEREX,
	CTRL_OBJ_PASSWORDPAD,
	CTRL_OBJ_IMAGELIST,
	CTRL_OBJ_CHART,
	CTRL_OBJ_TAB,
	CTRL_OBJ_TEXT,
	CTRL_OBJ_SIMPLELINE,
	CTRL_OBJ_PROGRESSRING,
	CTRL_OBJ_CALENDAR,
	CTRL_OBJ_MENU,
	CTRL_OBJ_IMAGE,
	CTRL_OBJ_BTNBAR,
	CTRL_OBJ_TOOLBAR,
	CTRL_OBJ_PROPERTYBOX,
	CTRL_OBJ_COLORCHOOSE,
	CTRL_OBJ_SUBWINDOW,
	CTRL_OBJ_FUNCTION,
};

namespace XCtrl
{
	inline std::string getCtrlNameByType(XCtrlObjType type);
	inline std::string getCtrlTypeByString(XCtrlObjType type);
	inline XCtrlObjType getCtrlTypeByString(const std::string &name);
}

class XCtrlManagerBase;
class XToolBar;
class XTab;
class XPropertyLine;
class XSubWindow;

class XControlBasic:public XObjectBasic
{
	friend XCtrlManagerBase;
	friend XToolBar;
	friend XTab;
	friend XPropertyLine;
	friend XSubWindow;
protected:
	XCtrlObjType m_ctrlType;
	XRect m_mouseRect;
	XRect m_curMouseRect;
	XVector2 m_scale;
	XVector2 m_position;
	XFColor m_color;

	XBool m_isEnable;
	XBool m_isVisible;
	XBool m_isActive;
	XBool m_isBeChoose;
	int m_objectID;
	XBool m_withAction;
	XBool m_isInAction;

	XComment m_comment;
	XBool m_isMouseInRect;
public:
	XVector2 getPixelSize() const {return XVector2(m_mouseRect.getWidth(),m_mouseRect.getHeight());}
	XCtrlObjType getCtrlType()const{return m_ctrlType;}
	void setWithAction(XBool flag){m_withAction = flag;}
	XBool getWithAction()const{return m_withAction;}
	XBool getIsInAction()const{return m_isInAction;}
	XRect getMouseRect() const {return m_mouseRect;}
	float getMouseRectWidth() const {return m_mouseRect.getWidth();}
	float getMouseRectHeight() const {return m_mouseRect.getHeight();}
	int getControlID() const {return m_objectID;}
	void setActive(){m_isActive = XTrue;}
	void disActive(){m_isActive = XFalse;}
	XBool getActive() const {return m_isActive;}
	void setVisible()
	{
		m_isVisible = XTrue;
		m_comment.setVisible();
		updateChildVisible();
	}
	void disVisible()
	{
		m_isVisible = XFalse;
		m_isBeChoose = XFalse;
		m_comment.disVisible();
		updateChildVisible();
	}
	XBool getVisible() const {return m_isVisible;}
	XBool getEnable() const {return m_isEnable;}
	XBool setACopy(const XControlBasic & temp);

	void setComment(const char *str) {m_comment.setString(str);}
	void disComment() {m_comment.setString(NULL);}
	void setCommentPos(float x,float y){m_comment.setPosition(x,y);}

protected:
	virtual void update(int){;}
	virtual void draw() = 0;
	virtual void drawUp() = 0;
	virtual XBool mouseProc(float x,float y,XMouseState mouseState) = 0;
	virtual XBool keyboardProc(int keyOrder,XKeyState keyState) = 0;
	virtual void insertChar(const char * ch,int len) = 0;

	virtual XBool canBeChoose()
	{
		return m_isActive &&
			m_isVisible &&
			m_isEnable;
	}
	virtual XBool canGetFocus(float x,float y) = 0;
	virtual XBool canLostFocus(float x,float y) = 0;
	virtual void setLostFocus() {m_isBeChoose = XFalse;}
	virtual void setFocus() {m_isBeChoose = XTrue;}
	virtual XBool isFocus() {return m_isBeChoose;}
public:
	using XObjectBasic::setPosition;

	virtual XVector2 getPosition() const {return m_position;}

	using XObjectBasic::setScale;
	virtual XVector2 getScale() const {return m_scale;}

	using XObjectBasic::setColor;

	virtual XFColor getColor() const {return m_color;}

	float getAngle() const {return 0.0f;}
	void setAngle(float){updateChildAngle();}

	XControlBasic();
	virtual ~XControlBasic() {};
private:
	XControlBasic(const XControlBasic &temp);
	XControlBasic& operator = (const XControlBasic& temp);
protected:
	void *m_pClass;
	void (*m_eventProc)(void *,int ID,int eventID);
public:
	virtual void setEventProc(void (* eventProc)(void *,int,int),void *pClass = NULL)
	{
		m_eventProc = eventProc;
		if(pClass != NULL) m_pClass = pClass;
		else m_pClass = this;
	}

protected:
	XBool m_needSaveAndLoad;
	std::string m_ctrlName;
public:
	virtual void setNeedSaveAndLoad(bool flag) {m_needSaveAndLoad = flag;}
	virtual XBool getNeedSaveAndLoad() const {return m_needSaveAndLoad;}
	virtual void setCtrlName(const std::string& name){m_ctrlName = name;}
	virtual std::string getCtrlName() const {return m_ctrlName;}
	virtual XBool saveState(TiXmlNode &)
	{
		if(!m_needSaveAndLoad) return XTrue;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *)
	{
		if(!m_needSaveAndLoad) return XTrue;
		return XTrue;
	}

};

#if WITH_INLINE_FILE
#include "XControlBasic.inl"
#endif
}
#endif
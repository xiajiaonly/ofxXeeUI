#ifndef _JIA_XCALENDAR_
#define _JIA_XCALENDAR_

#include "XButton.h"
#include "XTimer.h"
namespace XE{

class XCalendar:public XControlBasic
{
private:
	XBool m_isInited;
	bool m_haveChoose;
	bool m_needShowToday;
	bool m_needShowChoose;
	XVector2 m_todayPos;
	XVector2 m_choosePos;
	XRect m_rect;

	XSystemTime m_todayDate;
	XSystemTime m_curSetDate;
	XSystemTime m_curShowData;

	XButton m_yearAddBtn;
	XButton m_yearDecBtn;
	XFontUnicode m_yearTxt;
	XButton m_monthAddBtn;
	XButton m_monthDecBtn;
	XFontUnicode m_monthTxt;

	XFontUnicode m_titleFont[7];
	XFontUnicode m_dateFont[42];
	static void ctrlProc(void*,int,int);
public:
	XBool initWithoutSkin(const XFontUnicode &font);
	XBool initWithoutSkin(){return initWithoutSkin(XEE::systemFont);}
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XSystemTime getTodayDate() const {return m_todayDate;}
	void setTodayDate(const XSystemTime &t) {m_todayDate = t;}
	bool getHaveChoose() const{return m_haveChoose;}
	XSystemTime getCurChooseDate() const {return m_curSetDate;}
	void setCurChooseDate(const XSystemTime &t) {m_curSetDate = t;}
	XSystemTime getCurShowDate() const {return m_curShowData;}
	void setCurShowDate(const XSystemTime &t) {m_curShowData = t;}

protected:
	void updateCurDate();
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int,XKeyState){return XFalse;}
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
	void setLostFocus();
public:
	XCalendar()
		:m_isInited(XFalse)
		,m_haveChoose(false)
		,m_needShowToday(false)
		,m_needShowChoose(false)
	{
		m_ctrlType = CTRL_OBJ_CALENDAR;
	}
	~XCalendar(){release();}
	void release();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XCalendar(const XButton &temp);
	XCalendar& operator = (const XButton& temp);

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		XSystemTime tmp = getCurChooseDate();
		if(!XXml::addLeafNode(e,(m_ctrlName + "Year").c_str(),XString::toString(tmp.year))) return XFalse;
		if(!XXml::addLeafNode(e,(m_ctrlName + "Month").c_str(),XString::toString(tmp.month))) return XFalse;
		if(!XXml::addLeafNode(e,(m_ctrlName + "Day").c_str(),XString::toString(tmp.day))) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		XSystemTime tmp;
		if(XXml::getXmlAsInt(e,(m_ctrlName + "Year").c_str(),tmp.year) == NULL) return XFalse;
		if(XXml::getXmlAsInt(e,(m_ctrlName + "Month").c_str(),tmp.month) == NULL) return XFalse;
		if(XXml::getXmlAsInt(e,(m_ctrlName + "Day").c_str(),tmp.day) == NULL) return XFalse;
		setCurChooseDate(tmp);
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XCalendar.inl"
#endif
}
#endif
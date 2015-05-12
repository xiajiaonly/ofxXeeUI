#ifndef _JIA_XEDIT_
#define _JIA_XEDIT_

#include "XMouseRightButtonMenu.h"
namespace XE{
class XEditSkin
{
private:
	XBool m_isInited;
	void releaseTex();
public:
	XTextureData *editNormal;
	XTextureData *editDisable;
	XTextureData *editSelect;
	XTextureData *editInsert;
	XTextureData *editUpon;

	XRect m_mouseRect;

	XEditSkin();
	~XEditSkin(){release();}
	XBool init(const char *normal,const char *disable,const char *select,const char *insert,
		const char *upon = NULL,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};

class XDirectoryList;
class XPropertyLine;
class XEdit:public XControlBasic
{
	friend XDirectoryList;
	friend XPropertyLine;
private:
	static const int m_maxInputStringLength = 256;
	static const int m_textEdgeWidth = 5;
	static char m_copyString[m_maxInputStringLength];
	XBool m_isInited;
	XBool m_haveSelect;
	XBool m_selectMouseDown;
	bool m_isPassword;
	XMouseRightButtonMenu *m_mouseRightButtonMenu;

	XFontUnicode m_caption;

	char *m_curString;
	char *m_tempCurString;

	int m_curInsertPoint;
	int m_curStringLength;
	int m_selectStart;
	int m_selectEnd;

	const XTextureData *m_editNormal;
	const XTextureData *m_editDisable;
	const XTextureData *m_editSelect;
	const XTextureData *m_editInsert;
	const XTextureData *m_editUpon;

	XSprite m_spriteBackGround;
	XSprite m_spriteSelect;
	XSprite m_spriteInsert;
	XVector2 m_textPosition;
	XVector2 m_textSize;
	XFColor m_textColor;
	float m_curTextWidth;
	float m_curTextHeight;
public:
	enum XEditEvent
	{
		EDT_INPUT_CHANGE,
		EDT_INPUT_OVER,
	};
	enum XEditType
	{
		TYPE_STRING,
		TYPE_UNSIGNED_INT,
		TYPE_INT,
		TYPE_HEX,
		TYPE_FLOAT,
	};
	void setEditType(XEditType type){m_editType = type;}
	XEditType getEditType(){return m_editType;}
private:
	XEditType m_editType;
	XBool isStringPassable()
	{
		if(m_curString[0] == '\0') return XTrue;
		switch(m_editType)
		{
		case TYPE_STRING:return XTrue;
		case TYPE_UNSIGNED_INT:return XString::getIsUnsignedInt(m_curString);
		case TYPE_INT:return XString::getIsInt(m_curString);
		case TYPE_HEX:return XString::getIsHexNumber(m_curString);
		case TYPE_FLOAT:return XString::getIsNumber(m_curString);
		}
		return XFalse;
	}

	int m_timer;

	char m_keyShiftState;
	char m_keyCapsLockState;
	char m_keyNumLockState;
	char m_keyCtrlState;

	int m_canShowLength;
	int m_curShowStart;
	char *m_curShowString;
	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
	XRect m_selectRect;
	int keyJudgement(int keyOrder);
public:
	void upDataShowStr();
	void upDateInsertShowPosition();
	void changeInsertPoint(int sum);
	void upDataSelectShow();
	void mouseRightMenuProc();
	void deleteSelectStr();

public:
	XBool init(const XVector2& position,
		const XRect& Area,
		const XEditSkin &tex,
		const char *str,
		const XFontUnicode &font,
		float strSize = 1.0f,
		XMouseRightButtonMenu * mouseMenu = NULL);
	XBool initEx(const XVector2& position,
		const XEditSkin &tex,
		const char *str,
		const XFontUnicode &font,
		float strSize = 1.0f,
		XMouseRightButtonMenu * mouseMenu = NULL);
	XBool initPlus(const char * path,
		const char *str,
		const XFontUnicode &font,
		float strSize = 1.0f,
		XMouseRightButtonMenu * mouseMenu = NULL,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const XRect& area,
		const char *str,
		const XFontUnicode &font,
		float strSize = 1.0f,
		XMouseRightButtonMenu * mouseMenu = NULL);
	XBool initWithoutSkin(const XRect& area,
		const char *str,
		XMouseRightButtonMenu * mouseMenu = NULL)
	{
		return initWithoutSkin(area,str,XEE::systemFont,1.0f,mouseMenu);
	}
	XBool initWithoutSkin(const XVector2& pixelSize,
		const char *str,
		XMouseRightButtonMenu * mouseMenu = NULL)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),str,XEE::systemFont,1.0f,mouseMenu);
	}
	XBool initWithoutSkin(float width,
		const char *str,
		XMouseRightButtonMenu * mouseMenu = NULL)
	{
		return initWithoutSkin(XRect(0.0f, 0.0f, width, MIN_FONT_CTRL_SIZE), str, XEE::systemFont, 1.0f, mouseMenu);
	}
protected:
	void update(int stepTime);
	void draw();
	void drawUp();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char * ch,int len);
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float x,float y);
	virtual void setLostFocus();
	void setFocus()
	{
		printf("…Ë÷√Œ™Ωπµ„\n");
		m_isBeChoose = XTrue;
		setImmPos();
	}
	void setImmPos();
private:

	XBool keyProc(int keyOrder);
	int m_curKey;
	int m_curKeyDownTimer;
	int m_curKeyRepTimer;
	XBool m_curKeyDown;
public:
	void release();
	void setString(const char *str);

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);
	XBool getEdtIsNumber();
	int getAsInt();

	float getAsFloat();
	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XBool setACopy(const XEdit &temp);

	XEdit();
	~XEdit(){release();}

	void disable();
	void enable();
	char *getString() const;
	int getSelectLength() const;
	int getSelectHead() const;
	int getSelectEnd() const;

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	void setInputLen(int len);
private:
	XEdit(const XEdit &temp);
	XEdit& operator = (const XEdit& temp);

private:

	XVector2 m_oldPos;
	XVector2 m_oldSize;
	XMoveData m_lightMD;
	XRect m_lightRect;

	XMoveData m_insertActionMD;

	std::string m_promptStr;
	bool m_withPromptStr;
public:
	void setPromptStr(const std::string &str)
	{
		m_withPromptStr = true;
		m_promptStr = str;
	}
	void disPromptStr(){m_withPromptStr = false;}
	std::string getPromptStr(){return m_promptStr;}
	bool withPromptStr(){return m_withPromptStr;}

public:
	void setIsPassword(bool flag);
	bool getIsPassword() const{return m_isPassword;}

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		if(!XXml::addLeafNode(e,m_ctrlName.c_str(),getString())) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		std::string tmp;
		if(XXml::getXmlAsString(e,m_ctrlName.c_str(),tmp) == NULL) return XFalse;
		setString(tmp.c_str());
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XEdit.inl"
#endif
}
#endif
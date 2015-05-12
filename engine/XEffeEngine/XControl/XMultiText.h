#ifndef _JIA_XMUTITEXT_
#define _JIA_XMUTITEXT_

#include "XEdit.h"
#include "XSlider.h"
namespace XE{

typedef XEditSkin XMultiTextSkin;

struct XMultiTextLineString
{
	XBool isEnable;
	char *showString;

	XFontUnicode curText;
	int lineHeadorder;
	int lineEndOrder;

	XSprite spriteSelect;
	XBool haveAllSelect;

	int lineWidthPixel;

	XMultiTextLineString()
		:showString(NULL)
	{}
};

#define MAX_LINE_STRING_LENGTH (256)
#define MAX_LINE_SUM (256)
#define MAX_STRING_LENGTH (65536)
#ifndef DEFAULT_SLIDER_WIDTH
#define DEFAULT_SLIDER_WIDTH (32)
#endif
enum XMultiTextActionType
{
	MLTTXT_ACTION_TYPE_IN,
	MLTTXT_ACTION_TYPE_MOVE,
	MLTTXT_ACTION_TYPE_DCLICK,
	MLTTXT_ACTION_TYPE_OUT,
};
class XMultiText:public XControlBasic
{
private:
	XBool m_isInited;
	XBool m_haveSelect;

	XBool m_needShowVSlider;
	XBool m_needShowHSlider;
	XSlider m_verticalSlider;
	XSlider m_horizontalSlider;

	char *m_curString;

	const XTextureData *m_multiEditNormal;
	const XTextureData *m_multiEditDisable;
	const XTextureData *m_multiEditSelect;
	const XTextureData *m_multiEditUpon;

	XSprite m_spriteBackGround;

	XVector2 m_textSize;
	XFColor m_textColor;
	float m_textWidth;
	float m_curTextHeight;

	int m_selectLineOrder;

	XMultiTextLineString *m_lineStr;
	int m_showStartLine;
	int m_canShowLineSum;

	int m_curMaxLineSum;

	void updateLineStr();

	int m_curStartPixels;
	int m_curMaxLineWidthPixels;
	int m_maxLineWidthPixels;

	static void ctrlProc(void*,int,int);

	void setStartLine(int temp);
	void checkStr();

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
	char m_timer;
public:
	enum XMultiTextEvent
	{
		MLTTXT_SELECT,
	};

public:
	XBool init(const XVector2& position,
		const XRect& Area,
		const XMultiTextSkin& tex,
		const char *str,const XFontUnicode& font, float strSize,

		const XSlider &vSlider,const XSlider &hSlider);
	XBool initEx(const XVector2& position,
		const XMultiTextSkin& tex,
		const char *str,const XFontUnicode& font, float strSize,
		const XSlider &vSlider,const XSlider &hSlider);
	XBool initPlus(const char *path,
		const char *str,const XFontUnicode& font, float strSize = 1.0f,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const XRect& area,
		const char *str,const XFontUnicode& font, float strSize = 1.0f);
	XBool initWithoutSkin(const XRect& area,const char *str)
	{
		return initWithoutSkin(area,str,XEE::systemFont,1.0f);
	}
	XBool initWithoutSkin(const XVector2& pixelSize,const char *str)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),
			str,XEE::systemFont,1.0f);
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

	void setString(const char *str);
	const char *getString()const{return m_curString;}
	void addString(const char *str);
	void addALine(const char *str);

	XBool setACopy(const XMultiText &temp);

	XBool exportData(const char *fileName = NULL);
	XBool importData(const char *fileName = NULL);
	XBool deleteSelectLine();
	XBool moveUpSelectLine();
	XBool moveUpLine(int order);
	XBool moveDownSelectLine();
	XBool moveDownLine(int order);
	XBool insertALine(const char *str,int lineOrder);

	XMultiText();
	~XMultiText(){release();}

	void enable();
	void disable();
	void release();
	int getSelectLine() const;
	int getLineSum() const;

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XMultiText(const XMultiText &temp);
	XMultiText& operator = (const XMultiText& temp);

private:
	XMultiTextActionType m_actionType;
	XMoveData m_actionMD;
	int m_actionPosition;
	void setAction(XMultiTextActionType type,int index);

public:
	virtual XBool saveState(TiXmlNode &e);
	virtual XBool loadState(TiXmlNode *e);

};
#if WITH_INLINE_FILE
#include "XMultiText.inl"
#endif
}
#endif
#ifndef _JIA_XMUTILISTBASIC_
#define _JIA_XMUTILISTBASIC_

#include "XSlider.h"
#include "XMouseRightButtonMenu.h"
#include "XMultiList.h"
#include "XCheck.h"
namespace XE{
#ifndef DEFAULT_SLIDER_WIDTH
#define DEFAULT_SLIDER_WIDTH (32)
#endif
#ifndef DEFAULT_TITLE_HEIGHT
#define DEFAULT_TITLE_HEIGHT (32.0f)
#endif
#ifndef DEFAULT_END_WIDTH
#define DEFAULT_END_WIDTH (8.0f)
#endif
#ifndef DEFAULT_CHECK_SIZE
#define DEFAULT_CHECK_SIZE (32.0f)
#endif
class XMultiListBasic:public XControlBasic
{
private:
	XBool m_isInited;

	const XTextureData *m_mutiListNormal;
	const XTextureData *m_mutiListDisable;
	const XTextureData *m_mutiListSelect;
	const XTextureData *m_mutiListMove;
	const XTextureData *m_mutiListTitle;
	const XTextureData *m_mutiListTitleEnd;

	XBool m_needShowVSlider;
	XSlider m_verticalSlider;
	XBool m_needShowHSlider;
	XSlider m_horizontalSlider;

	int m_tableRowSum;
	XMultiListOneRow *m_tableRow;
	int m_tableLineSum;
	XMultiListOneBox *m_tableBox;

	XBool m_haveSelect;
	int m_selectLineOrder;
	XRect m_selectRect;
	XBool *m_haveSelectFlag;
	XKeyState m_stateOfShiftKey;

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;

public:
	XBool getHaveSelectState(int i);
	int getTableLineSum();
private:

	int m_showStartLine;
	float m_showStartRow;
	int m_canShowLineSum;

	XBool m_needShowMove;

	XSprite m_spriteBackGround;
	XSprite m_spriteSelect;
	XSprite m_spriteMove;

	static void ctrlProc(void *,int,int);

	XBool m_mouseLeftButtonDown;
	int m_startX;
	int m_changeRowOrder;
	XMultiListOneRow * m_changeRow;

	XBool m_mouseMoveDown;
	int m_oldLineOrder;
public:
	enum XMultiListBasicEvent
	{
		MLTLST_SELECT,
		MLTLSTB_CHK_STATE_CHANGE,
	};

public:
	int getSelectIndex() const;

	void clearAllSelect();

	int getLineSum() const {return m_tableLineSum;}
	int getRowSum() const {return m_tableRowSum;}
	void setTitleStr(const char *str,int order);
	void setBoxStr(const char *str,int line,int row);
	XBool setRowWidth(int temp,int order);
private:
	void updateShowChange();
	int m_showPixWidth;
	int m_showPixHight;
	void updateSliderState();
	void updateSelectLine();
	void initANewRowData(XMultiListOneRow * upRow,int i);
	void initANewBoxData(XMultiListOneBox * curBox,XMultiListOneRow * curRow,int i,int j);

	XFontUnicode m_caption;
	XVector2 m_fontSize;
	XFColor m_textColor;
	float m_curTextWidth;
	float m_curTextHeight;

	XCheck *m_check0;
	XCheck *m_check1;
	XBool *m_check0State;
	XBool *m_check1State;
public:
	XBool getCheckState(int order,int lineOrder);
	void setCheckState(int order,int lineOrder,XBool state);

	XBool init(const XVector2& position,
		const XRect& Area,
		const XMultiListSkin &tex,
		const XCheckSkin &checktex0,
		const XCheckSkin &checktex1,
		const XFontUnicode &font,
		float strSize,
		int rowSum,
		int lineSum,

		const XSlider &vSlider,
		const XSlider &hSlider);
	XBool initEx(const XVector2& position,
		const XMultiListSkin &tex,
		const XCheckSkin &checktex0,
		const XCheckSkin &checktex1,
		const XFontUnicode &font,
		float strSize,
		int rowSum,
		int lineSum,

		const XSlider &vSlider,
		const XSlider &hSlider);
	XBool initPlus(const char *path,
		const XFontUnicode &font,
		float strSize,
		int rowSum,
		int lineSum,

		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const XRect& area,
		const XFontUnicode &font,
		float strSize,
		int rowSum,
		int lineSum);
	XBool initWithoutSkin(const XRect& area,
		int rowSum,
		int lineSum)
	{
		return initWithoutSkin(area,XEE::systemFont,1.0f,rowSum,lineSum);
	}
	XBool initWithoutSkin(const XVector2& pixelSize,
		int rowSum,
		int lineSum)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),
			XEE::systemFont,1.0f,rowSum,lineSum);
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
	XBool exportData(const char *fileName = NULL);
	XBool importData(const char *fileName = NULL);
	XBool setRowSum(int rowSum);
	XBool setLineSum(int lineSum);
	XBool deleteLine(int order);
	XBool deleteRow(int order);
	XBool insertALine(int order);
	XBool insertARow(int order);
	XBool moveDownLine(int order);
	XBool moveRightRow(int order);

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XMultiListBasic();
	~XMultiListBasic(){release();}
	void release();
private:
	void releaseTempMemory();
public:

	XBool addALine();
	XBool addARow();
	XBool deleteCurSelectLine();
	XBool deleteSelectLines();
	XBool moveUpLine(int order);
	XBool moveLeftRow(int order);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XMultiListBasic(const XMultiListBasic &temp);
	XMultiListBasic& operator = (const XMultiListBasic& temp);

public:
	virtual XBool saveState(TiXmlNode &e);
	virtual XBool loadState(TiXmlNode *e);

};
#if WITH_INLINE_FILE
#include "XMultiListBasic.inl"
#endif
}
#endif
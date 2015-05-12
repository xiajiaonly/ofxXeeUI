#ifndef _JIA_XMUTILIST_
#define _JIA_XMUTILIST_

#include "XSlider.h"
#include "XMouseRightButtonMenu.h"
namespace XE{

class XMultiListSkin
{
private:
	XBool m_isInited;
	void releaseTex();
public:
	XTextureData *mutiListNormal;
	XTextureData *mutiListDisable;
	XTextureData *mutiListSelect;
	XTextureData *mutiListMove;
	XTextureData *mutiListTitle;
	XTextureData *mutiListTitleEnd;

	XRect m_mouseRect;

	XMultiListSkin();
	~XMultiListSkin(){release();}
	XBool init(const char *normal,const char *disable,const char *select,const char *move,
		const char *title,const char *titleEnd,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};

struct XMultiListOneBox
{
	XBool isEnable;
	XBool isShow;
	XFontUnicode text;

	XVector2 order;
	char *string;
	int stringLength;
	XMultiListOneBox *nextBox;
	XMultiListOneBox()
		:string(NULL)
		,nextBox(NULL)
	{}
};

struct XMultiListOneRow
{
	XBool isEnable;
	char isShow;
	char needChip;
	float left;
	float right;
	XFontUnicode text;

	int order;
	int stringShowWidth;
	XVector2 position;
	XVector2 pixSize;
	int posX;
	int pixLen;
	char *title;
	XMultiListOneRow *nextRow;
	XSprite m_spriteTitleEnd;
	XSprite m_spriteTitle;
	XMultiListOneRow()
		:title(NULL)
		,nextRow(NULL)
	{}
};

#define MUTILIST_MIN_WIDTH (80)
#define MUTILIST_MAX_ROW_SUM (256)
#define MUTILIST_TITLE_EXPAND_LENGTH (100)
#ifndef DEFAULT_SLIDER_WIDTH
#define DEFAULT_SLIDER_WIDTH (32)
#endif
#ifndef DEFAULT_TITLE_HEIGHT
#define DEFAULT_TITLE_HEIGHT (32.0f)
#endif
#ifndef DEFAULT_END_WIDTH
#define DEFAULT_END_WIDTH (8.0f)
#endif

enum XMultiListActionType
{
	MLTLST_ACTION_TYPE_IN,
	MLTLST_ACTION_TYPE_MOVE,
	MLTLST_ACTION_TYPE_DCLICK,
	MLTLST_ACTION_TYPE_OUT,
};
class XMultiList:public XControlBasic
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
	int m_showStartLine;
	int m_showStartRow;
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
	int getLineSum() const {return m_tableLineSum;}
	int getRowSum() const {return m_tableRowSum;}
	void setTitleStr(const char *str);
	std::string getTitleStr();
	std::string getTitleStr(int order);
	void setTitleStr(const char *str,int order);
	void setBoxStr(const char *str,int line,int row);
	char *getBoxStr(int line,int row);
	XBool setRowWidth(int temp,int order);
	int getSelectIndex();

	enum XMultiListEvent
	{
		MLTLST_SELECT,
		MLTLST_DCLICK,
	};
private:

	XBool m_withMouseDrag;
public:

	void setWithMouseDrag(XBool flag) {m_withMouseDrag = flag;}
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

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
public:
	XBool init(const XVector2& position,
		const XRect& Area,
		const XMultiListSkin &tex,
		const XFontUnicode &font,
		float strSize,
		int rowSum,
		int lineSum,

		const XSlider &vSlider,
		const XSlider &hSlider);
	XBool initEx(const XVector2& position,
		const XMultiListSkin &tex,
		const XFontUnicode &font,
		float strSize,
		int rowSum,
		int lineSum,

		const XSlider &vSlider,
		const XSlider &hSlider);
	XBool initPlus(const char * path,
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

	XMultiList();
	~XMultiList(){release();}
	void release();
private:
	void releaseTempMemory();
public:

	XBool addALine();
	XBool addARow();
	XBool deleteSelectLine();
	XBool moveUpLine(int order);
	XBool moveLeftRow(int order);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XMultiList(const XMultiList &temp);
	XMultiList& operator = (const XMultiList& temp);

private:
	XMultiListActionType m_actionType;
	XMoveData m_actionMD;
	int m_actionPosition;
	void setAction(XMultiListActionType type,int index);

public:
	virtual XBool saveState(TiXmlNode &e);
	virtual XBool loadState(TiXmlNode *e);

};
#if WITH_INLINE_FILE
#include "XMultiList.inl"
#endif
}
#endif
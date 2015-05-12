#ifndef _JIA_XDIRECTORYLIST_
#define _JIA_XDIRECTORYLIST_

#include "XSlider.h"
#include "XEdit.h"
#include "XCheck.h"
#include "XButton.h"
#include "XDirectory.h"
namespace XE{

class XDirListSkin
{
private:
	XBool m_isInited;
public:
	XTextureData *dirListNormal;
	XTextureData *dirListDisable;

	XRect m_mouseRect;

	XDirListSkin();
	~XDirListSkin(){release();}
	XBool init(const char *normal,const char *disable,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};

class XDirListOneLine
{
public:
	XFontUnicode m_font;
	char *m_string;
	XCheck *m_check;
	XBool m_needCheck;
	XBool m_isEnable;

	XFileInfo *m_file;
	XDirListOneLine()
		:m_isEnable(XFalse)
		,m_needCheck(XFalse)
		,m_check(NULL)
		,m_string(NULL)
		,m_file(NULL)
	{}
	~XDirListOneLine(){release();}
	void release();
};
#ifndef DEFAULT_SLIDER_WIDTH
#define DEFAULT_SLIDER_WIDTH (32)
#endif
#ifndef DEFAULT_DIRLIST_BT_SIZE
#define DEFAULT_DIRLIST_BT_SIZE (40)
#endif
#ifndef DEFAULT_DIRLIST_CK_SIZE
#define DEFAULT_DIRLIST_CK_SIZE (28)
#endif
class XDirectoryList:public XControlBasic
{
private:
	XBool m_isInited;

	XDirectory m_dir;

	XSprite m_spriteBackGround;
	const XTextureData *m_dirListNormal;
	const XTextureData *m_dirListDisable;

	XBool m_needShowVSlider;
	XSlider m_verticalSlider;
	XBool m_needShowHSlider;
	XSlider m_horizontalSlider;
	XButton m_button;
	XEdit m_edit;
	XCheck m_check;

	XBool m_haveSelect;
	int m_selectLineOrder;
	int m_showStartLine;
	int m_canShowLineSum;

	int m_curLineSum;
	int m_mouseTime;

	int m_maxLineWidth;
	int m_curLineLeft;
	int m_canShowMaxLineWidth;

	std::vector<XDirListOneLine *> m_lineData;
	int m_showPixWidth;
	int m_showPixHight;

	XFontUnicode m_caption;
	XVector2 m_fontSize;
	XFColor m_textColor;
	float m_curTextWidth;
	float m_curTextHeight;
	void furlFolder(int index,XBool flag = XTrue);
	void updateHSliderState();
	void updateShowPosition();

	static void ctrlProc(void *,int,int);

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;

	XBool m_canChangePath;
public:
	XBool getCanChangePath() const {return m_canChangePath;}
	void setCanChangePath(XBool flag);
public:
	XBool init(const XVector2& position,
		const XRect& Area,
		XDirListSkin & tex,
		XFontUnicode &font,
		float fontSize,
		const XCheck &check,
		const XButton &button,
		const XEdit &edit,
		const XSlider &vSlider,
		const XSlider &hSlider);
	XBool initEx(const XVector2& position,
		XDirListSkin & tex,
		XFontUnicode &font,
		float fontSize,
		const XCheck &check,
		const XButton &button,
		const XEdit &edit,
		const XSlider &vSlider,
		const XSlider &hSlider);
	XBool initPlus(const char * path,
		XFontUnicode &font,float fontSize = 1.0f,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const XRect& area,
		XFontUnicode &font,float fontSize = 1.0f);
	XBool initWithoutSkin(const XRect& area) {return initWithoutSkin(area,XEE::systemFont,1.0f);}
	XBool initWithoutSkin(const XVector2& pixelSize)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),XEE::systemFont,1.0f);
	}
	const char * getSelectFileName() const;
	int getSelectLineOrder() const;
protected:

	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int) {;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
public:
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	using XObjectBasic::setColor;
	virtual void setColor(float r,float g,float b,float a);
	virtual void setAlpha(float a);

	void release();
	XDirectoryList()
		:m_isInited(XFalse)
		,m_resInfo(NULL)
		,m_withoutTex(XFalse)
		,m_canChangePath(XTrue)
	{
		m_ctrlType = CTRL_OBJ_DIRECTORYLIST;
	}
	~XDirectoryList(){release();}
};
#if WITH_INLINE_FILE
#include "XDirectoryList.inl"
#endif
}
#endif
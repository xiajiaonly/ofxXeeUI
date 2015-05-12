#ifndef _JIA_XIMAGELIST_
#define _JIA_XIMAGELIST_

#include "XButtonEx.h"
#include "XSlider.h"
#include <deque>
namespace XE{
class XImageList:public XControlBasic
{
private:
	XBool m_isInited;
public:
	enum XImageListEvent
	{
		IMGLST_INIT,
		IMGLST_RELEASE,
		IMGLST_SELECT_CHANGE,
	};

protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int,XKeyState){return XFalse;}
private:
	float m_buttonWidth;
	XVector2 m_imageSize;
	int m_showImageSum;
	int m_curSelectImageIndex;
	int m_curShowImageIndex;

	XButtonEx m_leftBtn;
	XButtonEx m_rightBtn;
	XSlider m_imageSld;

	std::deque<XSprite *> m_imageList;
	void updateState(bool flag = true);

	static void ctrlProc(void *,int,int);
public:
	XBool initWithoutSkin(float buttonWidth,
		const XVector2 &imageSize,
		int showImageSum);
	XBool addImage(const char * filename);
	XBool addImage(const XTextureData &tex);
	XBool addImage(const XSprite &sprite);

	XImageList()
		:m_isInited(XFalse)

	{
		m_ctrlType = CTRL_OBJ_IMAGELIST;
	}
	~XImageList() {release();}
	void release();
	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);

	void setTextColor(const XFColor&) {;}
	XFColor getTextColor() const {return XFColor::white;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
	void setCallbackFun(void (* funInit)(void *,int),
		void (* funRelease)(void *,int),
		void (* funSelectChange)(void *,int),
		void *pClass = NULL);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}

	void disable();
	void enable();
	void setVisible();
	void disVisible();
	XBool setACopy(const XImageList &)
	{
		return XFalse;
	}

private:
	XImageList(const XImageList &temp);
	XImageList& operator = (const XImageList& temp);
};
#if WITH_INLINE_FILE
#include "XImageList.inl"
#endif
}
#endif
#ifndef _JIA_XCHECK_
#define _JIA_XCHECK_

#include "XControlBasic.h"
#include "XResourcePack.h"
#include "XResourceManager.h"
#include "../XMath/XMoveData.h"
#include "../XOprateDes.h"
namespace XE{
class XCheckSkin
{
private:
	XBool m_isInited;
	void releaseTex();
public:
	XTextureData *checkChoosed;
	XTextureData *checkDischoose;
	XTextureData *checkDisableChoosed;
	XTextureData *checkDisableDischoose;

	XRect m_mouseRect;
	XVector2 m_fontPosition;

	XCheckSkin();
	~XCheckSkin(){release();}
	XBool init(const char *choosed,const char *disChoose,const char *disableChoosed,const char *disableDischoose,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};
class XRadios;
class XMultiListBasic;
class XDirectoryList;
class XChart;
class XPropertyLine;
class XCheck:public XControlBasic,public XBasicOprate
{
	friend XRadios;
	friend XMultiListBasic;
	friend XDirectoryList;
	friend XChart;
	friend XPropertyLine;
private:

	XBool m_isInited;
	XFontUnicode m_caption;

	const XTextureData *m_checkChoosed;
	const XTextureData *m_checkDischoose;
	const XTextureData *m_checkDisableChoosed;
	const XTextureData *m_checkDisableDischoose;

	XSprite m_sprite;
	XVector2 m_textPosition;
	XVector2 m_textSize;
	XFColor m_textColor;

	XBool m_state;
	XRect m_mouseClickArea;
	XBool m_withCaption;

	XBool *m_pVariable;

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
public:
	void setConnectVar(XBool * p) {m_pVariable = p;}
	void disConnectVar() {m_pVariable = NULL;}

public:
	XBool getWithCaption() const {return m_withCaption;}
	void setWithCaption(XBool withCaption) {m_withCaption = withCaption;}
	XBool init(const XVector2 & position,
		const XRect &Area,
		const XCheckSkin &tex,
		const char *caption,const XFontUnicode &font,float captionSize,
		const XVector2 &textPosition);
	XBool initEx(const XVector2 & position,
		const XCheckSkin &tex,
		const char *caption,const XFontUnicode &font,float captionSize = 1.0f);
	XBool initPlus(const char * path,
		const char *caption,const XFontUnicode &font,float captionSize = 1.0f,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const char *caption,
		const XFontUnicode &font,float captionSize,
		const XRect& area,const XVector2 &captionPosition);
	XBool initWithoutSkin(const char *caption,
		const XFontUnicode &font,const XRect& area);
	XBool initWithoutSkin(const char *caption,const XRect& area) {return initWithoutSkin(caption,XEE::systemFont,area);}
	XBool initWithoutSkin(const char *caption,const XVector2& pixelSize)
	{
		return initWithoutSkin(caption,XEE::systemFont,XRect(0.0f,0.0f,pixelSize.x,pixelSize.y));
	}
	XBool initWithoutSkin(const char *caption)
	{
		return initWithoutSkin(caption, XEE::systemFont, XRect(0.0f, 0.0f, MIN_FONT_CTRL_SIZE, MIN_FONT_CTRL_SIZE));
	}
protected:
	void draw();
	void drawUp();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
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

	void setCaptionText(const char *temp);
	const char *getCaptionString() const {return m_caption.getString();}
	XBool setACopy(const XCheck &temp);
	XCheck();
	~XCheck(){release();}
	void release();
	void disable();
	void enable();
	XBool getState() const;
	void setState(XBool temp);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XCheck(const XCheck &temp);
	XCheck& operator = (const XCheck& temp);
public:
	void setOprateState(void * data)
	{
		XBool index = *(XBool *)data;
		setState(index);
	}
	void *getOprateState() const
	{
		XBool *data = XMem::createMem<XBool>();
		*data =  getState();
		return data;
	}
	void releaseOprateStateData(void *p)
	{
		XBool *data = (XBool*)p;
		XMem::XDELETE(data);
	}
	virtual bool isSameState(void * data)
	{
		if(data == NULL) return false;
		return(*(XBool*)data == getState());
	}

private:

	XVector2 m_oldPos;
	XVector2 m_oldSize;
	XMoveData m_lightMD;
	XRect m_lightRect;
protected:
	void update(int stepTime);

public:
	enum XCheckEvent
	{
		CHK_INIT,
		CHK_RELEASE,
		CHK_MOUSE_ON,
		CHK_MOUSE_DOWN,
		CHK_MOUSE_UP,
		CHK_STATE_CHANGE,
	};

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		if(getState())
			return XXml::addLeafNode(e,m_ctrlName.c_str(),true);
		else
			return XXml::addLeafNode(e,m_ctrlName.c_str(),false);
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		bool tmpB;
		if(XXml::getXmlAsBool(e,m_ctrlName.c_str(),tmpB) == NULL) return XFalse;
		setState(tmpB);
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XCheck.inl"
#endif
}
#endif
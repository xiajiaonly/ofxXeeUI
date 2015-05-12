#ifndef _JIA_XSLIDER_
#define _JIA_XSLIDER_

#include "XButton.h"
#include "../XOprateDes.h"
namespace XE{
enum XSliderType
{
	SLIDER_TYPE_VERTICAL,
	SLIDER_TYPE_HORIZONTAL
};
enum XSliderState
{
	SLIDER_STATE_NORMAL,
	SLIDER_STATE_DOWN,
	SLIDER_STATE_ON,
	SLIDER_STATE_DISABLE
};
class XSliderSkin
{
private:
	XBool m_isInited;
	void releaseTex();
public:
	XTextureData *sliderLineNormal;
	XTextureData *sliderLineDown;
	XTextureData *sliderLineOn;
	XTextureData *sliderLineDisable;
	XTextureData *sliderButtonNormal;
	XTextureData *sliderButtonDown;
	XTextureData *sliderButtonOn;
	XTextureData *sliderButtonDisable;

	XRect m_mouseRect;
	XRect m_mouseRectButton;
	XVector2 m_fontPosition;

	XSliderSkin();
	~XSliderSkin(){release();}
	XBool init(const char *LNormal,const char *LDown,const char *LOn,const char *LDisable,
		const char *BNormal,const char *BDown,const char *BOn,const char *BDisable,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};
class XMultiList;
class XMultiListBasic;
class XMultiText;
class XDirectoryList;
class XSliderEx;
class XImageList;
class XPropertyBox;
class XSlider:public XControlBasic,public XBasicOprate
{
	friend XMultiList;
	friend XMultiListBasic;
	friend XMultiText;
	friend XDirectoryList;
	friend XSliderEx;
	friend XImageList;
	friend XPropertyBox;
private:
	XBool m_isInited;
	XSliderState m_curSliderState;

	XSliderType m_typeVorH;

	const XTextureData *m_sliderLineNormal;
	const XTextureData *m_sliderLineDown;
	const XTextureData *m_sliderLineOn;
	const XTextureData *m_sliderLineDisable;
	const XTextureData *m_sliderButtonNormal;
	const XTextureData *m_sliderButtonDown;
	const XTextureData *m_sliderButtonOn;
	const XTextureData *m_sliderButtonDisable;
public:
	enum XSliderEvent
	{
		SLD_INIT,
		SLD_RELEASE,
		SLD_MOUSE_ON,
		SLD_MOUSE_DOWN,
		SLD_MOUSE_UP,
		SLD_MOUSE_MOVE,
		SLD_VALUE_CHANGE,
	};
private:
	XRect m_buttonArea;

	XSprite m_buttonSprite;
	XSprite m_lineSprite;

	XBool m_needFont;
	XFontUnicode m_caption;
	std::string m_fontString;
	XVector2 m_textPosition;
	XVector2 m_textSize;
	XFColor m_textColor;

	float *m_pVariable;
public:
	void setConnectVar(float * p)
	{
		m_pVariable = p;
		setCurValue(*p);
	}
	void disConnectVar() {m_pVariable = NULL;}
private:
	XVector2 m_upMousePoint;
	XVector2 m_mouseFlyArea;
	XVector2 m_curButtonPosition;
	float m_minValue;
	float m_maxValue;
	float m_curValue;
	float m_upValue;
	XBool m_dataChanged;
	float m_keyOneValue;
	void updateButtonData();

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;

	void setTexture(const XSliderSkin &tex);
public:
	XBool init(const XVector2& position,
		const XRect& Area,
		const XRect& buttonArea,
		const XSliderSkin &tex,float max = 100.0f,float min = 0.0f,XSliderType type = SLIDER_TYPE_HORIZONTAL);
	XBool initEx(const XVector2& position,
		const XSliderSkin &tex,float max = 100.0f,float min = 0.0f,XSliderType type = SLIDER_TYPE_HORIZONTAL);
	XBool initPlus(const char * path,float max = 100.0f,float min = 0.0f,XSliderType type = SLIDER_TYPE_HORIZONTAL,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	XBool initWithoutSkin(const XRect& area,float max = 100.0f,float min = 0.0f,
		XSliderType type = SLIDER_TYPE_HORIZONTAL,const XVector2 &fontPosition = XVector2(0.0f,16.0f));
	XBool initWithoutSkin(const XVector2& pixelSize,float max = 100.0f,float min = 0.0f,
		XSliderType type = SLIDER_TYPE_HORIZONTAL,const XVector2 &fontPosition = XVector2(0.0f,16.0f))
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),max,min,type,fontPosition);
	}

	XBool setFont(const char *caption,const XFontUnicode &font,float captionSize = 1.0f,const XVector2 &fontPosition = XVector2(0.0f,16.0f));
	XBool setFont(const char *caption,const XVector2 &fontPosition)
	{
		return setFont(caption,XEE::systemFont,1.0f,fontPosition);
	}
	XBool setFont(const char *caption)
	{
		return setFont(caption,XEE::systemFont,1.0f,m_textPosition);
	}

	using XObjectBasic::setPosition;

	void setPosition(float x,float y);

	using XObjectBasic::setScale;

	void setScale(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;

	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
protected:
	void draw();
	void drawUp();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return !(m_curSliderState == SLIDER_STATE_DOWN);}
	void setLostFocus();
	float getMapValue(float v);
public:
	void setCurValue(float temp,bool cbFun = true);
	void setRange(float max,float min);

	XBool setACopy(const XSlider &temp);

	XSlider();
	~XSlider(){release();}
	void release();

	void disable();
	void enable();
	float getCurValue() const;
	float getMaxValue() const;
	float getMinValue() const;

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XSlider(const XSlider &temp);
	XSlider& operator = (const XSlider& temp);
public:
	virtual void setOprateState(void * data);
	virtual void *getOprateState() const;
	virtual void releaseOprateStateData(void *p);
	virtual bool isSameState(void * data);

private:
	XMoveData m_actionMoveData;
	XVector2 m_oldPos;
	XVector2 m_oldSize;
	XMoveData m_lightMD;
	XRect m_lightRect;
protected:
	void update(int stepTime);

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		if(!XXml::addLeafNode(e,m_ctrlName.c_str(),XString::toString(getCurValue()))) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		float tmp;
		if(XXml::getXmlAsFloat(e,m_ctrlName.c_str(),tmp) == NULL) return XFalse;
		setCurValue(tmp);
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XSlider.inl"
#endif
}
#endif
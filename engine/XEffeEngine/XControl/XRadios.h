#ifndef _JIA_XRADIOS_
#define _JIA_XRADIOS_

#include "XCheck.h"
namespace XE{
typedef XCheckSkin XRadiosSkin;

class XRadios:public XControlBasic,public XBasicOprate
{
private:
	XBool m_isInited;

	int m_radioSum;
	int m_curChoose;
	XCheck *m_radio;
	XVector2 *m_checkPosition;
	XVector2 m_distance;
public:
	enum XRadiosEvent
	{
		RDS_STATE_CHANGE,
	};
private:

	const XCheckSkin *m_texture;

	XFontUnicode m_caption;
	float m_captionSize;
	XFColor m_textColor;
	XVector2 m_textPosition;

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
public:
	XBool init(int radioSum,
		const XVector2& distance,
		const XVector2& position,
		const XRect &Area,
		const XRadiosSkin* tex,const XFontUnicode &font,float captionSize,
		const XVector2& textPosition);
	XBool initEx(int radioSum,
		const XVector2& distance,
		const XVector2& position,
		const XRadiosSkin* tex,const XFontUnicode &font,float captionSize = 1.0);
	XBool initPlus(int radioSum,
		const XVector2& distance,
		const char *path,const XFontUnicode &font,float captionSize = 1.0f,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(int radioSum,
		const XVector2& distance,
		const XRect &area,
		const XFontUnicode &font,float captionSize,
		const XVector2& textPosition);
	XBool initWithoutSkin(int radioSum,
		const XVector2& distance,
		const XRect &area,
		const XFontUnicode &font,
		const XVector2& textPosition)
	{
		return initWithoutSkin(radioSum,distance,area,font,1.0f,textPosition);
	}
	XBool initWithoutSkin(int radioSum,
		const XVector2& distance,
		const XRect &area,
		const XVector2& textPosition)
	{
		return initWithoutSkin(radioSum,distance,area,XEE::systemFont,1.0f,textPosition);
	}
	XBool initWithoutSkin(int radioSum,
		const XVector2& distance,
		const XVector2 &pixelSize,
		const XVector2& textPosition)
	{
		return initWithoutSkin(radioSum,distance,XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),
			XEE::systemFont,1.0f,textPosition);
	}
protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
public:
	void disable();
	void enable();
	void setChoosed(int temp);
	void setRadioPosition(const XVector2& position,int order);
	void setRadioPosition(float x,float y,int order);

	void setDistance(const XVector2& distance);
	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XBool setACopy(const XRadios &temp);
	XBool setRadioSum(int radioSum);

	XRadios();
	~XRadios(){release();}

	void release();

	int getCurChoose() const;
	void setRadioText(const char *temp,int order);
	void setRadiosText(const char * temp);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:
	XRadios(const XRadios &temp);
	XRadios& operator = (const XRadios& temp);
public:
	void setOprateState(void * data)
	{
		int index = *(int *)data;
		setChoosed(index);
	}
	void *getOprateState() const
	{
		int *data = XMem::createMem<int>();
		*data =  getCurChoose();
		return data;
	}
	void releaseOprateStateData(void *p)
	{
		int *data = (int*)p;
		XMem::XDELETE(data);
	}
	virtual bool isSameState(void * data)
	{
		if(data == NULL) return false;
		return(*(int*)data == getCurChoose());
	}

public:
	virtual XBool saveState(TiXmlNode &e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		if(!XXml::addLeafNode(e,m_ctrlName.c_str(),XString::toString(getCurChoose()))) return XFalse;
		return XTrue;
	}
	virtual XBool loadState(TiXmlNode *e)
	{
		if(!m_needSaveAndLoad) return XTrue;
		int tmp;
		if(XXml::getXmlAsInt(e,m_ctrlName.c_str(),tmp) == NULL) return XFalse;
		setChoosed(tmp);
		return XTrue;
	}

};
#if WITH_INLINE_FILE
#include "XRadios.inl"
#endif
}
#endif
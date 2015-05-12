#ifndef _JIA_XPROGRESS_
#define _JIA_XPROGRESS_

#include "XControlBasic.h"
#include "XResourcePack.h"
#include "XResourceManager.h"
#include "../XFont/XNumber.h"
namespace XE{
class XProgressSkin
{
private:
	XBool m_isInited;
public:
	XTextureData *progressBackGround;
	XTextureData *progressMove;
	XTextureData *progressUpon;

	XRect m_mouseRect;
	XVector2 m_fontPosition;

	XProgressSkin();
	~XProgressSkin(){release();}
	XBool init(const char *backgound,const char *move,const char *upon,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};

class XProgress:public XControlBasic
{
private:
	float m_curValue;
	XNumber m_caption;

	const XTextureData *m_progressBackGround;
	const XTextureData *m_progressMove;
	const XTextureData *m_progressUpon;

	XSprite m_spriteBackground;
	XSprite m_spriteMove;

	XSprite m_spriteUpon;

	XVector2 m_textPosition;
	XVector2 m_textSize;
	XFColor m_textColor;

	XBool m_isShowFont;
	XBool m_isACopy;
	XBool m_isInited;
	XBool m_withoutTex;
	char m_mode;
	XResourceInfo *m_resInfo;
public:
	XBool init(const XVector2& position,
		const XRect &Area,
		const XProgressSkin &tex,
		XNumber* font,float captionSize,const XVector2& textPosition,
		int mode = 0);
	XBool initEx(const XVector2& position,
		const XProgressSkin &tex,
		XNumber* font,float captionSize = 1.0f,
		int mode = 0);
	XBool initPlus(const char * path,
		XNumber* font,float captionSize = 1.0f,
		int mode = 0,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const XRect &area,
		XNumber* font = NULL,float captionSize = 1.0f,
		const XVector2& textPosition = XVector2(0.0f,0.0f),int mode = 0);
	XBool initWithoutSkin(const XVector2 &pixelSize,
		XNumber* font = NULL,float captionSize = 1.0f,
		const XVector2& textPosition = XVector2(0.0f,0.0f),int mode = 0)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),
			font,captionSize,textPosition,mode);
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
	void drawUp(){};
	XBool mouseProc(float,float,XMouseState){return XTrue;}
	XBool keyboardProc(int,XKeyState){return XTrue;}
	void insertChar(const char *,int){;}
	XBool canGetFocus(float,float){return XFalse;}
	XBool canLostFocus(float,float){return XTrue;}
public:
	void setValue(float temp);
	float getValue() const;

	XBool setACopy(const XProgress &temp);
	XProgress();
	~XProgress(){release();}
	void release();

	void enable();
	void disable();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
private:
	XProgress(const XProgress &temp);
	XProgress& operator = (const XProgress& temp);

};
#if WITH_INLINE_FILE
#include "XProgress.inl"
#endif
}
#endif
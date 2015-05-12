#ifndef _JIA_XPASSWARDPAD_
#define _JIA_XPASSWARDPAD_

#include "XButton.h"
namespace XE{

struct XPasswordPadData
{
	XVector2 bottonOffsetPosition;
	XVector2 bottonEffectArea;
	XVector2 bottonDistance;
	XVector2 bottonTextPosition;
	XVector2 captionPosition;
};
class XPasswordPadSkin
{
private:
	XBool m_isInited;
public:
	XButtonSkin m_bottomTex;
	XTextureData *backGround;
	XPasswordPadData m_data;
	XPasswordPadSkin()
		:m_isInited(XFalse)
		,backGround(NULL)
	{}
	~XPasswordPadSkin(){release();}
	XBool init(const char *normal,const char *down,const char *on,const char *disable,
		const char *BG,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
};

class XPasswordPad:public XControlBasic
{
private:
	static const int m_maxEnterTry = 3;
	static const int m_maxPasswardLength = 14;
	static const int m_minPasswardLength = 4;

	int m_mode;

	XPasswordPadData m_passwardPadData;

	int m_stage;
	int m_couter;
	char m_oldPassword[m_minPasswardLength + 1];
	char m_newPassword[m_maxPasswardLength + 1];
	char m_enterPassword[m_maxPasswardLength + 1];
	char m_enterPasswordLength;
	char m_showString[m_maxPasswardLength + 1];
	XBool m_isInited;

	XFontUnicode m_caption;
	XSprite m_sprite;
	XButton m_button[12];

	const XPasswordPadSkin *m_texture;

	static void ctrlProc(void*,int,int);

	void addChar(char temp);
	void btn11Proc();
	void btn10Proc();

	XResourceInfo *m_resInfo;
	XBool m_withoutTex;
public:
	XBool init(const XVector2& position,XPasswordPadSkin *tex,const XFontUnicode& font,const XPasswordPadData& data);
	XBool initEx(const XVector2& position,XPasswordPadSkin *tex,const XFontUnicode& font);
	XBool initPlus(const char * path,const XFontUnicode& font,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initWithoutSkin(const XFontUnicode& font);
	XBool initWithoutSkin() {return initWithoutSkin(XEE::systemFont);}
protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int,XKeyState) {return XTrue;}
	virtual void insertChar(const char *,int) {;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
public:
	int getIsEnd();

	void setPassword(const char *p);
	void getPassword(char *p) const;
	void setStart(int mode);
	void setDisShow();

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);
	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	XPasswordPad();
	~XPasswordPad();
private:
	XPasswordPad(const XPasswordPad &temp);
	XPasswordPad& operator = (const XPasswordPad& temp);
};
#if WITH_INLINE_FILE
#include "XPasswordPad.inl"
#endif
}
#endif
#ifndef _JIA_XCOMMENT_
#define _JIA_XCOMMENT_

#include "../XFont/XFontUnicode.h"
#include "../XBasicWindow.h"
#include "XCtrlColorStyle.h"
#include "../XMath/XMoveData.h"
namespace XE{

class XComment
{
private:
	static const int m_appearTime = 1000;
	static const int m_disappear = 3000;
	static const int m_maxTime = 4000;
private:
	XBool m_isInited;
	XFontUnicode m_font;
	XRect m_bgRect;
	XBool m_haveString;
	XBool m_visible;
	XBool m_needShow;

	int m_timer;
	float m_alpha;
	XMoveData m_alphaMD;
public:
	XBool init(const XFontUnicode&font);
	XBool init();
	void update(int stepTime);
	XBool setACopy(const XComment & temp);
	void setPosition(float x,float y);
	void draw();
	void setString(const char *str);
	void setVisible(){m_visible = XTrue;}
	void disVisible();
	void setShow();
	void disShow()
	{
		if(!m_needShow) return;
		if(m_timer <= m_appearTime)
		{
			m_needShow = XFalse;
			return;
		}
		if(m_timer >= m_disappear) return;

		m_timer = m_disappear - 1;
	}
	void setAlpha(float a)
	{
		m_alpha = a;
		m_font.setAlpha(a);
	}
	XBool getIsShow(){return m_needShow;}
	XComment()
		:m_isInited(XFalse)
		,m_haveString(XFalse)
		,m_visible(XTrue)
		,m_needShow(XFalse)
		,m_alpha(1.0f)
	{}
	~XComment(){}
};
#if WITH_INLINE_FILE
#include "XComment.inl"
#endif
}
#endif
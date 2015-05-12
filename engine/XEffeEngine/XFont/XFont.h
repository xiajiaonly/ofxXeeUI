#ifndef _JIA_XFONT_
#define _JIA_XFONT_

#include "XFontBasic.h"
namespace XE{
#ifndef TEXT_FONT_MODE
#define TEXT_FONT_MODE (" !\"#$%&\'()*+,-./0123456789:;<=>\?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")
#endif

class XFont:public XFontBasic
{
private:
	void updateData();
	XVector2 *m_textPosition;
	XRect *m_textRect;
	XVector2 m_layout;

public:
	XBool init(const char *filename,
		const XVector2& size,
		const XVector2& layout,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,XBool withFBO = XFalse);
	XBool initEx(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,XBool withFBO = XFalse);
	XBool initFromTTF(const char * filename,int fontSize,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,XBool withFBO = XFalse);

	XFont& operator = (const XFont& temp);
	XBool setACopy(const XFont &temp);
	XFont(const XFont &temp);

	void draw();
	XFont();
	XFont(int maxStrLen);
	~XFont();
	void setMaxStrLen(int maxStrLen)
	{
		XMem::XDELETE_ARRAY(m_string);
		XMem::XDELETE_ARRAY(m_textPosition);
		XMem::XDELETE_ARRAY(m_textRect);

		if(maxStrLen < 2) m_maxStringLen = 2;
		else m_maxStringLen = maxStrLen;
		m_string = XMem::createArrayMem<char>(m_maxStringLen);
		m_string[0] = '\0';
		m_textPosition = XMem::createArrayMem<XVector2>(m_maxStringLen);
		m_textRect = XMem::createArrayMem<XRect>(m_maxStringLen);

		m_needUpdateData = XTrue;
	}
};
#if WITH_INLINE_FILE
#include "XFont.inl"
#endif
}
#endif
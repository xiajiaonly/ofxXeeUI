#ifndef _JIA_XFONTUNICODE_
#define _JIA_XFONTUNICODE_

#include "XFontBasic.h"

namespace XE{

#define MAX_FONT_UNICODE_FILE_NAME_LENGTH (256)
#define UNICODE_FONT_PAGE_SUM (30)
#if !WITH_FULL_ALL_CHINESE
#define MAX_UNICODE_TEXT_SUM (8000)
#else
#define MAX_UNICODE_TEXT_SUM (50000)
#endif
#define UNICODE_BYTES_WIDTH (2)

class XFontUnicode:public XFontBasic
{
private:
	XSCounter *m_cp;

	int m_pageW;
	int m_pageH;
	char *m_fontPageText;
	int m_libFontSum;

	void updateData();
	XVector2 *m_textPosition;
	XRect *m_textRect;
	int *m_textPageOrder;

	XTextureData *m_texture;
	int m_pageSum;
	XVector2 m_layout;

public:
	XBool init(const char *filenameIn,
		const XVector2 &size,
		const XVector2 &layout,
		int pageSum,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,XBool withFBO = XFalse);
	XBool initEx(const char *filenameIn,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,XBool withFBO = XFalse);
	XBool initFromTTF(const char *filenameIn,int fontSize,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,bool withOutLine = false,XBool withFBO = XFalse);

	int getStringLengthPix();
private:

	int getTextIndex(const char p[UNICODE_BYTES_WIDTH]);
public:

	XFontUnicode& operator = (const XFontUnicode& temp);
	XBool setACopy(const XFontUnicode & temp);
	XFontUnicode(const XFontUnicode & temp);

	void release(){}
	void setRotateBasePoint(float x,float y);
	void draw();
	XFontUnicode();
	XFontUnicode(int maxStrLen);
	virtual ~XFontUnicode();

	void setMaxStrLen(int maxStrLen);
};

}
#endif
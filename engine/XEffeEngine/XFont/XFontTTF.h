#ifndef _JIA_XFONTTTF_
#define _JIA_XFONTTTF_

#include "../SDL_ttf/SDL_ttf.h"
#include "../XMath/XVector2.h"
namespace XE{
extern unsigned int loadTextureFormSDL(SDL_Surface *surface,XVector2& size);

#define MAX_TTF_FONT_FILE_SUM (16)

#pragma comment(lib, "../../engine/lib/FreeType/freetype253.lib")

enum XTTFRenderType
{
	RENDER_LATIN1,
	RENDER_UTF8,
	RENDER_UNICODE
};
struct XFontTTFInfo
{
	XBool isEnable;

	std::string filename;
	TTF_Font *font;
	int fontSize;
	int widthOfSpace;
	XTTFRenderType type;
	SDL_Color color;

	void setType(XTTFRenderType t)
	{
		type = t;
		if(font == NULL) return;
		switch(t)
		{
		case RENDER_LATIN1:
			TTF_SizeText(font," ",&(widthOfSpace),NULL);
			break;
		case RENDER_UTF8:
			TTF_SizeUTF8(font," ",&(widthOfSpace),NULL);
			break;
		case RENDER_UNICODE:
			{
				char tempStr[4] = "  ";
				tempStr[2] = '\0';
				tempStr[3] = '\0';
				TTF_SizeUNICODE(font,(Uint16 *)tempStr,&(widthOfSpace),NULL);
			}
			break;
		}
	}
	void setColor(SDL_Color c){color = c;}
	XFontTTFInfo()
		:isEnable(XFalse)
		,font(NULL)
		,type(RENDER_UTF8)
	{
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.unused = 0x00;
	}
};
class XFontTTF
{

protected:
	XFontTTF();
	XFontTTF(const XFontTTF&);
	XFontTTF &operator= (const XFontTTF&);
	virtual ~XFontTTF();
public:
	static XFontTTF& GetInstance();

private:
	XBool m_isInited;

	XFontTTFInfo m_fontInfo[MAX_TTF_FONT_FILE_SUM];

	int m_curLoadTTFFontFileSum;

	SDL_Surface * getSurface(int index,const char * str);
public:
	int getTTFFileOrder(const char * filename,int ptsize);
	int loadTTFFile(const char * filename,int ptsize,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	int releaseTTFFile(int order)
	{
		if(order < 0 || order >= MAX_TTF_FONT_FILE_SUM) return 0;
		if(!m_fontInfo[order].isEnable) return 0;

		TTF_CloseFont(m_fontInfo[order].font);
		m_fontInfo[order].isEnable = XFalse;
		m_fontInfo[order].font = NULL;
		-- m_curLoadTTFFontFileSum;
		return 1;
	}
	void setAttitude(int fontOrder,XTTFRenderType type,SDL_Color color)
	{
		if(fontOrder >= 0 && fontOrder < MAX_TTF_FONT_FILE_SUM && m_fontInfo[fontOrder].isEnable)
		{
			m_fontInfo[fontOrder].setType(type);
			m_fontInfo[fontOrder].setColor(color);
		}

	}
	void setOutline(int fontOrder,int outLine)
	{
		if(fontOrder >= 0 && fontOrder < MAX_TTF_FONT_FILE_SUM &&
			m_fontInfo[fontOrder].isEnable)
		{
			TTF_SetFontOutline(m_fontInfo[fontOrder].font,outLine);
		}
	}
	void setStyle(int fontOrder,int style)
	{
		if(fontOrder >= 0 && fontOrder < MAX_TTF_FONT_FILE_SUM &&
			m_fontInfo[fontOrder].isEnable)
		{
			TTF_SetFontStyle(m_fontInfo[fontOrder].font,style);
		}
	}
	unsigned int getTexture(int fontOrder,const char * str,XVector2& size);
	void release()
	{
		for(int i = 0;i < MAX_TTF_FONT_FILE_SUM;++ i)
		{
			if(m_fontInfo[i].isEnable)
			{
				TTF_CloseFont(m_fontInfo[i].font);
				m_fontInfo[i].isEnable = XFalse;
				m_fontInfo[i].font = NULL;
			}
		}
		m_curLoadTTFFontFileSum = 0;
	}

	XBool getTextureNumber(int fontOrder,unsigned int &tex,XVector2 &layout);
	XBool getTextureFont(int fontOrder,unsigned int &tex,XVector2 &layout);
	XBool getTextureFontUnicode(int fontOrder,unsigned int *tex,int& texSum,XVector2 &layout,XBool withBlackOutLine = XFalse);
};
}
#endif
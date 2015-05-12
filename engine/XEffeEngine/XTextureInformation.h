#ifndef _JIA_XALLTEXTURE_
#define _JIA_XALLTEXTURE_

#include "XOSDefine.h"
#include "XBasicOpenGL.h"
namespace XE{
#define TEX_INFO_DEBUG (0)

class XTextureData
{
private:
	int m_ID;
	XBool m_isInited;
public:
	char isEnableInsideClip;
	XRect clipInsideRect;

	void setNoInited() {m_isInited = XFalse;}
	XTexture texture;
	XVector2 textureMove;
	XVector2 textureMove2;
	XVector2 textureSize;
	void updateTexture(const XPBO &pbo){texture.updateTexture(pbo);}
	void updateTextureR2B(const XPBO &pbo){texture.updateTextureR2B(pbo);}
	void updateTexture(const void * p);
	void updateTextureR2B(const void * p);
	XTextureData()
		:textureMove(0.0f,0.0f)

		,textureMove2(0.0f,0.0f)
		,isEnableInsideClip(-1)
		,clipInsideRect(0,0,1,1)
		,m_isInited(XFalse)
		,textureSize(0.0f,0.0f)
	{
		static int id = 0;
		m_ID = id ++;
	}

	~XTextureData(){release();}
	int getID() const {return m_ID;}
	XBool load(const char * filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool loadEmpty();
	XBool createWithTexture(int w,int h,XColorMode colorMode,unsigned int tex);

	XBool createTexture(int w,int h,XColorMode colorMode);
	void release();
	XBool setACopy(const XTextureData& temp);
	XTextureData& operator = (const XTextureData& temp);
	void bind() {texture.bind();}
	XBool reset() {return texture.reset();}
private:
	XTextureData(const XTextureData& temp);
};
inline XTextureData * createATextureData(const char * filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE)
{
	XTextureData *ret = XMem::createMem<XTextureData>();
	if(ret == NULL) return NULL;
	if(!ret->load(filename,resoursePosition))
	{
		XMem::XDELETE(ret);
		return NULL;
	}
	return ret;
}
#if TEX_INFO_DEBUG
extern int texInfoSum;
#endif
class XTextureInfo
{
private:
	XSCounter *m_cp;
public:
	char *textureName;

	XTexture texture;
	XVector2 textureOffset;
	XVector2 textureMove;
	XVector2 textureMove2;
	XVector2 textureSize;

	XTextureInfo()
		:textureOffset(0.0f,0.0f)
		,textureMove(0.0f,0.0f)
		,textureMove2(0.0f,0.0f)
		,textureSize(0.0f,0.0f)

	{
		m_cp = new XSCounter;
		textureName = XMem::createArrayMem<char>(MAX_FILE_NAME_LENGTH);
		textureName[0] = '\0';

#if TEX_INFO_DEBUG
		++ texInfoSum;
		printf("%d-\n",texInfoSum);
#endif
	}
	~XTextureInfo()
	{
		if(m_cp != NULL && --m_cp->m_counter <= 0)
		{
			XMem::XDELETE(m_cp);
			XMem::XDELETE_ARRAY(textureName);

#if TEX_INFO_DEBUG
			-- texInfoSum;
			printf("%d-\n",texInfoSum);
#endif
		}
	}

	XTextureInfo(const XTextureInfo & temp);

	XTextureInfo& operator = (const XTextureInfo& temp);
};

class XAllTexture
{

protected:
	XAllTexture();
	XAllTexture(const XAllTexture&);
	XAllTexture &operator= (const XAllTexture&);
	virtual ~XAllTexture(){release();}
public:
	static XAllTexture& GetInstance()
	{
		static XAllTexture m_instance;
		return m_instance;
	}

private:
	XResourcePosition m_resoursePosition;
private:
	XBool m_isInited;
	XBool m_isEnable;

	int m_textureSum;
	int m_targetTextureSum;

	XTextureInfo *m_texInfo;
	XTexture *m_pTexture;

public:
	XBool init(XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool getTexture(const char *temp,XTextureInfo &texInfo);

	void release();
};

extern XBool reductionTexture(const unsigned char *p,int length,const XTextureInfo &texInfo);
#if WITH_INLINE_FILE
#include "XTextureInformation.inl"
#endif
}
#endif
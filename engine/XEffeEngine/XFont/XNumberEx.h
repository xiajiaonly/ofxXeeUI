#ifndef _JIA_XNUMBEREX_
#define _JIA_XNUMBEREX_

#include "XSprite.h"
namespace XE{
#ifndef TEXT_MODE
#define TEXT_MODE "0123456789+-*/%."
#endif
#ifndef MAX_NUMBER_LENGTH
#define MAX_NUMBER_LENGTH 256
#endif

class XNumberTexture
{
private:
	XResourcePosition m_resoursePosition;
	XBool m_isInited;
public:

	XTextureData *m_texture00;
	XTextureData *m_texture01;
	XTextureData *m_texture02;
	XTextureData *m_texture03;
	XTextureData *m_texture04;
	XTextureData *m_texture05;
	XTextureData *m_texture06;
	XTextureData *m_texture07;
	XTextureData *m_texture08;
	XTextureData *m_texture09;
	XTextureData *m_texture0a;
	XTextureData *m_texture0b;
	XTextureData *m_texture0c;
	XTextureData *m_texture0d;
	XTextureData *m_texture0e;
	XTextureData *m_texture0f;

public:
	XBool init(const char *fileName,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void release();
	XNumberTexture();
};

class XNumberEx
{
private:
	const XNumberTexture *m_numberTexture;

	XSprite m_sprite;

	float m_angleSin;
	float m_angleCos;
public:
	char *m_number;
	XVector2 m_position;
	XVector2 m_setPosition;
	float m_angle;
	float m_distance;
	XVector2 m_size;
	XVector2 m_showSize;
	XVector2 m_rotateBasicPoint;
	char m_blendTypeScr;
	char m_blendTypeDst;
private:
	XBool m_isInited;
public:
	void setBlendType(int typeScr,int typeDst)
	{
		if(typeScr < 0) typeScr = 0;
		if(typeDst < 0) typeDst = 0;
		if(typeScr >= 9 ) typeScr = 8;
		if(typeDst >= 8 ) typeDst = 7;
		m_blendTypeScr = typeScr;
		m_blendTypeDst = typeDst;
		m_sprite.setBlendType(m_blendTypeScr,m_blendTypeDst);
	}

	XBool init(const XNumberTexture *numberTexture,const XVector2 &size);
	void draw();

	void setScale(const XVector2& scale);
	void setScale(float x,float y);
	void setAngle(float angle);
	void setPosition(const XVector2& position);
	void setPosition(float x,float y);
	void setRotateBasePoint(float x,float y);

	XBool setNumber(int temp);
	XBool setNumber(float temp,int decimalPartLength);
	XBool setNumber(const char *temp);
	XNumberEx& operator = (const XNumberEx& temp);
	XBool setACopy(const XNumberEx &temp);
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
	float getAlpha() const {return m_sprite.getAlpha();}
	XBool release();

	void setDistance(float distance){m_distance = distance;}
	float getDistance() const {return m_distance;}
	XNumberEx();
};
#if WITH_INLINE_FILE
#include "XNumberEx.inl"
#endif
}
#endif

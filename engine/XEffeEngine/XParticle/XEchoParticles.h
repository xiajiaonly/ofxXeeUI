#ifndef _JIA_XECHOPARTICLES_
#define _JIA_XECHOPARTICLES_

#include "XParticle.h"
namespace XE{

class XEchoParticles
{
public:
	char m_isInited;
	char m_isEnd;
private:
	static const int m_maxEchoParticlesSum = 16;
	char m_isSetEnd;
	char m_blendRGBScr;
	char m_blendRGBDst;
	char m_blendAScr;
	char m_blendADst;
	char m_blendTypeScr;
	char m_blendTypeDst;
	XGL::XBlendType m_blendType;
	int m_insertSum;
	int m_density;

	int m_curPoint;

	const XTexture *m_texture;
	int w;
	int h;
	int halfW;
	int halfH;

	int m_atomSum;
	int m_haveGetmemory;
public:
	void setBlendType(int typeScr,int typeDst)
	{
		if(typeScr < 0) typeScr = 0;
		if(typeDst < 0) typeDst = 0;
		if(typeScr >= 9 ) typeScr = 8;
		if(typeDst >= 8 ) typeDst = 7;
		m_blendTypeScr = typeScr;
		m_blendTypeDst = typeDst;
	}
	void setBlendType(int rgbScr,int rgbDst,int aScr,int aDst)
	{
		if(rgbScr < 0) rgbScr = 0;
		if(rgbScr >= 9 ) rgbScr = 8;
		if(aScr < 0) aScr = 0;
		if(aScr >= 9 ) aScr = 8;

		if(rgbDst < 0) rgbDst = 0;
		if(rgbDst >= 8 ) rgbDst = 7;
		if(aDst < 0) aDst = 0;
		if(aDst >= 8 ) aDst = 7;
		m_blendRGBScr = rgbScr;
		m_blendRGBDst = rgbDst;
		m_blendAScr = aScr;
		m_blendADst = aDst;
	}
	void setBlendMode(XGL::XBlendType mode) {m_blendType = mode;}

public:
	XParentParticle m_parentParticle;
	XBasicParticle *m_particles;

	int init(const XTexture *texture,
		int insertSum,
		int density,
		const XVector2& position,
		float dSize,
		float dAlpha,
		int atomSum = 0,
		float initSize = 1.0f);
	void setDSize(float dSize);
	void setDAlpha(float dAlpha);
	void setInsertSum(float insertSum);
	void setDensity(float density);
	void setTexture(const XTexture *texture)
	{
		if(texture == NULL || !glIsTexture(texture->m_texture)) return;
		m_texture = texture;
	}
	void setPosition(const XVector2 &position);
	void setPosition(float x,float y);
	void setPosition(float x,float y,float size);
	void setPosition(float x,float y,float size,float udR,float udG = 1.0f,float udB = 1.0f);
	void setAlpha(float temp);
	void move(int timeDelay);
	void moveEx(float sizeX,float sizeY,float alpha);

	void draw() const;

	void drawAsLine() const;

	void drawExBegin() const;
	void drawExBody() const;
	void drawExEnd() const {XGL::DisableBlend();}

	void drawExBeginEx() const;
	void drawExBodyEx() const;
	void drawExEndEx() const
	{
		glEnd();
		XGL::DisableBlend();
	}

	XEchoParticles();
	void release();
	int getMemory(int atomSum);
	void setEnd();
	void reset();
	void resetState(const XVector2& position,float initSize = 1.0f);
	int getIsEnd();
};
inline void XEchoParticles::setEnd()
{
	if(m_isInited != 0 && m_isEnd == 0 && m_isSetEnd == 0) m_isSetEnd = 1;
}
inline void XEchoParticles::reset()
{
	if(m_isInited != 0 && m_isEnd != 0)
	{
		m_isEnd = 0;
		m_isSetEnd = 0;
	}
}
inline void XEchoParticles::resetState(const XVector2& position,float initSize)
{
	if(m_isInited == 0) return;
	m_parentParticle.m_initColor.setColor(1.0f,1.0f,1.0f,1.0f);
	m_parentParticle.m_initPosition = position;
	m_parentParticle.m_curPosition = position;
	m_parentParticle.m_initSize.set(initSize,initSize);
	m_curPoint = 0;
	for(int i = 0;i < m_atomSum;++ i)
	{
		m_particles[i].m_isEnable = 0;
	}
}
inline int XEchoParticles::getIsEnd()
{
	return m_isEnd;
}
inline void XEchoParticles::setAlpha(float temp)
{
	if(temp < 0) m_parentParticle.m_initColor.setA(0.0f);
	else if(temp > 1) m_parentParticle.m_initColor.setA(1.0f);
	else m_parentParticle.m_initColor.setA(temp);
}
inline void XEchoParticles::setDSize(float dSize)
{
	m_parentParticle.m_dSize.x = dSize;
}
inline void XEchoParticles::setDAlpha(float dAlpha)
{
	m_parentParticle.m_dColor.setA(dAlpha);
}
inline void XEchoParticles::setInsertSum(float insertSum)
{
	if(insertSum < 0) insertSum = 0;
	m_insertSum = insertSum;
}
inline void XEchoParticles::setDensity(float density)
{
	if(density < 1) density = 1;
	m_density = density;
}
inline void XEchoParticles::setPosition(const XVector2 &position)
{
	setPosition(position.x,position.y);
}
}
#endif
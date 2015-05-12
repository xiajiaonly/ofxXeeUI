#ifndef _JIA_XFRAMEEX_
#define _JIA_XFRAMEEX_

#include "XSprite.h"
namespace XE{
class XFrameEx:public XObjectBasic
{

private:
	XSprite *m_pSprite;

	XSCounter *m_cp;
	XResourcePosition m_resoursePosition;
	float angle;
	XBool m_isVisible;
public:
	void setAngle(float temp);
	float getAngle() const;
	void setVisible()
	{
		m_isVisible = XTrue;
		updateChildVisible();
	}
	void disVisible()
	{
		m_isVisible = XFalse;
		updateChildVisible();
	}
	XBool getVisible() const {return m_isVisible;}
private:
	float x, y;
	float xsize, ysize;
	float alpha;
	float colorRed;
	float colorGreen;
	float colorBlue;
	XBool m_isOverturn;

	int m_allFramesSum;
	int m_allKeyFramesSum;
	float m_curFramesNumble;
	float m_actionSpeed;
	XBool m_isLoop;
	int m_startFrame;
	XBool m_isEnd;
	XBool m_isEndImmediately;
	XBool m_isSetEnd;
	XBool m_isDisappearAtEnd;

	char *m_frameName;
	int *m_keyFrameArray;
public:
	void setAttribute(const XVector2& position,
		XBool loop,
		XBool endImmediately,
		int startFrame,
		float actionSpeed,
		XBool disappearAtEnd,
		XBool isOverturn = XFalse);

	using XObjectBasic::setPosition;
	void setPosition(float a,float b);
	void setPositionX(float a);
	void setPositionY(float b);
	XVector2 getPosition() const;

	using XObjectBasic::setScale;
	void setScale(float x,float y);
	XVector2 getScale() const;

	XBool getIsEnd() const;
	void setEnd();
	void reset();
	void move(int timeDelay);
	int getAllFramesSum() const {return m_allFramesSum;}
	float getCurFramesNumber() const {return m_curFramesNumble;}

	XSprite * getCurSprite(char frameFlag = 0);
private:
	XBool m_isInited;
	char m_blendTypeScr;
	char m_blendTypeDst;
	XShaderGLSL *m_pShader;
public:
	void setBlendType(int typeScr,int typeDst)
	{
		if(typeScr < 0) typeScr = 0;
		if(typeDst < 0) typeDst = 0;
		if(typeScr > 8 ) typeScr = 8;
		if(typeDst > 7 ) typeDst = 7;
		m_blendTypeScr = typeScr;
		m_blendTypeDst = typeDst;
		for(int i = 0;i < m_allKeyFramesSum;++ i)
		{
			m_pSprite[i].setBlendType(m_blendTypeScr,m_blendTypeDst);
		}
	}

	void setShaderClass(XShaderGLSL * shader) {m_pShader = shader;}

	XBool init(const char *filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	void setIsTransformCenter(XTransformMode temp)
	{
		if(!m_isInited) return;
		for(int i = 0;i < m_allKeyFramesSum;++ i)
		{
			m_pSprite[i].setIsTransformCenter(temp);
		}
	}
private:
	XBool releaseMem();
public:
	void release(){}
	void draw();

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	XFColor getColor() const
	{
		if(m_pSprite == NULL) return XFColor::white;
		else return m_pSprite[0].getColor();
	}
	void setAlpha(float a);
	float getAlpha() const;

	void setActionSpeed(float actionSpeed);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
private:
	XBool m_isACopy;
	XFrameEx(const XFrameEx &temp);
public:
	XFrameEx& operator = (const XFrameEx& temp);
	void setACopy(const XFrameEx& temp);

	void setRestart();

	XFrameEx();
	~XFrameEx();

};

struct XFrameExParamData
{
	XResourcePosition resourcePosition;
	XVector2 pos;
	XBool loop;
	XBool endImmediately;
	int startFrame;
	float actionSpeed;
	XBool disappearAtEnd;
	XBool isOverturn;

	char * getStrFromData();
	int getDataFromStr(const char * str);
	XBool getDataFromFile(FILE *fp);

	XFrameExParamData()
		:resourcePosition(RESOURCE_SYSTEM_DEFINE)
		,pos(0.0f,0.0f)
		,loop(XFalse)
		,endImmediately(XFalse)
		,startFrame(0)
		,actionSpeed(0.03f)
		,disappearAtEnd(XFalse)
		,isOverturn(XFalse)
	{}
};
#if WITH_INLINE_FILE
#include "XFrameEx.inl"
#endif
}
#endif
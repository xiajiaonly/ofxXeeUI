#ifndef _JIA_XFRAME_
#define _JIA_XFRAME_

#include "XBasicClass.h"
#include "XBasicOpenGL.h"
#include "XShaderGLSL.h"
namespace XE{
class XFrame
{
private:
	static const int m_maxFrameSum = 65;
	XSCounter *m_cp;

	XResourcePosition m_resoursePosition;
	XBool m_isInited;

	float angle;
	float angleRadian;
	float sinAngle;
	float cosAngle;
	XShaderGLSL *m_pShader;
public:
	void setAngle(float temp);
	float getAngleDegree();
	float getAngleRadian();
	XBool m_isFlash;

	void setShaderClass(XShaderGLSL * shader) {m_pShader = shader;}
private:
	float x, y;
	float xsize, ysize;
	float alpha;
	float colorRed;
	float colorGreen;
	float colorBlue;
	XBool m_isOverturn;
	XBool m_isVisible;

	XTexture *m_texnum;

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

	int *wre;
	int *hre;
	int *xpa;
	int *ypa;

	char *m_frameName;
	int *m_keyFrameArray;

	float m_centerX;
	float m_centerY;
	float *m_centerDW;
	float *m_centerDH;
	XVector2 *m_keyFramePosition;

public:
	void setVisible() {m_isVisible = XTrue;}
	void disVisible() {m_isVisible = XFalse;}
	XBool getVisible() const {return m_isVisible;}

	void setAttribute(const XVector2& position,
		XBool loop,
		XBool endImmediately,
		int startFrame,
		float actionSpeed,
		XBool disappearAtEnd,
		XBool isOverturn = XFalse);

	void setPosition(const XVector2& position);
	void setPosition(float a,float b);
	XVector2 getPosition() const;

	int getCurX() const;
	int getCurY() const;

	int getCurWidth() const;
	int getCurHeight() const;

	int getInitHalfWidth() const;
	int getInitHalfHeight() const;

	void setSize(const XVector2& size);
	void setSize(float x,float y);
	XVector2 getSize();

	XBool getIsEnd() const;
	void setEnd();
	void reset();
	void move(int timeDelay);

	XTexture * getTexture(int frameFlag = 0);

	XBool init(const char *filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
private:
	XBool releaseMem();
public:
	void release(){}
	void draw(const GLuint *pTexnum = NULL) const;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float alpha);
	float getAlpha() const;

	void setActionSpeed(float actionSpeed);
private:

	XBool m_isACopy;
	XFrame(const XFrame& temp);
public:
	XFrame& operator = (const XFrame& temp);
	void setACopy(const XFrame& temp);

	void setRestart();

	XFrame();

	~XFrame();

	int getAllKeyFrameSum() const {return m_allKeyFramesSum;}
	XVector2 getKeyFramePos(int index) const {return m_keyFramePosition[index];}
	int getKeyFrameWre(int index) const {return wre[index];}
	int getKeyFrameHre(int index) const {return hre[index];}
};

#if WITH_INLINE_FILE
#include "XFrame.inl"
#endif
}
#endif
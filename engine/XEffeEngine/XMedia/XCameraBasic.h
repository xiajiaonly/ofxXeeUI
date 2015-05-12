#ifndef _JIA_XCAMERABASIC_
#define _JIA_XCAMERABASIC_

#include "../XOSDefine.h"
#include "../XBasicOpenGL.h"
#include "../XSprite.h"
namespace XE{
#define SUPPORT_FOR_HIK (1)

enum XCameraType
{
	CAMERA_TYPE_NORMAL,
#if SUPPORT_FOR_HIK
	CAMERA_TYPE_HIK,
#endif
	CAMERA_TYPE_AVER,
};

struct XCameraData
{
	int w;
	int h;
	int fps;
	int deviceOrder;
	XCameraType cameraType;

	void setNormal(int width,int height,int order = 0,int setfps = 30)
	{
		w = width;
		h = height;
		deviceOrder = order;
		fps = setfps;
		cameraType = CAMERA_TYPE_NORMAL;
	}
#if SUPPORT_FOR_HIK
	char ipAddress[16];
	char userName[64];
	char pwd[16];
	int port;

	void setHIK(int width,int height,const char *add,const char *usern,
		const char * passward,int p = 8000)
	{
		if(add == NULL || usern == NULL || passward == NULL) return;
		w = width;
		h = height;
		strcpy(ipAddress,add);
		strcpy(userName,usern);
		strcpy(pwd,passward);
		port = p;
		cameraType = CAMERA_TYPE_HIK;
	}
#endif
};

class XCameraBasic
{
private:
protected:
	XBool m_isInited;

	int m_cameraWidth;
	int m_cameraHeight;
	int m_cameraTexWidth;
	int m_cameraTexHeight;
	int m_buffSize;

	XBool m_isWork;
public:
	XTexture m_cameraTex;
	int getWidth() const {return m_cameraWidth;}
	int getHeight() const {return m_cameraHeight;}
	int getTexWidth() const {return m_cameraTexWidth;}
	int getTexHeight() const {return m_cameraTexHeight;}
	GLuint getCameraTex() const {return m_cameraTex.m_texture;}
	XSprite m_cameraSprite;

	void setWork() {m_isWork = XTrue;}
	void setStop() {m_isWork = XFalse;}
	XBool getWorkState() const {return m_isWork;}

	virtual XBool init(XCameraData &data) = 0;
	virtual void release() = 0;
	virtual XBool updateFrame() = 0;

	virtual int getBuffSize() const{return m_buffSize;}
	virtual void getData(unsigned char * p) const = 0;
	virtual unsigned char * getDataP() const = 0;

	virtual void draw()
	{
		if(!m_isInited) return;
		m_cameraSprite.draw(&m_cameraTex.m_texture);
	}

	XCameraBasic()
		:m_isInited(XFalse)
		,m_isWork(XTrue)
	{}
	virtual ~XCameraBasic(){}
};
}
#endif
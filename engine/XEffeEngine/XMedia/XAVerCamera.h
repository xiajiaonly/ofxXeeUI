#ifndef _JIA_XAVERCAMERA_
#define _JIA_XAVERCAMERA_

#include "XMedia/XCameraBasic.h"

#include "AVer/AVerCapAPI.h"
#pragma comment(lib,"../lib/AVer/AVerCapAPI.lib")
namespace XE{
class XAVerCamera:public XCameraBasic
{
private:
	HANDLE m_hHDCaptureDevice;
	int m_deviceSum;
	int m_deviceOrder;
	unsigned char *m_frameDataBuff1;
	unsigned char *m_frameDataBuff;
	unsigned char *m_texDataBuff;
	unsigned char *m_pixelsData;
	int m_px;
	int m_py;
	XBool m_isUp2Down;
	XBool m_isLeft2Right;
	friend BOOL WINAPI avCameraCB(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData,LONG lLength, __int64 tRefTime, LONG lUserData);
	XBool m_isNewFrame;

	XBool setPixels(const XCameraData &data);
public:
	void setUp2Down(XBool flag){m_isUp2Down = flag;}
	void setLeft2Right(XBool flag){m_isLeft2Right = flag;}

	void getData(unsigned char * p) const
	{
		if(!m_isInited) return;
		memcpy(p,m_pixelsData,m_buffSize);
	}
	unsigned char * getDataP() const
	{
		if(!m_isInited) return NULL;
		return m_pixelsData;
	}

	XBool init(XCameraData &data);
	XBool updateFrame();

	XAVerCamera()
		:m_frameDataBuff1(NULL)
		,m_frameDataBuff(NULL)
		,m_texDataBuff(NULL)
		,m_isUp2Down(XFalse)
		,m_isLeft2Right(XFalse)
		,m_isNewFrame(XFalse)
	{}
	~XAVerCamera(){release();}
	void release();
};
}
#endif
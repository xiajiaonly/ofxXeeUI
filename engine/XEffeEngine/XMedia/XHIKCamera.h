#ifndef _JIA_XHIKCAMERA_
#define _JIA_XHIKCAMERA_

#include "XCameraBasic.h"

#if SUPPORT_FOR_HIK

#include "HIK/HCNetSDK.h"
#include "HIK/plaympeg4.h"

#pragma comment(lib, "../../engine/lib/HIK/PlayCtrl.lib")
#pragma comment(lib, "../../engine/lib/HIK/HCNetSDK.lib")
#pragma comment(lib, "../../engine/lib/HIK/DsSdk.lib")
#pragma comment(lib, "../../engine/lib/HIK/GdiPlus.lib")
namespace XE{
#define HIK_WITH_LOECORE (1)

class XHIKCamera:public XCameraBasic
{
private:
	bool m_isGetInitData;
	void setInitData(int w,int h);
	LONG m_lUserID;
	NET_DVR_DEVICEINFO_V30 m_structDeviceInfo;
	LONG m_lRealPlayHandle;
	LONG m_lPort;

	unsigned char *m_dataRGB;
	XBool m_haveNewFrame;
	XBool isNewFrame()
	{
		XBool ret = m_haveNewFrame;
		m_haveNewFrame = XFalse;
		return ret;
	}

	static void CALLBACK decCBFun(long,char *,long,FRAME_INFO *, long,long);
	static void CALLBACK realDataCB(LONG, DWORD, BYTE *,DWORD ,void* );
	static void CALLBACK exceptionCB(DWORD, LONG, LONG, void *);
#if HIK_WITH_LOECORE
	unsigned char *m_yuvData;
	XCritical m_mutex;
#endif
public:
	XBool init(XCameraData &data);
	void getData(unsigned char * p) const
	{
		if(!m_isInited) return;
		memcpy(p,m_dataRGB,m_buffSize);
	}
	unsigned char * getDataP() const
	{
		if(!m_isInited) return NULL;
		return m_dataRGB;
	}

	XBool updateFrame();

	XHIKCamera()
		:m_haveNewFrame(XFalse)
		,m_dataRGB(NULL)
		,m_isGetInitData(false)
#if HIK_WITH_LOECORE
		,m_yuvData(NULL)
#endif
	{}
	~XHIKCamera() {release();}
	void release();
};

}
#endif

#endif

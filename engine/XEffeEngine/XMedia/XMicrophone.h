#ifndef _JIA_XMICROPHONE_
#define _JIA_XMICROPHONE_
#include "al.h"
#include "alc.h"
#include "stdlib.h"
#include "XBasicFun.h"

#pragma comment(lib, "../../engine/lib/Alut/alut.lib")
#pragma comment(lib, "../../engine/lib/OpenAL/Win32/OpenAL32.lib")

namespace XE{
enum XCaptureState
{
	CAPTURE_STATE_STOP,
	CAPTURE_STATE_START,
};
class XMicrophone
{
private:
	XBool m_isInited;
	ALCdevice * m_pCaptureDev;
	ALCuint m_frequency;
	ALCenum m_format;
	ALCsizei m_buffersize;
	XCaptureState m_captureState;

	unsigned char *m_captureData;
	int m_dataBuffMaxSize;
	int m_curDataBuffSize;
	int m_byteRate;
public:
	XCaptureState getCaptureState() const {return m_captureState;}
	void printAllCaptureDevice();
	XBool openDevice(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
	void captureStart() const
	{
		if(m_captureState == CAPTURE_STATE_STOP
			&& m_isInited) alcCaptureStart(m_pCaptureDev);
	}
	void captureStop() const
	{
		if(m_captureState == CAPTURE_STATE_START
			&& m_isInited) alcCaptureStop(m_pCaptureDev);
	}
	unsigned char * getCaptureData(int * size = NULL);
	int getByteRate() const {return m_byteRate;}

	void release()
	{
		if(!m_isInited) return;
		alcMakeContextCurrent(NULL);
		alcCaptureCloseDevice(m_pCaptureDev);
		XMem::XDELETE_ARRAY(m_captureData);

		m_isInited = XFalse;
	}
	XMicrophone()
		:m_pCaptureDev(NULL)
		,m_captureState(CAPTURE_STATE_STOP)
		,m_isInited(XFalse)
		,m_captureData(NULL)
		,m_byteRate(1)
	{}
	~XMicrophone(){release();}
};
}
#endif
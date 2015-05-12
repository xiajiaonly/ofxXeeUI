#ifndef _JIA_XCAMERA_
#define _JIA_XCAMERA_

#include "XCameraBasic.h"
#include "videoInput.h"
#ifdef _DEBUG
#pragma comment(lib, "videoInputD.lib")
#else
#pragma comment(lib, "videoInput.lib")
#endif

#pragma comment(linker, "/NODEFAULTLIB:atlthunk.lib")
#include <atlbase.h>

#if (_ATL_VER < 0x0700)
namespace ATL
{
  inline void * __stdcall __AllocStdCallThunk()
  {
  return ::HeapAlloc(::GetProcessHeap(), 0, sizeof(_stdcallthunk));
  }

  inline void __stdcall __FreeStdCallThunk(void *p)
  {
  ::HeapFree(::GetProcessHeap(), 0, p);
  }
};
#endif
namespace XE{
class XCamera:public XCameraBasic
{
private:
	videoInput m_VI;
	int m_deviceSum;
	int m_deviceOrder;
	unsigned char *m_frameDataBuff1;
	unsigned char *m_frameDataBuff;
	unsigned char *m_texDataBuff;
	int m_px;
	int m_py;
	XBool m_isUp2Down;
	XBool m_isLeft2Right;
public:
	void setUp2Down(XBool flag){m_isUp2Down = flag;}
	void setLeft2Right(XBool flag){m_isLeft2Right = flag;}

	void getData(unsigned char * p) const
	{
		if(!m_isInited) return;
		memcpy(p,m_frameDataBuff,m_buffSize);
	}
	unsigned char * getDataP() const
	{
		if(!m_isInited) return NULL;
		return m_frameDataBuff;
	}

	XBool init(XCameraData &data);
	XBool updateFrame();

	XCamera()
		:m_frameDataBuff1(NULL)
		,m_frameDataBuff(NULL)
		,m_texDataBuff(NULL)
		,m_isUp2Down(XFalse)
		,m_isLeft2Right(XFalse)
	{}
	~XCamera(){release();}
	void release();
};

}
#endif
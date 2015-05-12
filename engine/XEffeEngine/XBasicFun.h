#ifndef _JIA_XBASICFUN_
#define _JIA_XBASICFUN_

#include "XOSDefine.h"
#include "XMemoryPool.h"

#include "stdio.h"

#include "string.h"
#include "XCommonDefine.h"
#include "XStringFun.h"
#include "XMath/XByteFun.h"
#include "XMath/XRandomFun.h"
#include "XMath/XMath.h"
#include "XMemory.h"
#include "XFile.h"
namespace XE{
namespace XEE
{
extern int sleep(unsigned long sleepUSecond);
}

extern void getHalfData(unsigned char H1,unsigned char L1,unsigned char H2,unsigned char L2,unsigned char &Ho,unsigned char &Lo);

namespace XPixel
{
	#ifdef GET_ALL_PIXEL
	extern int XEE_AllPixel;
	#endif
	extern void pixelsZoomRGBA(unsigned char * src,unsigned char * dst,
						  int sw,int sh,int dw,int dh);

	extern void pixelDataZoomRGB(unsigned char * src,unsigned char * dst,float zoom,
						  int sw,int sh,int dw,int dh,
						  int sOffsetX,int sOffsetY,int dOffsetX,int dOffsetY,
						  int sClipW,int sClipH);

	enum XPixelFillMode
	{
		PIXEL_MODE_CENTER_TILE,
		PIXEL_MODE_ZOOM,
	};
	extern void pixelDataConvertRGB(unsigned char * src,unsigned char * dst,
									const XVector2 &srcSize,const XVector2 &dstSize,const XVector2& srcPos,
									const XVector2 &dstClipSize,XPixelFillMode mode = PIXEL_MODE_CENTER_TILE);

	template<class T>
	void pixelFillRGBA(T *src,T *dst,int sw,int sh,int dw,int dh)
	{

		XVector2 resSize(XEE_Min(sw,dw),XEE_Min(sh,dh));
		XVector2 resDstPos((XVector2(dw,dh) - resSize) * 0.5f);
		XVector2 resSrcPos((XVector2(sw,sh) - resSize) * 0.5f);

		int w = resSize.x * 4 * sizeof(T);
		int wS = (sw * sizeof(T)) << 2;
		int wD = (dw * sizeof(T)) << 2;
		int tmpD = int(resDstPos.x) * 4 * sizeof(T);
		int tmpS = int(resSrcPos.x) * 4 * sizeof(T);
		unsigned char *s = (unsigned char *)src;
		unsigned char *d = (unsigned char *)dst;
		for(int h = 0;h < resSize.y;++ h)
		{
			memcpy(d + (int)(h + resDstPos.y) * wD + tmpD,
				s + (int)(h + resSrcPos.y) * wS + tmpS,w);
		}
	}
}

struct XShaderHandle
{
	unsigned int shaderHandle;
	unsigned int shaderF;
	unsigned int shaderV;
	unsigned int shaderG;
	XShaderHandle()
		:shaderHandle(0)
		,shaderF(0)
		,shaderV(0)
		,shaderG(0)
	{}
};
}
#endif

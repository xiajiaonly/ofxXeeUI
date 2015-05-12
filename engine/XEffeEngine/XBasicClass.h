#ifndef _JIA_XBASICCLASS_
#define _JIA_XBASICCLASS_

#include "XBasicFun.h"

#include "XMath/XVector2.h"
#include "XMath/XVector3.h"
#include "XMath/XVector4.h"
#include "XMath/XLine.h"
#include "XMath/XMatrix2x2.h"
#include "XMath/XMatrix3x3.h"
#include "XMath/XMatrix4x4.h"
#include "XMath/XRect.h"
#include "XMath/XCColor.h"
#include "XMath/XFColor.h"
#include "XMath/XKalman.h"
#include "XCritical.h"
#include "XThread.h"
namespace XE{

class XVectorIndex3
{
public:
    int x;
    int y;
    int z;

	XVectorIndex3()
		:x(0),y(0),z(0)
	{}
	XVectorIndex3(int a,int b,int c)
		:x(a),y(b),z(c)
	{}
};

class XTexture;
class XTextureInfo;
class XFrame;
class XFrameEx;
class XNodeLine;
class XFontUnicode;
class XSCounter
{
private:
	friend XTexture;
	friend XTextureInfo;
	friend XFrame;
	friend XFrameEx;
	friend XNodeLine;
	friend XFontUnicode;

	int m_counter;
	XSCounter()
		:m_counter(1)
	{}
};

}
#endif
#ifndef _JIA_XSOCKETBASIC_
#define _JIA_XSOCKETBASIC_

#include "XOSDefine.h"
namespace XE{
#ifdef XEE_OS_WINDOWS
namespace XSock
{
	extern bool initSocket();
};
#endif
}
#endif
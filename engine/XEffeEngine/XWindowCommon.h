#ifndef _JIA_XWINDOWCOMMON_
#define _JIA_XWINDOWCOMMON_

#include "XCommonDefine.h"
#include "XWindowSDL.h"
#include "XWindowGlut.h"
namespace XE{
#ifdef CREATE_WINDOW_WITH_GLUT
#define XWindow XWindowGlut::GetInstance()
#endif
#ifdef CREATE_WINDOW_WITH_SDL
#define XWindow XWindowSDL::GetInstance()
#endif
}
#endif
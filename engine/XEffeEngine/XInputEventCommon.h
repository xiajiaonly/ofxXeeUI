#ifndef _JIA_XINPUTEVENTCOMMON_
#define _JIA_XINPUTEVENTCOMMON_

#include "XCommonDefine.h"
#include "XInputEventSDL.h"
#include "XInputEventGlut.h"
namespace XE{
#ifdef CREATE_WINDOW_WITH_GLUT
#define getInputEvent(p) getInputEventGlut(p)
#endif
#ifdef CREATE_WINDOW_WITH_SDL
#define getInputEvent(p) getInputEventSDL(p)
#endif
}
#endif
#ifndef _JIA_XINPUTEVENTCORE_
#define _JIA_XINPUTEVENTCORE_

#include "XMouseAndKeyBoardDefine.h"
namespace XE{

enum XInputType
{
	EVENT_NULL,
	EVENT_MOUSE,
	EVENT_KEYBOARD,
	EVENT_JOYSTICK,
	EVENT_SYSTEM,
	EVENT_RESIZE,
	EVENT_EXIT,
};

struct XInputEvent
{
	XInputType type;

	XKeyState keyState;
	XKeyValue keyValue;

	XMouseState mouseState;
	int mouseX;
	int mouseY;
	unsigned short unicode;
	XInputEvent()
		:type(EVENT_NULL)
	{}
};

}
#endif
#ifndef _JIA_XINPUTEVENTSDL_
#define _JIA_XINPUTEVENTSDL_

#include "XInputEventCore.h"
#include "SDL.h"
namespace XE{

extern bool SDLEventToInputEvent(XInputEvent &event,const SDL_Event &tmpEvent);
inline bool getInputEventSDL(XInputEvent &event)
{
	SDL_Event tmpEvent;
	if(SDL_PollEvent(&tmpEvent) == 0) return false;

	return SDLEventToInputEvent(event,tmpEvent);
}
}

#endif
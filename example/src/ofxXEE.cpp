#include "ofxXEE.h"
using namespace XE;
bool ofxXEE::XSetup()
{
	if(!XEE::readSystemConfigData(XEE::windowData)) LogStr("��ȡ�����ļ�ʧ��!");

	XSoundHandle.init();
	if(!XEE::engineInit()) LogStr("�����ʼ��ʧ��!");

	XEE::windowWidth = ofGetWindowWidth();
	XEE::windowHeight = ofGetWindowHeight();
	XEE::wHDC = wglGetCurrentDC();
	XEE::wCurrentHGLRC = wglGetCurrentContext();
	XEE::wCopyHGLRC = wglCreateContext(XEE::wHDC);
	wglShareLists(XEE::wCurrentHGLRC,XEE::wCopyHGLRC);
	XEE::wHandle = WindowFromDC(XEE::wHDC);
	XEE::mainThreadHandle = GetCurrentThreadId();
	XCtrlManger.setGame(this);
	//if(windowTitle != NULL) XWindow.setWindowTitle(windowTitle);	//���ô��ڱ���
	//if(XEE::windowData.isInitWindowPos
	//	|| XEE::windowData.isAlwaysTop) setWindowPos(XEE::windowData.windowPosX,XEE::windowData.windowPosY,XEE::windowData.isAlwaysTop);

	XEE::registerMyMsgProc();
	XEE::engineSysInit();
	return init();
}
bool ofxXEE::XUpdate()
{
	XEE::engineIdle();
	move(ofGetLastFrameTime() * 1000.0f);
	return true;
}
bool ofxXEE::XDraw()
{
	draw();
	XEE::engineDraw();
	return true;
}
XKeyValue mapOfKey(int key)
{
	switch(key)
	{
	case OF_KEY_BACKSPACE: return XKEY_BACKSPACE;
	case OF_KEY_RETURN: return XKEY_RETURN;
	case OF_KEY_ESC: return XKEY_ESCAPE;
    case OF_KEY_TAB: return XKEY_TAB;
	case OF_KEY_F1: return XKEY_F1;
	case OF_KEY_F2: return XKEY_F2;
	case OF_KEY_F3: return XKEY_F3;
	case OF_KEY_F4: return XKEY_F4;
	case OF_KEY_F5: return XKEY_F5;
	case OF_KEY_F6: return XKEY_F6;
	case OF_KEY_F7: return XKEY_F7;
	case OF_KEY_F8: return XKEY_F8;
	case OF_KEY_F9: return XKEY_F9;
	case OF_KEY_F10: return XKEY_F10;
	case OF_KEY_F11: return XKEY_F11;
	case OF_KEY_F12: return XKEY_F12;
	case OF_KEY_LEFT: return XKEY_LEFT;
	case OF_KEY_UP: return XKEY_UP;
	case OF_KEY_RIGHT: return XKEY_RIGHT;
	case OF_KEY_DOWN: return XKEY_DOWN;
	case OF_KEY_PAGE_UP: return XKEY_PAGEUP;
	case OF_KEY_PAGE_DOWN: return XKEY_PAGEDOWN;
	case OF_KEY_HOME: return XKEY_HOME;
	case OF_KEY_END: return XKEY_END;
	case OF_KEY_INSERT: return XKEY_INSERT;
	case OF_KEY_CONTROL: return XKEY_LCTRL;
	case OF_KEY_ALT: return XKEY_LALT;
	case OF_KEY_SHIFT: return XKEY_LSHIFT;
	//case OF_KEY_SUPER: return XKEY_DOWN;
	case OF_KEY_LEFT_SHIFT: return XKEY_LSHIFT;
	case OF_KEY_RIGHT_SHIFT: return XKEY_RSHIFT;
	case OF_KEY_LEFT_CONTROL: return XKEY_LCTRL;
	case OF_KEY_RIGHT_CONTROL: return XKEY_RCTRL;
	case OF_KEY_LEFT_ALT: return XKEY_LALT;
	case OF_KEY_RIGHT_ALT: return XKEY_RALT;
	case OF_KEY_LEFT_SUPER:
	case OF_KEY_RIGHT_SUPER:
	case OF_KEY_SUPER:
//	case OF_KEY_LEFT_COMMAND:
//	case OF_KEY_RIGHT_COMMAND:
		return XKEY_UNKNOWN;
	default:return XKEY_UNKNOWN;
	}
}
bool ofxXEE::XKeyDown(int key)
{
	XInputEvent e;
	e.type = EVENT_KEYBOARD;
	e.keyValue = XKEY_UNKNOWN;
	if(key < 128)
		e.keyValue = XEE::charToKeyValue(key);
	if(e.keyValue == XKEY_UNKNOWN)
		e.keyValue = mapOfKey(key);
	e.keyState = KEY_STATE_DOWN;
	XEE::inputEvent(e);
	input(e);
	return true;
}
bool ofxXEE::XKeyUp(int key)
{
	XInputEvent e;
	e.type = EVENT_KEYBOARD;
	e.keyValue = XKEY_UNKNOWN;
	if(key < 128)
		e.keyValue = XEE::charToKeyValue(key);
	if(e.keyValue == XKEY_UNKNOWN)
		e.keyValue = mapOfKey(key);
	e.keyState = KEY_STATE_UP;
	XEE::inputEvent(e);
	input(e);
	return true;
}
bool ofxXEE::XMouseMoved(int x,int y,int button)
{
	XInputEvent e;
	e.type = EVENT_MOUSE;
	e.mouseX = x;
	e.mouseY = y;
	e.mouseState = MOUSE_MOVE;
	XEE::inputEvent(e);
	input(e);
	return true;
}
bool ofxXEE::XMouseDragged(int x,int y,int button)
{
	XInputEvent e;
	e.type = EVENT_MOUSE;
	e.mouseX = x;
	e.mouseY = y;
	e.mouseState = MOUSE_MOVE;
	XEE::inputEvent(e);
	input(e);
	return true;
}
bool ofxXEE::XMousePressed(int x,int y,int button)
{
	XInputEvent e;
	e.type = EVENT_MOUSE;
	e.mouseX = x;
	e.mouseY = y;
	e.mouseState = MOUSE_LEFT_BUTTON_DOWN;
	XEE::inputEvent(e);
	input(e);
	return true;
}
bool ofxXEE::XMouseReleased(int x,int y,int button)
{
	XInputEvent e;
	e.type = EVENT_MOUSE;
	e.mouseX = x;
	e.mouseY = y;
	e.mouseState = MOUSE_LEFT_BUTTON_UP;
	XEE::inputEvent(e);
	input(e);
	return true;
}
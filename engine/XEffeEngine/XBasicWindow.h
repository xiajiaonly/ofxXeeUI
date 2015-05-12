#ifndef _JIA_XBASICWINDOW_
#define _JIA_XBASICWINDOW_

#include "XInputEventCommon.h"
#include "XMath\XVector2.h"
#include "XOSDefine.h"
#include "tlhelp32.h"
namespace XE{
class XFColor;
class XWindowTitle;
class XFontUnicode;
namespace XEE
{
	extern bool deamonWithConsole;
	extern bool forceToPaint;
	extern LRESULT daemonProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam, bool &end);
	extern int windowWidth;
	extern int windowHeight;
	extern int sceneX;
	extern int sceneY;
	extern int sceneWidth;
	extern int sceneHeight;
	extern float sceneSizeX;
	extern float sceneSizeY;
	extern float viewAngle3D;
	extern XWindowInfo windowData;
	extern XResourcePosition defaultResourcePosition;
	extern bool isWindowExit;
	extern bool isRestartWhenCrash;
	extern bool isAlwaysTop;

	extern int frameTime;
	extern float curFPS;
	extern int showDelay;

	extern int audioFrequency;
	extern int audioFormat;
	extern int audioChannel;
	extern XVector2 mousePosition;

	extern void release();
	extern void inputEvent(const XInputEvent& inputEvent);
	extern void keyProc(int key,XKeyState keyState);
	extern void mouseProc(int x,int y,XMouseState mouseState);
	extern bool isProjectAsDaemon;
	extern LRESULT (*customWinProc)(HWND hwnd,UINT Msg,WPARAM wParam,LPARAM lParam,bool &end);
	extern HWND wHandle;
	extern HDC wHDC;
	extern HGLRC wCurrentHGLRC;
	extern HGLRC wCopyHGLRC;
	extern unsigned int mainThreadHandle;

	extern char isOpenGL2Support;
	extern char isLineSmooth;
	extern int maxTextureSize;
	extern XFColor defaultBGColor;
	extern XBool isMultiSampleSupport;
	extern int maxTextureSum;
	extern XBool isFboSupported;

	extern XBool stopFlag;
	extern int manualFPS;
	extern float manualFrameTime;
	extern XBool needReset3DParam;

	extern XBool haveSystemFont;
	extern XFontUnicode systemFont;
	extern XBool isSuspend;

	extern int showVersionTimer;
	extern XFontUnicode showVersionStr;
	extern int autoShutDownTimer;
	extern char autoShutDownState;

	extern XWindowTitle customWinTitle;
	extern void registerMyMsgProc();
	extern void setBGColor(const XFColor &c);
	inline void setStop(int temp = -1)
	{
		if(temp > 0) XEE::stopFlag = XTrue;else
		if(temp == 0) XEE::stopFlag = XFalse;else
			XEE::stopFlag = !XEE::stopFlag;
	}
	inline XBool getStopState(){return XEE::stopFlag;}

	inline void setFPS(int temp)
	{
		if(temp <= 0) return;
		XEE::manualFPS = temp;
		XEE::manualFrameTime = 2000.0f / temp;
	}
	inline XBool getWindowNeedDraw()
	{
		if (XEE::forceToPaint) return XTrue;
		if(!(GetWindowLong(XEE::wHandle, GWL_STYLE) & WS_VISIBLE)) return XFalse;
		if(IsIconic(XEE::wHandle)) return XFalse;
		return XTrue;
	}
	extern bool createWindow(int width,int height,const char *windowTitle = NULL,int isFullScreen = 0,int withFrame = 1);
	inline void setWindowPos(int x,int y,bool always = false)
	{
		RECT rect;
		GetWindowRect(XEE::wHandle,&rect);
		XEE::isAlwaysTop = always;
		if(XEE::isAlwaysTop) SetWindowPos(XEE::wHandle,HWND_TOPMOST,x,y,rect.right - rect.left,rect.bottom - rect.top,SWP_SHOWWINDOW);
		else SetWindowPos(XEE::wHandle,HWND_TOP,x,y,rect.right - rect.left,rect.bottom - rect.top,SWP_SHOWWINDOW);
	}
	inline void setWindowHide(){ShowWindow(XEE::wHandle,SW_HIDE);}
	inline void setWindowShow(){ShowWindow(XEE::wHandle,SW_NORMAL);}
	inline void getWindowPos(int &x,int &y)
	{
		RECT rect;
		GetWindowRect(XEE::wHandle,&rect);
		x = rect.left;
		y = rect.top;
	}
	inline void getWindowSize(int &w,int &h)
	{
		RECT rect;
		GetWindowRect(XEE::wHandle,&rect);
		w = rect.right - rect.left;
		h = rect.bottom - rect.top;
	}
	inline void minSizeWindow(){ShowWindow(XEE::wHandle,SW_MINIMIZE);}
	inline void exitWindow(){XEE::isWindowExit = true;}
	inline void setWindowSize(float x,float y)
	{
		RECT rect;
		GetWindowRect(XEE::wHandle,&rect);
		if(XEE::isAlwaysTop) SetWindowPos(XEE::wHandle,HWND_TOPMOST,(int)rect.left,(int)rect.top,(int)x,(int)y,SWP_SHOWWINDOW);
		else SetWindowPos(XEE::wHandle,HWND_TOP,(int)rect.left,(int)rect.top,(int)x,(int)y,SWP_SHOWWINDOW);
	}

	inline void setWindowAlpha(float a)
	{
		bool isFirst = true;
		if(isFirst)
		{
			int ret = SetWindowLong(XEE::wHandle, GWL_EXSTYLE, GetWindowLong(XEE::wHandle, GWL_EXSTYLE) | WS_EX_LAYERED);
			if(ret == 0)
			{
				printf("SetWindowLong error:%d!\n",GetLastError());
				return;
			}
			isFirst = false;
		}

		SetLayeredWindowAttributes(XEE::wHandle,0,a * 255,LWA_ALPHA);

	}
#ifdef XEE_OS_WINDOWS
	enum XShutDownSystemMode
	{
		SYS_SD_MODE_G,
		SYS_SD_MODE_Z,
		SYS_SD_MODE_C,
	};

	extern void shutDownSystem(XShutDownSystemMode mode = SYS_SD_MODE_G);
	extern bool getSysPrivilege(const char * value);

	inline void waitingForKey() {system("pause");}

	inline void setConsoleColor(int index)
	{
		HANDLE consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
		switch(index)
		{
		case 1:
			SetConsoleTextAttribute(consolehwnd,FOREGROUND_BLUE);
			break;
		case 2:
			SetConsoleTextAttribute(consolehwnd,FOREGROUND_GREEN);
			break;
		default:
			SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);
			break;
		}
	}

	extern bool isProgramExist(const std::string &name);

	inline DWORD getCurProcessID(){return GetCurrentProcessId();}

	inline bool getIsProcessOver(DWORD id)
	{

		if(id == NULL) return true;
		return !WaitForSingleObject(OpenProcess(PROCESS_VM_OPERATION|SYNCHRONIZE,FALSE,id),0);
	}

#ifdef UNICODE
	inline std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
#endif
	inline DWORD getProcesssID(const std::string &name)
	{
		PROCESSENTRY32  pe32;

		HANDLE hSnaphot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
		Process32First(hSnaphot, &pe32);
		do
		{
#ifdef UNICODE
			if (lstrcmpi(pe32.szExeFile, s2ws(name).c_str()) == 0)
#else
			if (lstrcmpi(pe32.szExeFile, name.c_str()) == 0)
#endif
			{
				return pe32.th32ProcessID;
				break;
			}
		}while(Process32Next(hSnaphot, &pe32));
		return NULL;
	}
#endif
}
}
#endif
#ifndef _JIA_XFRAMEWORK_
#define _JIA_XFRAMEWORK_

#include "XBasicWindow.h"
#include "XBasicOpenGL.h"
#include "XLogBook.h"
#if WITH_OBJECT_MANAGER
#include "XObjectManager.h"
#endif
#include "XControl/XControlManager.h"
#include "XWindowTitle.h"
#include "XWindowCommon.h"
#include "XErrorReporter.h"
namespace XE{
namespace XEE
{
	struct XMemUsageInfo
	{
		unsigned int peakWorkSet;
		unsigned int curWorkingSet;

		XMemUsageInfo()
			:peakWorkSet(0)
			, curWorkingSet(0)
		{}
	};
	inline void makeABeep(){printf("\a");}

	extern XBool setSystemFont(const char * filename);
	extern XBool readSystemConfigData(XWindowInfo &data);
	extern XBool saveSystemConfigData(const XWindowInfo &data);

	extern XBool initWindowEx(const XWindowInfo& windowData);
	inline XBool initWindowEx(void)
	{

		if (!readSystemConfigData(XEE::windowData)) LogStr("读取配置文件失败!");
		return initWindowEx(XEE::windowData);
	}

	extern bool isSetToFullScreen;
	extern void toggleFullScreen();

	extern void releaseIcon();
	inline void makeCrash()
	{
		int *a = 0;
		*a = 0;
	}
	inline void setProjectAsDaemon(){ isProjectAsDaemon = true; }
	inline bool getIsProjectAsDaemon(){ return isProjectAsDaemon; }

	XMemUsageInfo getMemUsageInfo();
	float getCpuUsage();
	extern int engineIdle();
	extern void(*drawAfterCtrl)();
	extern void begin2DDraw();
	extern void end2DDraw();
	inline void clearScreen()
	{
		if (XEE::windowData.windowType == WINDOW_TYPE_3D)
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		else glClear(GL_COLOR_BUFFER_BIT);
	}
	inline void clearScreen(const XFColor & c)
	{
		glClearColor(c.fR, c.fG, c.fB, c.fA);
		if (XEE::windowData.windowType == WINDOW_TYPE_3D)
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		else glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(XEE::defaultBGColor.fR, XEE::defaultBGColor.fG, XEE::defaultBGColor.fB, XEE::defaultBGColor.fA);
	}
	extern XBool engineInit();
	extern void engineSysInit();
	inline void engineDraw()
	{
		if (haveSystemFont && windowData.isShowVersion
			&& showVersionTimer < 60000) showVersionStr.draw();
		if (windowData.withCustomTitle) customWinTitle.draw();
		XCtrlManger.draw();
#if WITH_OBJECT_MANAGER
		XObjManger.draw();
#endif
		if (drawAfterCtrl != NULL) drawAfterCtrl();

#ifdef WITHXEE_CURSOR
		if (windowData.isShowCursor != 0)
		{
			XRender::drawLine(mousePosition.x - 10.0f, mousePosition.y, mousePosition.x + 10.0f, mousePosition.y, 3, 1.0f, 1.0f, 1.0f);
			XRender::drawLine(mousePosition.x, mousePosition.y - 10.0f, mousePosition.x, mousePosition.y + 10.0f, 3, 1.0f, 1.0f, 1.0f);
			XRender::drawLine(mousePosition.x - 10.0f, mousePosition.y, mousePosition.x + 10.0f, mousePosition.y, 1, 0.0f, 0.0f, 0.0f);
			XRender::drawLine(mousePosition.x, mousePosition.y - 10.0f, mousePosition.x, mousePosition.y + 10.0f, 1, 0.0f, 0.0f, 0.0f);
		}
#endif
	}
	extern void updateScreen();
	extern void simulateFullScreen();

	extern void suspend(const char * str);

	enum XColorStyle
	{
		COLOR_STYLE_NORMAL,
		COLOR_STYLE_LIGHT,
	};
	extern void setStyle(XColorStyle style);

	extern void *pGame;
	inline void XEE_Error(const char *p){ REPORT_ERROR(p); }
	extern void startGame(void *game,const XWindowInfo* windowInfo = NULL);
	extern void restartGame();

	extern void gameProc(void *game);
	template<class Type> void runGame(const XWindowInfo* windowInfo = NULL)
	{
		__try{
			XException::initException();
			if(windowInfo == NULL)
			{
				if (!initWindowEx()) XEE_Error("建立窗体失败");
			}else
			{
				if (!initWindowEx(*windowInfo)) XEE_Error("建立窗体失败");
			}
			Type *tmpGame = XMem::createMem<Type>();
			if(tmpGame == NULL) XEE_Error("游戏建立失败");
			gameProc(tmpGame);
			XMem::XDELETE(tmpGame);
			release();
		}
		__except (XException::unhandledExceptionFilter(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
		{

		}
	}
	extern XBool startProgram(const char * programPath);

}
}
#endif
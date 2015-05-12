#ifndef _JIA_XCOMMONDEFINE_
#define _JIA_XCOMMONDEFINE_

#include <string>
namespace XE{
#define CREATE_WINDOW_WITH_SDL
#ifndef CREATE_WINDOW_WITH_SDL
#define CREATE_WINDOW_WITH_GLUT
#endif
#define WITH_INLINE_FILE (0)
#if WITH_INLINE_FILE
#define INLINE inline
#else
#define INLINE
#endif
#define BACKGROUND_ALPHA_MODE (1)
#define WITH_OBJECT_MANAGER (0)
#define WITH_FULL_ALL_CHINESE (1)
#define WITH_COMMON_RESOURCE_FOLDER (1)
#define WITHXSPRITE_EX (1)
#define BASE_RESOURCE_PATH ("ResourcePack/")
#define WITH_64BIT_SUPPLY (0)

#define WITH_LOG (1)

#define XEE_SYSTEM_CONFIG ("XEEConfig.xml")

#define MAX_FILE_NAME_LENGTH (256)

enum XResourcePosition
{
	RESOURCE_LOCAL_FOLDER = 0,
	RESOURCE_LOCAL_PACK,
	RESOURCE_WEB,
	RESOURCE_SYSTEM_DEFINE,
};

enum XWindowSizeMode
{
	WINDOW_SIZE_MODE_CLIP_LP,
	WINDOW_SIZE_MODE_CLIP_MID,
	WINDOW_SIZE_MODE_CLIP_RESIZE,
	WINDOW_SIZE_MODE_RESIZE_CLIP,
	WINDOW_SIZE_MODE_RESIZE,
};
enum XWindowRotateMode
{
	WINDOW_ROTATE_MODE_0,
	WINDOW_ROTATE_MODE_90,
	WINDOW_ROTATE_MODE_180,
	WINDOW_ROTATE_MODE_270,
};
enum XWindowTurnOverMode
{
	WINDOW_TURNOVER_MODE_NULL,
	WINDOW_TURNOVER_MODE_LTR,
	WINDOW_TURNOVER_MODE_TTD,
	WINDOW_TURNOVER_MODE_LTR_TTD,
};
enum XWindowType
{
	WINDOW_TYPE_NORMAL,
	WINDOW_TYPE_EX,
	WINDOW_TYPE_3D,
};
enum XColorMode
{
	COLOR_RGBA,
	COLOR_RGB,
	COLOR_GRAY,
	COLOR_RGBA_F,
	COLOR_GRAY_F,
	COLOR_BGRA,
	COLOR_BGR,
	COLOR_DEPTH,
};
struct XWindowInfo
{
	int w;
	int h;
	std::string windowTitle;
	int sceneW;
	int sceneH;
	int isFullScreen;
	int isTouch;
	int withLog;
	int isShowCursor;
	int positionX;
	int positionY;
	int withFrame;
	XWindowType windowType;
	XWindowSizeMode mode;
	int CFGMode;
	int startDelayTimer;
	bool isStartDelay;
	bool isShowVersion;
	bool isAutoShutDown;
	bool isShowConsole;
	bool isProjectAsDaemon;
	std::string versionString;
	int autoShutDownYear;
	int autoShutDownMonth;
	int autoShutDownDay;
	int autoShutDownHour;
	int autoShutDownMinute;
	int autoShutDownSecond;
	int BGVolume;
	int FWVolume;
	XWindowRotateMode rotateMode;
	XWindowTurnOverMode turnOverMode;
	XResourcePosition defResourcePos;
	std::string systemFontFile;
	std::string commonResourcePos;

	bool isInitWindowPos;
	bool isAlwaysTop;
	bool withCustomTitle;
	bool withAlphaBG;
	int windowPosX;
	int windowPosY;
	int systemFontSize;
	int logicFps;
	int drawFps;
	XWindowInfo()
		:w(800)
		,h(600)
		,sceneW(800)
		,sceneH(600)
		,isFullScreen(0)
		,isTouch(0)
		,withLog(3)
		,isShowCursor(1)
		,positionX(0)
		,positionY(0)
		,startDelayTimer(0)
		,autoShutDownYear(-1)
		,autoShutDownMonth(-1)
		,autoShutDownDay(-1)
		,autoShutDownHour(-1)
		,autoShutDownMinute(-1)
		,autoShutDownSecond(-1)
		,withFrame(1)
		,mode(WINDOW_SIZE_MODE_CLIP_LP)
		,rotateMode(WINDOW_ROTATE_MODE_0)
		,turnOverMode(WINDOW_TURNOVER_MODE_NULL)
		,windowType(WINDOW_TYPE_NORMAL)
		,CFGMode(0)
		,isStartDelay(false)
		,isShowVersion(false)
		,isAutoShutDown(false)
		,isShowConsole(true)
		,isProjectAsDaemon(false)
		,defResourcePos(RESOURCE_LOCAL_FOLDER)
		,BGVolume(100)
		,FWVolume(100)
		,isInitWindowPos(false)
		,windowPosX(0)
		,windowPosY(0)
		,isAlwaysTop(false)
		,withCustomTitle(false)
		,windowTitle("xiajia_1981@163.com")
		,versionString("1.0.0.0")
#if WITH_COMMON_RESOURCE_FOLDER
		,systemFontFile("../../Common/SIMLI.TTF")
		,commonResourcePos("../../Common/")
#else
		,systemFontFile("SIMLI.TTF")
		,commonResourcePos("./")
#endif
		, systemFontSize(30)
		,withAlphaBG(false)
		,logicFps(-1)
		,drawFps(30)
	{}
	XWindowInfo(int width,int height,XWindowType type = WINDOW_TYPE_NORMAL)
		:w(width)
		,h(height)
		,sceneW(width)
		,sceneH(height)
		,isFullScreen(0)
		,isTouch(0)
		,withLog(3)
		,isShowCursor(1)
		,positionX(0)
		,positionY(0)
		,startDelayTimer(0)
		,autoShutDownYear(-1)
		,autoShutDownMonth(-1)
		,autoShutDownDay(-1)
		,autoShutDownHour(-1)
		,autoShutDownMinute(-1)
		,autoShutDownSecond(-1)
		,withFrame(1)
		,mode(WINDOW_SIZE_MODE_CLIP_LP)
		,rotateMode(WINDOW_ROTATE_MODE_0)
		,turnOverMode(WINDOW_TURNOVER_MODE_NULL)
		,windowType(type)
		,CFGMode(0)
		,isStartDelay(false)
		,isShowVersion(false)
		,isAutoShutDown(false)
		,isShowConsole(true)
		,isProjectAsDaemon(false)
		,defResourcePos(RESOURCE_LOCAL_FOLDER)
		,BGVolume(100)
		,FWVolume(100)
		,isInitWindowPos(false)
		,windowPosX(0)
		,windowPosY(0)
		,isAlwaysTop(false)
		,windowTitle("xiajia_1981@163.com")
		,versionString("1.0.0.0")
#if WITH_COMMON_RESOURCE_FOLDER
		,systemFontFile("../../Common/SIMLI.TTF")
		,commonResourcePos("../../Common/")
#else
		,systemFontFile("SIMLI.TTF")
		,commonResourcePos("./")
#endif
		, systemFontSize(30)
		,withAlphaBG(false)
		,logicFps(-1)
		,drawFps(30)
	{}
};
}
#endif
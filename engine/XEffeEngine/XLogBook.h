#ifndef _JIA_XLOGBOOK_
#define _JIA_XLOGBOOK_
#include "XNetWork/XSocketEx.h"
#include "XOSDefine.h"
#include <string>
namespace XE{

struct XLogbookInfo
{
    XBool isEnable;
    char *logMessage;

	XLogbookInfo()
		:isEnable(XFalse)
		,logMessage(NULL)

	{}
};

enum XLogBookMode
{
    LOGBOOK_MODE_SIMPLE,
    LOGBOOK_MODE_SERVER
};
enum XLogBookLevel
{
	LB_LEVEL_NULL = 0,
	LB_LEVEL_CONSOLE,
	LB_LEVEL_FILE,
	LB_LEVEL_ALL,
};

enum XLogServerDataType
{
	LOG_DATA_TYPE_NULL,
	LOG_DATA_TYPE_ID,
	LOG_DATA_TYPE_INFO,
	LOG_DATA_TYPE_OVER,
	LOG_DATA_TYPE_MESSAGE,
	LOG_DATA_TYPE_MAX,
};
enum XLogLevel
{
	LOG_LEVEL_NULL,
	LOG_LEVEL_MESSAGE,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR,
};

class XLogbook
{

protected:
    XLogbook();
    XLogbook(const XLogbook&);
	XLogbook &operator= (const XLogbook&);
	virtual ~XLogbook(){releaseLog();}
public:
    static XLogbook& GetInstance()
	{
		static XLogbook m_instance;
		return m_instance;
	}

private:
#define LOG_SERVER_NAME "XLogBook_Server"
#define LOG_SERVER_IP "127.0.0.1"
	static const int m_logServerPort = 20086;
	static const int m_maxRecordSum = 256;
	static const int m_maxRecordLength = 512;

	static const int m_recordHeadLength = 20;

	XBool m_isEnable;
    XLogbookInfo *m_LogInfo;
    int m_logInfoPoint;
    FILE *m_logBookFile;
    XBool m_isInited;
    XThreadState m_isReleased;

    XLogBookMode m_workMode;
    XSocketEx m_socket;
	char *m_tmpBuff;
	XCritical m_locker;

	std::string m_logServerFilename;
	int m_clientID;
	std::string m_filename;

    int m_logInfoPushPoint;
    int m_logInfoPopPoint;
    XBool pushAMessage(const char * message);
    XBool popAMessage(char ** message);

    pthread_t m_outputLogMessageThreadP;
#ifdef XEE_OS_WINDOWS
    static DWORD WINAPI outputLogMessageThread(void * pParam);
#endif

#ifdef XEE_OS_LINUX
    static void *outputLogMessageThread(void * pParam);
#endif

    void popAllLogMessage();

	XBool m_needFlushFile;
public:
    XBool initLog(const char *fileName);
    void releaseLog();
    void addLogInfoStr(const char *p);
    void addLogInfoNull(const char *p,...);

    void addLogInfoExp(XBool exp,const char *p,...);

    void setWorkMode(XLogBookMode temp)
    {
        if(m_isInited) return;
        m_workMode = temp;
    }
	void setServerFilename(const std::string &filename)
	{
        if(m_isInited) return;
		m_logServerFilename = filename;
	}
	void enableLog(){m_isEnable = XTrue;}
	void disableLog(){m_isEnable = XFalse;}
};

#if WITH_LOG
#define LogStr XLogbook::GetInstance().addLogInfoStr
#define LogNull XLogbook::GetInstance().addLogInfoNull
#define LogExp XLogbook::GetInstance().addLogInfoExp
#define pauseLog XLogbook::GetInstance().disableLog
#define resumeLog XLogbook::GetInstance().enableLog
#else
#define LogStr(p) (void)(p)
#define LogNull (void)
#define LogExp (void)
#define pauseLog (void)
#define resumeLog (void)
#endif

inline void XLogbook::addLogInfoStr(const char *p)
{
	if(!m_isEnable) return;
    pushAMessage(p);
}
}
#endif
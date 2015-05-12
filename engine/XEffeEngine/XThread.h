#ifndef _JIA_XTHREAD_
#define _JIA_XTHREAD_

#include "windows.h"
#include <vector>
#include "XTimer.h"

namespace XE{

enum XThreadState
{
	STATE_BEFORE_START,
	STATE_START,
	STATE_SET_TO_END,
	STATE_END,
};
inline void waitThreadEnd(XThreadState &state)
{
	if(state != STATE_START) return;
	state = STATE_SET_TO_END;
	while(state != STATE_END)
	{
		Sleep(1);
	}
}

typedef DWORD pthread_t;

struct XThreadInfo
{
	XThreadState state;
	HANDLE h;
	void (* fun)(void *);
	void *p;
	XThreadInfo()
		:state(STATE_BEFORE_START)
		,h(0)
		,fun(NULL)
		,p(NULL)
	{}
};

class XThreadManager
{
protected:
    XThreadManager()
	{}
    XThreadManager(const XThreadManager&);
	XThreadManager &operator= (const XThreadManager&);
    virtual ~XThreadManager(){release();}
public:
    static XThreadManager& GetInstance()
	{
		static XThreadManager m_instance;
		return m_instance;
	}
private:
	std::vector<XThreadInfo *> m_threadBuff;
	void release();
public:

	bool createAThread(int *id,void (* fun)(void *),void *p);
	bool closeAThread(unsigned int id)
	{
		if(id >= m_threadBuff.size() || m_threadBuff[id]->state != STATE_START) return false;
		if(TerminateThread(m_threadBuff[id]->h,0))
		{
			m_threadBuff[id]->state = STATE_END;
			return true;
		}else
		{
			return false;
		}
	}
	bool closeAllThread()
	{
		return true;
	}
	XThreadState getThreadState();
	bool suspendAThread();
	bool resumeAThread();
	bool suspendAllThread();
	bool resumeAllThread();

	void update();
};
class XThread
{
private:
	void (*m_cbFun)(void *);
	void *m_pClass;
	bool m_isSetup;
	XThreadState m_threadState;

	static DWORD WINAPI threadFun(LPVOID hParameter);
	float m_fps;
public:
	float getFps() const {return m_fps;};
	bool setup(void (* cbFun)(void *),void *pClass);
	void threadEnd()
	{
		waitThreadEnd(m_threadState);
		m_isSetup = false;
	}
	XThread()
		:m_isSetup(false)
		,m_cbFun(NULL)
		,m_pClass(NULL)
		,m_threadState(STATE_BEFORE_START)
		,m_fps(0.0f)
	{}
	~XThread(){threadEnd();}
};
}
#endif
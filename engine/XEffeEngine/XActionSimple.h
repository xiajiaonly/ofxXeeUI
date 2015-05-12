#ifndef _JIA_XACTION_
#define _JIA_XACTION_

#include "XBasicFun.h"
#include "stdlib.h"
#include "string.h"
namespace XE{

enum XActionSimpleState
{
	ACTION_STATE_NULL,
	ACTION_STATE_ACTION,
	ACTION_STATE_PAUSE,
	ACTION_STATE_END,
};

enum XActionSimpleType
{
	ACTION_TYPE_COMPLEX,
	ACTION_TYPE_ATOMIC,
};
class XActionSimpleEx
{
private:
	static const int m_maxActionNameLength = 256;
	XResourcePosition m_resoursePosition;
	XBool m_isInited;
	XActionSimpleType m_type;
	XActionSimpleState m_actionState;
	XBool m_actionIsLoop;
	char m_actionName[m_maxActionNameLength];

	void (*m_funResetData)(void *);
	void (*m_funMove)(int stepTime,void *);
	void (*m_funDraw)(void *);
	void (*m_funAtEnd)(void *);
	XBool (*m_funIsEnd)(void *);

	int (*m_funInit)(int,void*);
	void (*m_funRelease)(void*);

	void * m_pClass;
public:
	virtual XBool isName(const char *name);
	void setStop();
	virtual void setLoop(XBool isLoop) {m_actionIsLoop = isLoop;}
	virtual XBool getIsLoop() {return m_actionIsLoop;}
	virtual void setStart();
	virtual void setPause();
	virtual void setResume();
	virtual void move(int stepTime = 1);
	XActionSimpleState getActionState() {return m_actionState;}
	XBool getIsEnd(){return m_actionState == ACTION_STATE_END;}

	XActionSimpleEx()
		:m_isInited(XFalse)
		,m_actionState(ACTION_STATE_NULL)
		,m_actionIsLoop(XFalse)
		,m_funResetData(NULL)
		,m_funMove(NULL)
		,m_funDraw(NULL)
		,m_funAtEnd(NULL)
		,m_funInit(NULL)
		,m_funRelease(NULL)
		,m_pClass(NULL)
		,m_actionSum(0)
		,m_pAction(NULL)
		,m_type(ACTION_TYPE_ATOMIC)
	{
		m_actionName[0] = '\0';
	}
	XBool init(XResourcePosition resoursePosition,
		const char *actionName,
		XBool (*funIsEnd)(void *),
		void (*funMove)(int,void *),
		void (*funDraw)(void *),
		void (*funResetData)(void *),
		void (*funAtEnd)(void *) = NULL,
		int (*funInit)(int,void *) = NULL,
		void (*funRelease)(void *) = NULL,
		void * pClass = NULL);
	void draw();

	~XActionSimpleEx(){release();}
	void release();

private:
	XActionSimpleEx **m_pAction;
	int m_actionSum;
	int m_curActionIndex;
public:
	XBool init(XResourcePosition resoursePosition,const char *actionName,int actionSum,...);
};

typedef int XActionSimpleHandle;
struct XActionSimpleData
{
	XActionSimpleHandle actionHandle;
	XBool actionIsEnable;
	XActionSimpleEx *pAction;

	XActionSimpleData()
		:actionIsEnable(XFalse)
		,pAction(NULL)
	{}
};
class XActionSimpleManager
{
private:
	static const int m_maxActionSum = 512;

protected:
	XActionSimpleManager()
		:m_curActionHandle(0)
		,m_actionSum(0)
	{
		m_pActions = XMem::createArrayMem<XActionSimpleData>(m_maxActionSum);
	}
	XActionSimpleManager(const XActionSimpleManager&);
	XActionSimpleManager &operator= (const XActionSimpleManager&);
	virtual ~XActionSimpleManager() {XMem::XDELETE_ARRAY(m_pActions);}
public:
	static XActionSimpleManager& GetInstance()
	{
		static XActionSimpleManager m_instance;
		return m_instance;
	}

private:
	int m_curActionHandle;
	XActionSimpleData *m_pActions;
	int m_actionSum;
public:
	XActionSimpleHandle pushAction(XActionSimpleEx *action);

	XActionSimpleHandle getActionHandle(const char *actionName);
	XActionSimpleHandle getActionHandle(const XActionSimpleEx *action);
	XBool popAction(const char *actionName);
	XBool popAction(XActionSimpleEx *action);
	XBool popAction(XActionSimpleHandle actionHandle);
	XBool releaseAction(const char *actionName);
	XBool releaseAction(XActionSimpleEx *action);
	XBool releaseAction(XActionSimpleHandle actionHandle);
	XBool setStartAction(const char *actionName);
	XBool setStartAction(XActionSimpleHandle actionHandle);
	XActionSimpleEx *getPAction(const char *actionName);
	XActionSimpleEx *getPAction(XActionSimpleHandle actionHandle);

	XBool getIsActionEnd(const char *actionName);
	XBool getIsActionEnd(XActionSimpleHandle actionHandle);

	void move(int stepTime);
	void draw();

	void setAllActionStop();
	void setAllActionPause();
	void setAllActionResume();
	void popAllAction();
};
#define XASManager XActionSimpleManager::GetInstance()
#if WITH_INLINE_FILE
#include "XActionSimple.inl"
#endif
}
#endif
#ifndef _JIA_XACTIONEX_
#define _JIA_XACTIONEX_

#include "XActionSimple.h"
#include "XInputEventCore.h"
#include <vector>
namespace XE{

class XActionEx
{
protected:
	XResourcePosition m_resoursePosition;
	XBool m_isInited;
	XActionSimpleType m_type;
	XActionSimpleState m_actionState;
	XBool m_actionIsLoop;
	std::string m_actionName;
public:
	XBool isName(const char *name);
	void setStop();
	void setLoop(XBool isLoop) {m_actionIsLoop = isLoop;}
	XBool getIsLoop() const {return m_actionIsLoop;}
	void setStart();
	void setPause();
	void setResume();
	void move(int stepTime = 1);
	XActionSimpleState getActionState()const{return m_actionState;}
	XBool getIsEnd() const {return m_actionState == ACTION_STATE_END;}
	std::string getName() const {return m_actionName;}

	XActionEx()
		:m_isInited(XFalse)
		,m_actionState(ACTION_STATE_NULL)
		,m_actionIsLoop(XFalse)
		,m_actionSum(0)
		,m_pAction(NULL)
		,m_type(ACTION_TYPE_ATOMIC)
		,m_actionName(" ")
	{}
	XBool init(XResourcePosition resoursePosition,
		const char *actionName);
	void draw();
	virtual void keepDraw();
	void input(const XInputEvent &inputEvent);

	~XActionEx(){release();}
	void release();

private:
	XActionEx **m_pAction;
	int m_actionSum;
	int m_curActionIndex;
public:
	XBool init(XResourcePosition resoursePosition,const char *actionName,int actionSum,...);
public:
	virtual void funResetData(){}
	virtual void funMove(int stepTime){}
	virtual void funDraw(){}
	virtual void funKeepDraw(){}
	virtual void funAtEnd(){}
	virtual XBool funIsEnd(){return XTrue;}

	virtual XBool funInit(XResourcePosition res){return XTrue;}
	virtual void funRelease(){}

	virtual void funInput(const XInputEvent &inputEvent){}

};

typedef int XActionExHandle;
struct XActionExData
{
	XActionExHandle actionHandle;
	XBool actionIsEnable;
	XActionEx *pAction;

	XActionExData()
		:actionIsEnable(XFalse)
		,pAction(NULL)
	{}
};
class XActionExManager
{

protected:
	XActionExManager()
		:m_curActionHandle(0)
	{}
	XActionExManager(const XActionExManager&);
	XActionExManager &operator= (const XActionExManager&);
	virtual ~XActionExManager() {;}
public:
	static XActionExManager& GetInstance()
	{
		static XActionExManager m_instance;
		return m_instance;
	}

private:
	int m_curActionHandle;
	std::vector<XActionExData> m_pActions;
	std::vector<int> m_actionOrder;
	std::vector<int> m_actionOrderX;
public:
	XActionExHandle pushAction(XActionEx *action);

	XActionExHandle getActionHandle(const char *actionName);
	XActionExHandle getActionHandle(const XActionEx *action);
	XBool popAction(const char *actionName);
	XBool popAction(XActionEx *action);
	XBool popAction(XActionExHandle actionHandle);
	XBool releaseAction(const char *actionName);
	XBool releaseAction(XActionEx *action);
	XBool releaseAction(XActionExHandle actionHandle);
	XBool setStartAction(const char *actionName);
	XBool setStartAction(XActionExHandle actionHandle);
	XActionEx *getPAction(const char *actionName);
	XActionEx *getPAction(XActionExHandle actionHandle);

	XBool getIsActionEnd(const char *actionName);
	XBool getIsActionEnd(XActionExHandle actionHandle);

	void move(int stepTime);
	void draw();

	void input(const XInputEvent &inputEvent);

	void setAllActionStop();
	void setAllActionPause();
	void setAllActionResume();
	void popAllAction();

	XBool moveToBottom(const char *actionName);
	XBool moveToBottom(XActionExHandle actionHandle);
	XBool moveToTop(const char *actionName);
	XBool moveToTop(XActionExHandle actionHandle);
	XBool moveUp(const char *actionName);
	XBool moveUp(XActionExHandle actionHandle);
	XBool moveDown(const char *actionName);
	XBool moveDown(XActionExHandle actionHandle);
	XBool moveUpTo(const char *s,const char *d);
	XBool moveUpTo(XActionExHandle s,XActionExHandle d);
	XBool moveDownTo(const char *s,const char *d);
	XBool moveDownTo(XActionExHandle s,XActionExHandle d);
	int getLayerIndex(const char *actionName);
	int getLayerIndex(XActionExHandle actionHandle);
};
#define XAExManager XActionExManager::GetInstance()
#if WITH_INLINE_FILE
#include "XActionEx.inl"
#endif
}
#endif
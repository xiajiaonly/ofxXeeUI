#ifndef _JIA_XOPRATEDES_
#define _JIA_XOPRATEDES_

#include "XBasicClass.h"
#include <vector>
namespace XE{
class XBasicOprate;

struct XOperateDes
{
	XBasicOprate *pObj;
	void *pData;
	XOperateDes()
		:pObj(NULL)
		,pData(NULL)
	{}
	void release();
};

class XOperateManager
{
protected:
	XOperateManager()
		:m_curStateIndex(-1)
	{}
	virtual~XOperateManager(){clearAll();}
	XOperateManager(const XOperateManager&);
	XOperateManager &operator= (const XOperateManager&);
public:
	static XOperateManager& GetInstance()
	{
		static XOperateManager m_instance;
		return m_instance;
	}
public:
	std::vector<XOperateDes> m_operateDes;
	std::vector<int> m_operateIndex;
	int m_curStateIndex;
public:
	void clearAll();
	void undo();
	void redo();
	XBool canUndo() {return (m_curStateIndex > 0 && m_operateIndex.size() > 0);}
	XBool canRedo() {return (m_curStateIndex < (int)(m_operateIndex.size()) - 1);}
	void addAOperate(XBasicOprate *obj);
	void setOperateOver();
	void decreaseObj(XBasicOprate *obj);
};

#define XOpManager XOperateManager::GetInstance()

class XBasicOprate
{
protected:
	bool m_withUndoAndRedo;
	void *m_pStateClass;
	void (*m_funStateChange)(void *);
public:
	virtual void setWithUndo(bool flag) {m_withUndoAndRedo = flag;}
	virtual void setOprateState(void * data) = 0;
	virtual void *getOprateState() const = 0;
	virtual void releaseOprateStateData(void *) = 0;
	virtual void stateChange()
	{
		if(m_withUndoAndRedo) XOpManager.addAOperate(this);
		if(m_funStateChange != NULL) m_funStateChange(m_pStateClass);
	}

	virtual void setStateChangeCB(void (* funStateChange)(void *),void * p)
	{
		m_funStateChange = funStateChange;
		m_pStateClass = p;
	}
	virtual bool isSameState(void * data) = 0;

	XBasicOprate()
		:m_withUndoAndRedo(false)
		,m_pStateClass(NULL)
		,m_funStateChange(NULL)
	{}

	virtual ~XBasicOprate() {XOpManager.decreaseObj(this);}
};

}
#endif
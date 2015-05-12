#ifndef _JIA_XCONTROLMANAGER_
#define _JIA_XCONTROLMANAGER_

#include "XCtrlManagerBase.h"
namespace XE{

class XControlManager:public XCtrlManagerBase
{
protected:
	XControlManager(){}
	XControlManager(const XControlManager&);
	XControlManager &operator= (const XControlManager&);
	virtual ~XControlManager(){;}
public:
	static XControlManager& GetInstance()
	{
		static XControlManager m_instance;
		return m_instance;
	}
};
#define XCtrlManger XControlManager::GetInstance()
}
#endif
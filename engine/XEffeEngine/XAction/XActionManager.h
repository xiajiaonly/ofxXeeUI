#ifndef _JIA_XACTIONMANAGER_
#define _JIA_XACTIONMANAGER_

#include "XActionDescription.h"
#include "../XDirectory.h"
#include <map>
namespace XE{

class XActionMananger
{

protected:
	XActionMananger()
		:m_isInited(XFalse)
	{
	}
	XActionMananger(const XActionMananger&);
	XActionMananger &operator= (const XActionMananger&);
	virtual ~XActionMananger() {release();}
public:
	static XActionMananger& GetInstance()
	{
		static XActionMananger m_instance;
		return m_instance;
	}

private:
	XBool m_isInited;
	std::map<int,XActionDescription *> m_actionDescriptions;
	std::map<std::string,int> m_actionDesMap;
	std::vector<int> m_actionIDList;

	XBool isActionDescriptionFile(const char * filename);

	void loadActionDesFromFold(const XDir *dir);
public:
	XBool loadAllActionDes(const char * path = NULL);
	XBool saveAllActionDes();

	XBool pushAActionDescription(XActionDescription * tempAD)
	{
		if(tempAD == NULL) return XFalse;
		if(getActionDes(tempAD->getName()) != NULL) return XFalse;
		if(getActionDes(tempAD->getID()) != NULL) return XFalse;

		m_actionDescriptions.insert(std::pair<int,XActionDescription *>(tempAD->getID(),tempAD));
		m_actionDesMap.insert(std::pair<std::string,int>(tempAD->getName(),tempAD->getID()));
		m_actionIDList.push_back(tempAD->getID());
		return XTrue;
	}
	XActionDescription *getActionDes(int ID)
	{
		if(m_actionDescriptions.count(ID) == 0) return NULL;
		return m_actionDescriptions[ID];
	}
	XActionDescription *getActionDes(const char * name)
	{
		if(name == NULL) return NULL;
		if(m_actionDesMap.count(name) == 0) return NULL;
		int id = m_actionDesMap[name];
		return getActionDes(id);
	}
	XActionDescription *getActionDesByIndex(int index)
	{
		int sum = m_actionIDList.size();
		if(index < 0 || index >= sum) return NULL;
		return getActionDes(m_actionIDList[index]);
	}
	XBool getIsReferenced(XActionDescription * AD);
	int getADSum()
	{
		if(!m_isInited) return 0;
		return m_actionDesMap.size();
	}

	void release();
	void deleteAActionDesNoReference(XActionDescription * AD);
	XBool setADName(XActionDescription * AD,const char *name);
};
}
#endif
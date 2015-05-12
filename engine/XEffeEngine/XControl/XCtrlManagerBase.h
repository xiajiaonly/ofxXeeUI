#ifndef _JIA_XCTRLMANAGERBASE_
#define _JIA_XCTRLMANAGERBASE_
#include "stdlib.h"
#include "XControlBasic.h"
#include "../XGameBasic.h"
namespace XE{

struct XCtrlObjetInfo
{
	XControlBasic *pObject;
	void (*pFunction)(void);
	XBool needDraw;
	XBool neadInput;
	XCtrlObjetInfo()
		:pObject(NULL)
		,pFunction(NULL)
		,needDraw(XFalse)
		,neadInput(XFalse)
	{}
};
class XCtrlManagerBase
{
public:
	XCtrlManagerBase()
		:m_isAutoDraw(1)
		,m_focusOrder(-1)
		,m_isShiftDown(false)
		,m_pGame(NULL)
		,m_withWireframe(true)
	{}
	XCtrlManagerBase(const XCtrlManagerBase&);
	virtual ~XCtrlManagerBase(){;}
protected:
	std::vector<XCtrlObjetInfo> m_ctrlObjInfos;
	std::vector<int> m_ctrlDrawOrderMap;
	char m_isAutoDraw;
	bool m_isShiftDown;
	int m_focusOrder;
	bool m_withWireframe;
public:
	unsigned int getObjSum() const {return m_ctrlObjInfos.size();}
	XBool addACtrl(XControlBasic * object);
	XBool addAFunction(void (* function)());
	void setNeedDraw(XBool flag,unsigned int objectID);
	void setNeedDraw(XBool flag,const void *object);
	void setNeedInput(XBool flag,unsigned int objectID);
	void setNeedInput(XBool flag,const void *object);
	void decreaseAObject(int objectID);
	void decreaseAObject(const void * object);
	void decreaseAObject(void (* function)());
	void clearAllObject();
	int findObjectID(const void * object) const;
	int findObjectID(void (* function)()) const;
	XCtrlObjType getObjectType(unsigned int objectID) const;
	void *getObject(unsigned int objectID) const;

	void moveAndInsert(int objectID,int insertObjectID);
	void moveToFirst(int objectID){moveAndInsert(objectID,m_ctrlDrawOrderMap[0]);}
	void moveToEnd(int objectID){moveAndInsert(objectID,m_ctrlDrawOrderMap[(int)(m_ctrlDrawOrderMap.size()) - 1]);}
	void changeTowObject(unsigned int object1,unsigned int object2);
	void setIsAutoDraw(XBool isAutoDraw)
	{
		if(isAutoDraw) m_isAutoDraw = 1;
		else m_isAutoDraw = 0;
	}
public:
	void setWithWireframe(bool flag){m_withWireframe = flag;}
	void mouseProc(int x,int y,XMouseState mouseState);
	void keyProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *ch,int len);
	void draw();
	void update(int stepTime);

	void draw(const void * obj);

	XGameBasic *m_pGame;
	void eventProc(int id,int eventID)
	{
		if(m_pGame != NULL) m_pGame->ctrlEventProc(id,eventID);
	}
	void setGame(XGameBasic *pGame){m_pGame = pGame;}

};
inline void XCtrlManagerBase::setNeedDraw(XBool flag,unsigned int objectID)
{
	if(objectID >= m_ctrlObjInfos.size()) return;
	m_ctrlObjInfos[objectID].needDraw = flag;
}
inline void XCtrlManagerBase::setNeedDraw(XBool flag,const void *object)
{
	setNeedDraw(flag,findObjectID(object));
}
inline void XCtrlManagerBase::setNeedInput(XBool flag,unsigned int objectID)
{
	if(objectID >= m_ctrlObjInfos.size()) return;
	m_ctrlObjInfos[objectID].neadInput = flag;
}
inline void XCtrlManagerBase::setNeedInput(XBool flag,const void *object)
{
	setNeedInput(flag,findObjectID(object));
}
inline void XCtrlManagerBase::decreaseAObject(const void * object)
{
	decreaseAObject(findObjectID(object));
}
inline void XCtrlManagerBase::decreaseAObject(void (* function)())
{
	decreaseAObject(findObjectID(function));
}
inline XCtrlObjType XCtrlManagerBase::getObjectType(unsigned int objectID) const
{
	if(objectID >= m_ctrlObjInfos.size()) return CTRL_OBJ_NULL;
	if(m_ctrlObjInfos[objectID].pObject == NULL) return CTRL_OBJ_FUNCTION;
	else return m_ctrlObjInfos[objectID].pObject->getCtrlType();
}
inline void *XCtrlManagerBase::getObject(unsigned int objectID) const
{
	if(objectID >= m_ctrlObjInfos.size()) return NULL;
	return m_ctrlObjInfos[objectID].pObject;
}
inline void XCtrlManagerBase::changeTowObject(unsigned int object1,unsigned int object2)
{
	if(object1 >= m_ctrlObjInfos.size() ||
		object2 >= m_ctrlObjInfos.size() ||
		object1 == object2) return;
	int index1 = -1;
	int index2 = -1;
	for(unsigned int i = 0;i < m_ctrlDrawOrderMap.size();++ i)
	{
		if(m_ctrlDrawOrderMap[i] == object1) index1 = i;
		if(m_ctrlDrawOrderMap[i] == object2) index2 = i;
		if(index1 >= 0 && index2 >= 0) break;
	}
	XMath::swapTwoSum(m_ctrlDrawOrderMap[index1],m_ctrlDrawOrderMap[index2]);

}
inline void XCtrlManagerBase::insertChar(const char *ch,int len)
{
	if(m_focusOrder < 0 || m_focusOrder >= m_ctrlDrawOrderMap.size()) return;
	if(m_ctrlObjInfos[m_focusOrder].pObject != NULL)
			m_ctrlObjInfos[m_focusOrder].pObject->insertChar(ch,len);
}
inline void XCtrlManagerBase::draw(const void * obj)
{

	if(obj == NULL) return;
	((XControlBasic *)obj)->draw();
	((XControlBasic *)obj)->drawUp();
}
}
#endif
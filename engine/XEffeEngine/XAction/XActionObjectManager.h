#ifndef _JIA_ACTIONOBJECTMANAGER_
#define _JIA_ACTIONOBJECTMANAGER_

#include "XBasicFun.h"
#include "XObjectBasic.h"
namespace XE{

#define MAX_ACTION_OBJECT_DES_LEN (1024)

struct XActionObjectDescription
{
	XBool m_isEnable;
	int m_objectID;
	char *m_objectFilename;
	XObjectType m_objectType;
	void * m_paramData;

	XActionObjectDescription()
		:m_objectFilename(NULL)
		,m_objectType(OBJ_NULL)
		,m_paramData(NULL)
		,m_isEnable(XFalse)
	{}
	~XActionObjectDescription(){release();}
	void release()
	{
		if(!m_isEnable) return;
		XMem::XDELETE_ARRAY(m_objectFilename);
		releaseParamData();
		m_isEnable = XFalse;
	}
	char * getStrFromData();
	int getDataFromStr(const char * str);
	void releaseParamData();
	XBool getDataFromFile(FILE *fp);

	XObjectBasic * createAObject();
};
#define MAX_ACTION_OBJECT_SUM (1024)
class XActionObjectManager
{

protected:
	XActionObjectManager()
		:m_objectSum(0)
	{
		m_pObject = XMem::createArrayMem<XObjectBasic *>(MAX_ACTION_OBJECT_SUM);
		m_pObjDes = XMem::createArrayMem<XActionObjectDescription *>(MAX_ACTION_OBJECT_SUM);
	}
	XActionObjectManager(const XActionObjectManager&);
	XActionObjectManager &operator= (const XActionObjectManager&);
	virtual ~XActionObjectManager(){release();}
public:
	static XActionObjectManager& GetInstance()
	{
		static XActionObjectManager m_instance;
		return m_instance;
	}

private:
	XObjectBasic ** m_pObject;
	XActionObjectDescription ** m_pObjDes;
	int m_objectSum;

	void release()
	{
		for(int i = 0;i < m_objectSum;++ i)
		{
			XMem::XDELETE(m_pObject[i]);
			XMem::XDELETE(m_pObjDes[i]);
		}
		m_objectSum = 0;
		XMem::XDELETE_ARRAY(m_pObject);
		XMem::XDELETE_ARRAY(m_pObjDes);
	}
public:
	void releaseAllObject()
	{
		for(int i = 0;i < m_objectSum;++ i)
		{
			XMem::XDELETE(m_pObject[i]);
			XMem::XDELETE(m_pObjDes[i]);
		}
		m_objectSum = 0;
	}
	XActionObjectDescription * getObjDes(const XObjectBasic * pObj)
	{
		if(pObj == NULL) return NULL;
		for(int i = 0;i < m_objectSum;++ i)
		{
			if(m_pObject[i] == pObj) return m_pObjDes[i];
		}
		return NULL;
	}
	int addAObject(XObjectBasic * pObj,XActionObjectDescription *pDes)
	{
		if(m_objectSum >= MAX_ACTION_OBJECT_SUM) return 0;
		if(pObj == NULL || pDes == NULL) return 0;
		if(getObjDes(pObj) != NULL) return 0;
		m_pObject[m_objectSum] = pObj;
		m_pObjDes[m_objectSum] = pDes;
		++ m_objectSum;
		return 1;
	}
	XBool decreaseAObject(XObjectBasic * pObj)
	{
		if(pObj == NULL) return XFalse;
		for(int i = 0;i < m_objectSum;++ i)
		{
			if(m_pObject[i] == pObj)
			{
				XMem::XDELETE(m_pObject[i]);
				XMem::XDELETE(m_pObjDes[i]);
				for(int j = i;j < m_objectSum - 1;++ j)
				{
					m_pObject[j] = m_pObject[j + 1];
					m_pObjDes[j] = m_pObjDes[j + 1];
				}
				-- m_objectSum;
				return XTrue;
			}
		}
		return XFalse;
	}
};
}
#endif

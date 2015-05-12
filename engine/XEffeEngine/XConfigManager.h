#ifndef _JIA_XCONFIGMANAGER_
#define _JIA_XCONFIGMANAGER_

#include "XControl\XButton.h"
#include "XOprateDes.h"
#include "XControl\XGroup.h"
#include "XNetWork/XNetServer.h"
#include "XNetWork/XNetClient.h"
#include <vector>
namespace XE{

enum XConfigDataType
{
	CFG_DATA_TYPE_INT,
	CFG_DATA_TYPE_CHAR,
	CFG_DATA_TYPE_UCHAR,
	CFG_DATA_TYPE_FLOAT,
	CFG_DATA_TYPE_XBOOL,
	CFG_DATA_TYPE_RADIOS,
	CFG_DATA_TYPE_CUSTOM,
	CFG_DATA_TYPE_XSPRITE,
	CFG_DATA_TYPE_NULL,
};

#define CFG_MANAGER_W_SPACE (5.0f)
#define CFG_MANAGER_H_SPACE (5.0f)
#define CFG_MNG_H_FONT	(32.0f)
#define CFG_MNG_H_SLD	(24.0f)

union XConfigValue
{
	int valueI;
	float valueF;
	XBool valueB;
};
#define CFG_DEFAULT_FILENAME ("xConfig.dat")
#define CFG_INJECT_FILENAME ("xCFGInject.dat")
#define CFG_DEFAULT_GROUPNAME ("Default")

class XCFGItemBasic:public XObjectBasic,public XBasicOprate
{
public:
	virtual bool save(FILE *fp) = 0;
	virtual bool load(FILE *fp) = 0;
	virtual bool update() = 0;
	virtual bool defValue() = 0;
	virtual bool enable() = 0;
	virtual bool disable() = 0;

	virtual ~XCFGItemBasic() {}

	virtual unsigned char *getInfo(int &len,int id) = 0;
	virtual void setValueFromStr(unsigned char * str) = 0;
	virtual bool needSendStr() = 0;
	virtual unsigned char *sendStr(int &len,int id) = 0;
};
class XConfigItem
{
private:
	int m_ID;
public:
	bool m_isEnable;
	bool m_isActive;
	XConfigDataType m_type;
	XConfigValue m_rangeMin;
	XConfigValue m_rangeMax;
	XConfigValue m_defaultValue;
	XConfigValue m_curValue;
	void * m_pVariable;

	void (* m_changeProc)(void *pObj,void *pClass);
	void *m_pClass;
	XControlBasic *m_pCtrl;
	std::string m_name;
	XCFGItemBasic * m_customIt;
	void release()
	{
		switch(m_type)
		{
		case CFG_DATA_TYPE_INT:
			{
				int *p = (int *)m_pVariable;
				XMem::XDELETE(p);
				m_pVariable = NULL;
			}
			break;
		case CFG_DATA_TYPE_CHAR:
			{
				char *p = (char *)m_pVariable;
				XMem::XDELETE(p);
				m_pVariable = NULL;
			}
			break;
		case CFG_DATA_TYPE_UCHAR:
			{
				unsigned char *p = (unsigned char *)m_pVariable;
				XMem::XDELETE(p);
				m_pVariable = NULL;
			}
			break;
		case CFG_DATA_TYPE_FLOAT:
			{
				float *p = (float *)m_pVariable;
				XMem::XDELETE(p);
				m_pVariable = NULL;
			}
			break;
		case CFG_DATA_TYPE_XBOOL:
			{
				XBool *p = (XBool *)m_pVariable;
				XMem::XDELETE(p);
				m_pVariable = NULL;
			}
			break;
		case CFG_DATA_TYPE_RADIOS:
			{
				int *p = (int *)m_pVariable;
				XMem::XDELETE(p);
				m_pVariable = NULL;
			}
			break;
		case CFG_DATA_TYPE_CUSTOM:
		case CFG_DATA_TYPE_XSPRITE:
		case CFG_DATA_TYPE_NULL:
			XMem::XDELETE(m_pVariable);
			break;
		}
	}
	XConfigItem()
		:m_isEnable(false)
		,m_pVariable(NULL)
		,m_changeProc(NULL)
		,m_pClass(NULL)
		,m_pCtrl(NULL)
		,m_isActive(true)
		,m_customIt(NULL)
	{
		static int ID = 0;
		m_ID = ID ++;
	}
	~XConfigItem(){XMem::XDELETE(m_pCtrl);}
	int getID()const {return m_ID;}
	void setID(int ID){m_ID = ID;}
};
class XConfigGroup
{
private:
	void moveDownPretreatment(int pixelW,int pixelH);
	void moveDownPretreatment(const XVector2 &size){moveDownPretreatment(size.x,size.y);}
	void moveDown(int pixelW,int pixelH);
	void moveDown(const XVector2 &size){moveDown(size.x,size.y);}
	void useANewRow()
	{
		m_curInsertPos.x += (m_maxRowWidth + CFG_MANAGER_W_SPACE) * m_scale.x;
		m_curInsertPos.y = m_position.y + (32.0f + CFG_MANAGER_H_SPACE) * m_scale.y;
		m_isNewRow = true;
	}
public:
	bool m_isEnable;
	bool m_isMaxH;
	bool m_isNewRow;
	XVector2 m_maxSize;
	XVector2 m_position;
	XVector2 m_scale;
	std::string m_name;
	XGroup m_group;

	std::vector<XConfigItem *> m_items;
	XVector2 m_curInsertPos;
	void relayout();
	float m_width;
	float m_maxHeight;
	float m_maxRowWidth;
	XVector2 calculateMaxSize();

	XConfigGroup()
		:m_isEnable(false)
		,m_name(CFG_DEFAULT_GROUPNAME)
		,m_position(0.0f,0.0f)
		,m_scale(1.0f,1.0f)
	{}
};
enum XConfigMode
{
	CFG_MODE_NORMAL,
	CFG_MODE_SERVER,
	CFG_MODE_CLIENT,
};
enum XConfigNetOperate
{
	CFG_NET_OP_SAVE,
	CFG_NET_OP_LOAD,
	CFG_NET_OP_DEFAULT,
};
class XConfigManager
{
public:
	static const int m_cfgMaxItemsSum = 10000;
protected:
	XConfigManager()
		:m_isInited(false)
		,m_isVisble(true)
		,m_position(0.0f,0.0f)
		,m_scale(1.0,1.0f)
		,m_maxHeight(300.0f)
		,m_width(256.0f)
		,m_curInsertPos(0.0f,0.0f)
		,m_configMode(CFG_MODE_NORMAL)

		,m_textColor(0.0f,0.0f,0.0f,1.0f)
		,m_isMouseDown(false)
	{}
	XConfigManager(const XConfigManager&);
	XConfigManager &operator= (const XConfigManager&);
	virtual ~XConfigManager(){release();}
public:
	static XConfigManager& GetInstance()
	{
		static XConfigManager m_instance;
		return m_instance;
	}
private:
	bool m_isInited;
	bool m_isVisble;
	bool m_isNewRow;
	std::vector<XConfigItem *> m_pItems;
	std::vector<XConfigGroup *> m_pGroups;

	static void ctrlProc(void*,int,int);

	XVector2 m_position;
	XVector2 m_scale;
	float m_maxHeight;
	float m_width;
	XVector2 m_curInsertPos;
	XFColor m_textColor;

	XButton m_saveBtn;
	XButton m_loadBtn;
	XButton m_defaultBtn;
	XButton m_undoBtn;
	XButton m_redoBtn;
	XButton m_netUpdateBtn;
	XButton m_netInjectBtn;

	void relayout();
	void release();

	XConfigMode m_configMode;
	XNetClient m_netClient;
	XNetServer m_netServer;

	unsigned char *getConfigInfo(int &len);
	void setOperateToServer(XConfigNetOperate op);
	void sendSynchToServer();
	void sendCFGInfo();
	void sendItemValue(const XConfigItem * it);
	void sendInject();
	void updateNet();
	void updateInfo(unsigned char *data);
	void setItemValue(int ID,const XConfigValue value);
	void updateItemToCFG(XConfigItem * it);
	void updateItemFromCFG(XConfigItem * it);

	bool createAItemFromStr(const unsigned char * str,int &offset,unsigned char *groupName,
		std::vector<XConfigItem *> *itemsList,std::vector<int> *itemsIDListD);

private:
	float m_maxRowWidth;
	void moveDown(int pixelW,int pixelH)
	{
		m_curInsertPos.y += (pixelH + CFG_MANAGER_H_SPACE) * m_scale.y;
		if(m_isNewRow || pixelW > m_maxRowWidth) m_maxRowWidth = pixelW;
		m_isNewRow = false;
		if(m_curInsertPos.y >= m_position.y + m_maxHeight)
		{
			useANewRow();
		}
	}
	void useANewRow()
	{
		m_curInsertPos.x += (m_maxRowWidth + CFG_MANAGER_W_SPACE) * m_scale.x;
		m_curInsertPos.y = m_position.y + (32.0f + CFG_MANAGER_H_SPACE) * m_scale.x;
		m_isNewRow = true;
	}
	void relayoutGroup(int index,bool flag = true);
public:
	bool init(XConfigMode mode = CFG_MODE_NORMAL);
	void update();
	void draw();
	void setItemActive(bool isActive,void * p);
	void setPosition(float x,float y)
	{
		if(!m_isInited) return;
		m_position.set(x,y);
		relayout();
	}
	void setScale(float s){ setScale(s, s); }
	void setScale(float x,float y)
	{
		if(!m_isInited) return;
		m_scale.set(x,y);
		relayout();
	}
	void setTextColor(const XFColor& color);
	XFColor getTextColor() const {return m_textColor;}
	void setMaxHeight(float h)
	{
		if(h < 1) h = 1;
		m_maxHeight = h;
		relayout();
	}
	void setVisible();
	void disVisible();
	bool getIsVisble(){return m_isVisble;}

	template<typename T>
	int addAItem(T *p,XConfigDataType type,const char * name,
		T max,T min,T def,
		void (* changeProc)(void *,void *) = NULL,const char * groupName = NULL,void *pClass = NULL);
	int addCustomItem(XCFGItemBasic *it,const char * groupName);
	int addSpecialItem(void * it,XConfigDataType type,const char * groupName);
	bool isSpecialItemExist(void *it)
	{
		if(it == NULL) return false;
		for(unsigned int i = 0;i < m_pItems.size();++ i)
		{
			if(m_pItems[i]->m_pVariable == it) return true;
		}
		return false;
	}

	bool isItemExist(void * p);
	bool isCustomItemExist(XCFGItemBasic *it);

private:
	bool getItemValueFromStr(XConfigItem *it,const char *str);
public:
	bool save(const char *filename = NULL);
	bool load(const char *filename = NULL){return loadEx(filename);}
	bool loadEx(const char *filename = NULL);
	void setDefault();

private:
	bool m_isMouseDown;
	XVector2 m_mousePos;
public:
	XBool mouseProc(float x,float y,XMouseState mouseState)
	{
		XRect tmpRect(m_position.x,m_position.y,
			m_position.x + 32.0f * m_scale.x,m_position.y + 32.0f * m_scale.y);
		switch(mouseState)
		{
		case MOUSE_MOVE:
			if(m_isMouseDown)
			{
				XVector2 tmp = XVector2(x,y) - m_mousePos;
				setPosition(m_position.x + tmp.x,m_position.y + tmp.y);
				m_mousePos.set(x,y);

			}
			break;
		case MOUSE_LEFT_BUTTON_DOWN:
		case MOUSE_LEFT_BUTTON_DCLICK:
			if(tmpRect.isInRect(x,y))
			{
				m_isMouseDown = true;
				m_mousePos.set(x,y);
			}
			break;
		case MOUSE_LEFT_BUTTON_UP:
			m_isMouseDown = false;
			break;
		default:
			break;
		}
		return XFalse;
	}

	XConfigItem *getItemByID(int ID);
	XConfigItem *getItemByVariable(void *p);
	XConfigItem *getItemByName(const char *name,int start = 0);

	bool decreaseAItem(void *p);
	bool clear();

	bool addGroup(const char * name);
	bool renameGroup(const char *oldName,const char *newName)
	{
		if(oldName == NULL || newName == NULL) return false;
		if(isGroupExist(newName)) return false;
		XConfigGroup *gp = getGroup(oldName);
		if(gp == NULL) return false;
		gp->m_name = newName;
		gp->m_group.setCaptionText(newName);
		return true;
	}
	bool isGroupExist(const char * name);
	XConfigGroup *getGroup(const char * name);
};
template<typename T>
int XConfigManager::addAItem(T *p,XConfigDataType type,const char * name,
	T max,T min,T def,
	void (* changeProc)(void *,void*),const char * groupName,void *pClass)
{
	if(type >= CFG_DATA_TYPE_CUSTOM || p == NULL) return -1;
	if(p != NULL && isItemExist(p)) return -1;
	XConfigItem *pItem = XMem::createMem<XConfigItem>();
	if(pItem == NULL ||
		type == CFG_DATA_TYPE_CUSTOM) return -1;
	if(name == NULL) pItem->m_name = " ";
	else pItem->m_name = name;
	pItem->m_changeProc = changeProc;
	pItem->m_pClass = pClass;
	char tempStr[1024];
	switch(type)
	{
	case CFG_DATA_TYPE_INT:
		pItem->m_defaultValue.valueI = (int)def;
		pItem->m_curValue.valueI = * (int *)p;
		pItem->m_rangeMin.valueI = (int)min;
		pItem->m_rangeMax.valueI = (int)max;
		{
			XSliderEx *pCtrl = XMem::createMem<XSliderEx>();
			if(pCtrl == NULL) return -1;
			if(m_configMode != CFG_MODE_CLIENT) pCtrl->setWithUndo(true);
			pCtrl->initWithoutSkin(XRect(0.0f,CFG_MNG_H_FONT,m_width,CFG_MNG_H_FONT + CFG_MNG_H_SLD),
				pItem->m_rangeMax.valueI,pItem->m_rangeMin.valueI,SLIDER_TYPE_HORIZONTAL,XVector2(0.0,16.0f));
			pCtrl->setScale(m_scale);
			pCtrl->setTextColor(m_textColor);
			if(name == NULL) pCtrl->setFont("%%.0f");
			else
			{
				sprintf(tempStr,"%s:%%.0f",name);
				pCtrl->setFont(tempStr);
			}

			pCtrl->setEventProc(ctrlProc,this);
			pCtrl->setCurValue(* (int *)p);
			pCtrl->stateChange();
			pItem->m_pCtrl = pCtrl;
		}
		break;
	case CFG_DATA_TYPE_CHAR:
		pItem->m_defaultValue.valueI = (char)def;
		pItem->m_curValue.valueI = * (char *)p;
		pItem->m_rangeMin.valueI = (char)min;
		pItem->m_rangeMax.valueI = (char)max;
		{
			XSliderEx *pCtrl = XMem::createMem<XSliderEx>();
			if(pCtrl == NULL) return -1;
			if(m_configMode != CFG_MODE_CLIENT) pCtrl->setWithUndo(true);
			pCtrl->initWithoutSkin(XRect(0.0f,CFG_MNG_H_FONT,m_width,CFG_MNG_H_FONT + CFG_MNG_H_SLD),
				pItem->m_rangeMax.valueI,pItem->m_rangeMin.valueI,SLIDER_TYPE_HORIZONTAL,XVector2(0.0,16.0f));
			pCtrl->setScale(m_scale);
			pCtrl->setTextColor(m_textColor);
			if(name == NULL) pCtrl->setFont("%%.0f");
			else
			{
				sprintf(tempStr,"%s:%%.0f",name);
				pCtrl->setFont(tempStr);
			}

			pCtrl->setEventProc(ctrlProc,this);
			pCtrl->setCurValue(* (char *)p);
			pCtrl->stateChange();
			pItem->m_pCtrl = pCtrl;
		}
		break;
	case CFG_DATA_TYPE_UCHAR:
		pItem->m_defaultValue.valueI = (unsigned char)def;
		pItem->m_curValue.valueI = * (unsigned char *)p;
		pItem->m_rangeMin.valueI = (unsigned char)min;
		pItem->m_rangeMax.valueI = (unsigned char)max;
		{
			XSliderEx *pCtrl = XMem::createMem<XSliderEx>();
			if(pCtrl == NULL) return -1;
			if(m_configMode != CFG_MODE_CLIENT) pCtrl->setWithUndo(true);
			pCtrl->initWithoutSkin(XRect(0.0f,CFG_MNG_H_FONT,m_width,CFG_MNG_H_FONT + CFG_MNG_H_SLD),
				pItem->m_rangeMax.valueI,pItem->m_rangeMin.valueI,SLIDER_TYPE_HORIZONTAL,XVector2(0.0,16.0f));
			pCtrl->setScale(m_scale);
			pCtrl->setTextColor(m_textColor);
			if(name == NULL) pCtrl->setFont("%%.0f");
			else
			{
				sprintf(tempStr,"%s:%%.0f",name);
				pCtrl->setFont(tempStr);
			}

			pCtrl->setEventProc(ctrlProc,this);
			pCtrl->setCurValue(* (unsigned char *)p);
			pCtrl->stateChange();
			pItem->m_pCtrl = pCtrl;
		}
		break;
	case CFG_DATA_TYPE_FLOAT:
		pItem->m_defaultValue.valueF = (float)def;
		pItem->m_curValue.valueF = * (float *)p;
		pItem->m_rangeMin.valueF = (float)min;
		pItem->m_rangeMax.valueF = (float)max;
		{
			XSliderEx *pCtrl = XMem::createMem<XSliderEx>();
			if(pCtrl == NULL) return -1;
			if(m_configMode != CFG_MODE_CLIENT) pCtrl->setWithUndo(true);
			pCtrl->initWithoutSkin(XRect(0.0f,CFG_MNG_H_FONT,m_width,CFG_MNG_H_FONT + CFG_MNG_H_SLD),
				pItem->m_rangeMax.valueF,pItem->m_rangeMin.valueF,SLIDER_TYPE_HORIZONTAL,XVector2(0.0,16.0f));
			pCtrl->setScale(m_scale);
			pCtrl->setTextColor(m_textColor);
			if(name == NULL) pCtrl->setFont("%%.4f");
			else
			{
				sprintf(tempStr,"%s:%%.4f",name);
				pCtrl->setFont(tempStr);
			}

			pCtrl->setEventProc(ctrlProc,this);

			pCtrl->setCurValue(* (float *)p);
			pCtrl->stateChange();
			pItem->m_pCtrl = pCtrl;
		}
		break;
	case CFG_DATA_TYPE_XBOOL:
		pItem->m_defaultValue.valueB = (XBool)def;
		pItem->m_curValue.valueB = *(XBool *)p;
		pItem->m_rangeMin.valueB = (XBool)min;
		pItem->m_rangeMax.valueB = (XBool)max;
		{
			XCheck *pCtrl = XMem::createMem<XCheck>();
			if(pCtrl == NULL) return -1;
			if(m_configMode != CFG_MODE_CLIENT) pCtrl->setWithUndo(true);
			if(name == NULL) pCtrl->initWithoutSkin(" ",XEE::systemFont,1.0f,XRect(0.0f,0.0f,CFG_MNG_H_FONT,CFG_MNG_H_FONT),
				XVector2(CFG_MNG_H_FONT,CFG_MNG_H_FONT * 0.5f));
			else pCtrl->initWithoutSkin(name,XEE::systemFont,1.0f,XRect(0.0f,0.0f,CFG_MNG_H_FONT,CFG_MNG_H_FONT),
				XVector2(CFG_MNG_H_FONT,CFG_MNG_H_FONT * 0.5f));
			pCtrl->setScale(m_scale);
			pCtrl->setEventProc(ctrlProc,this);
			pCtrl->setConnectVar((XBool *)p);
			pCtrl->setTextColor(m_textColor);
			if(*(XBool *)p) pCtrl->setState(XTrue);
			else pCtrl->setState(XFalse);
			pCtrl->stateChange();
			pItem->m_pCtrl = pCtrl;
		}
		break;
	case CFG_DATA_TYPE_RADIOS:
		pItem->m_defaultValue.valueI = (int)def;
		pItem->m_curValue.valueI = *(int *)p;
		pItem->m_rangeMin.valueI = (int)min;
		pItem->m_rangeMax.valueI = (int)max;
		{
			XRadios *pCtrl = XMem::createMem<XRadios>();
			if(pCtrl == NULL) return -1;
			if(m_configMode != CFG_MODE_CLIENT) pCtrl->setWithUndo(true);
			pCtrl->initWithoutSkin(1,XVector2(0.0f,CFG_MNG_H_FONT + 2.0f),XRect(0.0f,0.0f,CFG_MNG_H_FONT,CFG_MNG_H_FONT),XEE::systemFont,1.0f,
				XVector2(CFG_MNG_H_FONT + 2.0f,CFG_MNG_H_FONT * 0.5f));
			pCtrl->setRadiosText(name);
			pCtrl->setScale(m_scale);
			pCtrl->setTextColor(m_textColor);
			pCtrl->setEventProc(ctrlProc,this);
			pCtrl->setChoosed(*(int *)p);
			pCtrl->stateChange();
			pItem->m_pCtrl = pCtrl;
		}
		break;
	}
	pItem->m_isEnable = true;
	pItem->m_pVariable = p;
	pItem->m_type = type;
	m_pItems.push_back(pItem);
	if(groupName == NULL)
	{
		XConfigGroup *gp = m_pGroups[0];
		gp->m_items.push_back(pItem);
		if(pItem->m_pCtrl != NULL)
		{
			gp->m_group.pushChild(pItem->m_pCtrl);
			if(gp->m_group.getState() == XGroup::STATE_MINISIZE) pItem->m_pCtrl->disVisible();
		}
		relayout();
	}else
	{
		XConfigGroup *gp = getGroup(groupName);
		if(gp != NULL)
		{
			gp->m_items.push_back(pItem);
			if(pItem->m_pCtrl != NULL)
			{
				gp->m_group.pushChild(pItem->m_pCtrl);
				if(gp->m_group.getState() == XGroup::STATE_MINISIZE) pItem->m_pCtrl->disVisible();
			}
			relayout();
		}
	}
	return pItem->getID();
}

#define XCFGManager XConfigManager::GetInstance()

inline void XConfigManager::setItemValue(int ID,const XConfigValue value)
{
	XConfigItem * it = getItemByID(ID);
	if(it == NULL) return;
	it->m_curValue = value;
	updateItemFromCFG(it);
}
}
#endif
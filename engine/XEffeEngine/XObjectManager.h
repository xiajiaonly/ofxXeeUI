#ifndef _JIA_XOBJECTMANAGER_
#define _JIA_XOBJECTMANAGER_

#include "XControl\XMultiListBasic.h"
namespace XE{

#define OBJ_MANAGER_WITH_ID (1)

enum XObjectOptionType
{
	OBJ_OPTION_SIZE_ON,
	OBJ_OPTION_SIZE_DOWN,
	OBJ_OPTIONX_ON,
	OBJ_OPTIONX_DOWN,
	OBJ_OPTION_Y_ON,
	OBJ_OPTION_Y_DOWN,
	OBJ_OPTION_ROTATE_ON,
	OBJ_OPTION_ROTATE_DOWN,
	OBJ_OPTION_ROTATE_MODE_CHANGE,
	OBJ_OPTION_TURNOVER_MODE_CHANGE,
};
enum XObjectOption
{
	OBJ_OPTION_NULL,
	OBJ_OPTION_POSITION,
	OBJ_OPTION_SIZE,
	OBJ_OPTION_ROTATE,
	OBJ_OPTION_ROTATEMODE,
	OBJ_OPTION_TURNOVERMODE,

	OBJ_OPTION_EDIT,
};
enum XObjectOptionState
{
	OBJ_OPTION_STATE_NULL,
	OBJ_OPTION_STATE_CAN_NOT_CHOOSE,
	OBJ_OPTION_STATE_NO_MOUSE_PROC,
	OBJ_OPTION_STATE_NO_KEY_PROC,
};
enum XObjectMouseState
{
	OBJ_STATE_NULL,
	OBJ_STATE_MOUSE_DOWN,
	OBJ_STATE_MOUSE_MOVE,
	OBJ_STATE_MOUSE_ON,
};

struct XObjectInfo
{
	XVector2 m_position;
	XVector2 m_scale;
	float m_angle;

	float length;

	XObjectBasic *m_pObject;
	XObjectMouseState m_objectMouseState;
	XVector2 m_objectMousePoint;
	XObjectOption m_objectKeyOption;
	XObjectOptionState m_objectSetState;
	int m_objectEditParm;

	XBool m_objCanEdit;
	XBool m_objBeSelect;

	int m_objLineOrder;
	int m_lineObjOrder;
#if OBJ_MANAGER_WITH_ID
	XFontUnicode *m_fontID;
#endif
	XObjectInfo()
		:m_pObject(NULL)
		,m_objectMouseState(OBJ_STATE_NULL)
		,m_objectKeyOption(OBJ_OPTION_NULL)
		,m_objectSetState(OBJ_OPTION_STATE_NULL)
		,m_objLineOrder(-1)
		,m_lineObjOrder(-1)
		,m_objCanEdit(XFalse)
		,m_objBeSelect(XFalse)
#if OBJ_MANAGER_WITH_ID
		,m_fontID(NULL)
#endif
	{}
};

class XObjectManager
{
protected:
	XObjectManager();
	XObjectManager(const XObjectManager&);
	XObjectManager &operator= (const XObjectManager&);
	virtual ~XObjectManager();
public:
	static XObjectManager& GetInstance()
	{
		static XObjectManager m_instance;
		return m_instance;
	}
private:
	int m_curMouseOnObjectSum;

	XVector2 m_curMousePosition;

	void objectKeyOption(unsigned int order,XObjectOptionType optionType);

	std::vector<XObjectInfo> m_objInfo;

	XBool m_canAddObj;
#if OBJ_MANAGER_WITH_ID
	char m_showObjID;
	void setShowObjID();
#endif
	void release()
	{
#if OBJ_MANAGER_WITH_ID
		for(unsigned int i = 0;i < m_objInfo.size();++ i)
		{
			XMem::XDELETE(m_objInfo[i].m_fontID);
		}
#endif
		m_objInfo.clear();
	}
	XFontUnicode m_font;
	XBool m_isInited;
	XBool checkNeedUpdate(int order);
	void updateObjInfo(int order);
	void updateObjStateInfo(int order);

	XMultiListBasic m_mutiList;
	void upDateMultiListData();

	static void ctrlProc(void*,int,int);
	XBool m_isShowUI;
	XBool m_isOption;
	XBool m_canSelect;
	char m_editWindowsPos;
	void setEditWidowsPos();

	void chengeCanSelectState();
	void setShow();
	void disShow();
	void setOption();
	void disOption();
public:

	XKeyState m_keyState[4];
	int m_keyTimer[4];
	int m_keyCurTime[4];
	int m_keyMaxTime;
	int m_keyMinTime;

	XKeyState m_ctrlKeyState;
public:
	XBool init(XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	int addAObject(XObjectBasic * object);
	void decreaseAObject(unsigned int objectID);
	void decreaseAObject(const void * object);
	int findObjectID(const void * object) const;
	XObjectType getObjectType(unsigned int objectID) const;
	void *getObject(unsigned int objectID) const;

	void mouseProc(int x,int y,XMouseState eventType);
	void keyProc(int keyID,XKeyState keyState);
	int getCurObjectSum() const;
	int getCurMouseOnObjectSum() const;
	int getCurChooseObjectSum() const;
	void getCurChooseObjectID(int *ID) const;

	void draw();
	void move(int delay);
private:
	XFontUnicode m_mousePosFont;
};
#define XObjManger XObjectManager::GetInstance()
#if WITH_INLINE_FILE
#include "XObjectManager.inl"
#endif
}
#endif
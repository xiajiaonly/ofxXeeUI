#ifndef _JIA_XACTIONDESCRIPTION_
#define _JIA_XACTIONDESCRIPTION_

#include "../XObjectBasic.h"
#include "../XFont/XNumberEx.h"
#include "../XMath/XMoveData.h"

#include <vector>
#include "XActionObjectManager.h"
namespace XE{
#define ACTION_DES_PATH ("ResourcePack/ActionDescription/")
enum XActionType
{
	ACTION_TYPE_POSITION,
	ACTION_TYPE_POSITIONX,
	ACTION_TYPE_POSITION_Y,
	ACTION_TYPE_COLOR,
	ACTION_TYPE_R,
	ACTION_TYPE_G,
	ACTION_TYPE_B,
	ACTION_TYPE_ALPHA,
	ACTION_TYPE_ANGLE,
	ACTION_TYPE_SIZE,
	ACTION_TYPE_SIZE_EX,
	ACTION_TYPE_SIZEX,
	ACTION_TYPE_SIZE_Y,
	ACTION_TYPE_STAY,
	ACTION_TYPE_MAX,
};
extern std::string actionTypeStr[];
struct XActionState
{
	XBool isEnable;
	XVector2 position;
	XFColor color;
	float angle;
	XVector2 size;
	XActionState()
		:angle(0.0f)
		,isEnable(XFalse)
	{}
};

enum XActionStateType
{
	ACTION_STATE_TYPE_POSX,
	ACTION_STATE_TYPE_POS_Y,
	ACTION_STATE_TYPE_COLOR_R,
	ACTION_STATE_TYPE_COLOR_G,
	ACTION_STATE_TYPE_COLOR_B,
	ACTION_STATE_TYPE_COLOR_A,
	ACTION_STATE_TYPE_ANGLE,
	ACTION_STATE_TYPE_SIZEX,
	ACTION_STATE_TYPE_SIZE_Y,
	ACTION_STATE_TYPE_MAX,
};
struct XActionStateDescription
{
	int time;
	XBool isValidPosX;
	XBool isValidPosY;
	XBool isValidColorR;
	XBool isValidColorG;
	XBool isValidColorB;
	XBool isValidColorA;
	XBool isValidAngle;
	XBool isValidSizeX;
	XBool isValidSizeY;

	XVector2 position;
	XFColor color;
	float angle;
	XVector2 size;
	XActionStateDescription()
		:angle(0.0f)
	{}
};
typedef XActionStateDescription XActionStateDes;

class XActionCore
{
public:
	XBool m_isEnable;
	XActionType m_actionType;

	XMoveData *m_moveData;
	int m_moveDataSum;
	XObjectBasic* m_object;
	float m_startTime;
	float m_endTime;
	float m_timeLine;
	XActionState m_stayState;

	XBool m_isActionStart;
	XBool m_isEnd;
	XBool set(float startTime,float endTime,XActionType type,XMoveData *md = NULL,XActionState *state = NULL);
	void move(int delay);
	XBool getIsEnd() const {return m_isEnd;}
	void setEnd(){m_isEnd = XTrue;}

	void setStart();
	XActionCore()
		:m_isEnable(XFalse)
		,m_isEnd(XTrue)
		,m_startTime(0.0f)
		,m_timeLine(0.0f)

		,m_moveData(NULL)
		,m_moveDataSum(0)
	{}
	~XActionCore(){release();}
	void release();
};

class XActionMananger;
class XActionDescription
{
	friend XActionMananger;
private:
	int m_ID;
	XBool m_isEnable;
	std::vector<XActionDescription *> m_otherAction;
	std::vector<int> m_otherActionID;
	XObjectBasic* m_object;
	std::vector<XActionCore *> m_actionCore;
	char m_actionName[MAX_FILE_NAME_LENGTH];
	float m_startTime;
	float m_endTime;
	float m_timeLine;
	XBool m_isEnd;

	XBool m_isActionStart;

private:
	std::vector<XActionStateDes *> m_stateTable;
	int m_minTime;
	int m_maxTime;
	float getASValue(int time,XActionStateType type);
public:
	int getMinTime() {return m_minTime;}
	int getMaxTime() {return m_maxTime;}
	int getActionStateDesSum() {return m_stateTable.size();}
	XActionStateDes* getPreviousASD(int time,XActionStateType type);
	XActionStateDes* getNextASD(int time,XActionStateType type);
	XActionStateDes* getASD(int index)
	{
		if(index < 0 || index >= m_stateTable.size()) return NULL;
		return m_stateTable[index];
	}
	XActionState getActionState(int time);
	XBool insertASD(XActionStateDes* ASD);
	XBool popASD(const XActionStateDes* ASD);

public:
	float getEndTime() const {return m_endTime;}
	float getStartTime() const {return m_startTime;}
	float getCurTime() const {return m_timeLine;}
	XObjectBasic * getObject() {return m_object;}
	int getOtherActionSum(){return m_otherAction.size();}
	XActionDescription *getOtherAD(int index)
	{
		if(index < 0 || index >= m_otherAction.size()) return NULL;
		return m_otherAction[index];
	}
	int getActionCoreSum(){return m_actionCore.size();}
	XActionCore * getActionCore(int index)
	{
		if(!m_isEnable) return NULL;
		if(index < 0 || index >= m_actionCore.size()) return NULL;
		return m_actionCore[index];
	}

public:
	int getID() const{return m_ID;}
	const char * getName() const{return m_actionName;}
	XBool setName(const char * name)
	{
		if(name == NULL) return XFalse;
		if(strlen(name) >= MAX_FILE_NAME_LENGTH) return XFalse;
		if(strcmp(name,m_actionName) == 0) return XTrue;

		strcpy(m_actionName,name);
		return XTrue;
	}
	void move(int delay);
	void draw();
	void setStart();
	XBool getIsEnd() const {return m_isEnd;}
	void setLoop();
	XBool set(float startTime,float endTime,XObjectBasic *obj)
	{
		if(m_isEnable) return XFalse;
		m_startTime = startTime;
		m_endTime = endTime;
		m_object = obj;
		m_otherAction.clear();
		m_actionCore.clear();

		m_isEnable = XTrue;
		return XTrue;
	}
	int getADChildIndex(XActionDescription * p);
	void setObject(XObjectBasic *obj);
	XBool loadAction(const char * filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool saveAction(const char *filename = NULL);
	XBool pushAActionCore(XActionCore * p);
	XBool popAActionCore(XActionCore * p);
	XBool replaceAAction(int index,XActionCore * p);
	XBool popAActionCore(int index);
	XBool getIsChildActionDes(XActionDescription * p);
	XBool pushAActionDescription(XActionDescription * p);
	XBool popAActionDescription(int index);
	XActionDescription();
	~XActionDescription(){release();}
	void release();
};
}
#endif
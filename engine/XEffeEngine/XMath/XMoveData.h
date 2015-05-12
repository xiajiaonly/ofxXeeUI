#ifndef _JIA_XMOVEDATA_
#define _JIA_XMOVEDATA_
#include "../XOSDefine.h"
#include "stdio.h"
#include "XMath.h"
namespace XE{

enum XMoveDataMode
{
	MOVE_DATA_MODE_NULL,
	MOVE_DATA_MODE_LINE,
	MOVE_DATA_MODE_SIN,
	MOVE_DATA_MODE_SIN_MULT,
	MOVE_DATA_MODE_SQRT2,
	MOVE_DATA_MODE_SQRT2_MULT,
	MOVE_DATA_MODE_COS,
	MOVE_DATA_MODE_COS_MULT,
	MOVE_DATA_MODE_DSIN,
	MOVE_DATA_MODE_DCOS,
	MOVE_DATA_MODE_DSIN_MULT,
	MOVE_DATA_MODE_DCOS_MULT,
	MOVE_DATA_MODE_SHAKE,
	MOVE_DATA_MODE_MAX,
};

class XMoveData
{
private:
	float m_startData;
	float m_endData;
	float m_curData;
	float m_speed;
	float m_timer;
	int m_loopTimer;

	XBool m_isEnd;
	int m_isLoop;
	XMoveDataMode m_mode;
public:
	float getStartData() const {return m_startData;}
	float getEndData() const {return m_endData;}
	float getSpeed() const {return m_speed;}
	int getLoopTimer() const {return m_isLoop;}
	XMoveDataMode getMoveMode() const {return m_mode;}
public:

	void set(float start,float end,float speed,XMoveDataMode mode = MOVE_DATA_MODE_SIN_MULT,int isLoop = 0);
	void reset();
	void move(int delay);
	float getValue(float time);
	float getCurData() const {return m_curData;}
	float getCurTimer() const {return m_timer;}
	XBool getIsEnd() const {return m_isEnd;}
	void setEnd();
	XMoveData()
		:m_startData(0.0f)
		,m_endData(0.0f)
		,m_curData(0.0f)
		,m_isEnd(XTrue)
		,m_mode(MOVE_DATA_MODE_SIN)
		,m_isLoop(0)
	{}
	void getParamStr(char * str);
};
#if WITH_INLINE_FILE
#include "XMoveData.inl"
#endif
}
#endif
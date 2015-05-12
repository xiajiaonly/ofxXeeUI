#ifndef _JIA_XAUTOSHRINKBASE_
#define _JIA_XAUTOSHRINKBASE_

#include "../XOSDefine.h"
#include "../XMouseAndKeyBoardDefine.h"
#include "../XMath/XVector2.h"
#include "../XMath/XMoveData.h"
namespace XE{

class XAutoShrinkBase
{
protected:
	bool m_withAutoShrink;
	float m_shrinkTimer;
	bool m_isInShrink;
	float m_shrinkRate;
	XVector2 m_curMousePosition;
	bool m_oldIsInRect;
	XMoveData m_shrinkMD;
	enum XShrinkDirection
	{
		DIR_NULL,
		DIR_UP,
		DIR_LEFT,
		DIR_RIGHT,
	};
	XShrinkDirection m_curShrinkDir;
	virtual XShrinkDirection calShrinkDir() = 0;
	void startShrink(XShrinkDirection dir)
	{
		m_shrinkMD.set(m_shrinkRate,1.0f,0.01f,MOVE_DATA_MODE_COS_MULT);
		m_curShrinkDir = dir;
		m_isInShrink = true;
	}
	void disShrink()
	{
		m_shrinkMD.set(m_shrinkRate,0.0f,0.01f,MOVE_DATA_MODE_SIN_MULT);
		m_isInShrink = false;
	}
	void updateShrinkState(int stepTime);
public:
	void setAutoShrink(bool flag)
	{

		if(m_withAutoShrink && !flag && m_isInShrink)
		{
		}
		m_withAutoShrink = flag;
	}
	bool getAutoShrink()const{return m_withAutoShrink;}
public:
	XAutoShrinkBase()
		:m_withAutoShrink(false)
		,m_shrinkTimer(0.0f)
		,m_isInShrink(false)
		,m_shrinkRate(0.0f)
		,m_oldIsInRect(false)
	{}
	virtual ~XAutoShrinkBase(){}
protected:
	virtual void updateShrinkPosition() = 0;
	virtual XBool getIsInShrinkRect() = 0;
};
}
#endif
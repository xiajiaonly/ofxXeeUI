#ifndef _JIA_XRIGIDBALL_
#define _JIA_XRIGIDBALL_

#include "../XOSDefine.h"
#include "../XMath/XVector2.h"
namespace XE{
extern float gravity;

class XRigidBall
{
private:
	XBool m_isEnable;
public:
	XVector2 m_position;
	float m_radius;
	float m_mass;
	XVector2 m_speed;
	float m_airResistance;
	float m_adhereRate;
	float m_adhereRadius;

	XVector2 m_positionS;

	void setEnable(XBool isEnable) {m_isEnable = isEnable;}
	XBool getIsEnable() const	{return m_isEnable;}
	void init(const XVector2& position,float radius,float mass,const XVector2& speed,float airResistance,float adhereRate,float adhereRadius)
	{
		m_position = position;
		m_radius = radius;
		m_mass = mass;
		m_speed = speed;
		m_airResistance = airResistance;
		m_adhereRate = adhereRate;
		m_adhereRadius = adhereRadius;
	}
	XRigidBall()
		:m_isEnable(XFalse)
		,m_position(0.0f,0.0f)
		,m_radius(0.0f)
		,m_mass(0.0f)
		,m_speed(0.0f,0.0f)
		,m_airResistance(0.0f)
		,m_adhereRate(0.0f)
		,m_adhereRadius(0.0f)
	{}
};

struct XCrashData
{
	double m_crashTime;
	float m_crashAngle;
	char m_needFrash;
	XCrashData()
		:m_crashTime(0.0)
		,m_crashAngle(0.0f)
		,m_needFrash(0)
	{}
};
class XRigidBalls
{
private:
	XBool m_isInited;
	XBool m_isEnable;
	XBool crashInsideProc(double timeDelay,double upTime);
	void crashTimerProc(double timeDelay,double upTime);
	XBool checkProc();
public:

	XRigidBall *m_pRigidBall;
	int m_rigidBallSum;

	XLine *m_pLine;
	int m_lineSum;

	int m_rigidBallDataSum;
	XCrashData *m_pCrashData;

	double m_minTimer;
	int m_crashOrder;
	int m_crashObj0;
	int m_crashObj1;
	int m_crashSameTimeSum;
	int m_deep;

	XBool m_haveError;

	XBool init(int rigidBallSum,int lineSum);
	void move(int timeDelay)
	{
		if(!m_isInited &&
		!m_isEnable &&
		m_haveError) return;
		crashProc(timeDelay);
	}
	void crashProc(int timeDelay);
	XBool addOneBall(const XVector2& position,float radius,float mass,const XVector2 &speed,float airResistance,float adhereRate,float adhereRadius);
	XBool addOneLine(const XVector2& startPosition,const XVector2 &endPosition);
	XRigidBalls();
	void setEnable(XBool isEnable)	{m_isEnable = isEnable;}
	XBool getIsEnable() const {return m_isEnable;}
	XBool getBallIsEnable(int order) const	{return m_pRigidBall[order].getIsEnable();}
	XVector2 getBallPosition(int order) const {return m_pRigidBall[order].m_position;}
};
}
#endif
#ifndef _JIA_XBEZIERSPLINE_
#define _JIA_XBEZIERSPLINE_

#include "XBasicClass.h"
namespace XE{

class XBezierSpline
{
private:
	XVector2 m_pS;
	XVector2 m_pSP;
	XVector2 m_pEP;
	XVector2 m_pE;

	XBool m_isEnd;
	float m_speed;
	XVector2 m_curValue;
	float m_curAngle;
	float m_curPosition;
public:
	XVector2 getBezierSplineValue(float temp);
	float getBezierSplineAngle(float temp);
	XBool getIsEnd() const {return m_isEnd;}
	float getSpeed() const {return m_speed;}
	void setSpeed(float speed) {m_speed = speed;}
	XVector2 getCurValue() const {return m_curValue;}
	float getCurAngle() const {return m_curAngle;}
	float getCurPosition() const {return m_curPosition;}

	void move(int timeDelay);
	XBezierSpline();
	void draw();

	void init(const XVector2& pStart,const XVector2& pSP,const XVector2& pEP,const XVector2& pEnd);
	void init(float pSx,float pSy,float pSPx,float pSPy,float pEPx,float pEPy,float pEx,float pEy);
	void reset();

private:
	double m_length;
	double m_startSpeed;
	double m_endSpeed;
	void calculate()
	{
		m_length = getLength(1.0f);
		m_startSpeed = speed(0.0f);
		m_endSpeed = speed(1.0f);
	}
public:
	XVector2 getBezierSplineValueEx(float temp){return getBezierSplineValue(getT(temp));}
	float getBezierSplineAngleEx(float temp){return getBezierSplineAngle(getT(temp));}
	double speedX(double t)
	{
		double it = 1.0 - t;
		return -3.0*m_pS.x*it*it + 3.0*m_pSP.x*it*it - 6.0*m_pSP.x*it*t + 6.0*m_pEP.x*it*t - 3.0*m_pEP.x*t*t + 3.0*m_pE.x*t*t;
	}
	double speedY(double t)
	{
		double it = 1.0 - t;
		return -3.0*m_pS.y*it*it + 3.0*m_pSP.y*it*it - 6.0*m_pSP.y*it*t + 6.0*m_pEP.y*it*t - 3.0*m_pEP.y*t*t + 3.0*m_pE.y*t*t;
	}
	double speed(double t)
	{
		double sx = speedX(t);
		double sy = speedY(t);
		return sqrt(sx*sx+sy*sy);
	}
	double getLength(double t)
	{

		#define TOTAL_SIMPSON_STEP  (10000)

		int stepCounts = (int)(TOTAL_SIMPSON_STEP*t);
		if(stepCounts & 1) stepCounts++;
		if(stepCounts == 0) return 0.0;

		int halfCounts = (stepCounts >> 1);
		double sum1 = 0.0,sum2 = 0.0;
		double dStep = t/stepCounts;
		for(int i=0; i<halfCounts; i++)
		{
			sum1 += speed(((i << 1) + 1) * dStep);
		}
		for(int i=1; i<halfCounts; i++)
		{
			sum2 += speed((i << 1) * dStep);
		}
		return (m_startSpeed + m_endSpeed + 2.0f * sum2 + 4.0f * sum1) * dStep / 3.0;
	}
	double getT(double t)
	{
		double len = t * m_length;
		double t1=t, t2;
		while(true)
		{
			t2 = t1 - (getLength(t1)-len)/speed(t1);
			if(abs(t1-t2)<0.0001) break;
			t1=t2;
		}
		return t2;
	}
};
inline void XBezierSpline::init(const XVector2& pStart,const XVector2& pSP,const XVector2& pEP,const XVector2& pEnd)
{
	m_pS = pStart;
	m_pSP = pSP;
	m_pEP = pEP;
	m_pE = pEnd;
	calculate();
}
inline void XBezierSpline::init(float pSx,float pSy,float pSPx,float pSPy,float pEPx,float pEPy,float pEx,float pEy)
{
	m_pS.set(pSx,pSy);
	m_pSP.set(pSPx,pSPy);
	m_pEP.set(pEPx,pEPy);
	m_pE.set(pEx,pEy);
	calculate();
}
inline void XBezierSpline::reset()
{
	m_curPosition = 0.0f;
	m_isEnd = XFalse;
	m_curValue = m_pS;
}

class XBezierSpline2
{
private:
	XVector2 m_pS;
	XVector2 m_pP;
	XVector2 m_pE;

	XBool m_isEnd;
	float m_speed;
	XVector2 m_curValue;
	float m_curAngle;
	float m_curPosition;
public:
	XVector2 getBezierSplineValue(float temp);

private:
	double m_length;
	double ax,ay,bx,by;
	double A,B,C;
	void calculate()
	{
		m_length = getLength(1.0f);
		ax = m_pS.x - 2.0*m_pP.x + m_pE.x;
		ay = m_pS.y - 2.0*m_pP.y + m_pE.y;
		bx = 2.0*m_pP.x - 2.0*m_pS.x;
		by = 2.0*m_pP.y - 2.0*m_pS.y;

		A = 4.0 * (ax*ax+ay*ay);
		B = 4.0 * (ax*bx+ay*by);
		C = bx*bx+by*by;
	}
public:
	double getLength(double t)
	{
		double temp1 = sqrt(C+t*(B+A*t));
		double temp2 = (2.0*A*t*temp1+B*(temp1-sqrt(C)));
		double temp3 = log(B+2.0*sqrt(A)*sqrt(C));
		double temp4 = log(B+2.0*A*t+2.0*sqrt(A)*temp1);
		double temp5 = 2.0*sqrt(A)*temp2;
		double temp6 = (B*B-4.0*A*C)*(temp3-temp4);
		return (temp5+temp6)/(8.0*pow(A,1.5));
	}

	float speed(float t)
	{
		return sqrt(A*t*t + B*t+C);
	}
	double getT(float t)
	{
		float l = t * m_length;
		float t1 = t,t2;
		while(true)
		{
			t2 = t1 - (getLength(t1) - l) / speed(t1);
			if(abs(t1 - t2) < 0.0001) break;
			t1 = t2;
		}
		return t2;
	}

	float getBezierSplineAngle(float temp);
	XBool getIsEnd() const {return m_isEnd;}
	float getSpeed() const {return m_speed;}
	void setSpeed(float speed) {m_speed = speed;}
	XVector2 getCurValue() const {return m_curValue;}
	float getCurAngle() const {return m_curAngle;}
	float getCurPosition() const {return m_curPosition;}

	void move(int timeDelay);
	XBezierSpline2();
	void draw();

	void init(const XVector2& pStart,const XVector2& pP,const XVector2& pEnd);
	void init(float pSx,float pSy,float pPx,float pPy,float pEx,float pEy);
	void reset();
};
inline void XBezierSpline2::init(const XVector2& pStart,const XVector2& pP,const XVector2& pEnd)
{
	m_pS = pStart;
	m_pP = pP;
	m_pE = pEnd;
}
inline void XBezierSpline2::init(float pSx,float pSy,float pPx,float pPy,float pEx,float pEy)
{
	m_pS.set(pSx,pSy);
	m_pP.set(pPx,pPy);
	m_pE.set(pEx,pEy);
}
inline void XBezierSpline2::reset()
{
	m_curPosition = 0.0f;
	m_isEnd = XFalse;
	m_curValue = m_pS;
}

}
#endif
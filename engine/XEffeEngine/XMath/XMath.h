#ifndef _JIA_XMATH_
#define _JIA_XMATH_

#include "XOSDefine.h"
#include <math.h>
#include <complex>
#include <iostream>
#include <math.h>
namespace XE{
class XVector2;
#define PI (3.1415926535897932384626433832795f)
#define PI_HALF (1.5707963267948966192313216916395f)
#define PI2 (6.283185307179586476925286766558f)
#define RADIAN2DEGREE (57.295779513082320876798154814114f)
#define DEGREE2RADIAN (0.01745329251994329576923690768488f)
#define SIN45 (0.70710678118654752440084436210485f)
#define SQRT3 (1.7320508075688772935274463415059f)
#define SQRT2 (1.4142135623730950488016887242097f)

#define XEE_Max(a,b) (((a) > (b)) ? (a) : (b))
#define XEE_Min(a,b) (((a) < (b)) ? (a) : (b))

class XLine;
class XRect;
namespace XMath
{

	extern float getApproximateData(float f,int len,int &ex);

	inline double sinTay(double x)
	{
		double x2 = x * x;

		const static double a1 = 0.99999748719198;
		const static double a3 = -0.166651680984443;
		const static double a4 = 0.00830951691334793;
		const static double a5 = -0.000184472198573026;
		return x*( a1+ ( a3 + ( a4 + a5*x2 ) * x2 ) * x2);
	}
	inline double cosTay(double x)
	{
		double cos = 0.0;

		x += 1.57079632;
		if(x > 3.14159265) x -= 6.28318531;
		if(x < 0)
		{
			cos = 1.27323954 * x + 0.405284735 * x * x;
			if(cos < 0) cos = 0.225 * (cos *-cos - cos) + cos;
			else cos = 0.225 * (cos * cos - cos) + cos;
		}else
		{
			cos = 1.27323954 * x - 0.405284735 * x * x;
			if(cos < 0) cos = 0.225 * (cos *-cos - cos) + cos;
			else cos = 0.225 * (cos * cos - cos) + cos;
		}
		return cos;
	}

	inline float bilinear(float a,float b,float c,float d,float rate0,float rate1)
	{
		return a * (1.0f - rate0) * (1.0f - rate1) + (1.0f - rate0) * rate1 * b
			+ rate0 * (1.0f - rate1) * c + rate0 * rate1 * d;
	}

	inline int toInt(float f) {return int(f + 0.5f);}

	inline int toIntFloor(float f) {return (int)floorf(f);}

	inline int toIntCeil(float f) {return (int)ceilf(f);}

	extern float getMinRate(const XVector2 &a,const XVector2 &b);

	extern float getAngleXY(float x,float y);
	inline float angleAbbreviation(float angle)
	{
		angle = fmod(angle,PI2);
		if(angle < 0.0f) angle += (float)(PI2);
		return angle;
	}
	inline float angleReduce(float angle)
	{
		angle = fmod(angle,360.0f);
		if(angle < 0.0f) angle += 360.0f;
		return angle;
	}
	inline float maping1D(float in,float imin,float imax,float omin,float omax)
	{

		if(fabs(imax - imin) < 1.192092896e-07F) return omin;
		float ret = (in - imin) / (imax - imin) * (omax - omin) + omin;
		if(ret < omin) return omin;
		if(ret > omax) return omax;
		return ret;
	}
	template<typename T>
	bool isInArea(T value,T x,T y)
	{
		if(x < y) return (value >= x && value <= y);
		else return (value >= y && value <= x);
	}

	extern XVector2 maping2D(const XVector2 *inRect,const XVector2 *outRect,const XVector2 &in);

	extern XVector2 vectorFieldLineSlerp(const XVector2 *posRect,const XVector2 *vectorRect,const XVector2 &in);

	template<typename T>
	T lineSlerp(const T &s,const T &e,float r) {return e * r + s * (1.0f  - r);}

	template<typename T>
	T cSlerp(const T &u0,const T &u1,const T &u2,const T &u3,float x)
	{
		T p = (u3 - u2) - (u0 - u1);
		T q = (u0 - u1) - p;
		T r = u2 - u0;
		return x * (x * (x * p + q) + r) + u1;
	}

	inline int getMinWellSize2n(int temp) {return (int)powf(2.0, ceilf(logf((float)temp)/logf(2.0f)));}
	inline XBool isNPOT(int width, int height)
	{
		if(getMinWellSize2n(width) != width) return XTrue;
		if(getMinWellSize2n(height) != height) return XTrue;
		return XFalse;
	}
	extern void vector4Sort(XVector2* v,XVector2* u);

	extern int getEdgePoint(float angle,XVector2 * points,const XVector2* v,const XVector2* u);

	extern int getEdgePointEx(XRect &rect,XVector2 &point,float angle,XVector2 * points);
	extern int getEdgePointEx(XRect &vRect,XRect &uRect,XVector2 &vPoint,float angle,XVector2 * vPoints,XVector2 * uPoints);
	extern int getEdgePointEx(XRect &rect,XVector2 &point,float angle,float * points);
	extern int getEdgePointEx(XRect &vRect,XRect &uRect,XVector2 &vPoint,float angle,float * vPoints,float * uPoints);

	extern double getTwoLineTime(const XVector2& L1S,const XVector2& L1E,const XVector2& L2S,const XVector2& L2E,float distance,float timer);

	extern double getLineToPointTime(const XVector2& L1S,const XVector2& L1E,const XVector2& point,float distance,float timer);

	extern double getObjectToLineTime(const XVector2& L1S,const XVector2& L1E,const XVector2& L2S,const XVector2& L2E,float distance,float timer);

	extern double getCrashTimerB2B(const XVector2& position1,const XVector2& speed1,const XVector2& a1,
								   const XVector2& position2,const XVector2& speed2,const XVector2& a2,float distance,float time);

	extern double getCrashTimerB2P(const XVector2& position1,const XVector2& speed1,const XVector2& a1,
								   const XVector2& position2,float distance,float time);

	extern double getCrashTimerB2L(const XVector2& position1,const XVector2& speed1,const XVector2& a1,
								   const XVector2& positionS,const XVector2& positionE,float distance,float time);

	extern double getCrashTimerB2L(const XVector2& position1,const XVector2& speed1,const XVector2& a1,const XLine& pL,float distance,float time);

	extern void printfR();

	extern double distancePointToLine(const XVector2& point,const XVector2& lineS,const XVector2& lineE);
	extern double distancePointToLine(const XVector2& point,double a,double b,double c);

	extern XVector2 curtatePointToLine(const XVector2& point,const XVector2& lineS,const XVector2& lineE);
	extern XVector2 curtatePointToLine(const XVector2& point,double a,double b,double c);

	extern XVector2 crossPointTineToLine(const XVector2& line1S,const XVector2& line1E,const XVector2& line2S,const XVector2& line2E);
	extern XVector2 crossPointTineToLine(double a0,double b0,double c0,double a1,double b1,double c1);

	extern XBool twoPointLine(const XVector2& lineS,const XVector2& lineE,double *a,double *b,double *c);

	extern double minDistancePointToLine(const XVector2& point,const XVector2& lineS,const XVector2& lineE);

	extern XVector2 minDistanceTwoLine(const XVector2& line1S,const XVector2& line1E,const XVector2& line2S,const XVector2& line2E);

	extern XBool getIsInRect(float x,float y,const XVector2& p1,const XVector2& p2,const XVector2& p3,const XVector2& p4);
	extern XBool getIsInRect(const XVector2& p,const XVector2& p1,const XVector2& p2,const XVector2& p3,const XVector2& p4);

	extern XBool getIsInRect(const XVector2& p,const XVector2 *pR,int pRSum);
	extern XBool getIsInRect(float x,float y,const XVector2 *pR,int pRSum);

	extern int quarticEquation(
						  double a,double b,double c,double d,double e,
						  std::complex<double> &x1,std::complex<double> &x2,
						  std::complex<double> &x3,std::complex<double> &x4
						  );

	extern int quarticEquation(
						  double a,double b,double c,double d,double e,
						  double *x);

	extern double getValueMatrix(const double *d,int s);

	extern unsigned short CRC16_Modbus(unsigned char *p,unsigned short len);
	extern unsigned short CRC16XModen(unsigned char *buf,unsigned short length);

	template<class type> void swapTwoSum(type &sum0, type &sum1)
	{
		type temp = sum0;
		sum0 = sum1;
		sum1 = temp;
	}
	inline float rectResize(float w, float h, float Rx, float Ry)
	{
		if (w <= 0.0f || h <= 0.0f || Rx <= 0.0f || Ry <= 0.0f) return 1.0f;
		if (w <= Rx && h <= Ry) return 1.0f;
		float size = Rx / w;
		if (size < Ry / h) return size;
		else return Ry / h;
	}
	inline float squareFloat(float x) { return x * x; }

#ifdef SIN_BOOK
	extern void initSinData();
	extern float xSin(float x);
#endif

#ifdef SQRT_BOOK
	extern void initSqrtData();
	extern float xSqrt(float x);
#endif
	namespace QSort
	{
		template<class type>void qSort(type *a,int low,int high)
		{
			if (low >= high) return;
			int first = low;
			int last = high;
			type key = a[first];
			while (first<last)
			{
				while(first < last && a[last] >= key)
					--last;
				a[first] = a[last];
				while(first < last && a[first] <= key)
					++first;
				a[last] = a[first];
			}
			a[first] = key;
			qSort(a, low, first - 1);
			qSort(a, first + 1, high);
		}
	}

	template<class type> void quickSort(type *datas, int sum)
	{
		if (datas == NULL || sum <= 1) return;
		QSort::qSort(datas, 0, sum - 1);
	}
}

}
#endif
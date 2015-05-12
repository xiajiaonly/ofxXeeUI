#ifndef _JIA_XMATRIX3X3_
#define _JIA_XMATRIX3X3_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "XVector2.h"
#include "XVector3.h"
#include "XVector4.h"
namespace XE{
class XMatrix3x3
{
public:
	float data[9];
	static const XMatrix3x3 identity;
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	float& operator () (int x,int y);
	float operator () (int x,int y) const;

	void loadIdentity();
	XMatrix3x3(float d0,float d1,float d2,float d3,float d4,
		float d5,float d6,float d7,float d8)
	{
		data[0] = d0;data[1] = d1;data[2] = d2;
		data[3] = d3;data[4] = d4;data[5] = d5;
		data[6] = d6;data[7] = d7;data[8] = d8;
	}
	XMatrix3x3() {loadIdentity();}
	XMatrix3x3 operator*(const XMatrix3x3 & rhs) const;
	XMatrix3x3 inverse();
	float getValue();

	XVector2 resolveEquation();
	XVector3 operator *(const XVector3 &v);
	XMatrix3x3 anti();

};
#if WITH_INLINE_FILE
#include "XMatrix3x3.inl"
#endif
namespace XMath{

inline XVector3 transform3x3(const XVector3& v,const XMatrix3x3& m)
{
	return XVector3((m.data[0]*v.x + m.data[3]*v.y + m.data[6]*v.z),
	                 (m.data[1]*v.x + m.data[4]*v.y + m.data[7]*v.z),
	                 (m.data[2]*v.x + m.data[5]*v.y + m.data[8]*v.z));
}
inline XVector3 operator *(const XVector3 &v,const XMatrix3x3 & m)
{
	return transform3x3(v,m);
}

inline XVector3 transform3x3(const XMatrix3x3& m,const XVector3& v)
{
	return XVector3((m.data[0]*v.x + m.data[1]*v.y + m.data[2]*v.z),
	                 (m.data[3]*v.x + m.data[4]*v.y + m.data[5]*v.z),
	                 (m.data[6]*v.x + m.data[7]*v.y + m.data[8]*v.z));
}
inline XMatrix3x3 getMatrix3D(const XVector3 &s)
{
	return XMatrix3x3(s.x,0,0,
						0,s.y,0,
						0,0,s.z);
}

inline XMatrix3x3 getMatrix3D(float size,const XVector3 &v)
{
	float t = size - 1.0f;
	return XMatrix3x3(1.0f + t * v.x * v.x,t * v.x * v.y,t * v.x * v.z,
						t * v.x * v.y,1.0f + t * v.y * v.y,t * v.y * v.z,
						t * v.x * v.z,t * v.y * v.z,1.0f + t * v.z * v.z);
}

inline XMatrix3x3 getRotate3D(float angle,XVector3 v)
{
	float sinA = sin(angle * DEGREE2RADIAN);
	float cosA = cos(angle * DEGREE2RADIAN);
	float tCosA = 1 - cosA;
	v = normalize(v);
	return XMatrix3x3( tCosA * v.x * v.x + cosA,		tCosA * v.x * v.y + v.z * sinA, tCosA * v.x * v.z - sinA * v.y,
						tCosA * v.x * v.y - sinA * v.z,	tCosA * v.y * v.y + cosA,		tCosA * v.y * v.z + sinA * v.x,
						tCosA * v.x * v.z + sinA * v.y,	tCosA * v.y * v.z - v.x * sinA,	tCosA * v.z * v.z + cosA);
}

inline XMatrix3x3 getRotate3DX(float angle)
{
	float sinA = sin(angle * DEGREE2RADIAN);
	float cosA = cos(angle * DEGREE2RADIAN);
	return XMatrix3x3(	1,	0,		0,
						0,	cosA,	sinA,
						0,	-sinA,	cosA);
}

inline XMatrix3x3 getRotate3DY(float angle)
{
	float sinA = sin(angle * DEGREE2RADIAN);
	float cosA = cos(angle * DEGREE2RADIAN);
	return XMatrix3x3(	cosA,0,-sinA,
						0,1,0,
						sinA,0,cosA);
}

inline XMatrix3x3 getRotate3DZ(float angle)
{
	float sinA = sin(angle * DEGREE2RADIAN);
	float cosA = cos(angle * DEGREE2RADIAN);
	return XMatrix3x3(	cosA,sinA,0,
						-sinA,cosA,0,
						0,0,1);
}

inline XMatrix3x3 getRotate3D(const XVector3 &a)
{
	XMatrix3x3 ret = getRotate3DZ(a.z);
	ret = ret * getRotate3DX(a.x);
	ret = ret * getRotate3DY(a.y);
	return ret;
}

inline XMatrix3x3 getRotateMatrix(const XVector3 &a)
{
	float sh,ch, sp,cp, sb,cb;
	sp = sin(a.x * DEGREE2RADIAN);
	cp = cos(a.x * DEGREE2RADIAN);
	sh = sin(a.y * DEGREE2RADIAN);
	ch = cos(a.y * DEGREE2RADIAN);
	sb = sin(a.z * DEGREE2RADIAN);
	cb = cos(a.z * DEGREE2RADIAN);

	XMatrix3x3 ret;

	ret(0,0) = ch * cb + sh * sp * sb;
	ret(0,1) = -ch * sb + sh * sp * cb;
	ret(0,2) = sh * cp;

	ret(1,0) = sb * cp;
	ret(1,1) = cb * cp;
	ret(1,2) = -sp;

	ret(2,0) = -sh * cb + ch * sp * sb;
	ret(2,1) = sb * sh + ch * sp * cb;
	ret(2,2) = ch * cp;
	return ret;
}

inline XVector3 getEulerian(const XMatrix3x3& m)
{
	XVector3 ret;
	float sp = -(m(1,2));
	if(fabs(sp) > 0.9999f)
	{
		ret.x = PI_HALF * sp;
		ret.y = atan2(-(m(2,0)),m(0,0));
		ret.z = 0.0f;
	}else
	{
		ret.x = asin(sp);
		ret.y = atan2(m(0,2),m(2,2));
		ret.z = atan2(m(1,0),m(1,1));
	}
	return ret;
}

inline XMatrix3x3 toMatrix3x3(const XVector4 &v)
{
	float n = (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w);
	float s = (n > 0.0f) ? (2.0f / n) : 0.0f;
	return XMatrix3x3(1.0f - (v.y * v.y * s + v.z * v.z *s),	v.x * v.y * s - v.w * v.z * s,			v.x * v.z * s + v.w * v.y * s,
						v.x * v.y * s + v.w * v.z * s,			1.0f - (v.x * v.x * s + v.z * v.z * s),	v.y * v.z * s - v.w * v.x * s,
						v.x * v.z * s - v.w * v.y * s,			v.y * v.z * s + v.w * v.x * s,			1.0f - (v.x * v.x * s + v.y * v.y * s));
}
extern XVector4 toVector4(const XMatrix3x3 &m);
}
}
#endif
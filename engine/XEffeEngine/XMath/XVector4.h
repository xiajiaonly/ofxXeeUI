#ifndef _JIA_XVECTOR4_
#define _JIA_XVECTOR4_

#include "XVector3.h"
namespace XE{
class XVector4
{
public:
	float x;
	float y;
	float z;
	float w;

	static const XVector4 zero;
	void reset();
    void add(float a,float b,float c,float d);
    void set(float a,float b,float c,float d);
	XVector4 operator - (const XVector4& temp) const;
	XVector4 operator + (const XVector4& temp) const;
	XVector4 operator * (const XVector4& v) const;
	XVector4 operator + (const float& temp) const;
	XVector4 operator - (const float& temp) const;
	XVector4 operator * (const float& temp) const;
	XVector4 operator / (const float& temp) const;
	void operator += (const float& temp);
	void operator -= (const float& temp);
	void operator *= (const float& temp);
	void operator /= (const float& temp);
	XVector4 conjugate() const;
	XVector4 inverse() const;
    XVector4()
		:x(0.0f),y(0.0f),z(0.0f),w(0.0f)
	{}
	XVector4(float a,float b,float c,float d)
		:x(a),y(b),z(c),w(d)
	{}
	XVector4& operator = (const float* temp);
	XVector4(float *temp)
	{
		if(temp == NULL)
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}else
		{
			x = temp[0];
			y = temp[1];
			z = temp[2];
			w = temp[3];
		}
	}
	float getLength() const;
	float getLengthSqure() const;
	float dot(const XVector4 &v) const {return x*v.x + y*v.y + z*v.z + w * v.w;}
	void getRotate(float angle,const XVector3 &v);
	void getRotateX(float ax);
	void getRotateY(float ay);
	void getRotateZ(float az);
	void getFromPlane(const XVector3 &normal,const XVector3 &point);
	void getFromPlane(const XVector3 &p0,const XVector3 &p1,const XVector3 &p2);
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}
};
typedef XVector4 XQuaternions;
#if WITH_INLINE_FILE
#include "XVector4.inl"
#endif
namespace XMath{

inline XVector4 getPlane(const XVector3 p0,const XVector3 p1,const XVector3 p2)
{
	float d = 1.0f / (-p0.x*p1.y*p2.z+p0.x*p2.y*p1.z+p1.x*p0.y*p2.z-p2.x*p0.y*p1.z-p1.x*p2.y*p0.z+p2.x*p1.y*p0.z);

	return XVector4((p0.y*p1.z-p0.y*p2.z-p1.y*p0.z+p1.y*p2.z+p2.y*p0.z-p2.y*p1.z) * d,
		(-p0.x*p1.z+p0.x*p2.z+p1.x*p0.z-p1.x*p2.z-p2.x*p0.z+p2.x*p1.z) * d,
		(p0.x*p1.y-p0.x*p2.y-p1.x*p0.y+p1.x*p2.y+p2.x*p0.y-p2.x*p1.y) * d,
		1.0f);
}
inline XVector4 normalize(const XVector4& v)
{
	float d = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if(d == 0.0f) d = 0.0000001f;
	return XVector4(v.x/d,v.y/d,v.z/d,v.w/d);
}

extern XVector3 getPoint(const XVector4& v0,const XVector4& v1,const XVector4& v2);

inline XVector4 getSub(const XVector4& v0,const XVector4& v1)
{
	return v0.inverse() * v1;
}

extern XVector4 slerp(const XVector4& v0,const XVector4& v1,float r);

inline XVector4 toVector4(const XVector3& e)
{
	float xc = cos(e.x * 0.5f);
	float xs = sin(e.x * 0.5f);
	float yc = cos(e.y * 0.5f);
	float ys = sin(e.y * 0.5f);
	float zc = cos(e.z * 0.5f);
	float zs = sin(e.z * 0.5f);

	return XVector4(xs * yc * zc + xc * ys * zs,
		xc * ys * zc - xs * yc * zs,
		xc * yc * zs - xs * ys * zc,
		xc * yc * zc + xs * ys * zs);
}
inline XVector4 getVector4(const XVector3& v,float angle)
{
	float c = cos(angle * 0.5f * DEGREE2RADIAN);
	float s = sin(angle * 0.5f * DEGREE2RADIAN);
	return XVector4(v.x * s,v.y * s,v.z * s,c);
}
inline XVector3 toVector3(const XVector4& e)
{

	XVector3 ret;

	float sp = -2.f * (e.y * e.z - e.w * e.x);
	if(fabs(sp) > 0.9999999f)
	{
		ret.z = 0.0f;
		ret.x = PI_HALF * sp;
		ret.y = atan2(-e.x * e.z + e.w * e.y,0.5f - e.y * e.y - e.z * e.z);
	}else
	{
		ret.x = atan2(-e.x * e.z + e.w * e.y,0.5f - e.x * e.x - e.z * e.z);
		ret.y = asin(sp);
		ret.z = atan2(-e.x * e.z + e.w * e.y,0.5f - e.x * e.x - e.y * e.y);
	}
	return ret;
}
}
}
#endif
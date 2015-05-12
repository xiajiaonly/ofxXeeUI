#ifndef _JIA_XVECTOR3_
#define _JIA_XVECTOR3_

#include "XBasicFun.h"
namespace XE{
class XVector3
{
public:
    float x;
    float y;
    float z;
public:
	static const XVector3 zero;
    void reset();
    void add(float a,float b,float c);
    void set(float a,float b,float c);
	XVector3(float a,float b,float c)
		:x(a),y(b),z(c)
	{}
	XVector3(const XVector3 & temp)
		:x(temp.x),y(temp.y),z(temp.z)
	{}
	XVector3()
		:x(0.0f),y(0.0f),z(0.0f)
	{}

	XVector3 operator + (const XVector3& temp) const;
    XVector3 operator - (const XVector3& temp) const;

    XVector3 operator * (const XVector3& temp) const;
    XVector3 operator / (const XVector3& temp) const;
	XVector3 operator + (const float& temp) const;
    XVector3 operator - (const float& temp) const;
    XVector3 operator * (const float& temp) const;
    XVector3 operator / (const float& temp) const;
    void operator += (const XVector3& temp);
    void operator -= (const XVector3& temp);
    void operator *= (const XVector3& temp);
    void operator /= (const XVector3& temp);
    void operator += (const float& temp);
    void operator -= (const float& temp);
    void operator *= (const float& temp);
    void operator /= (const float& temp);

	float getLength(const XVector3& P0) const;
    float getLength(float a,float b,float c) const;
	float getLength() const;
	float getLengthSqure(const XVector3& P0) const;
    float getLengthSqure(float a,float b,float c) const;
	float getLengthSqure() const;

	float dot(const XVector3& temp) const;
	void normalize();

	XVector3 &operator = (const XVector3 &temp);
	XVector3& operator = (const float* temp);
	XVector3(const float *temp)
	{
		if(temp == NULL)
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}else
		{
			x = temp[0];
			y = temp[1];
			z = temp[2];
		}
	}
	XVector3 operator - () const;

	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}
};
typedef XVector3 XPoint3;
#if WITH_INLINE_FILE
#include "XVector3.inl"
#endif
namespace XMath{
inline XVector3 normalize(const XVector3& v)
{
	float d = v.getLengthSqure();
	if(d == 0.0f) return v * (1.0f/0.0000001f);
	else return v * (1.0f/sqrt(d));

}

inline XVector3 getNormal(const XVector3 &p0,const XVector3 &p1,const XVector3 &p2)
{

	return normalize((p2 - p1) * (p0 - p1));
}

inline XVector3 getNormal(const float *p0,const float *p1,const float *p2)
{

	return normalize(XVector3(p2[0] - p1[0],p2[1] - p1[1],p2[2] - p1[2]) *
		XVector3(p0[0] - p1[0],p0[1] - p1[1],p0[2] - p1[2]));
}
}
inline XVector3 operator *(float a,const XVector3 &temp)
{
	return temp * a;
}

inline float getAngle(const XVector3 &A,const XVector3 &B,const XVector3 &C)
{
	return acos(((B - A).dot(C - B))/sqrt((B - A).getLengthSqure() * (C - B).getLengthSqure()));
}
inline XVector3 projector(const XVector3 &v1,const XVector3 &v2)
{
	return v2 * (v1.dot(v2) / v2.getLengthSqure());
}
}
#endif
#ifndef _JIA_XVECTOR2_
#define _JIA_XVECTOR2_

#include "XBasicFun.h"

namespace XE{

class XVector2
{
public:
    float x;
    float y;
public:
	static const XVector2 zero;

    void reset();
	void set(const XVector2 &temp);
    void set(float a,float b);
	void set(float v) {set(v,v);}
    void add(float a,float b);

    XVector2 operator + (const XVector2& temp) const;
    XVector2 operator - (const XVector2& temp) const;

    XVector2 operator * (const XVector2& temp) const;
    XVector2 operator / (const XVector2& temp) const;
    XVector2 operator + (const float& temp) const;
    XVector2 operator - (const float& temp) const;

   XVector2 operator * (const float& temp) const;
    XVector2 operator / (const float& temp) const;
    void operator += (const XVector2& temp);
    void operator -= (const XVector2& temp);
    void operator *= (const XVector2& temp);
    void operator /= (const XVector2& temp);
    void operator += (const float & temp);
    void operator -= (const float & temp);
    void operator *= (const float & temp);
    void operator /= (const float & temp);

    float getLength(const XVector2& P0) const;
    float getLength(float a,float b) const;
	float getLength() const;
	float getLengthSqure(const XVector2& P0) const;
	float getLengthSqure(float a,float b) const;
	float getLengthSqure() const;
    float getAngle(const XVector2& P0) const;
    float getAngle(float a,float b) const;
	float getAngle() const;

	float dot(const XVector2 &temp) const {return (x * temp.x + y * temp.y);}

	void normalize();
	XVector2 perp(){return XVector2(y,-x);}

    XVector2::XVector2(float a,float b)
		:x(a),y(b)
	{}
	XVector2::XVector2()
		:x(0.0f),y(0.0f)
	{}
	XVector2(const XVector2 &temp)
		:x(temp.x),y(temp.y)
	{}

	XVector2 &operator = (const float* temp);
	XVector2(const float *temp)
	{
		if(temp == NULL)
		{
			x = 0.0f;
			y = 0.0f;
		}else
		{
			x = temp[0];
			y = temp[1];
		}
	}

	XVector2 operator - () const;
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}
};

typedef XVector2 XPoint;

#if WITH_INLINE_FILE
#include "XVector2.inl"
#endif

inline XVector2 operator *(float a,const XVector2 &temp)
{
	return temp * a;
}

namespace XMath{
inline float getAngle(const XVector2 &A,const XVector2 &B,const XVector2 &C)
{
	return acos(((B - A).dot(C - B))/sqrt((B - A).getLengthSqure() * (C - B).getLengthSqure()));
}
inline XVector2 projector(const XVector2 &v1,const XVector2 &v2)
{
	return v2 * (v1.dot(v2) / v2.getLengthSqure());
}
inline XVector2 normalize(const XVector2 &v)
{
	float r = v.getLengthSqure();
	if(r != 0) return v * (1.0f / sqrt(r));
	return XVector2::zero;
}
}
}
#endif
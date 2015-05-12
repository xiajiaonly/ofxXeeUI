#ifndef _JIA_XMATRIX2X2_
#define _JIA_XMATRIX2X2_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "XVector2.h"
namespace XE{
class XMatrix2x2
{
public:
	float data[4];
	static const XMatrix2x2 identity;
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	void loadIdentity();
	XMatrix2x2(float d0,float d1,float d2,float d3)
	{
		data[0] = d0;
		data[1] = d1;
		data[2] = d2;
		data[3] = d3;
	}
	XMatrix2x2() {loadIdentity();}

	float& operator () (int x,int y);
	float operator () (int x,int y) const;
	XVector2 operator *(const XVector2 &v);

	float getValue();

	XMatrix2x2 operator*(const XMatrix2x2 & rhs) const;
	XMatrix2x2 inverse();
	XMatrix2x2 anti();

};
#if WITH_INLINE_FILE
#include "XMatrix2x2.inl"
#endif
inline XVector2 operator *(const XVector2 &v,const XMatrix2x2 & m)
{
	return XVector2(v.x * m.data[0] + v.y * m.data[2],v.x * m.data[1] + v.y * m.data[3]);
}
namespace XMath{

inline XMatrix2x2 getMatrix2D(float size,const XVector2 &v)
{
	float t = size - 1.0f;
	return XMatrix2x2(1.0f + t * v.x * v.x,t * v.x * v.y,
						t * v.x * v.y,1.0f + t * v.y * v.y);
}

inline XMatrix2x2 getMatrix2D(float angle)
{
	return XMatrix2x2(cos(angle),sin(angle),-sin(angle),cos(angle));
}
inline XMatrix2x2 getMatrix2D(const XVector2 &s)
{
	return XMatrix2x2(s.x,0,0,s.y);
}

}
}
#endif
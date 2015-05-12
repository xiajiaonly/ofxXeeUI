#ifndef _JIA_XRANDOMFUN_
#define _JIA_XRANDOMFUN_

#include "stdlib.h"
#include "math.h"
#include "XMath/XMath.h"
namespace XE{
namespace XRand
{
	inline int random(int x)
	{
		if(x == 0) return 0;
		if(x < 0) x = -x;
		if(x <= RAND_MAX) return rand() % x;
		else return ((rand() << 12) + (rand() % 0x0fff)) % x;
	}
	inline float randomf(float tempMax) {return tempMax * rand() / (RAND_MAX + 1.0f);}
	inline float randomf(float x, float y)
	{
		if(x == y) return x;
		float high = XEE_Max(x,y);
		float low = XEE_Min(x,y);
		return (float)(low + ((high-low) * rand() / (RAND_MAX + 1.0)));
	}
	inline float gaussRand()
	{
		if((rand() % 100) < 50) return sin(randomf(PI_HALF)) * 0.5f;
		else return 0.5f + (1.0f - sin(randomf(PI_HALF))) * 0.5f;
	}

	extern void randomMomery(char *p,int size);
	template<class type> void randomArray(type *p,int size)
	{
		if(p == NULL ||
			size <= 1) return;
		int order;
		for(int i = 0;i < size; ++ i)
		{
			order = random(size);
			if(order >= 0 && order < size && order != i)
				XMath::swapTwoSum<type>(p[i],p[order]);
		}
	}
}
}
#endif
#ifndef _JIA_XMD5_
#define _JIA_XMD5_

#include "XOSDefine.h"
namespace XE{
class XMD5
{
public:
	typedef unsigned int size_type;
	typedef unsigned char uint1;
	typedef unsigned int uint4;

	XMD5();
	XMD5(const unsigned char *data,int len);
	void update(const unsigned char *buf, size_type length);
	XMD5& finalize();
	uint1 digest[16];

private:
	void init();
	enum {blocksize = 64};

	void transform(const uint1 block[blocksize]);
	static void decode(uint4 output[], const uint1 input[], size_type len);
	static void encode(uint1 output[], const uint4 input[], size_type len);

	XBool finalized;
	uint1 buffer[blocksize];
	uint4 count[2];
	uint4 state[4];

	static inline uint4 F(uint4 x, uint4 y, uint4 z);
	static inline uint4 G(uint4 x, uint4 y, uint4 z);
	static inline uint4 H(uint4 x, uint4 y, uint4 z);
	static inline uint4 I(uint4 x, uint4 y, uint4 z);
	static inline uint4 rotate_left(uint4 x, int n);
	static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

namespace XMath
{
	extern unsigned char * md5(const unsigned char *data,int len);
}
}
#endif
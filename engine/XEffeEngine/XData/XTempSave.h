#ifndef _JIA_XTEMPSAVE_
#define _JIA_XTEMPSAVE_

#include "..\XCommonDefine.h"
#include <deque>
namespace XE{

class XTempSave
{
private:
	bool m_isInited;
	int m_coreSize;
	int m_coreSum;
	unsigned char **m_cores;
	std::deque<unsigned char *> m_freeBuff;
	std::deque<unsigned char *> m_usedBuff;
	int m_curIndex;
public:
	XTempSave()
		:m_isInited(false)
		,m_cores(NULL)
		,m_coreSum(0)
	{}
	~XTempSave(){release();}
	bool init(int size,int sum);
	bool pushACore(const unsigned char *p);
	unsigned char *getPrevCore() const;
	void moveToPrev(){if(m_curIndex > 0) --m_curIndex;}
	unsigned char *getNextCore() const;
	void moveToNext(){if(m_curIndex >= 0 && m_curIndex + 1 < m_usedBuff.size()) ++ m_curIndex;}
	unsigned char *getCurCore() const;
	void release();
	void forTest();
};
#if WITH_INLINE_FILE
#include "XTempSave.inl"
#endif
}
#endif
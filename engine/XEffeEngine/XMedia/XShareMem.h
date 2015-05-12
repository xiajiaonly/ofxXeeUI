#ifndef _JIA_XSHAREMEM_
#define _JIA_XSHAREMEM_

#include "XOSDefine.h"

#ifdef XEE_OS_LINUX
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>
#endif
namespace XE{
class XShareMem
{
private:
	bool m_isInited;
	unsigned char *m_pAddress;
#ifdef XEE_OS_WINDOWS
	HANDLE m_hMapFile;
#endif
#ifdef XEE_OS_LINUX
	sem_t *m_prsem;
	int m_shmid;
#endif
	int m_size;
public:
	bool init(const char *name,int size);
	unsigned char *getBuff() {return m_pAddress;}
	int getSize() const {return m_size;}

	void release();
	XShareMem()
		:m_isInited(false)
		,m_pAddress(NULL)
#ifdef XEE_OS_LINUX
		,m_prsem(NULL)
#endif
	{}
	~XShareMem(){release();}
};
}
#endif
#ifndef _JIA_XDATABASIC_
#define _JIA_XDATABASIC_

#include "stdio.h"
#include "XBasicClass.h"
namespace XE{

#define DATABASIC_DEFAULT_FILE_NAME_A "databasicA.dat"
#define DATABASIC_DEFAULT_FILE_NAME_B "databasicB.dat"

enum XAnalyzingFileMode
{
    ANALYZING_BUFFERING,
    ANALYZING_IMMEDIATELY
};
class XDataBasic
{
private:
	static const int m_databasicKeyLength = 128;
    int m_ID;
    int m_versionsOrder;
    int m_dataLength;
    unsigned char *m_pData;
    unsigned char m_checkData;
    char m_curBackOrder;
    XBool m_isInited;
	XBool m_isSaveAsynchronous;
	XBool m_needSave;
    int m_secretKeyLength;
    unsigned char *m_secretKey;

    XBool EncryptData();
    XBool DeCryptData();
    unsigned char getCheckData();
    XBool checkDataIsRigth();

    XBool mergeDataBack(const char *fileName);
    XBool mergeDataBack(const char *fileNameA,const char *fileNameB);
    XBool analyzingDataBack(const char *fileName);
    XBool analyzingData(const char *fileName);

	char *m_fileName;

	XAnalyzingFileMode m_saveMode;

	XThreadState m_isEnd;

	XDataBasic(const XDataBasic &)
	{}
public:
    XDataBasic();
	~XDataBasic(){release();}
	void release();

    XBool init(int ID,XBool isSaveAsynchronous = XFalse,XAnalyzingFileMode saveMode = ANALYZING_BUFFERING);

    XBool mergeData(const unsigned char *pData,int dataLength);
    int analyzingData(unsigned char *pData,int dataLength);

    XBool mergeData(const char *fileName = NULL);
    XBool analyzingDataManager(const char *fileName = NULL);

#ifdef XEE_OS_WINDOWS
	static DWORD WINAPI saveDataThread(void * pParam);
#endif
#ifdef XEE_OS_LINUX
	static void *saveDataThread(void * pParam);
#endif
	pthread_t m_saveDataThreadP;

	void endDataBasic();
};
inline void XDataBasic::endDataBasic()
{
    if(!m_isInited) return;
	if(m_isSaveAsynchronous) m_isEnd = STATE_SET_TO_END;
}
inline XBool XDataBasic::checkDataIsRigth()
{
    if(!m_isInited ||
		m_dataLength <= 0 ||
		m_pData == NULL) return XFalse;
    return getCheckData() == m_checkData;
}
inline void XDataBasic::release()
{
	if(!m_isInited) return;
	if(m_isSaveAsynchronous) waitThreadEnd(m_isEnd);
	XMem::XDELETE_ARRAY(m_secretKey);
	m_isInited = XFalse;
}
inline int XDataBasic::analyzingData(unsigned char *pData,int dataLength)
{
    if(!m_isInited ||
		dataLength <= 0) return -1;
    if(m_pData == NULL || m_dataLength <= 0) return 0;
    if(dataLength <= m_dataLength) memcpy(pData,m_pData,dataLength);
    else  memcpy(pData,m_pData,m_dataLength);
    return m_dataLength;
}
}
#endif
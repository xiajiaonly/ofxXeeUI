#ifndef _JIA_XRESOURCEPACK_
#define _JIA_XRESOURCEPACK_

#include "XOSDefine.h"
#include "XBasicFun.h"

#include "stdio.h"
#include <memory>
#include "string.h"
namespace XE{
class XTextureInfo;

#pragma pack(push)
#pragma pack(1)
struct XResourceFileStruct
{
	char fileName[MAX_FILE_NAME_LENGTH];
	int fileLength;
	int filePosition;
};
#pragma pack(pop)

class XResourcePack
{
private:
	static const int m_maxFileSum = 3000;
	static const int m_lockCodeLength = 32;
	static const int m_allLockCodeLength = 128;

	static const int m_memoryChangeTimes = 36;
	static const int m_md5CodeSize = 16;

protected:
	XResourcePack();
	XResourcePack(const XResourcePack&);
	XResourcePack &operator= (const XResourcePack&);
	virtual ~XResourcePack();
public:
	static XResourcePack& GetInstance();

private:
	unsigned char *m_fileData;
	int m_fileDataLength;
	int m_fileDataPoint;

public:
	XResourceFileStruct *m_fileInfo;
	int m_fileSum;
	int m_normalFileSum;
	XBool m_haveReadedFileList;
	XBool m_haveReadedNormalFileList;
	long m_headLength;
	unsigned char tempCode[m_lockCodeLength ];
	unsigned char m_lockKey[m_allLockCodeLength];
	unsigned char m_hardLockKey[m_lockCodeLength ];

	char m_outFileName[MAX_FILE_NAME_LENGTH];
	void setOutFileName(const char *temp = NULL);
private:
	XBool m_isGetOptimizeInfo;
	XBool getOptimizeInfo();
	XBool releaseOptimizeInfo();
	XTextureInfo *m_texInfo;
	int *m_targetOrder;
	char *m_targetName;
	int m_texInfoSum;
	int m_targetTextureSum;
public:
	int makeFileList();
	int makeResourcePack(int packMode = 0);

	int unpackAllResource();
	int unpackResource(const char *fileName);
	int unpackResource(const char *fileName,unsigned char *p);
	int getStringLength(const char *p) const;
	void setHardLockKey(const unsigned char *p);

	int checkFileCode(const char *p) const;

	int readFileListFromResouce();
	int readNormalFileListFromResouce();
	int getFileLength(const char *fileName);
	unsigned char *getFileData(const char *filename);

	int writeCheckData();
	XBool checkCheckData();

	void lockOrUnlockProc(unsigned char *p,int startPoint,int length) const;
	void getlockKey();

	int isOptimized(const char *p) const;
	void release();
};

inline int XResourcePack::getStringLength(const char *p) const
{
	if(strlen(p) >= MAX_FILE_NAME_LENGTH)
	{
		return 0;
	}else
	{
		return (int)(strlen(p));
	}

}
inline void XResourcePack::setHardLockKey(const unsigned char *p)
{
	memcpy(m_hardLockKey,p,32);
}
inline XResourcePack::~XResourcePack()
{
	release();
}
inline XResourcePack& XResourcePack::GetInstance()
{
	static XResourcePack m_instance;
	return m_instance;
}
inline void XResourcePack::release()
{
	XMem::XDELETE_ARRAY(m_fileInfo);
	XMem::XDELETE_ARRAY(m_fileData);
	m_haveReadedFileList = XFalse;
}
}
#endif
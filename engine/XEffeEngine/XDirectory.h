#ifndef _JIA_XDIRECTORY_
#define _JIA_XDIRECTORY_

#include <vector>
#include "XOSDefine.h"
namespace XE{
class XDir;
class XFileInfo
{
public:
	XBool isEnable;
	char * allPath;
	char * filename;
	XBool isDirectory;
	XFileInfo()
		:isEnable(XFalse)
		,directory(NULL)
		,allPath(NULL)
		,filename(NULL)
	{}
	XDir * directory;
	void release();
};
class XDir
{
public:
	XBool isEnable;
	char * directoryName;
	std::vector<XFileInfo *> files;
	XDir()
		:isEnable(XFalse)
		,level(0)
		,directoryName(NULL)
	{}
	void release();
	int level;
};
class XDirectory
{
private:
	XBool m_isInited;
public:
	XDir m_curDirectory;
	XBool init(const char *directoryName);
	XBool initEx(const char *directoryName);

	XDirectory()
		:m_isInited(XFalse)
	{}
	~XDirectory(){release();}
	void release()
	{
		if(!m_isInited) return;
		m_curDirectory.release();
		m_isInited = XFalse;
	}
};
namespace XFile
{
	extern XBool infoConvert(WIN32_FIND_DATA &fileInfo,XFileInfo * file);
	extern XBool enumerationFiles(const char *path,XDir * dir);
	extern XBool enumerationFilesEx(const char *path,XDir * dir);
}
}
#endif
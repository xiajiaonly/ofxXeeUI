#ifndef _JIA_XFILE_
#define _JIA_XFILE_

#include <string>
#include "XStringFun.h"
#include "XBasicWindow.h"

#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")
namespace XE{
class XCColor;
namespace XFile
{

	inline int getFileLen(FILE * fp)
	{
		if (fp == NULL) return 0;
		int tempOffset = ftell(fp);
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		fseek(fp, tempOffset, SEEK_SET);
		return len;
	}

	extern std::string addIndexToFilename(const char *filename,int index);
	extern XBool fileNameCompare(const char *p1, const char *p2);
	extern int getPathDeep(const char *p);
	extern int getPathDeepByChar(const char *p);

	inline std::string getWorkPath();

	inline std::string getFileExtension(const char * filename);

	inline XBool setWorkPath(const std::string &path);

	inline std::string getCurrentExeFileFullPath();

	inline std::string getFullPath(const std::string &filename);

	extern void calPathDepth(const char *p, int &depth, int &lastPos);

	extern std::string getBackPath(const char *p, int backSum);

	inline XBool isAbsolutePath(const char * path);

	inline std::string mergeFilename(const std::string &base, const std::string &offset);

	extern int getCharsNumInPath(const char * path);
	extern bool isPathValid(const char * path);

	extern BOOL popFileOpenDlg(HWND hwnd, char* pstrFileName, char* pstrTitleName, char* title, bool isOpen, const std::string&defExt = "xml");

	inline std::string getChooseFilename(char * defName, char * title, bool isOpen, const std::string&defExt = "xml");

	extern XCColor getChooseColor(const XCColor &color);

	inline std::string getWindowsSysFontPath();

	inline std::string getFilenameFormPath(const char *path);

	inline std::string getFilePath(const char *filename);

	inline XBool isExistFile(const char *path)
	{
		if(path == NULL) return XFalse;
	#ifdef UNICODE
		return PathFileExistsA(path);
	#else
		return PathFileExists(path);
	#endif
	}

	extern XBool isExistFileEx(const char *path);

	inline XBool isFolder(const char * path)
	{
		if(path == NULL) return XFalse;
	#ifdef UNICODE
		return (GetFileAttributesA(path) & FILE_ATTRIBUTE_DIRECTORY);
	#else
		return (GetFileAttributes(path) & FILE_ATTRIBUTE_DIRECTORY);
	#endif
	}

	extern XBool isFolderEx(const char * path);

	inline XBool deleteFile(const char *filename)
	{
		if(filename == NULL) return XFalse;
	#ifdef UNICODE
		return DeleteFileA(filename);
	#else
		return DeleteFileA(filename);
	#endif
	}

}
}
#endif
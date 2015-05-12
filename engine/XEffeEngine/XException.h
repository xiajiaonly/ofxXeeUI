#ifndef _JIA_XEXCEPTION_
#define _JIA_XEXCEPTION_

#include "windows.h"
namespace XE{
namespace XException
{
	extern LONG WINAPI unhandledExceptionFilter(struct _EXCEPTION_POINTERS *pExceptionPointers);
	extern BOOL WINAPI consoleHandler(DWORD consoleEvent);
	extern bool initException();

	extern void dumpMemory(const char *filename, void *p);
};
}
#endif
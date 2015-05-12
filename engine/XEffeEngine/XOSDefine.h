#ifndef _JIA_OSDEFINE_
#define _JIA_OSDEFINE_

#define XEE_OS_WINDOWS

#define WITH_ALL_WARNING (0)

#if WITH_ALL_WARNING == 0
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 4100)
#pragma warning(disable: 4245)
#pragma warning(disable: 4127)
#pragma warning(disable: 4018)
#pragma warning(disable: 4996)
#pragma warning(disable: 4800)
#endif

#ifdef XEE_OS_WINDOWS
#include "windows.h"
#include <assert.h>
#endif
namespace XE{
#if 1

typedef int XBool;
#define XFalse (0)
#define XTrue (1)
#else
typedef bool XBool;
#define XFalse (false)
#define XTrue (true)
#endif
}

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
#endif

#ifndef _JIA_XRESOURCEOPTIMIZE_
#define _JIA_XRESOURCEOPTIMIZE_

#include "XOSDefine.h"
namespace XE{
#define PNG_FILE_LIST_NAME "pngFileList.txt"
#define PNG_INFORMATION_FILE_NAME "textureInformation.txt"

#define MAX_PIXELS_OFFSET (0)

	extern XBool ResourceOptimize();
	extern void releaseTempFile();
	extern void clearTempFile();
	extern int pixelCompare(const unsigned int *p0,const unsigned int *p1,int maxPixelsOffset);

}
#endif
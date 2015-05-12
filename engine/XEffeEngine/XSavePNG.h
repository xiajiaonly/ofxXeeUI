#ifndef __IMG_SAVETOPNG_H__
#define __IMG_SAVETOPNG_H__

#include "XOSDefine.h"
struct SDL_Surface;
namespace XE{
#define Z_NO_COMPRESSION (0)
#define Z_BEST_COMPRESSION (9)
#define Z_DEFAULT_COMPRESSION (-1)

enum XColorMode;
namespace XPng
{

	extern int savePNG(const char *fileName,
				SDL_Surface *surf,
				int compression = Z_BEST_COMPRESSION);

	extern int savePNG(const std::string &filename,
				const unsigned char * data,int w,int h,XColorMode color,
				int compression = Z_BEST_COMPRESSION);

	extern XBool savePngRGB2RGB(const char *fileName,
				const unsigned char * data,
				int w,int h,
				int compression = Z_BEST_COMPRESSION);
	extern XBool savePngRGB2RGBA(const char *fileName,
				const unsigned char * data,
				int w,int h,
				int compression = Z_BEST_COMPRESSION);
	extern XBool savePngRGBA2RGBA(const char *fileName,
				const unsigned char * data,
				int w,int h,
				int compression = Z_BEST_COMPRESSION);
	extern XBool savePngRGBA2RGB(const char *fileName,
				const unsigned char * data,
				int w,int h,
				int compression = Z_BEST_COMPRESSION);
}
}
#endif

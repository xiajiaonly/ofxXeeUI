#ifndef _JIA_XBMP_
#define _JIA_XBMP_

#include "XOSDefine.h"
namespace XE{
#pragma pack(push)
#pragma pack(1)
struct XBMPFileHeader
{
    unsigned short bfType;
    int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    int bfOffBits;

};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
struct XBMPInfoHeader
{
    int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    int biCompression;

    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
};
#pragma pack(pop)

class XBMP
{
private:
	static const int m_bmpColorBytes = 3;
    XBool m_isInited;
public:
    int m_width;
    int m_height;
    unsigned char *m_data;
public:
    XBool init(const char *filename,int needAlpha = 0);
    XBool init(int width,int height);
    XBool writeToFile(const char *filename);
    XBool release();
    XBMP()
    :m_isInited(XFalse)
    ,m_width(0)
    ,m_height(0)
    ,m_data(NULL)
    {}
};
}
#endif
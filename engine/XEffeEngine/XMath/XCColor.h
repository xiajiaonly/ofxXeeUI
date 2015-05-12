#ifndef _JIA_XCCOLOR_
#define _JIA_XCCOLOR_

#include "XBasicFun.h"
namespace XE{
class XFColor;

class XCColor
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
	unsigned char w;
	XCColor(const XFColor &temp);
	XCColor& operator = (const XFColor& temp);
	XCColor(unsigned int color)
	{
		r = color >> 24;
		g = (color >> 16) % 256;
		b = (color >> 8) % 256;
		a = color % 256;
	}
	void calculateW(){w = XEE_Max(r,XEE_Max(g,b));}
    XCColor()
        :r(0),g(0),b(0),a(0)
    {}
	XCColor(unsigned char R,unsigned char G,unsigned char B,unsigned char A = 255)
		:r(R),g(G),b(B),a(A)
	{}
	bool operator==(const XCColor& c) const{return (r == c.r && g == c.g && b == c.b && a == c.a);}

    void setColor(unsigned char cr,unsigned char cg,unsigned char cb,unsigned char ca);
	void randColor();
	void getHsb(float& hue, float& saturation, float& brightness) const;
	float getHue() const;
	float limit() const {return 255.0f;}
	XCColor anti(){return XCColor(255 - r,255 - g,255 - b,a);}
	static const XCColor white, gray, black, red, green, blue, cyan, magenta,
        yellow,aliceBlue,antiqueWhite,aqua,aquamarine,azure,beige,bisque,blanchedAlmond,
        blueViolet,brown,burlyWood,cadetBlue,chartreuse,chocolate,coral,cornflowerBlue,cornsilk,
        crimson,darkBlue,darkCyan,darkGoldenRod,darkGray,darkGrey,darkGreen,darkKhaki,
        darkMagenta,darkOliveGreen,darkorange,darkOrchid,darkRed,darkSalmon,darkSeaGreen,
        darkSlateBlue,darkSlateGray,darkSlateGrey,darkTurquoise,darkViolet,deepPink,
        deepSkyBlue,dimGray,dimGrey,dodgerBlue,fireBrick,floralWhite,forestGreen,fuchsia,
        gainsboro,ghostWhite,gold,goldenRod,grey,greenYellow,honeyDew,hotPink,indianRed,indigo,
        ivory,khaki,lavender,lavenderBlush,lawnGreen,lemonChiffon,lightBlue,lightCoral,
        lightCyan,lightGoldenRodYellow,lightGray,lightGrey,lightGreen,lightPink,lightSalmon,
        lightSeaGreen,lightSkyBlue,lightSlateGray,lightSlateGrey,lightSteelBlue,lightYellow,
        lime,limeGreen,linen,maroon,mediumAquaMarine,mediumBlue,mediumOrchid,mediumPurple,
        mediumSeaGreen,mediumSlateBlue,mediumSpringGreen,mediumTurquoise,mediumVioletRed,
        midnightBlue,mintCream,mistyRose,moccasin,navajoWhite,navy,oldLace,olive,oliveDrab,
        orange,orangeRed,orchid,paleGoldenRod,paleGreen,paleTurquoise,paleVioletRed,papayaWhip,
        peachPuff,peru,pink,plum,powderBlue,purple,rosyBrown,royalBlue,saddleBrown,salmon,
        sandyBrown,seaGreen,seaShell,sienna,silver,skyBlue,slateBlue,slateGray,slateGrey,snow,
        springGreen,steelBlue,tan,teal,thistle,tomato,turquoise,violet,wheat,whiteSmoke,
        yellowGreen;
	operator unsigned char* () const {return (unsigned char*) this;}
	operator const unsigned char* () const {return (unsigned char*) this;}
};
#if WITH_INLINE_FILE
#include "XCColor.inl"
#endif
}
#endif
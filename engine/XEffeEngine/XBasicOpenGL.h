#ifndef _JIA_XBASICOPENGL_
#define _JIA_XBASICOPENGL_

#include "glew.h"
#include "gl.h"

#include "XBasicFun.h"
#include "XMath/XVector2.h"
#include "XMath/XRect.h"
#include "XMath/XFColor.h"
#include "XBasicFun.h"
#include "XBasicClass.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
namespace XE{
namespace XGL
{

	enum XBlendType
	{
		BLEND_TWO_DATA,
		BLEND_FOUR_DATA,
	};
	extern int srcBlendMode[9];
	extern int dstBlendMode[8];

	extern void printShaderInfoLog(GLuint obj);
	extern int printOglError(const char *file, int line);
	#define printOpenGLError() printOglError(__FILE__, __LINE__)
	extern void printProgramInfoLog(GLuint obj);

	extern char *textFileRead(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	extern int textFileWrite(const char *filename, const char *s);
	extern XBool setShader(const char* vertFile,const char* fragFile,int &pHandle,
							XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	extern XBool setShader(const char* vertFile,const char* fragFile,const char* geomFile,XShaderHandle &pHandle,
							XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	extern XBool TextureLoadEx(GLuint &texture,const char *filename,int * w = NULL,int * h = NULL,
							 XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	extern XBool TextureLoadQuarter(GLuint &texture,const char *filename);

	extern GLuint emptyTexture(int x, int y, XColorMode mode = COLOR_RGBA);
	extern void showGLInfoToLog();

	inline void EnableTexture2D()
	{

		glEnable(GL_TEXTURE_2D);
	}
	inline void DisableTexture2D()
	{

		glDisable(GL_TEXTURE_2D);
	}

	inline void EnableBlend()
	{

		glEnable(GL_BLEND);
	}
	inline void DisableBlend()
	{

		glDisable(GL_BLEND);
	}

	inline void SetBlendFunc(int src,int dst)
	{

		glBlendFunc(src,dst);
	}
	inline void BindTexture2D(const unsigned int &t,const int &index = 0)
	{

		glBindTexture(GL_TEXTURE_2D,t);
	}

	inline void initOpenGLState()
	{

	}
}
namespace XEE
{
	extern void initWindowMatrix();
	extern XBool initOpenGL3D();
	extern XBool initOpenGL2D();
}
class XTexture;
namespace XRender
{

	enum XLineStyle
	{
		LS_SOLID = 0xFFFF,
		LS_DASHES = 0x00FF,
		LS_SHORT_DASHES = 0x0F0F,
		LS_DOTS = 0x5555,
		LS_SPARSE_DOTS = 0x2222,
		LS_DASH_DOT = 0xFE10,
		LS_DASH_DOT_DOT = 0x24FF,
	};

	extern void drawLine(float ax,float ay,float bx,float by,float width = 1.0f,float r = 1.0f,float g = 1.0f,float b = 1.0f);

	extern void drawLine(float ax, float ay, float bx, float by, float width, const XFColor &c, XLineStyle type = LS_SOLID);
	inline void drawLine(float ax, float ay, float bx, float by, float width, float r, float g, float b, float a, XLineStyle type = LS_SOLID)
	{
		drawLine(ax,ay,bx,by,width,XFColor(r,g,b,a),type);
	}
	inline void drawLine(const XVector2& p0, const XVector2& p1, float width = 1.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f, XLineStyle type = LS_SOLID)
	{
		drawLine(p0.x,p0.y,p1.x,p1.y,width,r,g,b,a,type);
	}
	inline void drawLine(const XVector2& p,float angle,float length)
	{
		drawLine(p,XVector2(p.x + length * cos(angle * DEGREE2RADIAN),p.y + length * sin(angle * DEGREE2RADIAN)));
	}

	extern void drawLinesVbo(unsigned int v,int pointSum,float w,float r,float g,float b);
	extern void drawLinesVbo(unsigned int v,int pointSum,float w,float r,float g,float b,float a);
	inline void drawRectS(const XRect &rect)
	{

		glBegin(GL_LINE_LOOP);
		glVertex2f(rect.left,rect.top);
		glVertex2f(rect.right,rect.top);
		glVertex2f(rect.right,rect.bottom);
		glVertex2f(rect.left,rect.bottom);

		glEnd();
	}

	extern void drawRect(const XVector2& pos,const XVector2& size,float width, const XFColor &c);
	extern void drawRect(const XRect& rect, float width, const XFColor &c, XLineStyle type = LS_SOLID);
	inline void drawRect(const XRect& rect, float width = 1.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f, XLineStyle type = LS_SOLID)
	{
		drawRect(rect,width,XFColor(r,g,b,a),type);
	}

	extern void drawRectAntiColor(const XRect& rect, float width = 1.0f, XLineStyle type = LS_SOLID);

	inline void drawBoxS(float x,float y,float sizeX,float sizeY)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(x - sizeX,y + sizeY);
		glVertex2f(x - sizeX,y - sizeY);
		glVertex2f(x + sizeX,y - sizeY);
		glVertex2f(x + sizeX,y + sizeY);
		glVertex2f(x - sizeX,y + sizeY);
		glEnd();
	}
	inline void drawBoxS(const XVector2 &p1,const XVector2 &p2,const XVector2 &p3,const XVector2 &p4)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2fv(p1);
		glVertex2fv(p2);
		glVertex2fv(p4);
		glVertex2fv(p3);
		glVertex2fv(p1);
		glEnd();
	}
	inline void drawBox(const XVector2 &pos,const XVector2 &size)
	{
		glBegin(GL_LINE_STRIP);
			glVertex2fv(pos);
			glVertex2f(pos.x + size.x,pos.y);
			glVertex2f(pos.x + size.x,pos.y + size.y);
			glVertex2f(pos.x,pos.y + size.y);
			glVertex2fv(pos);
		glEnd();
	}
	inline void drawFillBoxS(float x,float y,float w,float h)
	{
		glBegin(GL_QUADS);
		glVertex2f(x,y);
		glVertex2f(x + w,y);
		glVertex2f(x + w,y + h);
		glVertex2f(x,y + h);
		glEnd();
	}
	extern void drawBox(float x,float y,float sizeX,float sizeY,int w,const XFColor &c);
	inline void drawBox(float x,float y,float sizeX,float sizeY,int w,float r,float g,float b,float a)
	{
		drawBox(x,y,sizeX,sizeY,w,XFColor(r,g,b,a));
	}
	inline void drawBox(float x,float y,float sizeX,float sizeY,int w,float r = 1.0f,float g = 1.0f,float b = 1.0f)
	{
		XGL::DisableTexture2D();
		glColor3f(r,g,b);
		glLineWidth(w);
		drawBoxS(x,y,sizeX,sizeY);
	}
	inline void drawBox(float x,float y,float sizeX,float sizeY)
	{
		XGL::DisableTexture2D();
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		glLineWidth(1);
		drawBoxS(x,y,sizeX,sizeY);
	}
	extern void drawBox(float x,float y,float sizeX,float sizeY,float angle);
	extern void drawBox(const XVector2& p0,const XVector2& p1,const XVector2& p2,const XVector2& p3,float width = 1.0f,float r = 1.0f,float g = 1.0f,float b = 1.0f);
	extern void drawBox(const XVector2& p0,const XVector2& p1,const XVector2& p2,const XVector2& p3,float width,const XFColor & c);
	inline void drawBox(const XVector2& p0,const XVector2& p1,const XVector2& p2,const XVector2& p3,float width,float r,float g,float b,float a)
	{
		drawBox(p0,p1,p2,p3,width,XFColor(r,g,b,a));
	}

	extern void drawTriangle(const XVector2& p0,const XVector2& p1,const XVector2& p2,float width = 0.5f,float r = 1.0f,float g = 1.0f,float b = 1.0f);

	extern void drawTriangle(const XVector2& p,float size,float width,const XFColor &color);

	extern void drawPoint(float x,float y,float r,float g,float b,float a);
	inline void drawPoint(const XVector2& p,float r,float g,float b,float a)
	{
		drawPoint(p.x,p.y,r,g,b,a);
	}
	extern void drawPoint(float x,float y,float size,float r,float g,float b,float a);
	inline void drawPoint(const XVector2& p,float size,float r,float g,float b,float a)
	{
		drawPoint(p.x,p.y,size,r,g,b,a);
	}

	extern void drawPointsVbo(unsigned int v,int pointSum,float s,float r,float g,float b);
	extern void drawPointsVbo(unsigned int v,int pointSum,float s,float r,float g,float b,float a);

	extern void drawCross(const XVector2& p,float size = 10.0f,float w = 1.0f,float r = 1.0f,float g = 1.0f,float b = 1.0f);
	extern void drawCross(const XVector2& p,float size,float w,const XFColor& color);

	extern void drawMaskRight(const XVector2& p,const XVector2& size,float width,const XFColor& color);

	extern void drawMaskWrong(const XVector2& p,const XVector2& size,float width,const XFColor& color);

	extern void drawLeft(const XVector2& p,const XVector2& size,float width,const XFColor& color);
	extern void drawRight(const XVector2& p,const XVector2& size,float width,const XFColor& color);
	extern void drawUp(const XVector2& p,const XVector2& size,float width,const XFColor& color);
	extern void drawDown(const XVector2& p,const XVector2& size,float width,const XFColor& color);

	extern void drawCircle(float px, float py, float sr, int an,float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f);

	extern void drawCircleLine(float px, float py, float sr, int an,float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f);
	extern void drawCircleLine(const XVector2 &pos, float sr, int an,float w,const XFColor &color);

	extern void drawFillRing(float x,float y,float r0,float r1,float angleS,float angleE,int an,float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f);
	inline void drawFillRing(float x,float y,float r0,float r1,float angleS,float angleE,int an,const XFColor &c)
	{
		drawFillRing(x,y,r0,r1,angleS,angleE,an,c.fR,c.fG,c.fB,c.fA);
	}

	extern void drawFillRingEx(float x,float y,float r0,float r1,float angleS,float angleE,int an,float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f);

	extern void drawFillBox(const XVector2 &p0,const XFColor &c0,
							const XVector2 &p1,const XFColor &c1,
							const XVector2 &p2,const XFColor &c2,
							const XVector2 &p3,const XFColor &c3);
	extern void drawFillBox(float x,float y,float w,float h,
		const XFColor & c);
	inline void drawFillBox(float x,float y,float w,float h,
							float r,float g,float b,float a)
	{
		drawFillBox(x,y,w,h,XFColor(r,g,b,a));
	}
	extern void drawFillBox(const XVector2& pos,const XVector2& size,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,bool withLine = false);
	extern void drawFillBoxA(const XVector2& pos,const XVector2& size,
		const XFColor &c,bool withLine = false);
	inline void drawFillBoxA(const XVector2& pos,const XVector2& size,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f,bool withLine = false)
	{
		drawFillBoxA(pos,size,XFColor(r,g,b,a),withLine);
	}
	extern void drawFillBoxEx(const XVector2& pos,const XVector2& size,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,
							bool withLine = false,bool withRoundCorner = false,bool down = false);

	extern void drawFillBoxExAS(const XVector2& pos,const XVector2& size,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f,
							bool withLine = false,bool withRoundCorner = false,bool down = false);
	inline void drawFillBoxExAS(const XVector2& pos,const XVector2& size,
		const XFColor &c,bool withLine = false,bool withRoundCorner = false,bool down = false)
	{
		drawFillBoxExAS(pos,size,c.fR,c.fG,c.fB,c.fA,withLine,withRoundCorner,down);
	}

	extern void drawFillBoxExA(const XVector2& pos,const XVector2& size,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f,
							bool withLine = false,bool withRoundCorner = false,bool down = false);

	inline void drawFillBoxExA(const XVector2& pos,const XVector2& size,
							const XFColor &c,
							bool withLine = false,bool withRoundCorner = false,bool down = false)
	{
		drawFillBoxExA(pos,size,c.fR,c.fG,c.fB,c.fA,withLine,withRoundCorner,down);
	}

	inline void drawArrow(const XVector2& arm,float angle,float length)
	{
		drawLine(arm,angle,length);
		drawLine(arm,angle + 30,10);
		drawLine(arm,angle - 30,10);
	}

	inline void drawArrow(const XVector2& start,const XVector2& end)
	{
		float len = start.getLength(end);
		float angle = end.getAngle(start) * RADIAN2DEGREE;

		drawArrow(end,angle,len);
	}

	extern void drawFillBoxExEx(const XVector2& pos,const XVector2& size,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,
							unsigned char lineStyle = 0,unsigned char cornerStyle = 0,bool down = false);
	extern void drawFillBoxExExA(const XVector2& pos,const XVector2& size,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,float a = 1.0f,
							unsigned char lineStyle = 0,unsigned char cornerStyle = 0,bool down = false);
	inline void drawFillBoxExExA(const XVector2& pos,const XVector2& size,
		const XFColor &c,unsigned char lineStyle = 0,unsigned char cornerStyle = 0,bool down = false)
	{
		drawFillBoxExExA(pos,size,c.fR,c.fG,c.fB,c.fA,lineStyle,cornerStyle,down);
	}
	extern void drawFillBox(const XVector2& p0,const XVector2& p1,const XVector2& p2,const XVector2& p3,
							float r = 1.0f,float g = 1.0f,float b = 1.0f);
	extern void drawFillBoxEx(const XVector2& p0,const XVector2& p1,const XVector2& p2,const XVector2& p3,
							float r = 1.0f,float g = 1.0f,float b = 1.0f,
							bool withLine = false);
	extern void drawFillBoxBW(const XVector2& pos,const XVector2& size,const XVector2& cSize);
	extern void drawFillTriangle(const XVector2& p0,const XVector2& p1,const XVector2& p2,
							float r = 1.0f,float g = 1.0f,float b = 1.0f);
	extern void drawFillTriangleEx(const XVector2& p0,const XVector2& p1,const XVector2& p2,
							float r = 1.0f,float g = 1.0f,float b = 1.0f);

	extern void drawFillPolygon(const XVector2 *p,int sum,float r,float g,float b);
	extern void drawFillPolygon(const XVector2 *p,int sum,const XVector2 &pos,float angle,float r,float g,float b);
	extern void drawFillPolygonEx(const XVector2 *p,const float *c,int sum,float r,float g,float b,bool withLine = false);
	extern void drawFillPolygonExA(const XVector2 *p,const float *c,int sum,float r,float g,float b,float a,bool withLine = false);
	inline void drawFillPolygonExA(const XVector2 *p,const float *c,int sum,const XFColor &cl,bool withLine = false)
	{
		drawFillPolygonExA(p,c,sum,cl.fR,cl.fG,cl.fB,cl.fA,withLine);
	}

	extern void drawTexture(XTexture &tex,const XVector2 &pos,int cW,int cH,XVector2 *vArray,XVector2 *uArray,int arrayW,int arrayH);
	extern void drawTexture(unsigned int tex,const XVector2 &pos,int texW,int texH,bool blend = false);
	extern void drawTextureEx(unsigned int tex,const XVector2 &pos,const XVector2 &size,XVector2 *vArray,
							  XVector2 *uArray,int arrayW,int arrayH,bool blend = false);
}
namespace XEE
{

	extern XBool gameShot(const char *fileName,int w,int h,bool withThread = true,float x = 0.0f,float y = 0.0f);
	inline void setVSync(bool sync)
	{

		typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALPROC)( int );
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		const char *extensions = (char*)glGetString( GL_EXTENSIONS );

		if(strstr(extensions,"WGL_EXT_swap_control") == 0) return;
		else
		{
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress( "wglSwapIntervalEXT" );
			if(wglSwapIntervalEXT) wglSwapIntervalEXT(sync);
		}

	}
}

#define TEX_DEBUG (0)
#define TEX_DEBUG1 (0)
#if TEX_DEBUG
extern int XTSum;
#endif
#if TEX_DEBUG1
extern int CPSum;
#endif

class XResourceInfo;
class XPBO;
class XTexture
{
private:
	XSCounter *m_cp;
	void release();
	XBool m_isLoaded;
	XResourceInfo * m_resInfo;
public:
	GLuint m_texture;
	int m_w;
	int m_h;
	XBool getIsEnable() {return m_isLoaded;}
	XColorMode m_mode;
	void bind()
	{
		XGL::EnableTexture2D();
		XGL::BindTexture2D(m_texture);
	}
	XBool reset();
public:

	XBool load(const char *filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	XBool createTexture(int w,int h,XColorMode mode);
	XBool createWithTexture(int w,int h,XColorMode mode,unsigned int tex);
	void updateTexture(const XPBO &pbo);
	void updateTextureR2B(const XPBO &pbo);
	void updateTexture(const void *data,int w = 0,int h = 0,int x = 0,int y = 0)
	{
		if(!m_isLoaded ||
			data == NULL) return;
		updateTextureX(data,w,h,x,y);
	}
	void updateTextureR2B(const void *data,int w = 0,int h = 0,int x = 0,int y = 0)
	{
		if(!m_isLoaded ||
			data == NULL) return;
		updateTextureR2BX(data,w,h,x,y);
	}
private:
	void updateTextureX(const void *data,int w = 0,int h = 0,int x = 0,int y = 0);
	void updateTextureR2BX(const void *data,int w = 0,int h = 0,int x = 0,int y = 0);
public:
	XTexture()
		:m_texture(0)
		,m_isLoaded(XFalse)
		,m_cp(NULL)
		,m_mode(COLOR_RGBA)
		,m_resInfo(NULL)
		,m_w(0)
		,m_h(0)
	{}

	~XTexture()
	{
		if(m_cp != NULL && -- m_cp->m_counter <= 0)
		{
			release();
#if TEX_DEBUG1
			CPSum --;
			printf("%d-\n",CPSum);
#endif
			XMem::XDELETE(m_cp);
		}
	}
	XTexture(const XTexture& temp);
	XTexture& operator = (const XTexture &temp);
};
}
#endif

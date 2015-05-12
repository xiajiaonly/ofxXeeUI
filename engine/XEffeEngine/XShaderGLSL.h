#ifndef _JIA_XSHADER_GLSL_
#define _JIA_XSHADER_GLSL_

#include "XBasicFun.h"
#include "XBasicOpenGL.h"
#include <vector>
#include "XBasicWindow.h"
namespace XE{

enum XShaderDataType
{
	DATA_TYPE_INT,
	DATA_TYPE_FLOAT,
	DATA_TYPE_INT_ARRAY,
	DATA_TYPE_FLOAT_ARRAY,
	DATA_TYPE_2INT_ARRAY,
	DATA_TYPE_2FLOAT_ARRAY,
	DATA_TYPE_3INT_ARRAY,
	DATA_TYPE_3FLOAT_ARRAY,
	DATA_TYPE_3FLOAT_MATRIX,
	DATA_TYPE_4FLOAT_MATRIX,
	DATA_TYPE_2INT,
	DATA_TYPE_3INT,
	DATA_TYPE_2FLOAT,
	DATA_TYPE_3FLOAT,
};
class XShaderDataInfo
{
public:
	int m_handle;

	XShaderDataType m_type;
	void *m_p;
	int m_size;

	void updateData();
};

class XUBO
{
private:
	XBool m_isInited;
	unsigned int m_uboHandle;
public:
	XUBO()
		:m_isInited(XFalse)
		,m_uboHandle(0)
	{}
	~XUBO() {release();}
	void release();
	XBool init(int size,const void * p);
	void useUBO(unsigned int index);
};
class XShaderUBOInfo
{
public:
	unsigned int m_handle;
	XUBO *m_pUBO;

	void updateData() {m_pUBO->useUBO(m_handle);}
};
enum XShaderTexType
{
	TEX_TYPE_2D,
	TEX_TYPE_CUBE,
};
struct XSaderTexInfo
{
	unsigned int * texID;
	int texHandle;
	XShaderTexType texType;
};
class XShaderUBOData;
class XShaderGLSL
{
public:
	static const int m_maxShaderGLSLDataSum = 256;
private:
	XBool m_isInited;
	XShaderHandle m_shaderHandle;
	std::vector<XShaderDataInfo> m_dataInfos;
	std::vector<XSaderTexInfo> m_texInfos;
	std::vector<XShaderUBOInfo> m_UBOInfos;
	void release();
public:
	XBool init(const char* vertFile,const char* fragFile,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,const char* geomFile = NULL);
	XBool connectData(const char *name,XShaderDataType type,int size,void *p);
	XBool connectTexture(const char *name,unsigned int * tex,XShaderTexType type = TEX_TYPE_2D);
	void useShader(bool withTex0 = false);

	void useShaderEx(unsigned int tex0,XShaderTexType type = TEX_TYPE_2D);

	void setGeometryInfo(unsigned int inType,unsigned int outType,int outSum);
	int getGeometryMaxOutputCount() const;

	void disShader();
	unsigned int getShaderHandle()const{ return m_shaderHandle.shaderHandle;}
	XShaderGLSL()
		:m_isInited(XFalse)
	{}
	~XShaderGLSL() {release();}

	XBool connectUBO(const char *uboName,XUBO *ubo);

	XBool getUBOInfo(XShaderUBOData &uboData,int valueSum,const char *uboName,const char **valueNames);
};
class XShaderUBOData
{
public:
	unsigned int m_handle;
	char m_name[256];
	int m_offset[XShaderGLSL::m_maxShaderGLSLDataSum];
	unsigned int m_index[XShaderGLSL::m_maxShaderGLSLDataSum];
	int m_size;
};

#ifndef GL_FRONT
#define GL_FRONT (0x4040)
#endif
enum XPboMode
{
	PBO_MODE_UNPACK,
	PBO_MODE_PACK,
};
enum XColorMode;

class XPBO
{
private:
	XBool m_isInited;
	unsigned int m_pboID[2];
	int m_curPBOIndex;
	int m_size;
	XColorMode m_colorType;
	int m_w;
	int m_h;
	int m_px;
	int m_py;
	int m_wx;
	int m_wy;
	int m_dataSize;
	XPboMode m_mode;
public:
	XPBO()
		:m_isInited(XFalse)
		,m_curPBOIndex(0)
		,m_mode(PBO_MODE_PACK)
	{}
	~XPBO(){release();}
	void release();
	XBool init(int w,int h,int px,int py,int wx,int wy,XColorMode colorType,XPboMode mode = PBO_MODE_PACK);
	XBool getPixel(unsigned char * buff,int target = GL_FRONT);
	XBool setPixel(unsigned char * buff);
	void bind() const;
	void unbind() const;
};

class XVBO
{
private:
	XBool m_withVAO;
	XBool m_isInited;
	XBool m_withV;
	XBool m_withT;
	XBool m_withN;
	XBool m_withC;
	XBool m_withI;
	unsigned int m_vao;
	unsigned int m_v;
	unsigned int m_t;
	unsigned int m_n;
	unsigned int m_c;
	unsigned int m_i;
	int m_size;
	int m_indexSize;
	int m_vSize;
	XBool initX(int size,const float *v,const float *t = NULL,const float *n = NULL,const float *c = NULL,
		int iSize = 0,const unsigned int *i = NULL,bool withVAO = false);
	XBool updateDateX(int size,const float *v,const float *t = NULL,const float *n = NULL,const float *c = NULL,
		int iSize = 0,const unsigned int *i = NULL);
public:

	XBool init(int size,const float *v,const float *t = NULL,const float *n = NULL,const float *c = NULL,
		int iSize = 0,const unsigned int *i = NULL,bool withVAO = false)
	{
		m_vSize = 3;
		return initX(size,v,t,n,c,iSize,i,withVAO);
	}
	XBool updateDate(int size,const float *v,const float *t = NULL,const float *n = NULL,const float *c = NULL,
		int iSize = 0,const unsigned int *i = NULL)
	{
		if(!m_isInited) return init(size,v,t,n,c,iSize,i);
		return updateDateX(size,v,t,n,c,iSize,i);
	}
	XBool init2D(int size,const float *v,const float *t = NULL,const float *n = NULL,const float *c = NULL,
		int iSize = 0,const unsigned int *i = NULL,bool withVAO = false)
	{
		m_vSize = 2;
		return initX(size,v,t,n,c,iSize,i,withVAO);
	}
	XBool updateDate2D(int size,const float *v,const float *t = NULL,const float *n = NULL,const float *c = NULL,
		int iSize = 0,const unsigned int *i = NULL)
	{
		if(!m_isInited) return init2D(size,v,t,n,c,iSize,i);
		return updateDateX(size,v,t,n,c,iSize,i);
	}
	XBool updateDataV(int size,const float *v);
	XBool updateDataT(int size,const float *t);
	XBool updateDataN(int size,const float *n);
	XBool updateDataC(int size,const float *c);
	XBool updateDataI(int size,const unsigned int *i);
	void use(XBool withTex = XTrue);
	void disuse();
	void drawByIndex(unsigned int type,XBool withTex = XTrue);
	void drawByIndex(unsigned int type,int size,unsigned int indexType,void *pIndex,XBool withTex = XTrue);
	void drawByArray(unsigned int type,XBool withTex = XTrue);
	void drawByArray(unsigned int type,int index,int size,XBool withTex);
	void release();
	int getSize()const{return m_size;}
	int getIndexSize()const{return m_indexSize;}

	XBool setAsSubject(const XVBO &temp,XBool v,XBool n,XBool c,XBool t,XBool i,XBool cv,XBool cn,XBool cc,XBool ct,XBool ci);
	XBool m_isSubject;
	XBool m_subjectV;
	XBool m_subjectN;
	XBool m_subjectC;
	XBool m_subjectT;
	XBool m_subjectI;

	XVBO()
		:m_isInited(XFalse)
		,m_withV(XFalse)
		,m_withT(XFalse)
		,m_withN(XFalse)
		,m_withC(XFalse)
		,m_isSubject(XFalse)
		,m_v(0)
		,m_n(0)
		,m_t(0)
		,m_c(0)
		,m_i(0)
		,m_vSize(3)
		,m_withVAO(false)
	{}
	~XVBO(){release();}
};

namespace XGL
{
	inline XBool getIsFBOSupported(){return XEE::isFboSupported;}
	extern XBool getIsFramebufferReady();
}

class XFBOEx;
class XFBO
{
private:
	unsigned int m_fboId;
	unsigned int m_rboId;
	std::vector<XTexture *> m_pTextures;
	XColorMode m_type;
	int m_zeroTexIndex;
public:
	XBool init(int w,int h,XColorMode type = COLOR_RGBA);
	void useFBO(bool newSize = false,int w = 0,int h = 0);
	void bind();
	void attachTex(unsigned int order = 0);
	XBool attachTexs(int sum,int index,...);
	void removeFBO();
	void unbind();
	void addOneTexture(int w,int h,XColorMode type = COLOR_RGBA);
	void updateTexture(void *p,unsigned int index);
	unsigned int getTexture(unsigned int order) const;
	int getWidth(unsigned int order) const;
	int getHeight(unsigned int order) const;
	void release();
	XFBO()
		:m_zeroTexIndex(-1)
	{}
	~XFBO() {release();}

	unsigned int getFboID() const {return m_fboId;}
	void getPixelFromFboEx(const XFBOEx& ex);
	int getW() const;
	int getH() const;
};

class XFBOEx
{
private:
	unsigned int m_fboId;
	unsigned int m_rboId;
	unsigned int m_rbdId;
	int m_w;
	int m_h;

	bool m_isInited;
public:
	bool init(int w,int h,XColorMode type = COLOR_RGBA);
	void useFBO(bool newSize = false,int w = 0,int h = 0);
	void removeFBO();
	XFBOEx()
		:m_isInited(false)
	{}
	~XFBOEx(){release();}
	void release();
	unsigned int getFboID() const {return m_fboId;}
	int getW() const{return m_w;}
	int getH() const{return m_h;}
};

namespace XRender
{
extern void drawBlankPlane(int w,int h,unsigned int tex,XShaderGLSL *pShader = NULL);
}
#if WITH_INLINE_FILE
#include "XShaderGLSL.inl"
#endif
}
#endif

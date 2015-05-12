#ifndef _JIA_XTERRAIN_
#define _JIA_XTERRAIN_

#include "XBasicFun.h"
#include "XTextureInformation.h"
#include "XCam.h"
#include "XBasic3D.h"
#include "XShaderGLSL.h"
namespace XE{

class XWaterFlow;

class XTerrain
{
	friend XWaterFlow;
private:
	XBool m_isInited;
	float *m_terrainData;
	const float *m_newH;
	XTextureData m_texture;
	XBool m_withTexture;
	int m_width;
	int m_height;

	XVector3 m_position;
	XVector3 m_scale;
	XVector3 m_angle;

	float getHeight(float x,float z) const;
	XVector2 getTexturePosition(float x,float z) const;
	int m_allPointSum;
	int m_allFaceSum;
	float m_coordOffsetX;
	float m_coordOffsetY;

	XVBO m_vbo;
	std::string m_textureName;
public:
	float *m_v;
	float *m_n;
	float *m_t;
	float *m_c;
private:
	XVector3 *m_faceN;

	unsigned int *m_index;

	bool m_withTexGen;
	float m_reflectRate;
	int m_faceSum;
	XBool m_withColor;

	XShaderGLSL *m_pShader;
	void releaseMemory();
public:
	float getReflectRate(){return m_reflectRate;}
	void setShader(XShaderGLSL *p){m_pShader = p;}
public:
	XBool init(const char *mapFilename,const char * texFilename,int w,int h,
		XBool withColor = XFalse,
		XResourcePosition resourcePosition = RESOURCE_SYSTEM_DEFINE);
	XBool init(const float *mapData,const char * texFilename,int w,int h,
		XBool withColor = XFalse,
		XResourcePosition resourcePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *picFilename,const char * texFilename,
		XBool withColor = XFalse,
		XResourcePosition resourcePosition = RESOURCE_SYSTEM_DEFINE);
	void draw(XBool withTex = XTrue);
	void drawNormal(int step = 1);
	void updateTexture(const unsigned char * data);
	void setTexture(unsigned int tex);
	void setTexture(const XTextureData &tex);
	bool saveToObj(const char * filename);
private:
	bool saveMtl(const char * filename);
	void updateNormal(const float *heights);
public:

	XBool updateHeight(const float *heights,const bool *flags = NULL);
	XBool updateByHeightAndNormal(const float *heights,const float *normal);
	XBool updateByFlag(const bool *flags,const float * w);
	XBool updateVBO(bool v,bool n = false,bool c = false,bool t = false,bool i = false);
	XBool updateByStep(int step);

	void setPosition(float x,float y,float z) {m_position.set(x,y,z);}
	void setPosition(const XVector3 &pos) {m_position = pos;}
	void setScale(float x,float y,float z) {m_scale.set(x,y,z);}
	void setScale(const XVector3 &scale) {m_scale = scale;}
	void setAngle(float x,float y,float z) {m_angle.set(x,y,z);}
	void setAngle(const XVector3 &angle) {m_angle = angle;}

	void setWithTexGen(bool flag){m_withTexGen = flag;}
	void release();
	void setReflectRate(float rate);
	XVector3 myNormalize(float x,float z);
	bool getMousePoint(XVector2 &outPoint);
	bool getMousePointEx(const XVector3 &n,const XVector3 &f,XVector2 &outPoint);
	XVector3 getMyNormal(int x,bool flag);
private:
	XTerrain *m_pSubject;
	bool m_subjectV;
	bool m_subjectN;
	bool m_subjectC;
	bool m_subjectT;
	bool m_subjectI;
public:

	bool setSubject(XTerrain *T,bool cv,bool cn,bool cc,bool ct,bool ci);

	XTerrain()
		:m_isInited(XFalse)
		,m_terrainData(NULL)
		,m_position(0.0f,0.0f,0.0f)
		,m_scale(1.0f,1.0f,1.0f)
		,m_angle(0.0f,0.0f,0.0f)
		,m_v(NULL)
		,m_n(NULL)
		,m_faceN(NULL)
		,m_c(NULL)
		,m_withColor(XFalse)

		,m_t(NULL)

		,m_withTexGen(false)
		,m_reflectRate(0.5f)
		,m_faceSum(0)
		,m_pShader(NULL)
		,m_index(NULL)
		,m_pSubject(NULL)
		,m_tempFitTerrain(NULL)
		,m_subjectV(false)
		,m_subjectN(false)
		,m_subjectC(false)
		,m_subjectT(false)
	{}
	~XTerrain() {release();}
private:
	float *m_tempFitTerrain;
	int m_oInX;
	int m_oInY;
public:
	void myFitTerrain(const float *inData,int inX,int inY,float *outData);
};

namespace X3D
{
	extern void fitTerrain(const float *inData,int inX,int inY,float *outData,int outX,int outY);
}

struct XTerrainFaceInfo
{
	bool isEnable;
	int index[3];
	XVector3 normal;
	XTerrainFaceInfo()
		:isEnable(false)
	{}
};
struct XTerrainVertexInfo
{
	int faceSum;
	int index;
	int lastIndex;
	int normalIndex;
	int x,y;
	float h;
	int faceIndex[6];
};
class XTerrainOptimization
{
private:
	XBool m_isInited;
	float * m_data;
	int m_w;
	int m_h;
	int m_dataSize;
	std::vector<XTerrainFaceInfo> m_faceInfos;
	std::vector<XTerrainVertexInfo> m_vertexInfos;
public:
	XBool init(const float *data,int w,int h);
	XBool init(const char * filename);

	void optimization();
	XBool saveToObj(const char * filename,const char *texName = NULL);
	XTerrainOptimization()
		:m_isInited(XFalse)
		,m_data(NULL)
	{}
	~XTerrainOptimization()
	{release();}
	void release()
	{
		if(!m_isInited) return;
		XMem::XDELETE_ARRAY(m_data);
		m_isInited = XFalse;
	}
};
#if WITH_INLINE_FILE
#include "XTerrain.inl"
#endif
}
#endif

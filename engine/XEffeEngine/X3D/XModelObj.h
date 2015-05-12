#ifndef _JIA_XMODELOBJ_
#define _JIA_XMODELOBJ_

#include "XBasic3D.h"
#include "XTextureInformation.h"
#include "XMaterial.h"
#include "XShaderGLSL.h"
#include <vector>
namespace XE{
extern void removeRedundantSpace(char *p);

struct XFaceInfo
{
    XVectorIndex3 vIndex;
	XVectorIndex3 tIndex;
	XVectorIndex3 nIndex;
};
struct XMaterialInfo
{
	std::string matetialName;
	std::string mapKdName;
	std::string mapDumpName;
	XMaterial material;
	XTextureData textureData;
	XBool withTexture;
	XBool withDumpTex;
	XTextureData dumpTexData;

	XVector4 ka;
	XVector4 kd;
	XVector4 ks;
	XVector4 ke;
	float shininess;
	float alpha;

	float Ni;
	XVector3 Tf;
	int illum;
	void setData()
	{
		material.setAmblient(ka.x,ka.y,ka.z,ka.w);
		material.setDiffuse(kd.x,kd.y,kd.z,kd.w);
		material.setSpecular(ks.x,ks.y,ks.z,ks.w);
		material.setEmission(ke.x,ke.y,ke.z,ke.w);
		material.setShininess(shininess);
	}
	XMaterialInfo()
		:withDumpTex(XFalse)
		,withTexture(XFalse)

		,ka(0.2f,0.2f,0.2f,1.0f)
		,kd(0.8f,0.8f,0.8f,1.0f)
		,ks(0.0f,0.0f,0.0f,1.0f)
		,ke(0.0f,0.0f,0.0f,0.0f)
		,shininess(0.0f)
		,alpha(1.0f)
	{}
	~XMaterialInfo()
	{

	}
};
struct XGroupInfo
{
	char withTexInfo;
	char withNormalInfo;
	std::string groupName;
	int materialIndex;
	std::string materialName;
	std::vector<XFaceInfo> face;
	XVBO vbo;

	XGroupInfo()
		:withTexInfo(-1)
		,withNormalInfo(-1)
		,materialIndex(0)
	{}
	~XGroupInfo(){release();}
	void release()
	{
		face.clear();
		vbo.release();
	}
};

class XModelObj:public XBasic3DObject
{
private:
	XBool m_isInited;
	XVector3 m_bandBox[8];

	std::vector<XVector3> m_point;
	std::vector<XVector2> m_texturePoint;
	std::vector<XVector3> m_normal;
	std::vector<XMaterialInfo*> m_material;
	std::vector<XGroupInfo *> m_group;
	std::vector<std::string> m_materialFilename;
	std::vector<int> m_materialIndex;

	XBool readFaceInfo(XGroupInfo *group,char *lineData);
	XBool loadMaterial(const char *filename);
	XBool saveMaterial();
	int getMaterialIndex(const std::string &str);
	XMaterialInfo * getMaterialInfo(const std::string &MatName);
	XGroupInfo *getGroup(const char *name);
public:

	XBool save(const char *filename);
	XBool load(const char *filename);
	void draw(XBool withTex = XTrue,const XBasic3DObject *base = NULL);
	void drawBandbox()
	{
		XRender::drawLine(m_bandBox[0],m_bandBox[1]);
		XRender::drawLine(m_bandBox[1],m_bandBox[2]);
		XRender::drawLine(m_bandBox[2],m_bandBox[3]);
		XRender::drawLine(m_bandBox[3],m_bandBox[0]);
		XRender::drawLine(m_bandBox[4],m_bandBox[5]);
		XRender::drawLine(m_bandBox[5],m_bandBox[6]);
		XRender::drawLine(m_bandBox[6],m_bandBox[7]);
		XRender::drawLine(m_bandBox[7],m_bandBox[4]);
		XRender::drawLine(m_bandBox[0],m_bandBox[4]);
		XRender::drawLine(m_bandBox[1],m_bandBox[5]);
		XRender::drawLine(m_bandBox[2],m_bandBox[6]);
		XRender::drawLine(m_bandBox[3],m_bandBox[7]);
	}
private:
	XBool checkData();
public:
	int getVectorSum() const {return m_point.size();}
	XVector3 getVector(unsigned int index) const
	{
		if(index >= m_point.size()) return XVector3::zero;
		return m_point[index];
	}
	XVector3 getNormal(unsigned int index)
	{
		if(index >= m_normal.size()) return XVector3::zero;
		return m_normal[index];
	}
	XVectorIndex3 getFaceNormalIndex(unsigned int index) const
	{
		if(m_group.size() <= 0 || index >= m_group[0]->face.size()) return XVectorIndex3(0.0f,0.0f,0.0f);
		return m_group[0]->face[index].nIndex;
	}
	int getFaceSum() const
	{
		if(m_group.size() <= 0) return 0;
		return m_group[0]->face.size();
	}
	XVectorIndex3 getFaceVectorIndex(unsigned int index) const
	{
		if(m_group.size() <= 0 || index >= m_group[0]->face.size()) return XVectorIndex3(0.0f,0.0f,0.0f);
		return m_group[0]->face[index].vIndex;
	}

	void release();
	XModelObj()
		:m_isInited(XFalse)
	{}
	~XModelObj(){release();}
};

}
#endif
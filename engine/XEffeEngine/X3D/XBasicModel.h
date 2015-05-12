#ifndef _JIA_XBASICMODEL_
#define _JIA_XBASICMODEL_

#include "X3DWorld.h"
namespace XE{

class XBasicModel
{
private:
	bool m_isInited;
	int m_vSum;
	float *m_v;
	float *m_c;

	int m_iSum;
	unsigned int *m_i;
	XVector3 m_position;
	XVector3 m_scale;
	XVector3 m_angle;

	XVBO m_vbo;
public:

	bool init(int vSum,float *v,float *c,int iSum,int *i)
	{
		if(m_isInited) return false;
		if(vSum <= 0 || iSum <= 0) return false;
		m_vSum = vSum;
		m_iSum = iSum;

		m_v = XMem::createArrayMem<float>(m_vSum * 3);
		memcpy(m_v,v,m_vSum * 3 * sizeof(float));
		m_c = XMem::createArrayMem<float>(m_vSum * 4);
		memcpy(m_c,c,m_vSum * 4 * sizeof(float));
		m_i = XMem::createArrayMem<unsigned int>(m_iSum * 3);
		memcpy(m_i,i,m_iSum * sizeof(int));

		m_vbo.init(m_vSum,m_v,NULL,NULL,m_c,m_iSum,m_i);

		m_isInited = true;
		return true;
	}
	void draw();
	void setPosition(float x,float y,float z) {m_position.set(x,y,z);}
	void setPosition(const XVector3 &pos) {m_position = pos;}
	void setScale(float x,float y,float z) {m_scale.set(x,y,z);}
	void setScale(const XVector3 &scale) {m_scale = scale;}
	void setAngle(float x,float y,float z) {m_angle.set(x,y,z);}
	void setAngle(const XVector3 &angle) {m_angle = angle;}

	void updateV(float *v)
	{
		if(!m_isInited) return;
		memcpy(m_v,v,m_vSum * 3 * sizeof(float));
		m_vbo.updateDataV(m_vSum,m_v);
	}
	void updateC(float *c)
	{
		if(!m_isInited) return;
		memcpy(m_c,c,m_vSum * 4 * sizeof(float));
		m_vbo.updateDataC(m_vSum,m_c);
	}
	void updateI(int *i)
	{
		if(!m_isInited) return;
		memcpy(m_i,i,m_iSum * sizeof(int));
		m_vbo.updateDataI(m_iSum,m_i);
	}
	void release()
	{
		if(!m_isInited) return;
		XMem::XDELETE_ARRAY(m_v);
		XMem::XDELETE_ARRAY(m_i);
		m_isInited = false;
	}
	XBasicModel()
		:m_isInited(false)
		,m_vSum(0)
		,m_v(NULL)
		,m_iSum(0)
		,m_i(NULL)
		,m_position(0.0f,0.0f,0.0f)
		,m_scale(1.0f,1.0f,1.0f)
		,m_angle(0.0f,0.0f,0.0f)
	{}
	~XBasicModel() {release();}
};
}
#endif
#ifndef _JIA_XLIGHT_
#define _JIA_XLIGHT_

#include "XBasic3D.h"
namespace XE{
class XLight
{
private:
	XVector4 m_ambient;
	XVector4 m_diffuse;
	XVector4 m_position;
	XVector4 m_specular;
	int m_index;

	XVector3 m_lookAtPosition;
	XVector3 m_direction;
	XMatrix4x4 m_projectMatrix;
	XMatrix4x4 m_viewMatrix;
	XVector3 m_angle;
	float m_len;
	XBool m_needCalculate;
public:
	XMatrix4x4 getProjectMatrix() {return m_projectMatrix;}
	XMatrix4x4 getViewMatrix() {return m_viewMatrix;}
	XLight();
	void calculate();
	void setLength(float len)
	{
		m_len = len;
		m_needCalculate = XTrue;
	}
	void setAngle(float x,float y,float z)
	{
		m_angle.set(x,y,z);
		m_needCalculate = XTrue;
	}
	void setIndex(int index) {m_index = index;}
	void setPosition(float x,float y,float z,float w)
	{
		m_position.set(x,y,z,w);
	}
	void setPosition(const XVector4 &p) {m_position = p;}
	XVector3 getPosition() const {return XVector3(m_position.x,m_position.y,m_position.z);}
	void setAmblient(float x,float y,float z,float w)
	{
		m_ambient.set(x,y,z,w);
	}
	void setAmblient(const XVector4 &a) {m_ambient = a;}
	void setDiffuse(float x,float y,float z,float w)
	{
		m_diffuse.set(x,y,z,w);
	}
	void setDiffuse(const XVector4 &d) {m_diffuse = d;}
	void setSpecular(float x,float y,float z,float w)
	{
		m_specular.set(x,y,z,w);
	}
	void setSpecular(const XVector4 &s) {m_specular = s;}
	void useLight();
	void disLight();
	void disAllLight(){glDisable(GL_LIGHTING);}
};
}
#endif

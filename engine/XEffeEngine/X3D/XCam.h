#ifndef _JIA_XCAM_
#define _JIA_XCAM_

#include "XBasicFun.h"
#include "XBasicClass.h"
#include "glu.h"
namespace XE{

class XBasicCam
{
public:
	virtual void useCam() = 0;
	virtual ~XBasicCam() {}
};
class XCam:public XBasicCam
{
private:
	XVector3 m_position;
	XVector3 m_lookAtPosition;
	XVector3 m_direction;

public:
	void init(const XVector3 &pos,const XVector3 &lookAt,const XVector3 &direction)
	{
		m_position = pos;
		m_lookAtPosition = lookAt;
		m_direction = direction;
	}
	void setPosition(float x,float y,float z) {m_position.set(x,y,z);}
	void setPosition(const XVector3 &p) {m_position = p;}
	void setLookAt(float x,float y,float z) {m_lookAtPosition.set(x,y,z);}
	void setLookAt(const XVector3 &l) {m_lookAtPosition = l;}
	void setDirection(float x,float y,float z) {m_direction.set(x,y,z);}
	void setDirection(const XVector3 &d) {m_direction = d;}
	void useCam()
	{
		gluLookAt(m_position.x,m_position.y,m_position.z,
			m_lookAtPosition.x,m_lookAtPosition.y,m_lookAtPosition.z,
			m_direction.x,m_direction.y,m_direction.z);
	}
	XCam()
		:m_position(0.0f,0.0f,-100.0f)
		,m_lookAtPosition(0.0f,0.0f,0.0f)
		,m_direction(0.0f,1.0f,0.0f)
	{}
};

class XCamRoam:public XBasicCam
{
private:
	XVector3 m_position;
	float m_len;
	XVector3 m_angle;

	XVector3 m_lookAtPosition;
	XVector3 m_direction;
	XMatrix4x4 m_projectMatrix;
	XMatrix4x4 m_viewMatrix;
	XMatrix4x4 m_projXView;

	XBool m_needCalculate;
	XBool m_neadCalFrustum;
	XBool m_neadCalProjXView;
	float m_near;
	float m_far;
	float m_fov;
public:
	void setNear(float n)
	{
		m_near = n;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	float getNear()const {return m_near;}
	void setFar(float f)
	{
		m_far = f;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	float getFar()const {return m_far;}
	void setFov(float f)
	{
		m_fov = f;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	float getFov()const {return m_fov;}
public:
	XMatrix4x4 getProjXView()
	{
		calculate();
		if(m_neadCalProjXView)
		{
			m_projXView = m_projectMatrix * m_viewMatrix;
			m_neadCalProjXView = XFalse;
		}
		return m_projXView;
	}
	XMatrix4x4 getProjectMatrix() {return m_projectMatrix;}
	XMatrix4x4 getViewMatrix() {return m_viewMatrix;}
	XBool calculate();
	void init(const XVector3 &pos,float len,XVector3 &angle)
	{
		m_position = pos;
		m_len = len;
		m_angle = angle;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
		calculate();
	}
	void forward(float len)
	{
		m_position.z += len * cos(m_angle.x * DEGREE2RADIAN) * cos(m_angle.y * DEGREE2RADIAN);
		m_position.y += len * sin(m_angle.x * DEGREE2RADIAN);
		m_position.x += len * cos(m_angle.x * DEGREE2RADIAN) * sin(m_angle.y * DEGREE2RADIAN);
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	void backward(float len)
	{
		m_position.z -= len * cos(m_angle.x * DEGREE2RADIAN) * cos(m_angle.y * DEGREE2RADIAN);
		m_position.y -= len * sin(m_angle.x * DEGREE2RADIAN);
		m_position.x -= len * cos(m_angle.x * DEGREE2RADIAN) * sin(m_angle.y * DEGREE2RADIAN);
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	void turnLeft(float angle)
	{
		m_angle.y += angle;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	void turnRight(float angle)
	{
		m_angle.y -= angle;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	void turnUp(float angle)
	{
		m_angle.x += angle;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
		if(m_angle.x > 90.0f) m_angle.x = 90.0f;
	}
	void turnDown(float angle)
	{
		m_angle.x -= angle;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
		if(m_angle.x < -90.0f) m_angle.x = -90.0f;
	}
	XVector3 getPosition() const {return m_position;}
	XVector3 getLookAtPos() const {return m_lookAtPosition;}
	void setPosition(float x,float y,float z)
	{
		m_position.set(x,y,z);
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	void setPosition(const XVector3 &pos)
	{
		m_position = pos;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	float getLength() const {return m_len;}
	void setLength(float len)
	{
		m_len = len;
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	void setAngle(float x,float y,float z)
	{
		m_angle.set(x,y,z);
		m_needCalculate = XTrue;
		m_neadCalFrustum = XTrue;
	}
	XVector3 getAngle() const {return m_angle;}
	void useCam()
	{
		calculate();
		gluLookAt(m_position.x,m_position.y,m_position.z,
			m_lookAtPosition.x,m_lookAtPosition.y,m_lookAtPosition.z,
			m_direction.x,m_direction.y,m_direction.z);
	}
	XCamRoam()
		:m_position(0.0f,0.0f,-100.0f)
		,m_len(100.0f)
		,m_angle(0.0f,0.0f,0.0f)
		,m_near(10.0f)
		,m_far(10000.0f)
		,m_fov(45.0f)
	{}

private:
	XVector4 m_face[6];
	XVector3 m_point[9];
public:

	void calculateFrustumPlanes();
	bool isInFrustum(float x,float y,float z);
	void calculateFrustumPoint();
	void drawFrustum();
};
}
#endif

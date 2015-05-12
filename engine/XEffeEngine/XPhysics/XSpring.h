#ifndef XSPRING_
#define XSPRING_

#include "XPhysicsBasic.h"
namespace XE{
class XSpring:public XBasicPhysic2DObject
{
private:
	float m_normalLength;
	float m_minLength;
	float m_maxLength;
	float m_springRatio;
	float m_curLength;

	float m_curForce;
public:
	int init();
	int move(int timeDelay);

	XSpring()
	{
	}
};
}
#endif
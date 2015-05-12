#ifndef XPHYSICSBASIC_
#define XPHYSICSBASIC_

#include "XBasicClass.h"
namespace XE{

union XPhYsicObjectAttribute
{
	unsigned short canMove:1;
	unsigned short canCollide:1;
	unsigned short canFlag00:1;
	unsigned short canFlag01:1;
	unsigned short canFlag02:1;
	unsigned short canFlag03:1;
	unsigned short canFlag04:1;
	unsigned short canFlag05:1;
	unsigned short canFlag06:1;
	unsigned short canFlag07:1;
	unsigned short canFlag08:1;
	unsigned short canFlag09:1;
	unsigned short canFlag0b:1;
	unsigned short canFlag0c:1;
	unsigned short canFlag0d:1;
};
class XBasicPhysic2DObject
{
private:
	char m_isEnable;
	XPhYsicObjectAttribute m_attribute;
	float m_mass;
	XVector2 m_speed;
	float m_density;
	float m_volume;
	float m_collideEnergyWastageRadio;
	float m_airResistanceRadio;
	float m_surfaceFrictionCoefficient;

	XVector2 m_position;
	float m_rotate;
	XVector2 m_centreOfGravity;
	float m_rotationSpeed;
public:
	XBasicPhysic2DObject()
	{}
	virtual ~XBasicPhysic2DObject(){}
};
}
#endif
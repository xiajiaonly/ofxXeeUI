#ifndef _JIA_XFIREWORKPARTICLES_
#define _JIA_XFIREWORKPARTICLES_

#include "XEchoParticles.h"
namespace XE{
class XFireWorkParticles
{
private:
	char m_isInited;
	char m_isEnd;

	XVector2 m_position;
	XVector2 m_initSpeed;
	float m_decreaseSpeed;
	float m_gravity;
	int m_atomSum;

	XEchoParticles *m_atom;
	const XTexture *m_texture;

public:
	int init(const XVector2& position,const XVector2& initSpeed,float decreaseSpeed,float gravity,int atomSum,const XTexture *texture);
	void reset();
	void move(int timeDelay);
	void draw() const;
	void release();
	int getIsEnd()
	{
		if(m_isEnd != 0) return 1;
		return 0;
	}

	void setTexture(const XTexture *texture)
	{
		if(m_isInited == 0) return;
		if(texture == NULL || !glIsTexture(texture->m_texture)) return;
		m_texture = texture;
		for(int i = 0;i < m_atomSum;++ i)
		{
			m_atom[i].setTexture(m_texture);
		}
	}

	void setPosition(const XVector2& position)
	{
		m_position = position;
	}

	XFireWorkParticles();
};
}
#endif
#ifndef _JIA_XMOVENUMBER_
#define _JIA_XMOVENUMBER_
#include "../XOSDefine.h"
namespace XE{

class XMoveNumber
{
private:
	int m_curNumber;
	float m_armNumber;
public:
	void addArmNumber(float number){m_armNumber += number;}
	void setArmNumber(float number){m_armNumber = number;}
	int getCurNumber(){return m_curNumber;}
	int getArmNumber(){return (int)m_armNumber;}
	XBool move(int delay);
	void reset()
	{
		m_curNumber = 0;
		m_armNumber = 0.0f;
	}
	XMoveNumber()
	:m_curNumber(0)
	,m_armNumber(0.0f)
	{}
};
}
#endif
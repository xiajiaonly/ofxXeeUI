#ifndef _JIA_XSCENE_
#define _JIA_XSCENE_

#include "stdio.h"
#include <string>
#include "XInputEventCore.h"
namespace XE{
class XScene
{
public:
	XScene()
	:m_sceneName("x")
	{ printf("XScene Constructor \n"); }
	virtual ~XScene() { printf("XScene Destructor :: %s\n", m_sceneName.c_str());}

	virtual void setup(){ printf("XScene setup :: %s\n", m_sceneName.c_str());}

	virtual void update(float){}
	virtual void draw(){}

	virtual void willEnter(){}
	virtual void entered(){}
	virtual void willExit(){}
	virtual void exited(){}

	virtual void input(const XInputEvent &) {}

	std::string getSceneName()const{return m_sceneName;}
	void setSceneName(const std::string & name){m_sceneName = name;}
private:
	std::string m_sceneName;
};
}
#endif
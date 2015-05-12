#ifndef _JIA_XGAMEBASIC_
#define _JIA_XGAMEBASIC_
namespace XE{

class XGameBasic
{
private:
public:
	virtual bool init() = 0;
	virtual void move(int stepTime) = 0;
	virtual void draw() = 0;
	virtual void input(const XInputEvent &event) = 0;
	virtual void release() = 0;
	virtual void ctrlEventProc(int id,int eventID) = 0;
};
class XGameBasic3D:public XGameBasic
{
private:
public:
	virtual void draw3D(XBool) = 0;
};
}
#endif
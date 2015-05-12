#include "UI.h"
//#include "ofMain.h"
using namespace XE;
bool UI::init()
{//UI³õÊ¼»¯
	tmp.initWithoutSkin(256,"ÄãºÃ");
	tmp.setPosition(200,10);
	cmb.initWithoutSkin(256,5,3);
	cmb.setPosition(200,100);
	btn.initWithoutSkin("nihao",128);
	btn.setPosition(200,200);
	return true;
}
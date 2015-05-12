#include "UI.h"
using namespace XE;
bool UI::init()
{//TODO:init the UI items;
	tmp.initWithoutSkin(256,"ÄãºÃ");
	tmp.setPosition(200,10);
	cmb.initWithoutSkin(256,5,3);
	cmb.setPosition(200,100);
	btn.initWithoutSkin("hello",128);
	btn.setPosition(200,200);
	return true;
}
#ifndef _JIA_UI_
#define _JIA_UI_
#include "XEffeEngine.h"
class UI:public XE::XGameBasic
{
protected:
	UI()
		:pClass(NULL)
		,funCB(NULL)
	{}
	UI(const UI&);
	UI &operator= (const UI&);
	virtual ~UI(){}
public:
	static UI& GetInstance()
	{
		static UI m_instance;
		return m_instance;
	}
public:
	bool init();				//init the UI items;
	void move(int){}
	void draw(){}
	void input(const XE::XInputEvent &){}
	void release(){}
	void ctrlEventProc(int id,int eventID){if(funCB != NULL) funCB(id,eventID,pClass);}
	void *pClass;
	void (*funCB)(int,int,void*);
	//TODO:Define UI items
	XE::XEdit tmp;
	XE::XCombo cmb;
	XE::XButton btn;
};
#define UIMain UI::GetInstance()
#endif
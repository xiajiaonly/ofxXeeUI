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
	bool init();				//TODO:这里进行游戏的初始化
	void move(int stepTime){}	//TODO:这里是游戏的idle，也可以通过开启逻辑线程的方式处理
	void draw(){}				//TODO:绘制的函数
	void input(const XE::XInputEvent &){}	//TODO:键盘或者鼠标输入的事件
	void release(){}				//TODO:程序结束时的资源释放
	void ctrlEventProc(int id,int eventID){if(funCB != NULL) funCB(id,eventID,pClass);}
	void *pClass;
	void (*funCB)(int,int,void*);
	//下面定义UI元素
	XE::XEdit tmp;		//输入框
	XE::XCombo cmb;		//下拉框
	XE::XButton btn;	//按钮
};
#define UIMain UI::GetInstance()
#endif
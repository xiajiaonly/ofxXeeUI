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
	bool init();				//TODO:���������Ϸ�ĳ�ʼ��
	void move(int stepTime){}	//TODO:��������Ϸ��idle��Ҳ����ͨ�������߼��̵߳ķ�ʽ����
	void draw(){}				//TODO:���Ƶĺ���
	void input(const XE::XInputEvent &){}	//TODO:���̻������������¼�
	void release(){}				//TODO:�������ʱ����Դ�ͷ�
	void ctrlEventProc(int id,int eventID){if(funCB != NULL) funCB(id,eventID,pClass);}
	void *pClass;
	void (*funCB)(int,int,void*);
	//���涨��UIԪ��
	XE::XEdit tmp;		//�����
	XE::XCombo cmb;		//������
	XE::XButton btn;	//��ť
};
#define UIMain UI::GetInstance()
#endif
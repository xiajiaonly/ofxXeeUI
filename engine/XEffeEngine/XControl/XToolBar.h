#ifndef _JIA_XTOOLBAR_
#define _JIA_XTOOLBAR_

#include "XControlBasic.h"
namespace XE{

struct XToolBarUnit
{
	XBool enable;
	XControlBasic *obj;
	XVector2 scale;
	int width;
	XToolBarUnit()
		:obj(NULL)
		,enable(XTrue)
		,scale(1.0f,1.0f)
		,width(0)
	{}
};
class XToolBar:public XControlBasic
{
private:
	XBool m_isInited;

	float m_insertPoint;

	int m_height;
	std::vector<XToolBarUnit> m_objects;

	XBool m_isMouseDown;
	XVector2 m_oldMousePosition;
public:
	XBool initWithoutSkin(int height = 32);
protected:
	void draw();
	void drawUp();
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int keyOrder,XKeyState keyState);
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}

public:
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	using XObjectBasic::setScale;
	void setScale(float x,float y);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a){m_color.setColor(r,g,b,a);}
	void setAlpha(float a){m_color.setA(a);}

	void addAObject(XControlBasic *obj);
	XControlBasic *getObjByIndex(unsigned int index);
	int getIndexByP(const XControlBasic *obj);
	void releaseMem();
	XToolBar()
		:m_isInited(XFalse)
		,m_insertPoint(10.0f)
	{
		m_ctrlType = CTRL_OBJ_TOOLBAR;
	}
	~XToolBar(){release();}
	void release();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
	void setVisible();
	void disVisible();

private:
	XToolBar(const XToolBar &temp);
	XToolBar& operator = (const XToolBar& temp);

};
#if WITH_INLINE_FILE
#include "XToolBar.inl"
#endif
}
#endif
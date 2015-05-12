#ifndef _JIA_XOBJECTBASIC_
#define _JIA_XOBJECTBASIC_

#include "XOSDefine.h"
#include <string>
#include <vector>
#include "XMath\XVector2.h"
#include "XMath\XFColor.h"
namespace XE{
enum XObjectType
{
	OBJ_NULL,
	OBJ_SPRITE,
	OBJ_FRAME,
	OBJ_FRAMEEX,
	OBJ_NUMBER,
	OBJ_FONTUNICODE,
	OBJ_FONTX,
	OBJ_NODELINE,
	OBJ_CONTROL,
};
extern std::string objectTypeStr[];

class XObjectManager;
class XObjectBasic
{

	friend XObjectManager;
protected:
	XObjectType m_objType;
public:
	virtual XObjectType getObjectType() const {return m_objType;}
	virtual XBool isInRect(float x,float y) = 0;
	virtual XVector2 getBox(int order) = 0;

	virtual void setPosition(float x,float y) = 0;
	virtual void setPosition(const XVector2& pos) {setPosition(pos.x,pos.y);}
	virtual XVector2 getPosition() const  = 0;

	virtual void setScale(float x,float y) = 0;
	virtual void setScale(const XVector2& scale) {setScale(scale.x,scale.y);}
	virtual void setScale(float scale) {setScale(scale,scale);}
	virtual XVector2 getScale() const  = 0;

	virtual void setAngle(float angle) = 0;
	virtual float getAngle() const = 0;

	virtual void setVisible() = 0;
	virtual void disVisible() = 0;
	virtual XBool getVisible() const = 0;

	virtual void draw() = 0;

	virtual void setColor(float r,float g,float b,float a) = 0;
	virtual void setColor(const XFColor& color) {setColor(color.fR,color.fG,color.fB,color.fA);}
	virtual XFColor getColor() const = 0;
	virtual void setAlpha(float a) = 0;

	XObjectBasic()
		:m_parent(NULL)
		,m_objType(OBJ_NULL)
	{}
	virtual ~XObjectBasic()
	{
		if(m_parent == NULL) return;

		m_parent->popChild(this);
		m_parent = NULL;
		clearAllChild();
	}

protected:
	XObjectBasic *m_parent;
	std::vector<XObjectBasic *> m_childList;
	std::vector<XVector2> m_childRelativePos;
	std::vector<XVector2> m_childRelativeSize;
	std::vector<float> m_childRelativeAngle;

	virtual void updateChildPos();
	virtual void updateChildSize();
	virtual void updateChildAngle();
	virtual void updateChildAlpha();
	virtual void updateChildColor();
	virtual void updateChildVisible();
public:
	virtual void clearAllChild();
	virtual void pushChild(XObjectBasic * child);
	virtual void popChild(XObjectBasic * child);
	virtual XBool getIsChild(XObjectBasic * child);

};
}
#endif

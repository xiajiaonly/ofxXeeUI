#ifndef _JIA_XNODELINE_
#define _JIA_XNODELINE_

#include "XObjectBasic.h"
#include "XMath/XBezierSpline.h"
namespace XE{
#define NODELINE_DATA_FILE_NAME ("line/line00000.dat")
#pragma pack(push)
#pragma pack(1)
struct XNode
{
	XVector2 myPoint;
	float toNextAngle;
	float toNextSin;
	float toNextCos;
	float toNextLength;

	float toPreviousAngle;
	float toPreviousSin;
	float toPreviousCos;
	float toPreviousLength;
};
#pragma pack(pop)

enum XLeadMode
{

	LEAD_MODE_FOREWORD = 0x04,
	LEAD_MODE_BACKWORD = 0x08
};

struct XNodeSpecialPoint
{
	XBool isEnable;
	XBool isEnd;
	float curLength;
	XVector2 position;
	float angle;
	float upNodeLength;
	int upNodeOrder;
	XVector2 divergePoint;
	float speed;
	XNodeSpecialPoint()
		:isEnable(XFalse)
		,isEnd(XTrue)
	{}
};

class XSCounter;

class XNodeLine:public XObjectBasic
{
private:
	static const int m_maxNodeSum = 64;
	XVector2 *m_bezierPoint;
	XBool m_needUpdateData;
	XBool m_isLoop;
	XBool m_isACopy;
	XBool m_isVisible;
	void updateData();
	XBezierSpline m_bezierSpline;

	XSCounter *m_cp;
	int m_myOrder;
	XNode *m_node;
	XLeadMode m_leadMode;

	XVector2 m_offsetPosition;
	XVector2 m_scale;

	float m_lineLength;
	int m_nodeSum;
public:
	void setVisible() {m_isVisible = XTrue;}
	void disVisible() {m_isVisible = XFalse;}
	XBool getVisible() const {return m_isVisible;}

	void setOneNode(const XVector2& node,int nodeOrder);
	void setOneNode(float x,float y,int nodeOrder);
	void addOneNode(const XVector2& node);
	void addOneNode(float x,float y);
	void decreaseOneNode();
	void addOneNode(const XVector2& node,int nodeOrder);
	void addOneNode(float x,float y,int nodeOrder);
	void decreaseOneNode(int nodeOrder);
	XBool saveNodeLine();
	int getOrder() const;
	void setMyOrder(int temp);
	void clearUp();
	void setLoop();
	int getNodeOrder(float x,float y,float distance) const
	{
		if(distance < 0) return -1;
		XVector2 temp(x,y);
		for(int i = 0;i < m_nodeSum;i ++)
		{
			if(temp.getLength(m_node[i].myPoint) <= distance) return i;
		}
		return -1;
	}

	int getNodeSum() const {return m_nodeSum;}
	XVector2 getNode(int order) const
	{
		if(order < 0 || order >= m_nodeSum) return XVector2::zero;
		return m_node[order].myPoint;
	}

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	XVector2 getPosition() const {return m_offsetPosition;}
	XVector2 getScale() const {return m_scale;}
	using XObjectBasic::setScale;
	void setScale(float x,float y) {m_scale.set(x,y);}

	float getAngle() const {return 0.0f;}
	float getNodeLineLength() const {return m_lineLength;}
	void setAngle(float) {}

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

private:

	XNodeSpecialPoint m_specialPoint;
	void release();
public:
	XBool getNodeLine(XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void moveSpecialPoint(int timeDelay,int isLoop,XBool needBezier = XFalse);
	void resetSpecialPoint(XBool needBezier = XFalse);

	void setLeadMode(XLeadMode mode);
	void setSpecialPointSpeed(float speed);
	XBool getSpecialPointIsEnd() const;
	XVector2 getSpecialPointPosition() const;
	float getSpecialPointAngle() const;

	XBool setACopy(const XNodeLine &temp);
	XNodeLine(const XNodeLine &temp);
	XNodeLine& operator = (const XNodeLine& temp);

	virtual void setColor(float,float,float,float){}
	virtual XFColor getColor() const {return XFColor::white;}
	virtual void setAlpha(float){}

	void draw();

	XNodeLine();
	~XNodeLine();

};
#if WITH_INLINE_FILE
#include "XNodeLine.inl"
#endif
}
#endif
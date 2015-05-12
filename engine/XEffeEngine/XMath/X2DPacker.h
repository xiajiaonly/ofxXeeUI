#ifndef _JIA_X2DPACKER_
#define _JIA_X2DPACKER_

#include "XBasicClass.h"
namespace XE{

class XObjectBox
{
public:
	int m_setOrder;
    int m_order;
    int m_basicBoxOrder;
    XVector2 m_position;

    XVector2 m_size;
    float m_acreage;

	XRect m_AABB;
	XBool m_needRotate;
};

class XBasicBox
{
public:
    int m_order;
    int m_beUsed;
	XVector2 m_size;
    float m_releaseAcreage;

	int *m_objectBoxesOrder;

	int m_mayPositionSum;
	XVector2 *m_mayPosition;

	int m_mayPositionXSum;
	int *m_mayPositionX;
	int m_mayPositionYSum;
	int *m_mayPositionY;

    int putInRatio(const XObjectBox &temp);
};

class X2DPacker
{
private:
	int putInABox(XObjectBox &objectBox);
	int canPutIn(XObjectBox &objectBox,XBasicBox &basicBox);
	int m_optimizeLevel;

	void orderObjectByWidth();
	void orderObjectByArea();
	void orderObjectByBigEdgeAndArea();
	void updatePutOperate(XObjectBox &objectBox,XBasicBox &basicBox,XBool needRotate,float positionX,float positionY);
	void updateNewPoint(XBasicBox &basicBox,int sizeX,int sizeY,int pointOrder);
	void updateNewXY(XBasicBox &basicBox,int x,int y);

	XBool m_canRotate;
public:
	int m_basicBoxSum;
    XBasicBox * m_basicBox;
	int m_objectBoxSum;
    XObjectBox * m_objectBox;

	int init(int boxSum,int objectSum);

    int findResult(int orderMode = 0);
	int getNeedBoxSum() const;

	void setOptimizeLevel(int temp)
	{
		if(temp == 0) m_optimizeLevel = 0;
		else m_optimizeLevel = 1;
	}
	int getOptimizeLevel() const {return m_optimizeLevel;}

	void setCanRotate(XBool temp) {m_canRotate = temp;}
	XBool getCanRotate() const {return m_canRotate;}
	void reset();

	X2DPacker()
		:m_optimizeLevel(0)
		,m_basicBoxSum(0)
		,m_basicBox(NULL)
		,m_objectBoxSum(0)
		,m_objectBox(NULL)

		,m_canRotate(XFalse)
	{}
};
}
#endif


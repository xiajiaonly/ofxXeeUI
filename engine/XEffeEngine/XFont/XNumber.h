#ifndef _JIA_XNUMBER_
#define _JIA_XNUMBER_

#include "XSprite.h"
namespace XE{
#ifndef TEXT_MODE
#define TEXT_MODE ("0123456789+-*/%.")
#endif

#ifndef MAX_NUMBER_LENGTH
#define MAX_NUMBER_LENGTH (256)
#endif

enum XNumberAlignmentMode
{
	NUMBER_ALIGNMENT_MODE_LEFT,
	NUMBER_ALIGNMENT_MODE_MIDDLE,
	NUMBER_ALIGNMENT_MODE_RIGHT,
};

class XNumber:public XObjectBasic
{
private:
	XResourcePosition m_resoursePosition;

	XSprite m_sprite;
	XBool m_isInited;
	XBool m_isVisible;
	XBool m_needUpdateData;

	float m_angle;
	float m_angleSin;
	float m_angleCos;

	XNumberAlignmentMode m_alignmentMode;
public:
	void setAlignmentMode(XNumberAlignmentMode mode);
	void setVisible();
	void disVisible();
	XBool getVisible() const {return m_isVisible;}
private:
	char *m_string;

	int m_maxPixelWidth;
	int m_maxPixelHeight;
public:
	int getMaxPixelWidth();
	int getMaxPixelHeight();
private:
	void updateData();
	XVector2 *m_textPosition;
	XRect *m_textRect;
	int m_needShowTextSum;

	XVector2 m_position;
	XVector2 m_setPosition;
	float m_alpha;
	float m_distance;
	XVector2 m_size;
	XVector2 m_layout;
	XVector2 m_scale;
	XVector2 m_rotateBasicPoint;
public:
	XBool init(const char *fileName,
		const XVector2 &size,
		const XVector2 &layout,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initEx(const char *fileName,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	XBool initFromTTF(const char *filename,
		int fontSize,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);

	void draw();

	using XObjectBasic::setScale;
	void setScale(float x,float y);
	XVector2 getScale() const {return m_scale;}
	void setAngle(float angle);
	float getAngle() const {return m_angle;}

	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	void setPositionX(float x);
	void setPositionY(float y);
	XVector2 getPosition() const {return m_setPosition;}
	void setRotateBasePoint(float x,float y);

	XBool setNumber(int temp);
	XBool setNumber(float temp,int decimalPartLength);
	XBool setNumber(const char *temp);

	XNumber& operator = (const XNumber& temp);
	XBool setACopy(const XNumber &temp);

	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	XFColor getColor() const {return m_sprite.getColor();}
	void setAlpha(float a);
	float getAlpha() const {return m_alpha;}
	XBool release();

	void setDistance(float distance) {m_distance = distance;}
	float getDistance() const {return m_distance;}

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	XNumber();
	~XNumber();

};
#if WITH_INLINE_FILE
#include "XNumber.inl"
#endif
}
#endif

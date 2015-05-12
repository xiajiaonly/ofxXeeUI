#ifndef _JIA_XSPRITE_
#define _JIA_XSPRITE_

#include "XTextureInformation.h"
#include "XObjectBasic.h"
#include "XShaderGLSL.h"
namespace XE{
enum XTransformMode
{
	POINT_LEFT_TOP = 0,
	POINT_CENTER = 1
};
enum XTurnOverMode
{
	TURN_OVER_MODE_NULL,
	TURN_OVER_MODE_LEFT_TO_RIGHT,
	TURN_OVER_MODE_UP_TO_DOWN,
	TURN_OVER_MODE_L2R_AND_U2D,
};
#if WITHXSPRITE_EX
class XSprite:public XObjectBasic
{
private:
	XResourcePosition m_resoursePosition;

	XTurnOverMode m_turnOverMode;
	XVector2 m_position;
	XVector2 m_scale;
	XVector2 m_pixelSize;
	float m_angle;
	XVector2 m_changeCenter;

	float m_sinAngle;
	float m_cosAngle;
	XTextureData m_textureData;
	XFColor m_color;

	void updateData();
	void drawInside();

	XGL::XBlendType m_blendType;
	char m_blendRGBScr;
	char m_blendRGBDst;
	char m_blendAScr;
	char m_blendADst;

	XBool m_isInited;
	XBool m_needAngleClip;
	char m_blendTypeScr;
	char m_blendTypeDst;
	XBool m_isVisible;
	XBool m_needUpdateData;
	XBool m_needClip;
	XRect m_clipRect;

	XShaderGLSL *m_pShader;

	XVector2 m_rectPoint[4];
	int m_pointSum;
	int m_upTexDataID;

	float m_vPointer[14];
	float m_uPointer[14];
	float m_clipAngle;
private:
	XSprite(const XSprite& temp);
public:
	void setAngle(float angle);
	float getAngle() const;
	using XObjectBasic::setScale;
	void setScale(float x,float y);
	XVector2 getScale() const;
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	void setPositionX(float x);
	void setPositionY(float y);
	XVector2 getPosition() const;
	void setTurnOverMode(XTurnOverMode mode);
	void setClipRect(const XRect& clipRect);
	void setClipRect(float left,float top,float right,float bottom);
	void disClip();
	void setChangeCenter(const XVector2& center);
	XBool init(const char * filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,
		const XVector2 &changePoint = XVector2(0.5f,0.5f));
	XBool init(int tempW = 0,int tempH = 0,int needSizeCheck = 1,const XVector2 &changePoint = XVector2(0.5f,0.5f));
	XBool init(XTextureData& texData,const XVector2 &changePoint = XVector2(0.5f,0.5f));
	XBool init(int w,int h,XColorMode colorMode,unsigned int tex,const XVector2 &changePoint = XVector2(0.5f,0.5f));
	void draw();
	void draw(GLuint tex);
	void draw(const XTextureData& texData);
	void draw(const XVector2 *u,const XVector2 *v,int w,int h);

	XSprite()
		:m_isInited(XFalse)
		,m_turnOverMode(TURN_OVER_MODE_NULL)
		,m_needClip(XFalse)
		,m_color(1.0f,1.0f,1.0f,1.0f)
		,m_isVisible(XTrue)
		,m_pShader(NULL)

		,m_blendType(XGL::BLEND_TWO_DATA)
		,m_blendTypeScr(4)
		,m_blendTypeDst(5)
		,m_needAngleClip(XFalse)
		,m_clipAngle(0.0f)
		,m_upTexDataID(-1)
	{
		m_objType = OBJ_SPRITE;
		for(int i = 0;i < 14;++ i)
		{
			m_vPointer[i] = 0.0f;
			m_uPointer[i] = 0.0f;
		}
	}
	~XSprite(){release();}
	void release();

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);

	void setAlpha(float temp);
	float getAlpha() const;
	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	XFColor getColor() const {return m_color;}

	void setVisible();
	void disVisible();
	XBool getVisible() const;

	void setBlendType(int typeScr,int typeDst);
	void setBlendType(int rgbScr,int rgbDst,int aScr,int aDst);
	void setBlendMode(XGL::XBlendType mode);

	void setShaderClass(XShaderGLSL * shader);

	XTexture * getTexture();
	XTextureData * getTextureData();

	void setAngleClip(float angle);
	void disAngleClip();

	XSprite& operator = (const XSprite& temp);
	void setACopy(const XSprite& temp);

	void setIsTransformCenter(XTransformMode temp)
	{
		if(temp == POINT_LEFT_TOP) setChangeCenter(XVector2::zero);
		else setChangeCenter(XVector2(0.5f,0.5f));
	}
	void draw(GLuint *tex) {draw(*tex);}
	void draw(const XTextureData* texData) {draw(*texData);}
	void drawWithoutBlend() {draw();}
	XBool init(const char * filename,
		XResourcePosition resoursePosition,
		XTransformMode isTransformCenter)
	{
		if(isTransformCenter == POINT_CENTER) return init(filename,resoursePosition,XVector2(0.5f,0.5f));
		else return init(filename,resoursePosition,XVector2::zero);
	}
	XBool init(int tempW,int tempH,int needSizeCheck,XTransformMode isTransformCenter)
	{
		if(isTransformCenter == POINT_CENTER) return init(tempW,tempH,needSizeCheck,XVector2(0.5f,0.5f));
		else return init(tempW,tempH,needSizeCheck,XVector2::zero);
	}
	XBool init(XTextureData& texData,XTransformMode isTransformCenter)
	{
		if(isTransformCenter == POINT_CENTER) return init(texData,XVector2(0.5f,0.5f));
		else return init(texData,XVector2::zero);
	}
	XBool init(int w,int h,XColorMode colorMode,unsigned int tex,XTransformMode isTransformCenter)
	{
		if(isTransformCenter == POINT_CENTER) return init(w,h,colorMode,tex,XVector2(0.5f,0.5f));
		else return init(w,h,colorMode,tex,XVector2::zero);
	}

	void setOverturn(char temp)
	{
		if(temp == 0) resetLeftRightUpDown();
		else setLeft2Right();
	}
	void setLeft2Right(){setTurnOverMode(TURN_OVER_MODE_LEFT_TO_RIGHT);}
	void setUp2Down() {setTurnOverMode(TURN_OVER_MODE_UP_TO_DOWN);}
	void resetLeftRightUpDown()	{setTurnOverMode(TURN_OVER_MODE_NULL);}
	XTurnOverMode getTurnOverMode() const {return m_turnOverMode;}
	XTransformMode getTransformMode() const
	{
		if(m_changeCenter.x == 0.0f && m_changeCenter.y == 0.0f) return POINT_LEFT_TOP;
		else return POINT_CENTER;
	}
	int XSprite::getW() const {return m_textureData.texture.m_w;}
	int XSprite::getH() const {return m_textureData.texture.m_h;}

};
#else

#define IS_USE_SOLIDIFY (0)

class XSprite:public XObjectBasic
{
private:
	XResourcePosition m_resoursePosition;

	XTextureData m_textureData;

	XVector2 m_setPosition;
	XVector2 m_setTransformCenter;

	XRect m_clipOutsideRect;
	XRect m_clipRect;
	char m_isEnableOutsideChip;
	char m_isVisible;

	void updateClipAndRotatoData();
	char m_needUpdateInsideData;
	void updateInsideData();
public:
	void disClip();
	void setClipRect(const XRect &temp);

	void setClipRect(float left,float top,float right,float bottom);

	int isInRect(float x,float y);
	XVector2 getPosition() const{return m_setPosition;}

	XVector2 getBox(int order);
private:

	XTurnOverMode m_turnOverMode;
	float m_shapeData[16];
private:

	XTransformMode m_isTransformCenter;

	XVector2 m_transformCenter;
	char m_changeTransformCenterManual;
public:
	void setIsTransformCenter(XTransformMode temp);
	XTransformMode getTransformMode() const
	{
		return m_isTransformCenter;
	}

	void setTransformCenter(float x,float y)
	{
		m_changeTransformCenterManual = 1;
		if(m_textureData.isEnableInsideClip != 0)
		{
			m_setTransformCenter.set(x,y);
			if(m_clipOutsideRect.left < m_textureData.textureMove.x) m_transformCenter.x = m_clipOutsideRect.left - m_textureData.textureMove.x + m_setTransformCenter.x;
			else m_transformCenter.x = m_setTransformCenter.x;
			if(m_clipOutsideRect.top < m_textureData.textureMove.y) m_transformCenter.y = m_clipOutsideRect.top - m_textureData.textureMove.y + m_setTransformCenter.y;
			else m_transformCenter.y = m_setTransformCenter.y;

		}else
		{
			m_transformCenter.set(x,y);
		}
	}
public:
	void setAlpha(float temp);
	float getAlpha() const;
	float getAngle() const{return angle;}
	void setAngle(float temp);
	int getW() const;
	int getH() const;
	void setVisible() {m_isVisible = 1;}
	void disVisible() {m_isVisible = 0;}
	char getVisible() const {return m_isVisible;}

private:
	GLfloat angle;
	float sinAngle;
	float cosAngle;

	GLfloat m_positionX;
	GLfloat m_positionY;
	GLfloat xsize, ysize;
	GLfloat alpha;
	GLfloat colorRed;
	GLfloat colorGreen;
	GLfloat colorBlue;

	int wr,hr,xp,yp;

public:
	void setPosition(const XVector2& position);
	void setPosition(float a,float b);
	void setPositionX(float x);
	void setPositionY(float y);

	void setSize(const XVector2& size);
	void setSize(float a,float b);
	void setSize(float s);
	XVector2 getScale() const
	{
		return XVector2(xsize,ysize);
	}

	XTexture * getTexture();
	XTextureData * getTextureData();
#if IS_USE_SOLIDIFY

	void setIsUseSolidify(int temp);
private:
	int m_glListOrder;
	int m_needSolidify;

#endif
private:
	char m_isInited;
	char m_blendTypeScr;
	char m_blendTypeDst;
public:
	void setBlendType(int typeScr,int typeDst)
	{
		if(typeScr < 0) typeScr = 0;
		if(typeDst < 0) typeDst = 0;
		if(typeScr >= 9 ) typeScr = 8;
		if(typeDst >= 8 ) typeDst = 7;
		m_blendTypeScr = typeScr;
		m_blendTypeDst = typeDst;
	}

private:
	XBlendType m_blendType;
	char m_blendRGBScr;
	char m_blendRGBDst;
	char m_blendAScr;
	char m_blendADst;
public:
	void setBlendType(int rgbScr,int rgbDst,int aScr,int aDst)
	{
		if(rgbScr < 0) rgbScr = 0;
		if(rgbScr >= 9 ) rgbScr = 8;
		if(aScr < 0) aScr = 0;
		if(aScr >= 9 ) aScr = 8;

		if(rgbDst < 0) rgbDst = 0;
		if(rgbDst >= 8 ) rgbDst = 7;
		if(aDst < 0) aDst = 0;
		if(aDst >= 8 ) aDst = 7;
		m_blendRGBScr = rgbScr;
		m_blendRGBDst = rgbDst;
		m_blendAScr = aScr;
		m_blendADst = aDst;
	}
	void setBlendMode(XBlendType mode) {m_blendType = mode;}
	XShaderGLSL *m_pShader;
	void (*m_pShaderProc)(void);
public:
	int init(const char *filename,
		XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE,
		XTransformMode isTransformCenter = POINT_CENTER);

	int init(int tempW = 0,int tempH = 0,int needSizeCheck = 1,XTransformMode isTransformCenter = POINT_CENTER);
	int init(XTextureData& texData,XTransformMode isTransformCenter = POINT_CENTER);
	int init(int w,int h,int colorMode,unsigned int tex,XTransformMode isTransformCenter = POINT_CENTER);

	int release();

	void drawBasic(const GLuint *pTexnum = NULL);
	void drawBasic(const XTextureData *pTexData);

	void draw(const GLuint *pTexnum = NULL);
	void draw(const XTextureData *pTexData);

	void drawEx(const GLuint *pTexnum = NULL);
	void drawEx(const XTextureData *pTexDatam);

	void drawWithoutBlend(const GLuint *pTexnum = NULL);
	void drawWithoutBlend(const XTextureData *pTexDatam);
private:
	void drawInside();
public:
	void setColor(float r,float g,float b,float a);
	void setColor(const XFColor& color);

private:
	int m_isACopy;
	XSprite(const XSprite& temp);

	char m_needAngleClip;
	float m_clipAngle;
	XVector2 m_pointArray[14];
	float m_uPoint[14];
	float m_vPoint[14];
	int m_pointArraySize;
#ifdef GET_ALL_PIXEL
	float m_thisDrawArea;
#endif
	char m_needUpdatePointArray;
	void updatePointArray();
public:
	void setAngleClip(float angle)
	{
		m_needAngleClip = 1;
		m_clipAngle = angle;
		m_needUpdatePointArray = 1;
	}
	void disAngleClip()
	{
		m_needAngleClip = 0;
		m_needUpdatePointArray = 1;
	}
public:
	XSprite& operator = (const XSprite& temp);
	void setACopy(const XSprite& temp);

	void setOverturn(char temp);
	void setLeft2Right();
	void setUp2Down();
	void resetLeftRightUpDown();
	XTurnOverMode getTurnOverMode() const
	{
		return m_turnOverMode;
	}

	XSprite();
	~XSprite();
};
#endif

struct XSpriteParamData
{
	XResourcePosition resourcePosition;
	XVector2 changePoint;
	char * getStrFromData()
	{
		char *tempStr = XMem::createArrayMem<char>(256);
		if(tempStr == NULL) return NULL;
		int offset = 0;
		sprintf(tempStr + offset,"ResPos:%d,\n",resourcePosition);
		offset = strlen(tempStr);
		sprintf(tempStr + offset,"ChaCnt:%f|%f,\n",changePoint.x,changePoint.y);
		offset = strlen(tempStr);
		return tempStr;
	}
	int getDataFromStr(const char * str)
	{
		if(str == NULL) return 0;
		int offset = 0;
		if(sscanf(str + offset,"ResPos:%d,\n",&resourcePosition) != 1) return offset;
		offset += XString::getCharPosition(str + offset,',') + 1;
		if(sscanf(str + offset,"ChaCnt:%f|%f,\n",&changePoint.x,&changePoint.y) != 1) return offset;
		offset += XString::getCharPosition(str + offset,',') + 1;
		return offset;
	}
	XBool getDataFromFile(FILE *fp)
	{
		if(fp == NULL) return XFalse;
		if(fscanf(fp,"ResPos:%d,\n",&resourcePosition) != 1) return XFalse;
		if(fscanf(fp,"ChaCnt:%f|%f,\n",&changePoint.x,&changePoint.y) != 2) return XFalse;
		return XTrue;
	}

	XSpriteParamData()
		:resourcePosition(RESOURCE_SYSTEM_DEFINE)
		,changePoint(0.5f,0.5f)
	{}
};
#if WITH_INLINE_FILE
#include "XSprite.inl"
#endif
}
#endif
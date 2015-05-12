#ifndef _JIA_XIMAGECTRL_
#define _JIA_XIMAGECTRL_

#include "XControlBasic.h"
namespace XE{
class XImageCtrl:public XControlBasic
{
private:
	XBool m_isInited;
	XTextureData m_texture;
	XSprite m_sprite;
	int m_pixelSum;
public:
	XBool init(const char *filename);
	XBool init(int w,int h,XColorMode mode);
	void updateTxt(unsigned char *data)	{m_texture.updateTexture(data);}
	int getWidth() const {return (int)(m_texture.textureMove2.x - m_texture.textureMove.x);}
	int getHeight() const {return (int)(m_texture.textureMove2.y - m_texture.textureMove.y);}
protected:
	void draw();
	void drawUp() {;}

	XBool mouseProc(float,float,XMouseState){return XFalse;}
	XBool keyboardProc(int,XKeyState){return XFalse;}
	void insertChar(const char *,int) {;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float){return XTrue;}
public:
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);
	using XObjectBasic::setScale;
	void setScale(float x,float y);
	XImageCtrl()
		:m_isInited(XFalse)
	{
		m_ctrlType = CTRL_OBJ_IMAGE;
	}
	~XImageCtrl(){release();}
	void release();
	XBool isInRect(float x,float y) {return m_sprite.isInRect(x,y);}
	XVector2 getBox(int order) {return m_sprite.getBox(order);}
	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
};
#if WITH_INLINE_FILE
#include "XImageCtrl.inl"
#endif
}
#endif
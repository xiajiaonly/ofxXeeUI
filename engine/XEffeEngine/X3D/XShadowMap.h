#ifndef _JIA_XSHADOWMAP_
#define _JIA_XSHADOWMAP_

#include "XShaderGLSL.h"
namespace XE{

#define SHADOW_MAP_TEXTURE_SIZE (1024)

class XShadowMap
{
private:
	XBool m_isInited;
	XFBO m_fbo;
public:
	unsigned int getShadowMapTexture(){return m_fbo.getTexture(0);}
	XBool init();
	void updateShadowMap();

	void release();

	XShadowMap()
		:m_isInited(XFalse)
	{}
	~XShadowMap(){release();}
};
}
#endif
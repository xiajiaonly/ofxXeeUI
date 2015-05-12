#ifndef _JIA_XMODELSTL_
#define _JIA_XMODELSTL_

#include "X3DWorld.h"
#include "XShaderGLSL.h"
namespace XE{

class XModelStl:public XBasic3DObject
{
private:
	bool m_isInited;

	unsigned char m_modelName[80];
	int m_faceSum;
	float *m_normalData;
	float *m_vectorData;
	XVBO vbo;
public:
	bool load(const char * filename);
	void draw();
	void release()
	{
		if(!m_isInited) return;
		XMem::XDELETE_ARRAY(m_normalData);
		XMem::XDELETE_ARRAY(m_vectorData);
		vbo.release();
		m_isInited = false;
	}
	XModelStl()
		:m_isInited(false)
		,m_normalData(NULL)
		,m_vectorData(NULL)
	{}
	~XModelStl(){release();}
};
}
#endif
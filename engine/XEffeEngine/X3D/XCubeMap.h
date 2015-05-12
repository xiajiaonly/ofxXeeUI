#ifndef _JIA_XCUBEMAP_
#define _JIA_XCUBEMAP_
#include "XPixelCommon.h"

namespace XE{
class XCubeMap
{
private:
	bool m_isInited;
	unsigned int m_texture;

	bool loadPic(const std::string & name,int index,XResourcePosition resPos);
	void release();
public:
	bool init(const std::string &path,XResourcePosition resPos = RESOURCE_SYSTEM_DEFINE);
	void draw();
	unsigned int getTexture() const {return m_texture;}

	XCubeMap()
		:m_isInited(false)
		,m_texture(0)
	{}
	~XCubeMap(){release();}
};
}
#endif
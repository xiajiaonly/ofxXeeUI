#ifndef _JIA_XCAMERAFACTORY
#define _JIA_XCAMERAFACTORY

#include "XCameraBasic.h"
namespace XE{
class XCameraFactory
{

protected:
	XCameraFactory(){}
	XCameraFactory(const XCameraFactory&);
	XCameraFactory &operator= (const XCameraFactory&);
	virtual ~XCameraFactory(){}
public:
	static XCameraFactory& GetInstance()
	{
		static XCameraFactory m_instance;
		return m_instance;
	}

public:
	template<typename T>
	T * create(XCameraData & data)
	{
		T *pCamera = NULL;
		pCamera = XMem::createMem<T>();
		if(pCamera != NULL)
		{
			if(!pCamera->init(data)) XMem::XDELETE(pCamera);
		}
		return pCamera;
	}
};
}
#endif

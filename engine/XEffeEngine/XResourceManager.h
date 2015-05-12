#ifndef _JIA_XRESOURCEMANAGER_
#define _JIA_XRESOURCEMANAGER_

#include <list>
#include "XBasicFun.h"
#include "XMedia/XSoundCommon.h"
namespace XE{

enum XResourceType
{
	RESOURCE_TYPE_NULL,
	RESOURCE_TYPE_TEXTURE,
	RESOURCE_TYPE_SOUND,
	RESOURCE_TYPE_MUSIC,

	RESOURCE_TYPEXBUTTON_TEX,
	RESOURCE_TYPEXCHECK_TEX,
	RESOURCE_TYPEXEDIT_TEX,
	RESOURCE_TYPEXSLIDER_TEX,
	RESOURCE_TYPEXPROGRESS_TEX,
	RESOURCE_TYPEXMULTILIST_TEX,
	RESOURCE_TYPEXCOMBO_TEX,
	RESOURCE_TYPEXDIRLIST_TEX,
	RESOURCE_TYPEXPASSWORDPAD_TEX,
};
class XResourceTex
{
public:
	unsigned int m_texID;
	int m_width;
	int m_height;
	XResourceTex()
		:m_texID(0)
	{}
	~XResourceTex() {release();}
	void release();
};
class XResourceSound
{
public:
	void *m_handle;
	XResourceSound()
		:m_handle(NULL)
	{}
	~XResourceSound(){release();}
	void release()
	{
		if(m_handle == NULL) return;
		XSoundHandle.clearSound(m_handle);
		m_handle = NULL;
	}
};

class XResourceInfo
{
private:
	XBool m_isInited;
	void release();
public:
	int m_ID;
	char *m_name;
	XResourceType m_type;
	int m_counter;

	void *m_pointer;

	XBool load(XResourcePosition resoursePosition);
	XBool isLoaded() const {return m_isInited;}
	XResourceInfo()
		:m_isInited(XFalse)
		,m_name(NULL)
		,m_pointer(NULL)
		,m_counter(0)
		,m_type(RESOURCE_TYPE_NULL)
	{
		static int index = 0;
		m_ID = index ++;
	}

	XResourceInfo(XResourceInfo &temp)
	{
		m_isInited = temp.m_isInited;
		m_ID = temp.m_ID;
		m_name = temp.m_name;
		m_type = temp.m_type;
		++ m_counter;
		m_pointer = temp.m_pointer;
	}
	~XResourceInfo()
	{
		if(m_counter <= 0) release();
	}
	XResourceInfo &operator= (const XResourceInfo & temp)
	{
		if(this == & temp) return * this;
		m_isInited = temp.m_isInited;
		m_ID = temp.m_ID;
		m_name = temp.m_name;
		m_type = temp.m_type;
		++ m_counter;
		m_pointer = temp.m_pointer;
		return * this;
	}
};

class XResourceManager
{

protected:
	XResourceManager()
		:m_resourceSum(0)
	{}
	XResourceManager(const XResourceManager&);
	XResourceManager &operator= (const XResourceManager&);
	virtual ~XResourceManager(){release();}
public:
	static XResourceManager& GetInstance()
	{
		static XResourceManager m_instance;
		return m_instance;
	}

private:

	std::list<XResourceInfo *> m_resourceBuff;
	int m_resourceSum;
	void release();
private:
	XBool isLoaded(const char * name);
	XResourceInfo * isLoad(const char * name);
public:
	XResourceInfo *loadResource(const char * name,XResourceType type,XResourcePosition resoursePosition);
	XBool releaseResource(const XResourceInfo *p);
	XResourceInfo *copyResource(XResourceInfo *p)
	{
		if(p != NULL) ++ p->m_counter;
		return p;
	}
};

#define XResourceMng XResourceManager::GetInstance()
}
#endif
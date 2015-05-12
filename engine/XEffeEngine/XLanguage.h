#ifndef _JIA_XLANGUAGE_
#define _JIA_XLANGUAGE_
#include "XOSDefine.h"
#include <string>
namespace XE{
enum XLanguage
{
	XLGG_CN,
	XLGG_EN,
};
class XLanguageBasic
{
protected:
	XBool m_isInited;
	XLanguage m_currentLanguage;
	virtual XBool loadFromFile(const std::string &filename) = 0;
	virtual XBool saveToFile(const std::string &filename) = 0;
public:
	virtual XBool init(XLanguage language,const std::string &filename)
	{
		if(!setCurrentLanguage(language,filename)) return XFalse;
		m_isInited = XTrue;
		return XTrue;
	}
	virtual XBool setCurrentLanguage(XLanguage language,const std::string &filename) = 0;
	virtual XLanguage getCurrentLanguage() const {return m_currentLanguage;}

	XLanguageBasic()
		:m_isInited(XFalse)
		,m_currentLanguage(XLGG_CN)
	{}
	virtual ~XLanguageBasic(){}
};
}
#endif
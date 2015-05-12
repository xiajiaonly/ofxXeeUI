#ifndef _JIA_XERRORREPORTER_
#define _JIA_XERRORREPORTER_

#include <string>

#include "XControl\XEdit.h"

namespace XE{
#define ERROR_REPORTER_TXT_FILENAME ("ErrorReport.txt")
#define ERROR_REPORTER_PIC_FILENAME ("ErrorReport.png")
class XErrorReporter
{
protected:
    XErrorReporter()
		:m_isInited(false)
		,m_isBtnChecked(false)
		,m_needShow(false)
		,m_isMainThreadProc(false)
	{}
    XErrorReporter(const XErrorReporter&);
	XErrorReporter &operator= (const XErrorReporter&);
    virtual ~XErrorReporter(){}
public:
    static XErrorReporter& GetInstance()
	{
		static XErrorReporter m_instance;
		return m_instance;
	}
private:
	bool m_isInited;
	bool m_isBtnChecked;
	bool m_needShow;
	bool m_isMainThreadProc;

	XSprite m_screenShot;
	XSprite m_background;
	XButton m_button;
	XFontUnicode m_font;
	XFontUnicode m_fontDescrip;
	XEdit m_edit;
	bool reportFile(const std::string &errorDescription,const std::string &filename,int line,const std::string &funName);
	int inputEvent();
	static void ctrlProc(void *,int,int);

	std::string m_errDescription;
	std::string m_errFilename;
	std::string m_errFunname;
	int m_errLine;
public:
	bool init(XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void draw();

	void reportError(const std::string & errorDescription,const std::string &filename,int line,const std::string &funName);
	void errorProc();
	bool isErrored()const{return m_needShow;}
	void setMainProc(){m_isMainThreadProc = true;}
	bool getIsMainProc()const{return m_isMainThreadProc;}
};
inline void reportError(const std::string & errorDescription,const std::string &filename,int line,const std::string &funName)
{
	XErrorReporter::GetInstance().reportError(errorDescription,filename,line,funName);
}
#define REPORT_ERROR(p) reportError(p,__FILE__,__LINE__,__FUNCDNAME__)
}
#endif
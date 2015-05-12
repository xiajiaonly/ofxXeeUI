#ifndef _JIA_XSTRING_
#define _JIA_XSTRING_

namespace XE{

class XSunday
{
private:
	static const int m_maxCharsSum = 256;
	XBool m_isInited;
	int *m_shift;
	int m_pattSize;
	char * m_patt;
public:
	XBool init(const char *patt);
	XBool search(const char *text,int &position);
	XSunday()
		:m_isInited(XTrue)
		,m_patt(NULL)
	{
		m_shift = XMem::createArrayMem<int>(m_maxCharsSum);
	}
	~XSunday();
};
namespace XString
{

	extern XBool sundaySearch(const char *text,const char *patt,int &position);

	extern XBool kmpSearch(const char *text,const char *m,int &pos);
}
}
#endif
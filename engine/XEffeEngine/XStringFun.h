#ifndef _JIA_XSTRINGFUN_
#define _JIA_XSTRINGFUN_

#include "XOSDefine.h"
#include <string>
namespace XE{
enum XStringCodeType
{
	STR_TYPE_ANSI,
	STR_TYPE_UTF8,
	STR_TYPE_UTF16,
	STR_TYPE_UNKNOWN,
};

namespace XString
{
	extern XBool getIsNumber(const char * p);
	extern XBool getIsUnsignedInt(const char * p);
	extern XBool getIsInt(const char * p);
	extern XBool getIsValidIp(const char *p);
	extern XBool getIsLocalhost(const char *p);
	extern int getIsHexNumber(const char * p);
	extern int getCharSum(const char *p,char temp);
	extern int getCharPosition(const char *p,char temp,int mode = 0);
	extern int getCharPositionEx(const char *p,char temp,int index,int mode = 0);
	extern XBool getFirstWord(const char *p,int &s,int &e);
	extern XBool getFirtCanShowString(const char *p,int &s,int &e);

	extern std::string getCanShowString(const char *str,int canShowLen);

	extern int getANSIStrPosLen(const char * str,int index);

	inline std::string getCanShowString(const char *str,int len,int charWidth)
	{
		if(charWidth <= 0) return "";
		return getCanShowString(str,len / charWidth);
	}

	extern XBool isAtUnicodeEnd(const char *p,int pos);

	inline int hexCharToInt(char p);

	inline XBool hexToBin(const char *in,unsigned char *out);
	inline XBool binToHex(const char *in,unsigned char *out);

	inline std::string intToStr(int temp,int radix = 16);

	inline std::string floatToStr(float temp,int len = 6);
	extern std::string getTextFromClipboard();
	extern void setTextToClipboard(const std::string & str);

	extern int strToInt(const std::string &temp,int radix = 10);

	extern char* ANSIToUTF8(const char* src);
	extern std::string ANSI2UTF8(const char * src);
	extern char* UTF8ToANSI(const char* src);
	extern std::string UTF82ANSI(const char * src);
	extern wchar_t* ANSIToWchar(const char* src);
	extern char* WcharToANSI(const wchar_t* src);
	inline std::string Wchar2ANSI(const wchar_t* src);
	inline wchar_t oneCharToWchar(const char* src);
	extern bool isUTF8(const char * str,int length);
	inline bool isUTF8(const std::string &str){return isUTF8(str.c_str(),str.size());}
	extern bool isUTF16(const char * str,int length);
	extern bool isANSI(const char * str,int length);

	extern XStringCodeType getStrCodeType(const char * str,int length);

	template <typename T>
	std::string toString(const T& value)
	{
		std::ostringstream out;

		out << value;
		return out.str();
	}

	template <typename T>
	const T toValue(const std::string& str)
	{
		T val;
		std::stringstream ss;
		ss << str;
		ss >> val;
		if(ss.fail())
				throw std::runtime_error((std::string)typeid(T).name() + "type wanted:" + str);
		return val;
	}

	extern int getStrLen(const char * p);
}

namespace XEE
{

	inline XBool getCapsLockState(){return (GetKeyState(VK_CAPITAL) == 1);}
	inline XBool getNumLockState(){return (GetKeyState(VK_NUMLOCK) == 1);}

	inline void setCapsLockState(XBool state);
	inline void setNumLockState(XBool state);
}

}
#endif
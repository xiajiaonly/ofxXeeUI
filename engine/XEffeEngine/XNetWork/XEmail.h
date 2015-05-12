#ifndef _JIA_XEMAIL_
#define _JIA_XEMAIL_

#include <iostream>
#include <String.h>
#include <fstream>
#include <string>
#include "XBasicFun.h"
#include "XBasicClass.h"
#include <List>
#include <vector>
namespace XE{

struct sMailInfo
{
	std::string m_pcUserName;
	std::string m_pcUserPassWord;
	std::string m_pcSenderName;
	std::string m_pcSender;
	std::string m_pcReceiver;
	std::string m_pcReceiverName;
	std::string m_pcTitle;
	std::string m_pcBody;
	std::string m_pcIPAddr;
	std::string m_pcIPName;
	sMailInfo()
		:m_pcUserName("")
		,m_pcUserPassWord("")
		,m_pcSenderName("")
		,m_pcSender("")
		,m_pcReceiver("")
		,m_pcReceiverName("")
		,m_pcTitle("")
		,m_pcBody("")
		,m_pcIPAddr("")
		,m_pcIPName("")
	{}
};
class XEmailSender
{
public:
    XEmailSender()
		:m_pcFileBuff(NULL)
	{
		memset(m_cSendBuff,0,sizeof(m_cSendBuff));
		memset(m_cReceiveBuff,0,sizeof(m_cReceiveBuff));
	}
	~XEmailSender(){DeleteAllPath();}
public:
    bool SendMail(sMailInfo &smailInfo);
    void AddFilePath(char * pcFilePath);
    void DeleteFilePath(char* pcFilePath);
	void DeleteAllPath(){m_pcFilePathList.clear();}
protected:
    void Char2Base64(char* pBuff64,char* pSrcBuff,int iLen);
    bool CReateSocket(SOCKET &sock);
    bool Logon(SOCKET &sock);
    int GetFileData(const char* FilePath);

    bool SendHead(SOCKET &sock);
    bool SendTextBody(SOCKET &sock)
	{
		memset(m_cSendBuff,0,sizeof(m_cSendBuff));
		sprintf_s(m_cSendBuff,"--INVT\r\nContent-Type: text/plain;\r\n  charset=\"gb2312\"\r\n\r\n%s\r\n\r\n",m_sMailInfo.m_pcBody.c_str());
		return (send(sock,m_cSendBuff,strlen(m_cSendBuff),0) == strlen(m_cSendBuff));
	}
    bool SendFileBody(SOCKET &sock);
    bool SendEnd(SOCKET &sock);
protected:

	std::vector<std::string> m_pcFilePathList;

    char m_cSendBuff[4096];
    char m_cReceiveBuff[1024];
    char* m_pcFileBuff;
    sMailInfo m_sMailInfo;
};
#include "XEmail.inl"
}
#endif
#ifndef _JIA_XFTPSERVER_
#define _JIA_XFTPSERVER_

#include "XFtpCommon.h"
namespace XE{

enum XFtpTransnationType
{
	FTP_TRANSNAION_TYPE_ASCII,
	FTP_TRANSNAION_TYPE_BIN,
};
struct XFtpClientSockInfo
{
	void * pClass;
	int clientSock;
	int clientDataSock;
	sockaddr_in clientAddr;
	XFtpTransnationType transnatType;
	char curPath[MAX_FILE_NAME_LENGTH];

	XFtpClientSockInfo()
		:pClass(NULL)
		,transnatType(FTP_TRANSNAION_TYPE_ASCII)
	{
		curPath[0] = '/';
		curPath[1] = '\0';
	}
};
class XFtpServer
{
private:
	XBool m_isCreated;
	int m_serverSock;
	int m_clientSum;
	int m_allClientSum;
	WSADATA m_wsaData;

	XBool sendData(int clientSock,const char * data,int len)
	{

		if(data == NULL || len <= 0) return XFalse;
		int ret = send(clientSock,data,len,0);
		if(ret < 0) return XFalse;
		return XTrue;
	}
	XBool recvData(int clientSock,char * p)
	{

		if(p == NULL) return XFalse;
		int ret = recv(clientSock,p,RECV_BUFF_SIZE,0);
		if(ret < 0) return XFalse;
		p[ret] = '\0';
		printf("%s",p);
		return XTrue;
	}
	XFtpUserType clientLoginProc(int clientSock);
	pthread_t m_serverCMDThread;
	pthread_t m_serverAcceptThread;
#ifdef XEE_OS_WINDOWS
    static DWORD WINAPI serverCMDThread(void * pParam);
	static DWORD WINAPI serverAcceptThread(void * pParam);
	static DWORD WINAPI serverRequestThread(void * pParam);
#endif
public:
	XBool createServer();
	void close()
	{
		if(!m_isCreated) return;

		m_isCreated = XFalse;
	}
	XFtpServer()
		:m_isCreated(XFalse)
		,m_clientSum(0)
		,m_allClientSum(0)
	{}
	~XFtpServer(){close();}
};
}
#endif
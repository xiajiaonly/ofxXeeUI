#ifndef _JIA_XFTPCLIENT_
#define _JIA_XFTPCLIENT_

#include "XFtpCommon.h"
namespace XE{
class XFtpClient
{
private:
	XBool m_isConnect;
	WSADATA m_wsaData;
	SOCKET m_cmdsocket;
	int m_retCode;
	char m_commandBuff[RECV_BUFF_SIZE + 1];

	XBool recvRetCode()
	{
		int ret = recv(m_cmdsocket,m_commandBuff,RECV_BUFF_SIZE,0);
		if(ret == SOCKET_ERROR || ret == 0)
		{
			LogStr("Recv error!");
			return XFalse;
		}
		m_commandBuff[ret] = '\0';
		LogNull("%s",m_commandBuff);
		if(!getRetCode(m_commandBuff,ret)) return XFalse;
		return XTrue;
	}
	XBool getRetCode(const char *buf,int len)
	{
		if(len > 4 && buf[0] >= '0' && buf[0] <= '9'
			&& buf[1] >= '0' && buf[1] <= '9'
			&& buf[2] >= '0' && buf[2] <= '9'
			&& buf[3] == ' ')
		{
			m_retCode = (buf[0] - '0') * 100 + (buf[1] - '0') * 10 + (buf[2] - '0');
			return XTrue;
		}
		return XFalse;
	}
	XBool sendCommand(const char * cmd)
	{
		LogNull("%s",cmd);
		if(send(m_cmdsocket,cmd,strlen(cmd),0) == SOCKET_ERROR) return XFalse;
		return recvRetCode();
	}
public:
	XBool connectServer(const char * serverIP,int port = FTP_SOCKET_PORT);
	XBool sendClose()
	{
		if(!m_isConnect) return XFalse;
		if(!sendCommand("QUIT\r\n")) return XFalse;
		closesocket(m_cmdsocket);
		m_isConnect = XFalse;
		if(m_retCode != 221) return XFalse;
		return XTrue;
	}

	XBool sendUserName(const char * userName)
	{
		if(userName == NULL) return XFalse;
		if(!m_isConnect) return XFalse;
		strcpy(m_commandBuff,"USER ");
		strcat(m_commandBuff,userName);
		strcat(m_commandBuff,"\r\n");
		if(!sendCommand(m_commandBuff)) return XFalse;
		if(m_retCode != 331) return XFalse;
		return XTrue;
	}
	XBool sendPassword(const char * password)
	{
		if(password == NULL) return XFalse;
		if(!m_isConnect) return XFalse;
		strcpy(m_commandBuff,"PASS ");
		strcat(m_commandBuff,password);
		strcat(m_commandBuff,"\r\n");
		if(!sendCommand(m_commandBuff)) return XFalse;
		if(m_retCode != 230) return XFalse;
		return XTrue;
	}
	XBool setPort(SOCKET &listenSock);
	XBool setPasv(SOCKET &listenSock);
	XBool sendFileList();
	XBool sendDeleteFile(const char *filename)
	{
		if(!m_isConnect) return XFalse;
		if(filename == NULL) return XFalse;
		strcpy(m_commandBuff,"DELE ");
		strcat(m_commandBuff,filename);
		strcat(m_commandBuff,"\r\n");
		if(!sendCommand(m_commandBuff)) return XFalse;
		if(m_retCode != 250) return XFalse;
		return XTrue;
	}
	XBool sendDownloadFile(const char *filename);
	XBool sendUpdateFile(const char *filename);
	XBool sendUpdateFile(const char *inFilename,const char *outFilename);
	XBool sendChangeDirectory(const char *dir)
	{
		if(!m_isConnect) return XFalse;
		if(dir == NULL) return XFalse;
		strcpy(m_commandBuff,"CWD ");
		strcat(m_commandBuff,dir);
		strcat(m_commandBuff,"\r\n");
		if(!sendCommand(m_commandBuff)) return XFalse;
		if(m_retCode != 250) return XFalse;
		if(!sendCommand("PWD\r\n")) return XFalse;
		if(m_retCode != 257) return XFalse;
		return XTrue;
	}
	int sendGetFileSize(const char *filename)
	{
		if(!m_isConnect) return -1;
		if(filename == NULL) return -1;
		strcpy(m_commandBuff,"SIZE ");
		strcat(m_commandBuff,filename);
		strcat(m_commandBuff,"\r\n");
		if(!sendCommand(m_commandBuff)) return -1;
		if(m_retCode != 213) return -1;
		int size = -1;
		if(sscanf(m_commandBuff,"213 %d",&size) != 1) return -1;
		return size;
	}

	XFtpClient()
		:m_isConnect(XFalse)
	{}
};
}
#endif
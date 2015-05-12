#ifndef _JIA_XNETSERVER_
#define _JIA_XNETSERVER_

#include "XNetCommon.h"
namespace XE{
class XNetServer
{
private:
	WSADATA m_wsaData;

	SOCKET m_netSocket;
	SOCKET m_serverSocket;

	XCritical m_mutex;

	XConnectState m_connectState;
	XBool m_isExit;
	XNetData * m_recvPacket;
	std::deque<XNetData *> m_recvDataBuff;
	std::deque<XNetData *> m_sendDataBuff;
	pthread_t m_recvThread;
	pthread_t m_sendThread;
	pthread_t m_acceptThread;
	pthread_t m_boardcastThread;
	static DWORD WINAPI recvThread(void * pParam);
	static DWORD WINAPI sendThread(void * pParam);
	static DWORD WINAPI acceptThread(void * pParam);
	static DWORD WINAPI boardcastThread(void * pParam);

	int m_recvPacketSize;
	unsigned char m_packetHeadData[PACKET_HEAD_LEN];
	XBool getDataPacket(unsigned char *buff,int len);
	XBool sendDataSocket(char * data,int len);

	XBool m_autoIPMode;
	int m_serverPort;
	char m_projectStr[PROJECT_STRING_LEN];
public:
	XBool createServer(int port = NET_SERVER_PORT,XBool autoIP = XFalse);
	XBool setProjectStr(const char * str)
	{
		if(str == NULL ||
			strlen(str) >= PROJECT_STRING_LEN) return XFalse;
		strcpy(m_projectStr,str);
		return XTrue;
	}
	XBool sendData(XNetData *data)
	{
		if(data == NULL) return XFalse;
		m_mutex.Lock();
		m_sendDataBuff.push_back(data);
		m_mutex.Unlock();
		return XTrue;
	}
	void clearSendData(XNetDataType type)
	{
		m_mutex.Lock();
		std::deque<XNetData *>::iterator it = m_sendDataBuff.begin();
		for(;it != m_sendDataBuff.end();it ++)
		{
			if((* it)->type == type) (* it)->isEnable = XFalse;
		}
		m_mutex.Unlock();
	}
	XNetData *getData()
	{
		if(m_recvDataBuff.size() <= 0) return NULL;
		m_mutex.Lock();
		if(m_recvDataBuff.front()->isEnable)
		{
			XNetData * ret = m_recvDataBuff.front();
			m_recvDataBuff.pop_front();
			m_mutex.Unlock();
			return ret;
		}else
		{
			m_mutex.Unlock();
			return NULL;
		}
	}
	XConnectState getConnectState() const {return m_connectState;}
	void release();
	XNetServer()
		:m_connectState(CONNECT_STATE_DISCONNECT)
	{
		m_recvDataBuff.clear();
		setProjectStr(DEFAULT_PROJECT_STR);
	}
	~XNetServer()
	{
		release();
	}
};
}
#endif
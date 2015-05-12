#ifndef _JIA_XNETCLIENT_
#define _JIA_XNETCLIENT_

#include "XNetCommon.h"
namespace XE{

class XNetClient
{
private:

	SOCKET m_netSocket;

	XCritical m_mutexThread;
	XCritical m_mutexSend;
	XCritical m_mutexRecv;
	XCritical m_mutexBoardCast;

	XConnectState m_connectState;
	XNetData * m_recvPacket;
	std::deque<XNetData *> m_recvDataBuff;
	std::deque<XNetData *> m_sendDataBuff;
	pthread_t m_recvThread;
	pthread_t m_sendThread;
	pthread_t m_boardcastThread;
	static DWORD WINAPI recvThread(void * pParam);
	static DWORD WINAPI sendThread(void * pParam);
	static DWORD WINAPI boardcastThread(void * pParam);

private:
	pthread_t m_connectThread;
	static DWORD WINAPI connectThread(void * pParam);
	XBool m_isClientCreated;
	int m_threadSum;
	XBool m_useBroadcast;
	std::string m_serverIP;
public:
	XBool createClient(XBool useBroadcast = XTrue,const char *ip = NULL,int port = 0);
	void (*m_connectBrokenFun)();
	void (*m_connectFun)();

private:
	int m_recvPacketSize;
	unsigned char m_packetHeadData[PACKET_HEAD_LEN];
	XBool getDataPacket(unsigned char *buff,int len);
	XBool sendDataSocket(char * data,int len);

	sockaddr_in m_serverAddr;
	int m_serverPort;
	char m_projectStr[PROJECT_STRING_LEN];
	XBool m_boardcastThreadState;

	XBool sendBoardcast();
	XBool m_isExit;
public:
	XBool connectToServer(const char *ip,int port = NET_SERVER_PORT);
	XBool connectToServer();
	XBool getIsConnect() const{return m_connectState == CONNECT_STATE_CONNECT;}
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
		m_mutexSend.Lock();
		m_sendDataBuff.push_back(data);
		m_mutexSend.Unlock();
		return XTrue;
	}
	void clearSendData(XNetDataType type)
	{
		m_mutexSend.Lock();
		std::deque<XNetData *>::iterator it = m_sendDataBuff.begin();
		for(;it != m_sendDataBuff.end();it ++)
		{
			if((* it)->type == type) (* it)->isEnable = XFalse;
		}
		m_mutexSend.Unlock();
	}
	XNetData *getData()
	{
		if(m_recvDataBuff.size() <= 0) return NULL;
		m_mutexRecv.Lock();
		if(m_recvDataBuff.front()->isEnable)
		{
			XNetData * ret = m_recvDataBuff.front();
			m_recvDataBuff.pop_front();
			m_mutexRecv.Unlock();
			return ret;
		}else
		{
			m_mutexRecv.Unlock();
			return NULL;
		}
	}
	XConnectState getConnectState() const {return m_connectState;}
	void release();
	XNetClient()
		:m_connectState(CONNECT_STATE_DISCONNECT)

		,m_netSocket(0)
		,m_boardcastThreadState(XFalse)
		,m_isExit(XFalse)
		,m_connectBrokenFun(NULL)
		,m_connectFun(NULL)
		,m_isClientCreated(XFalse)
		,m_threadSum(0)
	{
		m_recvDataBuff.clear();
		setProjectStr(DEFAULT_PROJECT_STR);
	}
	~XNetClient(){release();}
};
}
#endif
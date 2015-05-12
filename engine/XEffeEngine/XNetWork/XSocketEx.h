#ifndef _JIA_XSOCKETEX_
#define _JIA_XSOCKETEX_

#include "XOSDefine.h"
#include <string>
#include <vector>
#include <deque>
#include "XCritical.h"
#include "XThread.h"
#include "XNetWork/XNetCommon.h"

namespace XE{

enum XSocketConnectState
{
	CON_STATE_NULL,
	CON_STATE_NORMAL,
	CON_STATE_UNSTABLE,
	CON_STATE_ERROR,
};
enum XSocketNetRole
{
	NET_NULL,
	NET_SERVER,
	NET_CLIENT,
};
enum XSocketMode
{
	SOCKET_LAN,
	SOCKET_WAN,
};
enum XSocketWorkMode
{
	SOCKET_WORK_MODE_IP,
	SOCKET_WORK_MODE_NAME,
};
enum XSocketSysDataType
{
	SYS_DATA_TYPE_SETNAME,
	SYS_DATA_TYPE_SETID,
	SYS_DATA_TYPE_UPDATEINIFO,
	SYS_DATA_TYPE_HEARTBEAT,
};
enum XSocketExDataType
{
	SOCKET_DATA_TYPE_SYSTEM,
	SOCKET_DATA_TYPE_CUSTOM,
};
#define SOCKET_PACKET_HEAD_SIZE (16)
#define DEFAULT_CLIENT_NAME ("xiajia_1981@163.com")
#pragma pack(push)
#pragma pack(1)
struct XSocketDataPack
{
	int fromID;
	int toID;
	XSocketExDataType dataType;
	int dataLen;
	unsigned char * data;
	XSocketDataPack()
		:data(NULL)
		,dataType(SOCKET_DATA_TYPE_CUSTOM)
	{}
};
#pragma pack(pop)
enum XSocketClientState
{
	CLIENT_STATE_ONLINE,
	CLIENT_STATE_OFFLINE,
};
#define SOCKET_INFO_HEAD_SIZE (16)
struct XSocketUserInfo
{
	int userID;
	int userSocket;
	XSocketClientState userState;
	int userNameLen;
	char *userName;
	XSocketUserInfo()
		:userName(NULL)
		,userNameLen(0)
	{}
};
enum XSocketClinetState
{
	CLINET_STATE_UNCONNECT,
	CLINET_STATE_CONNECT,
	CLINET_STATE_DISCONNECT,
};
struct XSocketRecvPacket
{
	int recvDataLen;
	unsigned char headData[SOCKET_PACKET_HEAD_SIZE];
	XSocketDataPack *dataPacket;
	XSocketRecvPacket()
		:recvDataLen(0)
		,dataPacket(NULL)
	{}
};
struct XSocketUserData
{
	bool isEnable;
	int userID;
	int userSocket;
	XSocketClinetState state;
	int heartbeatTimer;

	XSocketRecvPacket recvPacket;
	XThreadState recvThreadState;

	XSocketUserData()
		:isEnable(false)
		,state(CLINET_STATE_UNCONNECT)
		,heartbeatTimer(0)
		,recvThreadState(STATE_BEFORE_START)
	{}
};

class XSocketEx
{
private:
	bool m_isInited;
	bool m_clientStateChange;
	SOCKET m_netSocket;
	XSocketNetRole m_socketRole;
	int m_timer;

	XSocketConnectState m_conState;
	XSocketRecvPacket m_recvPacket;

	int m_curAddClientID;
	void addAClient(int clientSocket);
	int m_myID;
	int m_IDIndex;

	XCritical m_recvMutex;
	std::deque<XSocketDataPack *> m_recvDeque;
	XCritical m_sendMutex;
	std::deque<XSocketDataPack *> m_sendDeque;
	XCritical m_userInfoMutex;
	std::vector<XSocketUserInfo *> m_usersInfo;

	std::vector<XSocketUserData *> m_usersData;

	XSocketWorkMode m_workMode;

	sockaddr_in m_serverAddr;
	std::string m_serverName;
	std::string m_serverIP;
	int m_serverPort;
	std::string m_myName;

	bool getDataPacket(XSocketRecvPacket &packet,unsigned char *buff,int len);

	XThreadState m_connectThreadState;
	XThreadState m_recvThreadState;
	XThreadState m_sendThreadState;
	XThreadState m_acceptThreadState;
	HANDLE m_acceptThreadHandle;
	XThreadState m_boardcastThreadState;
#ifdef XEE_OS_WINDOWS
    static DWORD WINAPI connectThread(void * pParam);
	static DWORD WINAPI recvThread(void * pParam);
	static DWORD WINAPI sendThread(void * pParam);
	static DWORD WINAPI acceptThread(void * pParam);
	static DWORD WINAPI recvThreadX(void * pParam);
	static DWORD WINAPI boardcastThread(void * pParam);
#endif
	bool connectToNet();

	bool connectToServer();
	bool createServer();
	void sendClientInfo();
	void systemDataproc(const XSocketDataPack *data);
	void lockData(unsigned char *data,int len);
	void unlockData(unsigned char *data,int len);
	bool sendAData(XSocketDataPack * data);
	void requestRename();
	void sendHeartbeat();
	void setOffline(int id);
	void heartbeatProc(int stepTime);
	bool sendBoardcast();
public:
	bool createNetWorkByName(const char *serverName,int port);
	bool createNetWorkByIP(const char *serverIP,int port);

	bool sendAData(int toID,const unsigned char * data,int len);
	bool sendToAll(unsigned char * data,int len);

	XSocketDataPack *popAData();
	void deleteAData(XSocketDataPack * p);
	bool haveRecvData() const {return m_recvDeque.size() > 0;}
	int getRecvDataSum() const {return m_recvDeque.size();}

	void release();
	XSocketEx()
		:m_isInited(false)
		,m_socketRole(NET_NULL)
		,m_conState(CON_STATE_NULL)
		,m_workMode(SOCKET_WORK_MODE_IP)
		,m_netSocket(INVALID_SOCKET)
		,m_curAddClientID(-1)
		,m_IDIndex(0)
		,m_myID(0)
		,m_myName(DEFAULT_CLIENT_NAME)
		,m_timer(0)
		,m_clientStateChange(false)
		,m_connectThreadState(STATE_BEFORE_START)
		,m_recvThreadState(STATE_BEFORE_START)
		,m_sendThreadState(STATE_BEFORE_START)
		,m_acceptThreadState(STATE_BEFORE_START)
		,m_boardcastThreadState(STATE_BEFORE_START)
		,m_acceptThreadHandle(0)
	{}
	~XSocketEx() {release();}

	int getClientSum() {return m_usersInfo.size();}
	const XSocketUserInfo * getUserInfo(unsigned int index);
	void setAsClient();
	void setAsServer();
	XSocketNetRole getRole() const {return m_socketRole;}
	int getMyID() const {return m_myID;}
	int getMySocket() const {return m_netSocket;}
	bool setMyName(const std::string &myName);
	std::string getMyName()const {return m_myName;}
	XSocketConnectState getConState() const {return m_conState;}
	int getSendBuffSize()
	{
		m_sendMutex.Lock();
		int ret = m_sendDeque.size();
		m_sendMutex.Unlock();
		return ret;
	}
};
#if WITH_INLINE_FILE
#include "XSocketEx.inl"
#endif
}
#endif
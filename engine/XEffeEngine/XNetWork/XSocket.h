#ifndef _JIA_XSOCKET_
#define _JIA_XSOCKET_

#include "XOSDefine.h"

#pragma comment(lib, "ws2_32.lib")

#ifdef XEE_OS_WINDOWS
#include "winsock.h"
#endif

#include "stdio.h"
#include "stdlib.h"
#include "XBasicFun.h"

#ifdef XEE_OS_LINUX
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#endif

#include "XBasicClass.h"
namespace XE{

class XSocket;

#ifdef DEBUG_MODE
#define DSHOW printf

inline void addLogText(XSocket *p,char *pCN,char *pEN)
{
#ifdef DEBUG_FOR_CN

#ifdef DEBUG_MODE_SHOW
        DSHOW("%s",pCN);
#endif
#else

#ifdef DEBUG_MODE_SHOW
	DSHOW("%s",pEN);
#endif
#endif
}
#else
#define DSHOW (void)
#define addLogText (void)
#endif

#define MAX_CLIENT            (2048)
#define MAX_DELAY_TIMES        (10)
#define MAX_NET_FLAGS        (20)
#define MAX_DATABUFF_DEEP    (500)
#define DATA_HEAD_SIZE        (15)
#define BC_DATA_SIZE        (1024)
#define BC_BUFF_DEEP        (128)

#define SERVER_PORT       (8019)

enum XSocketDataType
{
    DATA_TYPE_NULL = 0,
    DATA_TYPE_MUTUAL,
    DATA_TYPE_USER_DATA,
    DATA_TYPE_BOARDCAST_DATA,
    DATA_TYPE_SERVER_STATE
};

#pragma pack(push)
#pragma pack(1)
struct XSocketData
{
    char dataType;
    int sourceSocket;
    int targetSocket;
    int dataLength;
    char lockKey;
    char checkKey;
    char *pData;
    XSocketData()
        :dataType(DATA_TYPE_NULL)
        ,sourceSocket(0)
        ,targetSocket(0)
        ,dataLength(0)
        ,lockKey(0)
        ,checkKey(0)
        ,pData(NULL)
    {}

    ~XSocketData()
    {

    }

};
#pragma pack(pop)

enum
{
    ERROR_TYPE_NULL = 0,
    ERROR_TYPE_SERVER_SOCKET_APPLY = 10000,
    ERROR_TYPE_SERVER_SOCKET_BIND,
    ERROR_TYPE_SERVER_SOCKET_LISTEN,
    ERROR_TYPE_ACCEPT_CLIENT,
    ERROR_TYPE_THREAD_ACCEPT_CREATE,
    ERROR_TYPE_CLIENT_SOCKET_APPLY,
    ERROR_TYPE_CLIENT_SOCKET_BIND,
    ERROR_TYPE_THREAD_BROADCAST_CREATE,
    ERROR_TYPE_CLIENT_S_SOCKET_APPLY,
    ERROR_TYPE_THREAD_GETBROADCAST_CREATE_N,
    ERROR_TYPE_THREAD_GETDATA_CREATE_N,
    ERROR_TYPE_THREAD_MUNUAL_CREATE,
    ERROR_TYPE_THREAD_MUNUAL_CREATE_N,
    ERROR_TYPE_THREAD_CLIENT_GETDATA_CREATE,
    ERROR_TYPE_CLIENT_CONNECT_SERVER
};
enum
{
    NET_STATE_NULL = 0,
    NET_STATE_SERVER,
    NET_STATE_CLIENT
};
enum
{
    BROADCAST_DATA_TYPE_NULL = 0,
    BROADCAST_DATA_TYPE_SERVER_INFO,
    BROADCAST_DATA_TYPE_CLIENT_DATA
};
enum
{
    BROADCAST_WAY_TCPIP,
    BROADCAST_WAY_UDP
};
class XSocket
{

private:

    int m_isServer;
    int m_myConnectState;

    char *m_clientConnectState;
    int m_myDelayTimes;

    char *m_clientDelayTimes;

    XBool m_needMutual;

    int m_serverExitFlag;
    int m_clientExitFlag;

    XBool dataProtectionFlag;

    int m_mySocket;
    int m_serverSocket;
    int m_serverPort;

    int *m_clientSocket;
    int m_clientSum;

    int m_serverID;
    int m_clientID;

    pthread_t m_serverAcceptThreadP;
    pthread_t m_serverBroadcastThreadP;
    pthread_t m_mutualThreadP;
    pthread_t m_getDataThreadPOnClient;
    pthread_t m_clientGetBroadcastThreadP;

    pthread_t m_getDataThreadPOnServer;
    int m_flagClientThreadID;

    char *m_netFlags;

    XSocketData *m_getDataBuff;
    int m_getDataNewP;
    int m_getDataOldP;
    int pushAMessage(XSocketData tempData);
    int popAMessage(XSocketData *tempData);

    void clearDataBuff();
    pthread_mutex_t m_mutex;

    int m_WrongFlag;

    int m_broadCastWay;

    XSocketData *m_broadcastBuff;
    int m_broadcastNewPoint;
    int m_broadcastOldPoint;
    int pushABroadcastMessage(XSocketData tempData);
public:
    void setBroadCastWay(int temp);

public:
    void setDataProtection(XBool temp);
    void disNeedMutual();
    int getClientSum() const;
    int getMyDelay() const;
    int getWrongFlag() const;
    int getIsServer() const;

    int getClientID(int order) const;
    int getIsOnline() const;

private:

    void addAClient(int clientSocket);
    int getAMessageServer(XSocketData tempData,int clientID);
    int getAMessageClient(XSocketData tempData);
    void broadcastDataByTcpIP(XSocketData tempData);

private:
    int getDataCheckKey(int length,char *data) const;
    void dataLockProc(int length,char *data,char lockKey);
    int dataUnlockProc(int length,char *data,char lockKey);
    void dataBale(XSocketData *temp);
    int dataRelieve(XSocketData *temp);

#ifdef XEE_OS_WINDOWS
    static DWORD WINAPI acceptThread(void * pParam);
    static DWORD WINAPI broadcastThread(void * pParam);
    static DWORD WINAPI searchNetThread(void * pParam);
    static DWORD WINAPI mutualThread(void * pParam);
    static DWORD WINAPI getDataThreadOnClient(void * pParam);

    static DWORD WINAPI getDataThreadOnServer(void * pParam);
#endif

#ifdef XEE_OS_LINUX
    static void *acceptThread(void * pParam);
    static void *broadcastThread(void * pParam);
    static void *searchNetThread(void * pParam);
    static void *mutualThread(void * pParam);

    static void *getDataThreadOnClient(void * pParam);
    static void *getDataThreadOnServer(void * pParam);
#endif

    void resetSocketAddr(int socket);

    int createServer(int port);
    void distroyServer();
    int createClient();
    void distroyClient();
    int connectToServer(sockaddr_in serverAddr);

    void setHostID(const char *p);

    int searchNet(const char *p);
    int searchNet();

    void sendServerState();

    void dropNetProc(int clientID = 0);

    int recvDataProc(int sock,XSocketData *temp_data);
    int recvDataFunction(int sock,char *temp_data,int length);
    int sendDataFunction(int sock,XSocketData temp_data,int length);

public:
    int connectToNet(int port,const char *serverID);

    int xCreateServer(const char *serverIP,int port);
    int xCreateClient(const char *serverIP,int serverPort);

    int sendDataToNet(int clientOrder,char *p,int length);
    int getDataFromNet(int *clientOrder,int *clientID,char **p,int *length);

    void disconnect();

    int isRecvBuffEmpty() const;
    int isSendBuffEmptyBC() const;

    XSocket();
    ~XSocket();
};

inline void XSocket::setBroadCastWay(int temp)
{
    if(temp != BROADCAST_WAY_TCPIP)
    {
        m_broadCastWay = BROADCAST_WAY_UDP;
    }else
    {
        m_broadCastWay = BROADCAST_WAY_TCPIP;
    }
}
inline int XSocket::getClientSum() const
{
    return m_clientSum;
}
inline int XSocket::getMyDelay() const
{
    return m_myDelayTimes;
}
inline int XSocket::getWrongFlag() const
{
    return m_WrongFlag;
}
inline int XSocket::getIsServer() const
{
    return m_isServer;
}
inline int XSocket::getClientID(int order) const
{
    if(m_clientSum <= 0) return 0;
    if(order < 0 || order >= MAX_CLIENT) return 0;
    return m_clientSocket[order];
}
inline int XSocket::getIsOnline() const
{
    if(m_isServer == NET_STATE_SERVER && m_serverExitFlag == 1) return 0;
    if(m_isServer == NET_STATE_CLIENT && m_clientExitFlag == 1) return 0;
    return 1;
}
inline void XSocket::resetSocketAddr(int socket)
{
    int opt = 1;
    int len = sizeof(opt);
    setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,len);
}
inline void XSocket::disconnect()
{
    m_serverExitFlag =1;
    m_clientExitFlag =1;
    XEE::sleep(500);
    closesocket(m_mySocket);
}
inline int XSocket::isRecvBuffEmpty() const
{
    if(m_getDataBuff[m_getDataOldP].pData == NULL) return 1;
    else return 0;
}
inline int XSocket::isSendBuffEmptyBC() const
{
    if(m_broadcastBuff[m_broadcastOldPoint].pData == NULL) return 1;
    else return 0;
}
inline void XSocket::setDataProtection(XBool temp)
{
    dataProtectionFlag = temp;
}
inline void XSocket::disNeedMutual()
{
    m_needMutual = XFalse;
}
}
#endif

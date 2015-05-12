#ifndef _JIA_XNETCOMMON_
#define _JIA_XNETCOMMON_

#include <deque>
#include <iostream>
#include <String.h>
#include <fstream>
#include <string>
#include "XBasicFun.h"
#include "XBasicClass.h"
#include "winsock.h"
namespace XE{
#define NET_SERVER_IP ("192.168.1.110")
#define NET_SERVER_PORT (9988)
#define BOARDCAST_PORT (7898)
#define BOARDCAST_DATA_LEN (1024)
#define PROJECT_STRING_LEN (256)
#define DEFAULT_PROJECT_STR ("xiajia_1981@163.com")

enum XConnectState
{
	CONNECT_STATE_DISCONNECT,
	CONNECT_STATE_CONNECT,
};

enum XNetDataType
{
	DATA_TYPE_EPC,
	DATA_TYPE_EXCESS_SUM,
	DATA_TYPE_VIDEO,
	DATA_TYPE_VIDEO_UPDATE,
	DATA_TYPE_GAME_OVER,
	DATA_TYPE_GAME_START,
	DATA_TYPE_PHOTO,
	DATA_TYPE_KEY,

	DATA_TYPE_CONFIG_INFO,
	DATA_TYPE_CONFIG_ITEM,
	DATA_TYPE_CONFIG_ITEMS,
	DATA_TYPE_CONFIG_INJECT,
	DATA_TYPE_CONFIG_OPERATE,
};

#define PACKET_HEAD_LEN (5)
struct XNetData
{
	XBool isEnable;
	XNetDataType type;
	int dataLen;
	unsigned char * data;
	XNetData()
		:isEnable(XFalse)
		,dataLen(0)
		,data(NULL)
	{}
	~XNetData()
	{
		if(!isEnable) return;
		XMem::XDELETE_ARRAY(data);
		isEnable = XFalse;
	}
};
inline void showNetData(XNetData *)
{

}

inline void resetSocketAddr(int socket)
{
	int opt = 1;
    int len = sizeof(opt);
    setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,len);
}

inline bool getANewSocket(SOCKET &mySock)
{
	if(mySock != INVALID_SOCKET)
	{
		closesocket(mySock);
		mySock = INVALID_SOCKET;
	}
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0) return false;
	mySock = socket(AF_INET,SOCK_STREAM,0);
	if(mySock == INVALID_SOCKET) return false;
	resetSocketAddr(mySock);
	return true;
}

inline std::string getMyIP()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	char hname[128] = "";
	gethostname(hname,sizeof(hname));
	hostent *hent = gethostbyname(hname);
	if(hent != NULL && hent->h_addr_list[0])
	{
		sprintf(hname,"%d.%d.%d.%d",(unsigned char)(hent->h_addr_list[0][0]),
			(unsigned char)(hent->h_addr_list[0][1]),
			(unsigned char)(hent->h_addr_list[0][2]),
			(unsigned char)(hent->h_addr_list[0][3]));
	}
	WSACleanup();
	return hname;
}

}
#endif
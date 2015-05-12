#ifndef _JIA_XHTTPREQUEST_
#define _JIA_XHTTPREQUEST_

#include "XOSDefine.h"
#ifdef XEE_OS_WINDOWS
#include "winsock.h"
#pragma comment(lib, "ws2_32.lib")
#endif

#ifdef XEE_OS_LINUX
#include <sys/socket.h>
#include <sys/types.h>
#include <malloc.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "XBasicClass.h"
namespace XE{
#define MEM_BUFFER_SIZE (10)

struct XHTTPRequestStruct
{
	char *headerSend;
	char *headerReceive;
	char *message;
	long messageLength;
	XHTTPRequestStruct()
		:headerSend(NULL)
		,headerReceive(NULL)
		,message(NULL)
		,messageLength(0)
	{}
};

struct XMemBuffer
{
	unsigned char *buffer;
	unsigned char *position;
	size_t size;
	XMemBuffer()
		:buffer(NULL)
		,position(NULL)
		,size(0)
	{}
};
class XHTTPRequest
{
public:
	XHTTPRequest();
	virtual ~XHTTPRequest();
private:
	void memBufferCreate(XMemBuffer *b);
	void memBufferGrow(XMemBuffer *b);
	void memBufferAddByte(XMemBuffer *b, unsigned char byt);
	void memBufferAddBuffer(XMemBuffer *b, unsigned char *buffer, size_t size);
	unsigned long getHostAddress(const char *host);
	int sendString(int sock,char *str);
	int validHostChar(char ch);
	void parseURL(char *url,char * protocol, char * host,char * request,int *port);
	int sendHTTP(char *url,char * headerReceive,unsigned char *post, int postLength,XHTTPRequestStruct *req);
public:
	int sendRequest(XBool IsPost,char *url,XHTTPRequestStruct &req);
};

inline int XHTTPRequest::sendString(int sock,char *str)
{
	return send(sock,str,strlen(str),0);
}

inline int XHTTPRequest::validHostChar(char ch)
{

	return (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) || ch == '-' || ch == '.' || ch == ':');
}
}
#endif

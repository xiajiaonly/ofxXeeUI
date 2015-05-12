#ifndef _JIA_XFTPCOMMON_
#define _JIA_XFTPCOMMON_

#include <iostream>
#include <String.h>
#include <fstream>
#include <string>
#include "XBasicFun.h"
#include "XBasicClass.h"

#include "..\XLogBook.h"
namespace XE{
#define RECV_BUFF_SIZE (4096)
#define FTP_SOCKET_PORT (21)
#define SERVER_COMMAND_LEN (64)

enum XFtpUserType
{
	FTP_USER_TYPE_NULL,
	FTP_USER_TYPE_DEFAULT,
	FTP_USER_TYPE_ANONY,
};

extern char returnStr125[];
extern char returnStr150[];
extern char returnStr200[];
extern char returnStr202[];
extern char returnStr211[];
extern char returnStr213[];
extern char returnStr215[];
extern char returnStr220[];
extern char returnStr221[];
extern char returnStr226[];
extern char returnStr230[];
extern char returnStr250[];
extern char returnStr257[];
extern char returnStr331[];
extern char returnStr350[];
extern char returnStr530[];
extern char returnStr531[];

extern char defaultUserName[];
extern char defaultUserPassword[];
extern char anonyUserName[];
extern char anonyUserPassword[];

extern XBool analyseFTPString(const char * str,char * IP,char * path,int &port);

extern XBool analyseFTPStrEx(const char * str,std::string &protocol,
							  std::string &name,
							  std::string &password,
							  std::string &IP,
							  int &port,
							  std::string &path);
}
#endif
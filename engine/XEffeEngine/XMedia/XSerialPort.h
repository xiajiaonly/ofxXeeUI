#ifndef _JIA_SERIALPORT_
#define _JIA_SERIALPORT_

#include <windows.h>
#include "XOSDefine.h"
#include "XBasicClass.h"
#include "../XTimer.h"
#include "../XLogBook.h"
#include "../XXml.h"
namespace XE{

enum XSerialPortMode
{
	SP_MODE_MANUAL,
	SP_MODE_AUTO,
};
#define SP_WITH_STATISTICS
#define SP_RECORDE_FILENAME ("serialPortRecv.dat")
struct XSerialPortInfo
{
	XSerialPortMode mode;
	int byteSize;
	int nPort;
	int nBaud;
	int nParity;
	XBool withEventMode;
	XBool withOverLaped;
	int stopBits;
	int dtr;
	int rts;
	int waitingDataTime;
	XSerialPortInfo()
		:mode(SP_MODE_MANUAL)
		,nPort(1)
		,nBaud(9600)
		,nParity(NOPARITY)
		,withEventMode(XTrue)
		,withOverLaped(XFalse)
		,stopBits(ONESTOPBIT)
		,dtr(DTR_CONTROL_ENABLE)
		,rts(RTS_CONTROL_ENABLE)
		,waitingDataTime(0)
		,byteSize(8)
	{}
	bool readFromFile(const char * filename);
	bool writeToFile(const char * filename);
	bool readFromFile(TiXmlNode * node);
	bool writeToFile(TiXmlElement &element);
	bool checkData() const;
};
class XSerialPort
{
public:
	XSerialPort()
		:m_hIDComDev(NULL)
		,m_bOpened(XFalse)
		,m_funRecv(NULL)
		,m_pClass(NULL)
		,m_withStatistics(false)
		,m_withRecord(XFalse)
		,m_withPlay(XFalse)
		,m_recordFile(NULL)
		,m_playFile(NULL)
	{
		memset(&m_overlappedRead,0,sizeof(OVERLAPPED));
		memset(&m_overlappedWrite,0,sizeof(OVERLAPPED));
	}
	~XSerialPort()
	{
		endRecord();
		stopPlay();
		close();
	}

	XBool open(int nPort = 1,int nBaud = 9600,int nParity = 0,
		XSerialPortMode mode = SP_MODE_MANUAL,XBool withEventMode = XTrue);
	XBool open(const XSerialPortInfo &info);
	XBool close();

	int readData(void *buff, int limit);
	int sendData(const unsigned char *,int size);
	int readDataWaiting();

	XBool isOpened() const {return m_bOpened;}
	void setCallBackFun(void (* funRecv)(void *,unsigned char *,int),void *pClass);
protected:

	XSerialPortInfo m_serialPortInfo;

	HANDLE m_hIDComDev;
	OVERLAPPED m_overlappedRead;
	OVERLAPPED m_overlappedWrite;
	XBool m_bOpened;

	XThreadState m_threadState;
	pthread_t m_recvThread;
	static DWORD WINAPI recvThread(void * pParam);

	void (*m_funRecv)(void *,unsigned char *,int);
	void *m_pClass;

public:
	void setWaitingDataTime(int tmp){m_serialPortInfo.waitingDataTime = tmp;}
	int getWaitingDataTime() const{return m_serialPortInfo.waitingDataTime;}
private:

	bool m_withStatistics;
	int m_sendTimesAll;
	int m_sendBytesAll;
	int m_recvTimesAll;
	int m_recvBytesAll;

	int m_statisticsTimer;
	int m_sendTimesCur;
	int m_sendBytesCur;
	int m_recvTimesCur;
	int m_recvBytesCur;

	float m_sendTimesAvg;
	float m_sendBytesAvg;
	float m_recvTimesAvg;
	float m_recvBytesAvg;
public:
	int getSendTimesAll()const{return m_sendTimesAll;}
	int getSendBytesAll()const{return m_sendBytesAll;}
	int getRecvTimesAll()const{return m_recvTimesAll;}
	int getRecvBytesAll()const{return m_recvBytesAll;}
	float getSendTimesAvg()const{return m_sendTimesAvg;}
	float getSendBytesAvg()const{return m_sendBytesAvg;}
	float getRecvTimesAvg()const{return m_recvTimesAvg;}
	float getRecvBytesAvg()const{return m_recvBytesAvg;}
	void setStatistics(bool flag);
	void update();

private:
	XBool m_withRecord;
	XBool m_withPlay;
	FILE *m_recordFile;
	FILE *m_playFile;
	XCritical m_recordMutex;
	void recordRecvAData(const unsigned char *data,int len);
	XBool readADataFromRecord(std::string &oparetion,XSystemTime &t,unsigned char *date,int &len);
	int m_playTimer;
	XSystemTime m_upTime;
	XSystemTime m_nextTime;
	unsigned char m_nextData[1024];
	int m_nextDataLen;
	std::string m_oparetion;
public:
	XBool getWithRecord() const {return m_withRecord;}
	XBool getWithPlay() const {return m_withPlay;}
	XBool startRecord();
	XBool endRecord();
	XBool startPlay();
	XBool stopPlay();
};
#if WITH_INLINE_FILE
#include "XSerialPort.inl"
#endif
}
#endif
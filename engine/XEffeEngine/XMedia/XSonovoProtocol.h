#ifndef _JIA_XSONOVOPROTOCOL_
#define _JIA_XSONOVOPROTOCOL_

#include "XBasicClass.h"
#include "XMedia/XSerialPort.h"
#include "XLogBook.h"
#include <deque>
namespace XE{

enum XSPDevType
{
	DEV_MASTER,
	DEV_SLAVE,
};
enum XSPCommand
{
	CMD_WRITE = 0x00,
	CMD_READ = 0x01,
	CMD_WRITE_ACK = 0x10,
	CMD_READ_ACK = 0x11,
};
struct XSPData
{
	int dataLen;
	unsigned char * data;
	XSPData()
		:dataLen(0)
		,data(NULL)
	{}
};

struct XSPInfo
{
	XSerialPortInfo serialPortInfo;
	XSPDevType devType;
	unsigned short * buff;
	int buffSize;
	XSPInfo()
		:devType(DEV_MASTER)
		,buff(NULL)
		,buffSize(0)
	{}
};
class XSonovoProtocol
{
private:
	XBool m_isInited;
	std::deque<XSPData> m_recvData;
	std::deque<XSPData> m_sendData;

	XBool m_needRecv;
	int m_delayTime;

	XSerialPort m_serialPort;
	XThreadState m_sendThreadState;
	static DWORD WINAPI sendThread(void * pParam);
	XCritical m_recvMutex;
	XCritical m_sendMutex;

	static void SPRecvCB(void *pClass,unsigned char * data,int len);
	void (*m_callBackFun)(const XSPData & data,void *p);
	void * m_pClass;

	XBool pushAData(XSPData &data);
	void answerProc(XSPData &data);

	XSPInfo m_info;
	XSPData m_curSendData;
	XBool m_withLog;

	void sendCurData();
	unsigned char *m_sendBuff;
	int m_sendBuffSize;
public:
	XSPDevType getWorkType() const {return m_info.devType;}
	void setWithLog(XBool flag) {m_withLog = flag;}
	XBool getWithLog() {return m_withLog;}
	void setCallBackFun(void (*p)(const XSPData &,void *),void *pC)
	{
		m_callBackFun = p;
		m_pClass = pC;
	}

	XBool getIsOpen() const {return m_isInited;}
	XBool openDevice(const XSPInfo &info);
	int getSendBuffSize();

	XSonovoProtocol()
		:m_isInited(false)
		,m_withStatistics(false)
		,m_callBackFun(NULL)
		,m_pClass(NULL)
	{}
	~XSonovoProtocol(){release();}
	void release()
	{
		if(!m_isInited) return;
		waitThreadEnd(m_sendThreadState);

		for(unsigned int i = 0;i < m_sendData.size();++ i)
		{
			XMem::XDELETE_ARRAY(m_sendData[i].data);
		}
		m_sendData.clear();
		for(unsigned int i = 0;i < m_sendData.size();++ i)
		{
			XMem::XDELETE_ARRAY(m_recvData[i].data);
		}
		m_recvData.clear();

		m_serialPort.close();
		m_isInited = XFalse;
	}
	XSPData popData()
	{
		XSPData tempData;
		if(m_info.devType == DEV_MASTER)
		{
			m_recvMutex.Lock();
			if(m_recvData.size() > 0)
			{
				tempData = m_recvData[0];
				m_recvData.pop_front();
			}
			m_recvMutex.Unlock();
		}
		return tempData;
	}
	XBool pushData(XSPData &data)
	{
		if(m_info.devType == DEV_MASTER)
			return pushAData(data);
		return XFalse;
	}

	void showData(const XSPData &data,const std::string &title);
private:

	bool m_withStatistics;
	int m_statisticsTimer;
	int m_comunicateTimesCur;
	int m_delayTimeCur;
	float m_delayTimeAvg;
public:
	int getSendTimesAll()const{return m_serialPort.getSendTimesAll();}
	int getSendBytesAll()const{return m_serialPort.getSendBytesAll();}
	int getRecvTimesAll()const{return m_serialPort.getRecvTimesAll();}
	int getRecvBytesAll()const{return m_serialPort.getRecvBytesAll();}
	float getSendTimesAvg()const{return m_serialPort.getSendTimesAvg();}
	float getSendBytesAvg()const{return m_serialPort.getSendBytesAvg();}
	float getRecvTimesAvg()const{return m_serialPort.getRecvTimesAvg();}
	float getRecvBytesAvg()const{return m_serialPort.getRecvBytesAvg();}

	float getDelayTimeAvg()const{return m_delayTimeAvg;}
	void setStatistics(bool flag)
	{
		if(flag == m_withStatistics) return;
		if(flag)
		{
			m_withStatistics = true;

			m_statisticsTimer = 0;
			m_comunicateTimesCur = 0;
			m_delayTimeCur = 0;
			m_delayTimeAvg = 0.0f;
			m_serialPort.setStatistics(true);
		}else
		{
			m_withStatistics = false;
			m_serialPort.setStatistics(false);
		}
	}
	void update();

	void writeOneRegister(int addr,int value);
	void readRegisters(int startAddr,int sum);
};

inline void XSonovoProtocol::showData(const XSPData &data,const std::string &title)
{
	std::string tmp = title + "data:";
	char tmpStr[32];
	for(int i = 0;i < data.dataLen;++ i)
	{
		sprintf(tmpStr,"0x%02x ",data.data[i]);
		tmp += tmpStr;
	}
	LogStr(tmp.c_str());
}
inline int XSonovoProtocol::getSendBuffSize()
{
	m_sendMutex.Lock();
	int ret = m_sendData.size();
	m_sendMutex.Unlock();
	return ret;
}
inline bool getSPCMDAddress(const XSPData &CMD,unsigned int &addr)
{
	if(CMD.dataLen <= 0) return 0;
	switch(CMD.data[0])
	{
	case CMD_WRITE:

		addr = CMD.data[1];
		return true;
	case CMD_WRITE_ACK:
		return false;
	case CMD_READ_ACK:

		addr = CMD.data[2];
		return true;
	}
	return false;
}
inline int getSPCMDDataSum(const XSPData &CMD)
{
	if(CMD.dataLen <= 0) return 0;
	switch(CMD.data[0])
	{
	case CMD_WRITE:
		return (CMD.dataLen - 4) >> 1;
	case CMD_READ:
		return 0;
	case CMD_WRITE_ACK:
		return 0;
	case CMD_READ_ACK:
		return (CMD.dataLen - 5) >> 1;
	}
	return false;
}
inline bool getSPCMDData(const XSPData &CMD,int index,unsigned int &data)
{
	if(CMD.dataLen <= 0) return false;
	if(index < 0 || index >= getSPCMDDataSum(CMD)) return false;
	int offset;
	switch(CMD.data[0])
	{
	case CMD_WRITE:
		offset = (index << 1) + 2;
		data = (CMD.data[offset] << 8) + CMD.data[offset + 1];
		return true;
	case CMD_READ:
		return false;
	case CMD_WRITE_ACK:
		return false;
	case CMD_READ_ACK:
		offset = (index << 1) + 3;
		data = (CMD.data[offset] << 8) + CMD.data[offset + 1];
		return true;
	}
	return false;
}
#include "XSonovoProtocol.inl"

}
#endif
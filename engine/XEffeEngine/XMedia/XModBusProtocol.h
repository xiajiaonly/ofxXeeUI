#ifndef _JIA_XMODBUSPROTOCOL_
#define _JIA_XMODBUSPROTOCOL_

#include <deque>
#include "XBasicClass.h"
#include "XMedia/XSerialPort.h"

namespace XE{

enum XModBusWorkMode
{
	MODE_ASCII,
	MODE_RTU,
};
enum XModBusType
{
	TYPE_MASTER,
	TYPE_SLAVE,
};

struct XModBusData
{
	int delayTime;
	unsigned char * data;
	unsigned short addr;
	int dataLen;
	XModBusData()
		:data(NULL)
		,dataLen(0)
	{}
};
enum XModeBusCMD
{
	CMD_READ_COIL_VOLUME = 1,
	CMD_READ_INPUT = 2,
	CMD_READ_HOLD_REGISTER = 3,
	CMD_READ_INPUT_REGISTER = 4,
	CMD_SET_ONE_COIL = 5,
	CMD_SET_ONE_REGISTER = 6,
	CMD_SET_COILS = 15,
	CMD_SET_REGISTERS = 16,
};
enum XModeBusErrorCode
{
	ERROR_READ_COIL_VOLUME = 0x81,
	ERROR_READ_INPUT = 0x82,
	ERROR_READ_HOLD_REGISTER = 0x83,
	ERROR_READ_INPUT_REGISTER = 0x84,
	ERROR_SET_ONE_COIL = 0x85,
	ERROR_SET_ONE_REGISTER = 0x86,
	ERROR_SET_COILS = 0x8f,
	ERROR_SET_REGISTERS = 0x90,
};
#define MODBUS_HEAD_LEN (8)
struct XModbusState
{
	XSerialPortInfo serialPortInfo;
	unsigned char deviceID;
	XModBusWorkMode workMode;
	XModBusType workType;
	unsigned char *coilsBuff;
	int coilsBuffSize;
	int coilsOffset;
	unsigned short *hRegisterBuff;
	int hRegisterBuffSize;
	int hRegisterOffset;
	unsigned short *iRegisterBuff;
	int iRegisterBuffSize;
	int iRegisterOffset;
	unsigned char *inputBuff;
	int inputBuffSize;
	int inputOffset;
	int outTime;
	int maxResendTimes;
	int maxR2STime;
	XModbusState()
		:workMode(MODE_RTU)
		,workType(TYPE_MASTER)
		,coilsBuff(NULL)
		,coilsBuffSize(0)
		,hRegisterBuff(NULL)
		,hRegisterBuffSize(0)
		,iRegisterBuff(NULL)
		,iRegisterBuffSize(0)
		,inputBuff(NULL)
		,inputBuffSize(0)
		,outTime(300)
		,maxResendTimes(3)
		,deviceID(1)
		,coilsOffset(0)
		,hRegisterOffset(0)
		,iRegisterOffset(0)
		,inputOffset(0)
		,maxR2STime(5)
	{}
};
class XModBusProtocol
{
private:
	XBool m_isInited;
	std::deque<XModBusData> m_recvData;
	std::deque<XModBusData> m_sendData;

	XSerialPort m_serialPort;

	static DWORD WINAPI sendThread(void * pParam);

	XBool m_needRecv;
	int m_delayTime;
	int m_delaySendTime;

	XCritical m_sendMutex;
	XCritical m_recvMutex;

	XThreadState m_sendThreadState;

	XModbusState m_modbusState;
	XModBusData m_curSendData;
	void sendCurData();
	int m_sendTime;
	XBool m_connectState;
	XBool pushAData(XModBusData &data);
	void answerProc(XModBusData &data);
	void (*m_callBackFun)(const XModBusData & data,void *p);
	void * m_pClass;
	XBool m_withLog;
public:
	XModBusType getWorkType() const {return m_modbusState.workType;}
	void setWithLog(XBool flag) {m_withLog = flag;}
	XBool getWithLog() const {return m_withLog;}
	void setCallBackFun(void (*p)(const XModBusData &,void *),void *pC)
	{
		m_callBackFun = p;
		m_pClass = pC;
	}
	XBool getIsOpen() const {return m_isInited;}

	XBool openDevice(XModbusState &modbusState);
	int getSendBuffSize();
	XBool pushData(XModBusData &data)
	{
		if(m_modbusState.workType == TYPE_MASTER)
			return pushAData(data);
		return XFalse;
	}
	int getRecvBuffSize();
	XModBusData popData();

	void release();
	XModBusProtocol()
		:m_isInited(XFalse)

		,m_withLog(XTrue)
		,m_withStatistics(false)
	{}
	~XModBusProtocol(){release();}
	static void recvCallback(void *pClass,unsigned char * data,int len);

	void readCoilState(int startAddr,int sum,int arm);
	void readInputState(int startAddr,int sum,int arm);
	void writeOneCoilState(int Addr,int value,int arm);
	void writeCoilsState(int startAddr,int sum,unsigned char *value,int arm);

	void readHoldRegisters(int startAddr,int sum,int arm);
	void readInputRegisters(int startAddr,int sum,int arm);

	void writeRegisters(int startAddr,int sum,const unsigned short *data,int arm);
	void writeOneRegister(int addr,int value,int arm);
	int getHoldRegisterOffset(){return m_modbusState.hRegisterOffset;}
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
};
inline int XModBusProtocol::getRecvBuffSize()
{
	m_recvMutex.Lock();
	int ret = m_recvData.size();
	m_recvMutex.Unlock();
	return ret;
}
inline int XModBusProtocol::getSendBuffSize()
{
	m_sendMutex.Lock();
	int ret = m_sendData.size();
	m_sendMutex.Unlock();
	return ret;
}
namespace XModBus{

extern int getModbusCMDDataSum(const XModBusData &CMD);
inline bool getModbusCMDAddress(const XModBusData &CMD,unsigned int &addr)
{
	if(CMD.dataLen <= 0) return false;
	addr = CMD.addr;
	return true;
}
extern bool getModbusCMDData(const XModBusData &CMD,int index,unsigned int &data);
inline int getModbusCMDID(const XModBusData &CMD){return CMD.data[0];}
}
}
#endif
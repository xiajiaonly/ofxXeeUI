#ifndef _JIA_XSIMPLEPROTOCOL_
#define _JIA_XSIMPLEPROTOCOL_

#include "XBasicClass.h"
#include "XMedia/XSerialPort.h"
#include "XLogBook.h"
#include <deque>
namespace XE{
enum XSimProDataType
{
	SIMPRO_TYPE_STATE,
	SIMPRO_TYPE_DATA,
};
struct XSimProData
{
	XSimProDataType type;
	int index;
	int data;
};
#define MAXXSP_STATE_INDEX (16)
#define MAXXSP_DATA_INDEX (96)
class XSimpleProtocol
{
private:
	XBool m_isInited;
	XBool m_isSigned;
	char m_state[MAXXSP_STATE_INDEX];
	unsigned short m_data[MAXXSP_DATA_INDEX];
	unsigned char m_recvedData[3];
	int m_recvedDataLen;

	XSerialPort m_serialPort;
	static void simpleProctocolRecvCB(void *pClass,unsigned char * data,int len);
	void (*m_callBackFun)(const XSimProData &data,void *p);
	void * m_pClass;

	void recvDataProc(unsigned char *data,int len);
public:
	void setCallBackFun(void (*p)(const XSimProData &,void *),void *pC);
	XBool openDevice(int portIndex,int bitRate,int parity = 0,XBool withEventMode = XFalse);
	XBool openDevice(const XSerialPortInfo &info);
	XSimpleProtocol()
		:m_isInited(XFalse)
		,m_recvedDataLen(0)
		,m_isSigned(XFalse)
	{}
	~XSimpleProtocol(){release();}
	void release();
	char getState(int index) const;
	int getData(int index) const;
	int getMaxStateSum() const{return MAXXSP_STATE_INDEX;}
	int getMaxDataSum() const{return MAXXSP_DATA_INDEX;}

private:
	std::deque<XSimProData> m_sendData;
	XThreadState m_sendThreadState;
	XCritical m_sendMutex;
	static DWORD WINAPI sendThread(void * pParam);
	void sendData(const XSimProData&tmp);
	int decodeData(unsigned char *data);
	void encodeData(int src,unsigned char *data);
public:
	XBool pushAData(XSimProData &data);

	XBool getWithRecord() const {return m_serialPort.getWithRecord();}
	XBool getWithPlay() const {return m_serialPort.getWithPlay();}
	XBool startRecord() {return m_serialPort.startRecord();}
	XBool endRecord() {return m_serialPort.endRecord();}
	XBool startPlay() {return m_serialPort.startPlay();}
	XBool stopPlay() {return m_serialPort.stopPlay();}
	void update() {m_serialPort.update();}
	void setIsSigned(XBool flag) {m_isSigned = flag;}
	XBool getIsSigned() const {return m_isSigned;}
};
#if WITH_INLINE_FILE
#include "XSimpleProtocol.inl"
#endif
}
#endif
#pragma once

#include "../lib/BHComm/BHSerial.h"

/////// Master, Slave Handler///////////


#define WM_MASTERDISPLAY_VALUE	(WM_USER+300)


////////////////////////////////////////////


#define COMM_ERROR_CONNECTION   0
#define SEND_OK        1
#define SEND_END		2
#define SEND_OFF		 3

#define RECEIVE_OK			4	  
#define RECEIVE_END		5
#define OFF_RECEIVE		6
#define STOP_IMG				8


  
#define WM_MASTERDISPLAY_VALUE	(WM_USER+300)
#define   WM_VOLTGAIN_VALUE		    (WM_USER+303)



typedef enum
{
	ERR_NO						= 0x00,
	ERR_EX_ILLEGAL_FUNCTION		= 0x01,
	ERR_EX_ILLEGAL_DATA_ADDRESS = 0x02,
	ERR_EX_ILLEGAL_DATA_VALUE	= 0x03,
	ERR_EX_SLAVE_DEVICE_FAILURE = 0x04,
	ERR_EX_ACKNOWLEDGE			= 0x05,
	ERR_EX_SLAVE_BUSY			= 0x06,
	ERR_EX_MEMORY_PARITY_ERROR	= 0x08,
	ERR_EX_GATEWAY_PATH_FAILED	= 0x0A,
	ERR_EX_GATEWAY_TGT_FAILED	= 0x0B,
	ERR_NOREGISTER,
	ERR_ILLEGALARGUMENT,
	ERR_PORT,
	ERR_NORESOURCE,
	ERR_IO,
	ERR_ILLEGALSTATE,
	ERR_TIMEOUT,
	ERR_RETRY,
	ERR_NOTIMPLEMENTED,
	ERR_CHECKSUM,
	ERR_ILLEGALFRAME
} ERRCODE;


typedef enum
{
	MASTER_STATE_IDLE,			// No pending request
	MASTER_STATE_WAITING,		// Wait response
	MASTER_STATE_CHECKRESPONE,	// Check response
	MASTER_STATE_PROCESSING,	// Processing response
	MASTER_STATE_TURNAROUND,	// Wait slave processing (100 msec to 200 msec)
	MASTER_STATE_ERROR			
} MASTERSTATE;


typedef enum
{
	SLAVE_STATE_IDLE,			// No pending request
	SLAVE_STATE_WAITING,		// Wait response
	SLAVE_STATE_CHECKRESPONE,	// Check response
	SLAVE_STATE_PROCESSING,	// Processing response
	SLAVE_STATE_TURNAROUND,	// Wait slave processing (100 msec to 200 msec)
	SLAVE_STATE_ERROR
	
} SLAVESTATE;





/// Modeless Dialog Packet




//extern int nLeng;

class CComm 
{
public:
	////////////////////////////////////////////////
	CComm(COMM_INFO *pComInfo, BOOL bOvl=TRUE);
	virtual ~CComm(void);
	//동시에 접근 하지 못하도록 막음

	CCriticalSection m_sync;
	CSerialPort m_serial;
	
	INT STATUS;



	void SetOvl(BOOL b);
	BOOL GetOvl();

	BOOL Open();
	BOOL Close();

	static void CloseEvent(LPVOID lpData);

	int IsOpen();
	
	// Slave Module Data
	int SendRecv(unsigned char* sndbuf, int len, int nWaitSize, unsigned char* rcvbuf, int waitTime);
	int SendRecv(unsigned char* sndbuf, int len, LPCSTR  szStart, LPCSTR szEnd, int iExtByte, unsigned char* rcvbuf, int waitTime);

	// MV 2000 Data
	int ExtendSendRecv(unsigned char* sndbuf, int len, int nWaitSize, unsigned char* rcvbuf, int waitTime);

	int SendForWait(unsigned char* buf, int len, int nWaitSize);
	int SnedForWait(unsigned char* buf, int len, LPCSTR szStart, LPCSTR szEnd, int iExtByte=0);


	void MaskStart(LPCSTR szStart, LPCSTR szEnd, int iExtByte=0);
	
	int RecvLen(unsigned char* buf, int waitTime);
	int RecvMask(unsigned char* buf, int waitTime);

	int Send(unsigned char* buf, int len);
	int Recv(unsigned char* buf, int nWaitsize, int nTimeout);

	/*void SetWaitMilliSecond(DWORD dwMillisecond);*/
	
	//TIC용 BCC


	int BCCAddType1(char* lpBuf);
	BOOL BCCCheckType1(LPCSTR lpBuf);

	BYTE BCCCheckType2(BYTE *packet, int size);
	void Poll(INT nSlaveAddress, INT nFunctionCode, INT Addr,LPBYTE lpTxBuffer, INT nTxDataLength);

	
	//CRC Calcurate
	unsigned short int CRC16(unsigned int nLength,BYTE lpFrame[]);

	// Check Modbus Status
	virtual void SetCommState(INT nState);
	
	


protected:
		COMM_INFO *m_pComInfo;
		BOOL m_bOvl;
};




//
//
//
// TX, RX LED 켜기

//>> 제작일자 20130522, 수

//extern void CHECK_COMM_LED(int nKind);

extern clock_t m_receive_time;
extern clock_t sendtime;
extern void TURN_LED(int nKind);



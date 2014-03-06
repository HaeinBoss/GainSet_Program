#pragma once
// BHSerial.h

// 통신 버퍼
#define COM_BUF_SIZE	4096
#define	MAX_READ_SIZE	4096
#define	MAX_SEND_SIZE	MAX_READ_SIZE

// FOR GOLDSEC
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

#define XON       0x11
#define XOFF      0x13

// 제어문자
#define NUL		0x00	// null
#define SOH		0x01	// Start Of Header		: 메세지의 처음
#define STX		0x02	// Start of TeXt		: 데이타 블럭의 처음
#define ETX		0x03	// End of TeXt			: 데이타 블럭의 끝 
#define EOT		0x04	// End Of Transmission	: 전송상태의 종료 
#define ENQ		0x05	// iNQuiry				: 확인이나 정보 요구
#define ACK		0x06	// ACKnowledgement		: 질문에 대해 'yes', 다음 전송 준비 상태 표시, 비동기 통신의 타이밍을 위해 사용				
#define BEL		0x07	// BELl					: 터미널 상의 벨이나 알람 
#define BS		0x08	// BackSpace			: 커서를 한글자 뒤로 이동 
#define HT		0x09	// Horizontal Tab		: 커서를 수평 탭의 위치로 이동 
#define LF		0x0A	// Lind Feed			: 커서를 다음 줄로 이동
#define VT		0x0B	// Vertical Tab			: 커서를 다음 수직 탭 위치로 이동
#define FF		0x0C	// Form Feed			: 커서를 다음 페이지 상단으로 이동
#define CR		0x0D	// Carriage Return		: 커서를 좌측 끝으로 이동 
//#define SO		0x0E	// Shift Out			: 다음 문자는 ASCII 정의 따르지 않음 
//#define SI		0x0F	// Shift In				: 다음 문자는 ASCII 정의에 따름 
#define SHO		0x0E	// Shift Out			: 다음 문자는 ASCII 정의 따르지 않음 
#define SHI		0x0F	// Shift In				: 다음 문자는 ASCII 정의에 따름 
#define DLE		0x10	// Data Link Escape		: ESC 제어를 사용하는 전송의 제어에 사용
#define DC1		0x11	// Device Control 1		: 미정의 
#define DC2		0x12	// Device Control 2		: 미정의 
#define DC3		0x13	// Device Control 3		: 미정의 
#define DC4		0x14	// Device Control 4		: 미정의 
#define NAK		0x15	// Negative AcK			: 질문에 대해 'no', 에러발생 재전송 요청, 비동기 통신에 사용
#define SYN		0x16	// SYNchronous idle		: idle 상태 때 동기장치에 보냄 
#define ETB		0x17	// End of Transmission Block : 전송시 블록의 경계 표시 
#define CAN		0x18	// CANcel				: 전에 전송한 것을 무시 
#define EM		0x19	// End of Medium		: 종이 테이프 등 물리적 메체의 종단 표시 
#define SUB		0x1A	// SUBstitute			: 잘못된 문자를 대치하는 데 사용 
#define ESC		0x1B	// ESCape				: ESC 제어순서의 시작 표시 
#define FS		0x1C	// File Separator		: 전송의 가장 중요 부분임을 표시 
#define GS		0x1D	// Group Separator		: 전송의 중요 부분임을 표시 
#define RS		0x1E	// Record Separator		: 전송의 부차 부분임을 표시
#define US		0x1F	// Unit Separator		: 전송의 가장 부차 부분임을 표시 

//RUN Error
#define RE_NONE					0	// No Error
#define RE_PORT_ALREADY_OPENED	1	// Port already opend
#define RE_HANDLE_INIT_ERROR	2	// COM Handle Init Error
#define RE_PORT_OPEN_ERROR		3	// Port Open Error - Maybe port is using
#define RE_THREADS_RUN_ERROR	4	// Threads Run Error

//ERROR
#define COMM_ERROR			-1
#define COMM_NOCONNECT		-2
#define COMM_TIMEOUT		-3
#define COMM_DATA_ERROR		-4 //(BCC등 송수신 데이터 오류)
#define COMM_OK				 0


/////////////////////////////////////////////////////////////////////////////
// BHSerial:
#include "..//..//lib/KLib/KThread.h"



class CBHSerial // : public CObject
{
private:
	// Handle, buf

	HANDLE     m_hCommError;
	HANDLE		m_hCOM;			// COM Port Handle
	OVERLAPPED	m_OSRead;		// COM Port에서 data를 읽어 내는 것과 관련, COMPortRead() -> ReceiveData() ->ReadCOMBlock()
	OVERLAPPED	m_OSWrite;		// COM Port에 data를 쓰는 것과 관련, WriteCOMPort()
	OVERLAPPED	m_OS;			// os overlapped, COM Port에 data가 들어 오는 것과 관련, COMPortRead()
	
	HANDLE	m_hWait;			// COM port Write후 바로 Read시 사용
	HANDLE	m_hWaitOK;
	int		m_waitBytes;
	int		m_waitBufPos;
	unsigned char m_waitBuf[MAX_READ_SIZE];

	// main 함수
	BOOL	COMHandleInit();
	void	COMHandleClose();
	BOOL	COMPortOpen(char* port);
	int		COMPortRead();
	void	COMPortClose();

	BOOL	SetupConnection();
	int		ReceiveData();
	int		COMBlockRead(unsigned char *lpszBlock, int nMaxLength);

	// Thread 함수 
	__int64				m_lastTime;		// 마지막으로 DATA를 읽은 시간
	CKThread m_ThreadRead;
	static BOOL WINAPI ProcessRead(CKThread* pThread, LPVOID lpData);

	BOOL RunCOMThreads();
protected:
	CBHSerial();
	
	// 제어변수
	BOOL	m_bClosing;
	BOOL	m_bOpen;

	// 하위 class 사용 함수
	BOOL COMPortWrite(unsigned char* sBuf, int size, int waitSize = 0);
	BOOL COMPortWriteMask(unsigned char* sBuf, int size, LPCSTR szStart, LPCSTR szEnd, int iExtByte=0);

	virtual void	OnReceiveData(unsigned char *buf, int nSize);
	virtual int		Run();
	virtual BOOL	Stop();

	BOOL m_bMaskRcvFlag;
	int m_iExtByte;
	char m_szStart[100];
	char m_szEnd[100];

	unsigned char m_waitMaskBuf[MAX_READ_SIZE];
	int		m_waitMaskBufPos;

	HANDLE	m_hWaitMaskOK;
	HANDLE	m_hWaitSTX;

public:
	char	m_port[20];
	DCB		m_dcb;

	// OnReceiveData를 이용하지 않고, Write후 바로 읽는 함수
	int	Recv(unsigned char *buf, int waitTime);
	int	RecvMask(unsigned char *buf, int waitTime );

	void MaskStart(LPCSTR szStart, LPCSTR szEnd, int iExtByte=0);

	BOOL	SetCommState(DCB dcb, BOOL bDuring=FALSE);
	BOOL	IsOpen(){ return m_bOpen; }
};

// COM.h
//

/////////////////////////////////////////////////////////////////////////////
// CSerialPort:

class CSerialPort : public CBHSerial
{
public:

	BOOL Send(unsigned char* sBuf, int size, int waitSize = 0);
	BOOL Send(unsigned char* sBuf, int size, LPCSTR szStart, LPCSTR szEnd, int iExtByte=0);

	
	CWnd  *m_pParent;
	CCriticalSection  m_sync;

	CSerialPort(CWnd * pParent=NULL, LPCSTR szPort=NULL, DCB *pDcb=NULL);
	virtual ~CSerialPort();

	virtual int Run();
	virtual BOOL Stop();

	//	////////////CRC 계산 및 체크//////////////////
	//unsigned short int calculateCRC(unsigned int len, BYTE messageArray[]);
	//BOOL checkCRC(BYTE messageToCheck[], int numberOfBytes);



protected:
	virtual void OnReceiveData(unsigned char *recvBuf, int nSize);
								// m_clearCOMErrorTime 동안 데이타가 들어오지 않으면 실행됨 
public:
	char CalcSum(char *pbuf, int ncount);

};



//extern BOOL GetMillisecTime(__int64 *pTime);

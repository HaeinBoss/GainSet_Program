#pragma once
// BHSerial.h

// ��� ����
#define COM_BUF_SIZE	4096
#define	MAX_READ_SIZE	4096
#define	MAX_SEND_SIZE	MAX_READ_SIZE

// FOR GOLDSEC
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

#define XON       0x11
#define XOFF      0x13

// �����
#define NUL		0x00	// null
#define SOH		0x01	// Start Of Header		: �޼����� ó��
#define STX		0x02	// Start of TeXt		: ����Ÿ ���� ó��
#define ETX		0x03	// End of TeXt			: ����Ÿ ���� �� 
#define EOT		0x04	// End Of Transmission	: ���ۻ����� ���� 
#define ENQ		0x05	// iNQuiry				: Ȯ���̳� ���� �䱸
#define ACK		0x06	// ACKnowledgement		: ������ ���� 'yes', ���� ���� �غ� ���� ǥ��, �񵿱� ����� Ÿ�̹��� ���� ���				
#define BEL		0x07	// BELl					: �͹̳� ���� ���̳� �˶� 
#define BS		0x08	// BackSpace			: Ŀ���� �ѱ��� �ڷ� �̵� 
#define HT		0x09	// Horizontal Tab		: Ŀ���� ���� ���� ��ġ�� �̵� 
#define LF		0x0A	// Lind Feed			: Ŀ���� ���� �ٷ� �̵�
#define VT		0x0B	// Vertical Tab			: Ŀ���� ���� ���� �� ��ġ�� �̵�
#define FF		0x0C	// Form Feed			: Ŀ���� ���� ������ ������� �̵�
#define CR		0x0D	// Carriage Return		: Ŀ���� ���� ������ �̵� 
//#define SO		0x0E	// Shift Out			: ���� ���ڴ� ASCII ���� ������ ���� 
//#define SI		0x0F	// Shift In				: ���� ���ڴ� ASCII ���ǿ� ���� 
#define SHO		0x0E	// Shift Out			: ���� ���ڴ� ASCII ���� ������ ���� 
#define SHI		0x0F	// Shift In				: ���� ���ڴ� ASCII ���ǿ� ���� 
#define DLE		0x10	// Data Link Escape		: ESC ��� ����ϴ� ������ ��� ���
#define DC1		0x11	// Device Control 1		: ������ 
#define DC2		0x12	// Device Control 2		: ������ 
#define DC3		0x13	// Device Control 3		: ������ 
#define DC4		0x14	// Device Control 4		: ������ 
#define NAK		0x15	// Negative AcK			: ������ ���� 'no', �����߻� ������ ��û, �񵿱� ��ſ� ���
#define SYN		0x16	// SYNchronous idle		: idle ���� �� ������ġ�� ���� 
#define ETB		0x17	// End of Transmission Block : ���۽� ����� ��� ǥ�� 
#define CAN		0x18	// CANcel				: ���� ������ ���� ���� 
#define EM		0x19	// End of Medium		: ���� ������ �� ������ ��ü�� ���� ǥ�� 
#define SUB		0x1A	// SUBstitute			: �߸��� ���ڸ� ��ġ�ϴ� �� ��� 
#define ESC		0x1B	// ESCape				: ESC ��������� ���� ǥ�� 
#define FS		0x1C	// File Separator		: ������ ���� �߿� �κ����� ǥ�� 
#define GS		0x1D	// Group Separator		: ������ �߿� �κ����� ǥ�� 
#define RS		0x1E	// Record Separator		: ������ ���� �κ����� ǥ��
#define US		0x1F	// Unit Separator		: ������ ���� ���� �κ����� ǥ�� 

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
#define COMM_DATA_ERROR		-4 //(BCC�� �ۼ��� ������ ����)
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
	OVERLAPPED	m_OSRead;		// COM Port���� data�� �о� ���� �Ͱ� ����, COMPortRead() -> ReceiveData() ->ReadCOMBlock()
	OVERLAPPED	m_OSWrite;		// COM Port�� data�� ���� �Ͱ� ����, WriteCOMPort()
	OVERLAPPED	m_OS;			// os overlapped, COM Port�� data�� ��� ���� �Ͱ� ����, COMPortRead()
	
	HANDLE	m_hWait;			// COM port Write�� �ٷ� Read�� ���
	HANDLE	m_hWaitOK;
	int		m_waitBytes;
	int		m_waitBufPos;
	unsigned char m_waitBuf[MAX_READ_SIZE];

	// main �Լ�
	BOOL	COMHandleInit();
	void	COMHandleClose();
	BOOL	COMPortOpen(char* port);
	int		COMPortRead();
	void	COMPortClose();

	BOOL	SetupConnection();
	int		ReceiveData();
	int		COMBlockRead(unsigned char *lpszBlock, int nMaxLength);

	// Thread �Լ� 
	__int64				m_lastTime;		// ���������� DATA�� ���� �ð�
	CKThread m_ThreadRead;
	static BOOL WINAPI ProcessRead(CKThread* pThread, LPVOID lpData);

	BOOL RunCOMThreads();
protected:
	CBHSerial();
	
	// �����
	BOOL	m_bClosing;
	BOOL	m_bOpen;

	// ���� class ��� �Լ�
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

	// OnReceiveData�� �̿����� �ʰ�, Write�� �ٷ� �д� �Լ�
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

	//	////////////CRC ��� �� üũ//////////////////
	//unsigned short int calculateCRC(unsigned int len, BYTE messageArray[]);
	//BOOL checkCRC(BYTE messageToCheck[], int numberOfBytes);



protected:
	virtual void OnReceiveData(unsigned char *recvBuf, int nSize);
								// m_clearCOMErrorTime ���� ����Ÿ�� ������ ������ ����� 
public:
	char CalcSum(char *pbuf, int ncount);

};



//extern BOOL GetMillisecTime(__int64 *pTime);

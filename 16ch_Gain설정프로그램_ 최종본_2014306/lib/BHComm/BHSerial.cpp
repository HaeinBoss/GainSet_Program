// BHSerial.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BHSerial.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBHSerial construction


CBHSerial::CBHSerial()
{
	m_hCOM = NULL;
	//GetMillisecTime(&m_lastTime);
	m_bClosing = TRUE;
	m_bOpen=FALSE;

	m_waitBufPos = 0;
	m_waitBytes = 0;

	memset ( m_szStart,0x00, sizeof(m_szStart));
	memset ( m_szEnd,0x00,sizeof(m_szEnd));

	m_waitMaskBufPos=0;
	m_iExtByte=0;

	m_hWaitMaskOK=CreateEvent(NULL, TRUE, FALSE, NULL);
	if(m_hWaitMaskOK == NULL)
		TRACE("COM2 / m_hWaitMaskOk : CreateEvent Error !!");

	m_hWaitSTX=CreateEvent(NULL, TRUE, FALSE, NULL);
	if(m_hWaitSTX == NULL)
		TRACE("COM2 / m_hWaitSTX : CreateEvent Error !!");

	m_bMaskRcvFlag=FALSE;
}

void CBHSerial::OnReceiveData(unsigned char *buf, int nSize)
{
	
}

int CBHSerial::Run()
{
	if(m_hCOM != NULL)
		return RE_PORT_ALREADY_OPENED;

	if(!COMHandleInit())							// COM port �ʱ�ȭ 
		return RE_HANDLE_INIT_ERROR;

	if(COMPortOpen(m_port))
	{
		if(	!RunCOMThreads())						// COM Port ����  Thread �⵿ 
		{
			COMPortClose();
			return RE_THREADS_RUN_ERROR;							
		}
	}
	else
	{
		COMHandleClose();
		return RE_PORT_OPEN_ERROR;
	}

	m_bClosing = FALSE;
	m_bOpen=TRUE;

	return RE_NONE;
}

BOOL CBHSerial::Stop()
{
	m_bClosing = TRUE;
	if(m_hCOM == NULL)
		return TRUE;

	Sleep(0);  // ���� �����̶�� �� �������� ���� ��ٸ� 
	int count = 0;

 	if( m_ThreadRead.IsRun() )							// ���� Mutexes ����
	{
		BOOL bStop=m_ThreadRead.Stop();
		if (!bStop)
		{
			VERIFY(SetEvent(m_OS.hEvent));			// COMPortRead���� ��� ���� 
			VERIFY(SetEvent(m_OSWrite.hEvent));		// COMPortWrite���� ��� ���� 
			VERIFY(SetEvent(m_OSRead.hEvent));

			VERIFY(SetEvent(m_hWait));			// COMPortRead���� ��� ���� 
			VERIFY(SetEvent(m_hWaitOK));		// COMPortWrite���� ��� ���� 
			VERIFY(SetEvent(m_hWaitMaskOK));

			count++;
		}
	}


	TRACE ("COM Close!! %d\n", count);
	Sleep(100);  // ���� �����̶�� �� �������� ���� ��ٸ� 
	//TRACE ("COM Close!! %d\n", count);
	COMPortClose();
	m_bOpen=FALSE;
	//OnCOMError();
	return TRUE;

	/*
	if(count == 0)
	{
		COMPortClose();
		m_bOpen=FALSE;
		//OnCOMError();
		return TRUE;
	}
	else
	{
		TRACE("FALSE\n");
		return FALSE;
	}
	*/
}

BOOL CBHSerial::RunCOMThreads()
{
	if(m_ThreadRead.IsRun())
		return FALSE;

	m_ThreadRead.SetWaitTime(0);
	m_ThreadRead.CKThread::Start(ProcessRead,(LPVOID)this);

	return TRUE;
}

BOOL CBHSerial::COMHandleInit()
{
	m_hWait	= CreateEvent(NULL, TRUE, FALSE, NULL);
	if(m_hWait == NULL)
	{
		TRACE("CBHSerial / m_hWait : CreateEvent Error !!");
		return FALSE;
	}

	m_hWaitOK	= CreateEvent(NULL, TRUE, FALSE, NULL);
	if(m_hWaitOK == NULL)
	{
		CloseHandle(m_hWait);	m_hWait = NULL;

		TRACE("CBHSerial / m_hWaitOK : CreateEvent Error !!");
		return FALSE;
	}


	m_OS.hEvent = CreateEvent(	NULL, TRUE, FALSE, NULL);
	if(m_OS.hEvent == NULL)
	{
		CloseHandle(m_hWait);	m_hWait = NULL;
		CloseHandle(m_hWaitOK);	m_hWaitOK = NULL;

		TRACE("CBHSerial / m_OS.hEvent : CreateEvent Error !!");
		return FALSE;
	}

	m_OSRead.hEvent = CreateEvent(	NULL, TRUE, FALSE, NULL);
	if(m_OSRead.hEvent == NULL)
	{
		CloseHandle(m_hWait);		m_hWait = NULL;
		CloseHandle(m_hWaitOK);		m_hWaitOK = NULL;

		CloseHandle(m_OS.hEvent);	m_OS.hEvent = NULL;

		TRACE("CBHSerial / m_OSRead.hEvent : CreateEvent Error !!");
		return FALSE;
	}
	// �̰� �����ָ�  �а� ����  ERROR_IO_PENDING�� �ȶ����� �� ����(debug mode)
	// help������ ��Ž� �����ϴٰ� �Ǿ� ����
	m_OSRead.Offset = 0;
	m_OSRead.OffsetHigh = 0;

	m_OSWrite.hEvent = CreateEvent(	NULL, TRUE, FALSE, NULL);
	if(m_OSWrite.hEvent == NULL)
	{
		CloseHandle(m_hWait);			m_hWait = NULL;
		CloseHandle(m_hWaitOK);			m_hWaitOK = NULL;

		CloseHandle(m_OS.hEvent);		m_OS.hEvent = NULL;
		CloseHandle(m_OSRead.hEvent);	m_OSRead.hEvent = NULL;

		TRACE("CBHSerial / m_OSWrite.hEvent : CreateEvent Error !!");
		return FALSE;
	}
	// �̰� �����ָ�  �а� ����  ERROR_IO_PENDING�� �ȶ����� �� ����(debug mode)
	// help������ ��Ž� �����ϴٰ� �Ǿ� ����
	m_OSWrite.Offset = 0;
	m_OSWrite.OffsetHigh = 0;

	return TRUE;
}

void CBHSerial::COMHandleClose()
{
	CloseHandle(m_hWait);			m_hWait = NULL; 
	CloseHandle(m_hWaitOK);			m_hWaitOK = NULL; 

	CloseHandle(m_OS.hEvent);		m_OS.hEvent = NULL; 
	CloseHandle(m_OSRead.hEvent);	m_OSRead.hEvent = NULL; 
	CloseHandle(m_OSWrite.hEvent);	m_OSWrite.hEvent = NULL; 


}

BOOL CBHSerial::COMPortOpen(char* port)
{ 
	if(m_hCOM != NULL)// ��� port ��� ��   
		return FALSE;

	CString strPort;

	strPort.Format("\\\\.\\%s", port );
	m_hCOM = CreateFile(strPort, GENERIC_READ | GENERIC_WRITE,
						0, NULL, OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
						NULL);

	if(m_hCOM == (HANDLE)-1)
	{
		m_hCOM = NULL;
		return FALSE;
	}

	COMMTIMEOUTS CommTimeOuts;
	SetCommMask(m_hCOM, EV_RXCHAR );
	SetupComm(m_hCOM, COM_BUF_SIZE, COM_BUF_SIZE);	  // �Է�, ��� ���� ũ�� ����
	PurgeComm(m_hCOM, PURGE_TXABORT | PURGE_RXABORT |
						 PURGE_TXCLEAR | PURGE_RXCLEAR);

	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadIntervalTimeout = 0;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;

	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 100000;// Origin 5000 - Write�� 5�� �̻� �ɸ��� timeout error

	SetCommTimeouts(m_hCOM, &CommTimeOuts);

	BOOL rtn = SetupConnection();			// set up comm device
	if(rtn)
	//if(1)
	{
		return TRUE;
	}
	else 
	{
		CloseHandle(m_hCOM);
		m_hCOM = NULL;
		return FALSE;
	}  
}

BOOL CBHSerial::SetupConnection()
{
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hCOM, &dcb);

	dcb.BaudRate =	m_dcb.BaudRate;
	dcb.ByteSize =	m_dcb.ByteSize;
	dcb.Parity =	m_dcb.Parity;
	dcb.StopBits =  m_dcb.StopBits;

	////dcb.fBinary =	m_dcb.fBinary;
	////dcb.fParity =	m_dcb.fParity;
	////dcb.fOutxCtsFlow = m_dcb.fOutxCtsFlow;
	////dcb.fOutxDsrFlow = m_dcb.fOutxDsrFlow;
	////dcb.fDtrControl = m_dcb.fDtrControl;
	////dcb.fRtsControl = m_dcb.fRtsControl;

	////dcb.fInX =		m_dcb.fInX;
	////dcb.fOutX =		m_dcb.fOutX;
	////dcb.XonChar =	m_dcb.XonChar;
	////dcb.XoffChar =	m_dcb.XoffChar;
	////dcb.XonLim =	m_dcb.XonLim;
	////dcb.XoffLim =	m_dcb.XoffLim;

	BOOL b=::SetCommState(m_hCOM, &dcb);
	return b;
}

BOOL CBHSerial::COMPortWrite(unsigned char* sBuf, int size, int waitSize)
{
	if(m_bClosing)
		return FALSE;

	if(m_hCOM == NULL)
		return FALSE;

	if((size <=0)|| (size> MAX_SEND_SIZE))
		return FALSE;

	// wait �ʱ�ȭ
	if(waitSize > 0 && waitSize <= MAX_READ_SIZE)
	{
		m_waitBufPos = 0;
		m_waitBytes = waitSize;
		VERIFY(SetEvent(m_hWait));
		VERIFY(ResetEvent(m_hWaitOK));
	}

	unsigned long int  dwErrorFlags;
	COMSTAT comState;

	unsigned long int dwBytesWritten;
	DWORD	error;
	BOOL	fWriteStat;
	BOOL	bRet = TRUE;

	// win95/98������ fWriteStat�� �ǰ�, nt������ overapped�� �� 
	// �ؼ� m_OSWrite overapped�� ����Ͽ��� ��
	// �׷��� ������ ����Ÿ�� ������ �ߴ��ϴ� ��찡 ����
	fWriteStat = WriteFile(	m_hCOM, sBuf, size,	&dwBytesWritten, &m_OSWrite	);
	if(!fWriteStat)
	{	
		error = GetLastError();
		if(error == ERROR_IO_PENDING)   // USB ���̺��� ���ڱ� �������ų� ��� off �Ǿ ��� �Ҵ��϶� �����޽��� ����
		{
			if(!GetOverlappedResult(m_hCOM, &m_OSWrite, &dwBytesWritten, TRUE))
			{
				error = GetLastError();
				if(error == ERROR_IO_INCOMPLETE)
					TRACE("COMPortWrite - ERROR_IO_INCOMPLETE\n");

				TRACE("COMPortWrite - overlapped error!!\n");
				ClearCommError(m_hCOM, &dwErrorFlags, &comState);
				bRet = FALSE;				
				VERIFY(ResetEvent(m_OSWrite.hEvent));
			}
		}
		else
		{
			//A  �۽�: 01  03  b3  b0  00  0c  62  ac 
			//COMPortWrite - not ERROR_IO_PENDING
		//	ADD_COMM_LOG(COMM_ERROR_CONNECTION,"Error Connection");
			//STOP_GRAPH(STOP_MASTER_GRAPH);	
					
			//
			Sleep(100);			

		/// �ֱ�
		 //ControlLED(SEND_OFF);
		 //ControlLED(OFF_RECEIVE);
		
		 TRACE("COMPortWrite - not ERROR_IO_PENDING\n");
		 
		ClearCommError(m_hCOM, &dwErrorFlags, &comState);
		bRet = FALSE;	

			// nErrorFlag = SEND_ERROR;
		}
	}

	
	
	
	return bRet;
}

int	CBHSerial::COMPortRead()	  // COM Port �� �о� ���ۿ� ���� 
{
	unsigned long int dwEventMask;
	unsigned long int  dwTransfer;
	dwEventMask = 0;

	if(!WaitCommEvent(m_hCOM, &dwEventMask, &m_OS))	// m_OS�� CreateEvent�����ָ� ��⼭ ���߾� ���� 
	{	
		DWORD lastError = GetLastError();	   
		if(lastError == ERROR_IO_PENDING)			// ��ü�� �� �ٽ� ����
		{	
			if(!GetOverlappedResult(m_hCOM, &m_OS, &dwTransfer,TRUE))
			{
				VERIFY(ResetEvent(m_OS.hEvent));
				return 0;
			}
		}				
		else
		{
			VERIFY(ResetEvent(m_OS.hEvent));
			return 0;
		}
	}
						
	VERIFY(ResetEvent(m_OS.hEvent));

	// Data�� ���ƿ����� �а� ���ۿ� ���� 
	if((dwEventMask & EV_RXCHAR)== EV_RXCHAR)
 		return ReceiveData();
	else
		return 0;
}

int	CBHSerial::ReceiveData()
{
	if(m_hCOM == NULL)
		return 0 ;

	int nLength, totLength = 0;
	unsigned char readBuf[MAX_READ_SIZE];
	unsigned char mod_byte[MAX_READ_SIZE];
	int mod_len=0;

	do 
	{ 
		nLength = COMBlockRead(readBuf, MAX_READ_SIZE);
		if(nLength)
		{
		//	GetMillisecTime(&m_lastTime);		// ���� ����Ÿ�� ���� �ð� 

			// Write�� Waitó��
			if(WaitForSingleObject(m_hWait, 0) == WAIT_OBJECT_0)
			{
				if(m_waitBufPos + nLength > MAX_READ_SIZE)
				{
					memcpy(m_waitBuf, readBuf, nLength);
					m_waitBufPos = nLength;
				}
				else
				{
					memcpy(&m_waitBuf[m_waitBufPos], readBuf, nLength);
					m_waitBufPos += nLength;
				}

				if(m_waitBufPos == m_waitBytes)		// ��ٸ��� byte�� ������ ������
				{
					//TRACE("CBHSerial::ReceiveData() - Wait Receive OK\n");
					VERIFY(ResetEvent(m_hWait));
					VERIFY(SetEvent(m_hWaitOK));
				}
				else if(m_waitBufPos > m_waitBytes)	// ������ OnReceiveData()�� �ѱ� 
				{
					//TRACE("CBHSerial::ReceiveData() - Wait + OnReceiveData\n");
					int overBytes = m_waitBufPos - m_waitBytes;
					m_waitBufPos = m_waitBytes;
					VERIFY(ResetEvent(m_hWait));
					VERIFY(SetEvent(m_hWaitOK));
					OnReceiveData(&m_waitBuf[m_waitBytes], overBytes);
				}
				else								// ���ڶ�� ��� ��ġ
				{
					//TRACE("CBHSerial::ReceiveData() - Wait Receiving...\n");
					;
				}
			}
			else
			{
				memset ( mod_byte, 0x00, sizeof(mod_byte) );
				mod_len=0;

				if ( m_bMaskRcvFlag==FALSE )
				{
					if ( readBuf[0]==STX )
					{
						VERIFY(SetEvent(m_hWaitSTX));
						Sleep(500);
					}

				}

				for(int i = 0; i<nLength; i++)
				{
					//temp.Format("%02X", readBuf[i]);
					if ( m_bMaskRcvFlag==TRUE )
					{
						m_waitMaskBuf[m_waitMaskBufPos++]=readBuf[i];
						if ( (int)(strlen(m_szStart)+strlen(m_szEnd)) < (int)((int)m_waitMaskBufPos+(int)m_iExtByte) )
						{
							if ( !strncmp ( m_szStart, (char*)&m_waitMaskBuf[0], strlen(m_szStart) ) &&
								 !strncmp ( m_szEnd, (char*)&m_waitMaskBuf[m_waitMaskBufPos-strlen(m_szEnd)-m_iExtByte], strlen(m_szEnd) ))
							{
								m_bMaskRcvFlag=FALSE;
								VERIFY(SetEvent(m_hWaitMaskOK));
							}
						} //if ( (int)(strlen(m_szStart)+strlen(m_szEnd)) < (int)m_waitMaskBufPos )
					}//if ( m_bMaskRcvFlag==TRUE )
					else
					{
						//TRACE ( "[%02x]\n",readBuf[i]);
						mod_byte[mod_len]=readBuf[i];
						mod_len++;
					}
				}//for(i = 0; i<nSize; i++)

				if ( mod_len > 0 )
					OnReceiveData(mod_byte, mod_len);
			}

			totLength += nLength;
		} 

	} while(nLength > 0);
	
	return totLength;
}

int CBHSerial::COMBlockRead(unsigned char* lpszBlock, int nMaxLength)
{
	BOOL fReadStat;
	COMSTAT comState;
	unsigned long int dwErrorFlags, dwLength;

	ClearCommError(m_hCOM, &dwErrorFlags, &comState);

	dwLength = min((DWORD)nMaxLength, comState.cbInQue);
	if(dwLength <= 0)
		return 0;

	fReadStat = ReadFile(m_hCOM, lpszBlock, dwLength, &dwLength, &m_OSRead);
	if(!fReadStat)
	{
		DWORD lastError = GetLastError();	   

		if(lastError == ERROR_IO_PENDING)		// ��ü�� �� �ٽ� ����
		{
			if(!GetOverlappedResult(m_hCOM, &m_OSRead, &dwLength, TRUE))							
			{
				TRACE("ReadBlock - overlapped error!!\n");
				ClearCommError(m_hCOM, &dwErrorFlags, &comState);
				VERIFY(ResetEvent(m_OSRead.hEvent));
				return 0;
			}
			else
			{
				TRACE("ReadBlock - overlapped.\n");
			}
		}
		else	// ���� ERROR_IO_PENDING�ε�, Ȥ �ٸ� ������ ���� ��� 
		{
			TRACE("ReadBlock - not ERROR_IO_PENDING\n");
			ClearCommError(m_hCOM, &dwErrorFlags, &comState);
			VERIFY(ResetEvent(m_OSRead.hEvent));
			return 0;
		}
	}
		
	VERIFY(ResetEvent(m_OSRead.hEvent));
	return dwLength;
}

void CBHSerial::COMPortClose()
{
	if(m_hCOM ==  NULL)
		return;

	EscapeCommFunction(m_hCOM, CLRDTR);
	EscapeCommFunction(m_hCOM, CLRRTS);
	PurgeComm(m_hCOM, PURGE_TXABORT | PURGE_RXABORT |
		PURGE_TXCLEAR | PURGE_RXCLEAR);
	

	COMHandleClose();
	CloseHandle(m_hCOM);
	m_hCOM = NULL;

}

//BOOL GetMillisecTime(__int64 *pTime)
//{
//	SYSTEMTIME	sysTime;
//
//	GetLocalTime( &sysTime );
//	
//	if(SystemTimeToFileTime(&sysTime, (FILETIME *)pTime))
//	{							// nHuge = 100 nanosec, pTime = 0 : 1601/1/1 0:0:0
//		*pTime /= 10000;		// millisec
//		return TRUE;
//	}
//	else
//	{
//		*pTime = 0;
//		return FALSE;
//	}
//}
//
/*
BOOL CBHSerial::BCCCheck(unsigned char *pBuf, int nCount)
{
	char check[2];

	unsigned int sum = 0;

	for (int i = 1 ; i < nCount-2; i++) // STX�� ���� 
		sum  += pBuf[i];

	sum = sum & 0x000000FF;

	sprintf(check, "%.2X", sum);

	if(strncmp(check, (char*)&pBuf[nCount-2], 2)== 0)
		return TRUE;
	else
		return FALSE;
}

void CBHSerial::BCCAdd(unsigned char *pBuf, int nCount)
{
	unsigned int sum = 0;

	for (int i = 1 ; i < nCount-2; i++) // STX�� ���� 
		sum  += pBuf[i];

	sum = sum & 0x000000FF;

	sprintf((char*)&pBuf[nCount-2], "%.2X", sum);		 // %.2X �빮�� X ���� �� 
}
*/

///////////////(2012-08-22) Wed, WaitForSigleObject()////////////////////
//::WaitForSigleObject() = Ư�� ��ü�� ���°� �����ɶ����� ���� �������� ������ ���ߴ� ��Ȱ
//
// DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
//
//  �־��� �ð� �̳��� Ư�� �ڵ�(�޸�)�� ���°� �����Ǳ⸦ ��ٸ�
// ie> 1000ms ���� ��ٸ���� ������ 500ms �� ����� �������� ��ü�� ���°� �����Ǹ� �Լ��� ��ȯ
//::Sleep(100)  = �־��� �ð� ��ŭ ������ �帧�� ������

//  - hHandle : ������ ����ȭ�� ����ϴ� Ŀ�� ��ü�� �ڵ�.���μ��� �ڵ�
//  - dwMilliseconds: 

BOOL CBHSerial::Recv(unsigned char *buf, int waitTime)
{
	// ������ ������ timeout
	if(WaitForSingleObject(m_hWaitOK, waitTime) != WAIT_OBJECT_0)
	{ 
		ControlLED(OFF_RECEIVE);  
		TRACE("CBHSerial::Read() - No Data!!\n");
		return COMM_TIMEOUT;
	}
   

	VERIFY(ResetEvent(m_hWaitOK));

	if(m_waitBytes != m_waitBufPos)
	{
		TRACE("CBHSerial::Read() - size mismatch %d-%d!!\n", m_waitBytes, m_waitBufPos);
		return COMM_ERROR;
	}

 
	memcpy(buf, m_waitBuf, m_waitBytes);

	return m_waitBytes;
}

BOOL CBHSerial::SetCommState(DCB dcb, BOOL bDuring/*=FALSE*/)
{
	//DCB dcb_o;

	m_dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hCOM, &m_dcb);

	m_dcb.BaudRate =	dcb.BaudRate;
	m_dcb.ByteSize =	dcb.ByteSize;
	m_dcb.Parity =		dcb.Parity;
	m_dcb.StopBits =	dcb.StopBits;

	m_dcb.fBinary =		dcb.fBinary;
	m_dcb.fParity =		dcb.fParity;
	m_dcb.fOutxCtsFlow= dcb.fOutxCtsFlow;
	m_dcb.fOutxDsrFlow= dcb.fOutxDsrFlow;
	m_dcb.fDtrControl = dcb.fDtrControl;
	m_dcb.fRtsControl = dcb.fRtsControl;

	m_dcb.fInX =		dcb.fInX;
	m_dcb.fOutX =		dcb.fOutX;
	m_dcb.XonChar =		dcb.XonChar;
	m_dcb.XoffChar =	dcb.XoffChar;
	m_dcb.XonLim =		dcb.XonLim;
	m_dcb.XoffLim =		dcb.XoffLim;

	BOOL b=FALSE;
	if ( bDuring )
		b=::SetCommState(m_hCOM, &m_dcb);
	else
		b=TRUE;

	return b; 
}

BOOL WINAPI CBHSerial::ProcessRead(CKThread* pThread, LPVOID lpData)
{
	CBHSerial *pParent=(CBHSerial*)lpData;
	unsigned long int  dwEvent=0, dwData=0;
	while(1)
	{
		
		if(!pThread->GetQueue(&dwEvent, &dwData))
		{
			if((dwEvent=GetLastError())!=KTE_TIMEOUT)
				break;
		}
		//������ ���� �̺�Ʈ
		if(dwEvent==KTE_STOP)
			break;

		dwData=dwEvent=0;
		pParent->COMPortRead();
	}

	return 0;
}

void CBHSerial::MaskStart(LPCSTR szStart, LPCSTR szEnd, int iExtByte/*=0*/)
{
	strcpy_s( m_szStart, szStart );
	strcpy_s ( m_szEnd, szEnd );
	m_iExtByte=iExtByte;
	m_waitMaskBufPos=0;
	VERIFY(ResetEvent(m_hWaitMaskOK));

	m_bMaskRcvFlag=TRUE;
}

BOOL CBHSerial::COMPortWriteMask(unsigned char* sBuf, int size, LPCSTR szStart, LPCSTR szEnd, int iExtByte/*=0*/)
{
	strcpy_s ( m_szStart, szStart );
	strcpy_s ( m_szEnd, szEnd );
	m_iExtByte=iExtByte;
	m_waitMaskBufPos=0;
	VERIFY(ResetEvent(m_hWaitMaskOK));

	if(CBHSerial::COMPortWrite(sBuf, size, 0))
	{
		m_bMaskRcvFlag=TRUE;
		return TRUE;
	}
	else
	{
		m_bMaskRcvFlag=FALSE;
		return FALSE;
	}
}

BOOL CBHSerial::RecvMask(unsigned char *buf, int waitTime)
{
	int nLength=0;
	if(WaitForSingleObject(m_hWaitMaskOK, waitTime) != WAIT_OBJECT_0)
	{
		//TRACE("CSerialPort::ReadMask() - No Data!!\n");
		m_waitMaskBufPos=0;
		return COMM_TIMEOUT;
	}

	VERIFY(ResetEvent(m_hWaitMaskOK));

	memcpy(buf, m_waitMaskBuf, m_waitMaskBufPos);
	nLength=m_waitMaskBufPos;
	m_waitMaskBufPos=0;

	return nLength;
}

/////////////////////////////////////////////////////////////////////////////
// CSerialPort construction
CSerialPort::CSerialPort(CWnd * pParent/*=NULL*/, LPCSTR szPort/*=NULL*/, DCB *pDcb/*=NULL*/) 
{
	m_pParent = pParent;
	// modify this COM Port Option

	if ( szPort==NULL )
		sprintf_s(m_port, "COM1");
	else
		sprintf_s(m_port, szPort);
	//sprintf(m_port, "COM2"); //Test ��

	DCB dcb;

	dcb.BaudRate =	CBR_115200;
	//dcb.BaudRate =	CBR_4800;
	dcb.ByteSize =	8;
	dcb.StopBits =	ONESTOPBIT;
	dcb.Parity =	NOPARITY;

	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;
	
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;

	//dcb.fOutxCtsFlow = TRUE;
	//dcb.fOutxDsrFlow = TRUE;

	//dcb.fDtrControl = DTR_CONTROL_ENABLE;
	//dcb.fRtsControl = RTS_CONTROL_ENABLE;

	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	
	dcb.fInX =	FALSE;
	dcb.fOutX = FALSE;		// flow : XOn/XOff not use

	dcb.XonChar =	0x11;		// ASCII_XON
	dcb.XoffChar =	0x13;		// ASCII_XOFF
	dcb.XonLim =	100;
	dcb.XoffLim =	100;

	if ( pDcb==NULL )
		m_dcb = dcb;
	else
		m_dcb = *pDcb;

	// modify this
	// Add your code here
}

CSerialPort::~CSerialPort()
{
	// Add your code here
}

void CSerialPort::OnReceiveData(unsigned char *recvBuf, int nSize)
{
	if(m_bClosing)	// dialog�� list box�� �Ѹ����� �ð��� ��� 
		return;		// ���������� data�� ���� ��� CBHSerial::ReceiveData()��
				// do loop�� ��� Ÿ�ٰ� Stop�� �ȵǴ� ���� ���� 
}
/*
	nCount += nSize;
	if(nCount>=1200)
	{
		GetLocalTime(&time);

		temp.Format("%02d/%03d: %04d Bytes: ", time.wSecond, time.wMilliseconds, nCount);
		m_pDlg->AddListBox(&m_pDlg->m_LBCreceived, temp);
		nCount = 0;
	}
*/

int CSerialPort::Run()
{
	// Add Your Code
	//ReceiveInit();

	// don't modify
	return CBHSerial::Run();
}

BOOL CSerialPort::Stop()
{
	// don't modify
	BOOL ret=0;
	ret=CBHSerial::Stop();
	//TRACE("COM Stop��!!\n");
	return ret;
}

int CSerialPort::Send(unsigned char * sBuf, int size, int waitSize)
{
	// don't modify
	if(CBHSerial::COMPortWrite(sBuf, size, waitSize))
	{
		return COMM_OK;
	}
	else
	{	
		return COMM_ERROR;
	}
}

int CSerialPort::Send(unsigned char* sBuf, int size, LPCSTR szStart, LPCSTR szEnd, int iExtByte)
{
	if(CBHSerial::COMPortWriteMask(sBuf, size, szStart, szEnd, iExtByte) )
		return COMM_OK;
	else
		return COMM_ERROR;
}


char CSerialPort::CalcSum(char *pbuf, int ncount)
{
	char	checksum = 0;
	for(int i = 0; i < ncount; i ++)
	{
		checksum += pbuf[i];
	}
	return checksum;
}


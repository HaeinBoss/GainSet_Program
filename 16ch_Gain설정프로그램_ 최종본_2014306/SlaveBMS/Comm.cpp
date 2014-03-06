// Comm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Comm.h"


 //int nErrorFlag;




// CComm


/* Table of CRC values for High & Low order byte*/
static const BYTE CRCHi[] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40
};

static const BYTE CRCLo[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
	0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
	0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
	0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
	0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
	0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
	0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 
	0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
	0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
	0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
	0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 
	0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
	0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
	0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
	0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
	0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
	0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
	0x41, 0x81, 0x80, 0x40
};



CComm::CComm(COMM_INFO *pComInfo, BOOL bOvl)
{
	m_bOvl=bOvl;
	m_pComInfo=pComInfo;

	
}

CComm::~CComm()
{
}

BOOL CComm::Open()
{

	if (  m_pComInfo->nKind==COMM_INFO::SERIAL )
	{
		strcpy ( m_serial.m_port, m_pComInfo->szPorSerial );
		m_serial.SetCommState( m_pComInfo->dcb );
		if ( m_serial.Run()!=RE_NONE)
		{
			//TRACE("COM PORT ERROR\n");
		//	AfxMessageBox(_T("Com Port Error"));

		//	ShowErrorDialog("The Com Port setting is incorrect!");
			//CHECK_COMM_LED(SEND_END);
			
			return FALSE;
		}

	}
	else
	{
		//ADD_COMM_LOG(COMM_ERROR_CONNECTION,"설정이 잘못되었습니다.");
		return FALSE;
	}

	// 이미 포트가 열린 상태..(port 성공)
	//if(m_serial.Run()==RE_PORT_ALREADY_OPENED)
	//{
	//	TRACE("진입\n");
	//} 

	//ADD_COMM_LOG(COMM_LOG_STATUS,">>Open Serial");
	return TRUE;
}

// CComm 메시지 처리기입니다.

int CComm::IsOpen()
{
	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
		return m_serial.IsOpen();
	}

	return COMM_NOCONNECT;

}

void CComm::CloseEvent(LPVOID lpData)
{
	CComm *pComm=(CComm*)lpData;
	int iRet=pComm->IsOpen();
	//ADD_COMM_LOG(COMM_LOG_STATUS,pComm->m_nNum,"TCP/IP Disconnect");
}

void CComm::SetOvl(BOOL b)
{
	m_bOvl=b;
	
	CString str;
	str.Format("Overlapped 설정 %d", m_bOvl );
	//ADD_COMM_LOG(COMM_LOG_STATUS,str);

}
BOOL CComm::GetOvl()
{
	return m_bOvl;
}


BOOL CComm::Close()
{
	if( m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
	 	return m_serial.Stop();
	}

	return TRUE;
}

int CComm::SendForWait(unsigned char *buf, int len, int nWaitSize)
{
	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
		CString str;
	//	str.Format("Serial %d Byte 송신..",len);
		//ADD_COMM_LOG(COMM_LOG_STATUS,str);

		str.Format("S: %*.*s", len, len, buf );
		//ADD_COMM_LOG(COMM_LOG_RCVSND,str);	
		
		return m_serial.Send(buf,len,nWaitSize);
		
	}
	return COMM_NOCONNECT;
}

int CComm::SnedForWait(unsigned char *buf, int len, LPCSTR szStart, LPCSTR szEnd, int iExtByte /* 0*/)
{
	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{	
		CString str;
		str.Format("Serial %d Byte 송신..",len);
		//ADD_COMM_LOG(COMM_LOG_STATUS,str);

		str.Format("S: %*.*s", len, len, buf );
		//ADD_COMM_LOG(COMM_LOG_RCVSND,str);	
		
		return m_serial.Send(buf,len,szStart,szEnd,iExtByte);
		
	}
	return COMM_NOCONNECT;
}

void CComm::MaskStart(LPCSTR szStart, LPCSTR szEnd, int iExtByte /*= 0*/)
{
	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
		m_serial.MaskStart(szStart,szEnd,iExtByte);
	}
}

int CComm::RecvLen(unsigned char* buf, int waitTime)
{
	
	if(m_pComInfo->nKind==COMM_INFO::SERIAL)		
	{
		int ret=m_serial.Recv(buf, waitTime);

		CString str;
		str.Format("Serial Receive [%d] ", ret);
		//ADD_COMM_LOG(COMM_LOG_STATUS,str);

		str="R:";
		for ( int i=0; i<ret; i++)
		{
			CString strTxt;
			strTxt.Format("%02X ", buf[i]);
			str+=strTxt;

		}
		//ADD_COMM_LOG(COMM_LOG_RCVSND,str);

		return ret;
	}

	return COMM_NOCONNECT;
}

int CComm::RecvMask(unsigned char* buf, int waitTime)
{
	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
		int ret=m_serial.Recv(buf, waitTime);

		CString str;
		str.Format("Serial Receive [%d] ", ret);
		//ADD_COMM_LOG(COMM_LOG_STATUS,str);
		
		str="R:";
		for ( int i=0; i<ret; i++ )
		{
			CString strTxt;
			strTxt.Format("%02X ", buf[i] );
			str+=strTxt;
		}
		
		//str.Format("R: %*.*s", ret, ret, buf );
		//ADD_COMM_LOG(COMM_LOG_RCVSND,str);

		return ret;
	}
	return COMM_NOCONNECT;
}

int CComm::SendRecv(unsigned char *sndbuf, int len, int nWaitSize, unsigned char *rcvbuf, int waitTime)
{
	int iRet=0;
				
	CSingleLock sl(&m_sync);
	//CSingleLock sl(&m_sync, TRUE);
	USHORT crc=0;
	DWORD    response =0;
	
	sl.Lock();		// lock 걸어서 아무도 접근 못하게..
		
	//Send
	iRet=m_serial.Send(sndbuf,len,nWaitSize);

	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
		if(iRet==0)
		{
			ControlLED(SEND_END);
			CString str;
			str.Format("Serial %d Byte 송신..",len);
		
		str="S:";
		TRACE("\n송신:");
	//	CHECK_COMM_LED(SEND_END);	
		for( int i=0; i<len; i++)
		{
			CString strTxt;
			strTxt.Format("%02X ", sndbuf[i] );
			TRACE(" %02x ",  sndbuf[i]);
			//TRACE("\n");
			str+=strTxt;

		}


			ControlLED(SEND_OK);
		TRACE("\n");


		}
		else if( iRet == COMM_ERROR)
		{
			 ControlLED(SEND_OFF);
			return iRet;
		}

	
		//Recv
		iRet=m_serial.Recv(rcvbuf, waitTime);

		sl.Unlock();		//보내고 받는것 끝나면 Unlock을!
			
		if(iRet >0)
		{
			CString str;
	
			//// Make Modbus Data Type
			str.Format("Serial Receive [%d] ", iRet);

			
			str="R:";
			TRACE("\n수신:");
			
			
			//Sleep(5);
			//ControlLED(RECEIVE_END);

			for( int i=0; i<iRet; i++)
			{	
				CString strTxt;
				strTxt.Format("%02X ", rcvbuf[i]);
				TRACE("%2x ",  rcvbuf[i]);
				str+=strTxt;

			}
			TRACE("\n");

			ControlLED(RECEIVE_OK);

		}



	}




	return iRet;

}


int CComm::SendRecv(unsigned char* sndbuf, int len, LPCSTR szStart,LPCSTR szEnd, int iExtByte, unsigned char* rcvbuf, int waitTime)
{
	int iRet=0;
	CSingleLock sl(&m_sync);

	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
		CString str;
		str.Format("Serial %d Byte 송신..",len);
		//ADD_COMM_LOG(COMM_LOG_STATUS,str);

		str.Format("S: %*.*s", len, len, sndbuf);
		//ADD_COMM_LOG(COMM_LOG_RCVSND,str);

		sl.Lock();		//lock 걸고
		iRet=m_serial.Send(sndbuf,len,szStart,szEnd,iExtByte);	//send 하고 나서
		if(iRet != COMM_OK)										//  Com 포트 연결하면,,
			return iRet;
		iRet=m_serial.RecvMask(rcvbuf,waitTime);			//Recv함..
		sl.Unlock();
	
		if(iRet > 0)
		{
			CString str;
			str.Format("Serial Receive [%d] ", iRet);
			//ADD_COMM_LOG(COMM_LOG_STATUS,str);

			str="R:";
			for( int i=0;i<iRet;i++)
			{
				CString strTxt;
				strTxt.Format("%02X ",rcvbuf[i]);
				str+=strTxt;
			}

			//str.Format("R: %*.*s", iRet, iRet, rcvbuf );
			//ADD_COMM_LOG(COMM_LOG_RCVSND,str);
	
		}
	
	}
	return iRet;
	
}

int CComm::Send(unsigned char *buf, int len)
{
	if(m_pComInfo->nKind==COMM_INFO::SERIAL )
	{
		CString str;
		str.Format("Serial %d Byte 송신..", len );
	//	ADD_COMM_LOG(COMM_LOG_STATUS,str);		//Comm Log status

		str.Format("S: %*.*s", len, len, buf );
	//	ADD_COMM_LOG(COMM_LOG_RCVSND,str);		//Comm Log Receive 시

		return m_serial.Send(buf,len);
	}

	return COMM_NOCONNECT;

}

int CComm::BCCAddType1(char *lpBuf)
{
	UINT  nSum =0;						
	int nLength = (int)strlen(lpBuf);// strlen(const char *str) 문자열 길이 반환			
									/// 널문자를 제외한 문자열의 문자 개수 반환//
	char szBCC[3];

	if(nLength<4)		return 0;
	
	//STX 또는 ENQ는 빠짐
	for(int i =1 ; i <nLength-4; i++)
	{
		nSum +=lpBuf[i];
	}
	
	// %.2X 대문자 X여야 함
	nSum = nSum & 0x000000FF;
	sprintf(szBCC, "%.2X", nSum);

	//TIC 는 BCC 순서가 바뀌었음!!
	lpBuf[nLength++]=szBCC[1];
	lpBuf[nLength++]=szBCC[0];
	lpBuf[nLength]='\0';

	return nLength;

}


BOOL CComm::BCCCheckType1(LPCSTR lpBuf)
{
	UINT nSum = 0;
	int nLength = (int)strlen(lpBuf);
	char szBCC[3];

	if(nLength<4)	return 0;

	// STX 또는 ENQ 는 빠짐
	for( int i = 1; i < nLength-4; i++)
	{
		nSum += lpBuf[i];
	}

	// %.2X 대문자 X여야 함
	nSum=nSum & 0x000000FF;
	sprintf(szBCC, "%.2X", nSum);
	
	//TIC는 BCC 순서가 바뀌었음!!
	if(lpBuf[nLength-3]==szBCC[0] && lpBuf[nLength-4]==szBCC[1])
		return 1;
	return 0;

}

BYTE CComm::BCCCheckType2(BYTE *packet, int size)
{
	BYTE BCC = 0x00;

	if(!packet || size<=0)
	return BCC;
	while(size--)
	{
		BCC ^= *packet++;
	}

	return BCC;
}

void CComm::SetCommState(INT nState)
{
	STATUS = nState;

}


int CComm::ExtendSendRecv(unsigned char *sndbuf, int len, int nWaitSize, unsigned char *rcvbuf, int waitTime)
{
	int iRet=0;
				
	CSingleLock sl(&m_sync);
	//CSingleLock sl(&m_sync, TRUE);
	USHORT crc=0;
	DWORD    response =0;
	
	sl.Lock();		// lock 걸어서 아무도 접근 못하게..
		
	//Send
	iRet=m_serial.Send(sndbuf,len,nWaitSize);

	if(m_pComInfo->nKind==COMM_INFO::SERIAL)
	{
		if(iRet==0)
		{
			ControlLEDB(SEND_END);
			CString str;
			str.Format("Serial %d Byte 송신..",len);
		
		str="S:";
		TRACE("\n송신:");

		for( int i=0; i<len; i++)
		{
			CString strTxt;
			strTxt.Format("%02X ", sndbuf[i] );
			TRACE(" %02x ",  sndbuf[i]);
			//TRACE("\n");
			str+=strTxt;

		}
		ControlLEDB(SEND_OK);
		TRACE("\n");


		}
		else if( iRet == COMM_ERROR)
		{
			 ControlLEDB(SEND_OFF);
			return iRet;
		}

	
		//Recv
		iRet=m_serial.Recv(rcvbuf, waitTime);

		sl.Unlock();		//보내고 받는것 끝나면 Unlock을!
			
		if(iRet >0)
		{
			CString str;
	
			//// Make Modbus Data Type
			str.Format("Serial Receive [%d] ", iRet);

			
			str="R:";
			TRACE("\n수신:");
			
			
			//Sleep(5);
			//ControlLEDB(RECEIVE_END);

			for( int i=0; i<iRet; i++)
			{	
				CString strTxt;
				strTxt.Format("%02X ", rcvbuf[i]);
				TRACE("%2x ",  rcvbuf[i]);
				str+=strTxt;

			}
			TRACE("\n");

			ControlLEDB(RECEIVE_OK);
		}

	}

	return iRet;

}




////////////////////////////////////////////////////////////////////
///////////      PostMessage(), SendMessage()          //////////
/// **PostMessage() :보내고자 하는 메시지를 메시지 큐에 추가하는 함수
//
//					Message queue							
//   Message loop--> [0][1][2][3]  --->PostMessage()
//	 5단계를 거쳐서 메시지 핸들러 함수를 호출
//   메시지 큐에 메시지를 추가하면 반환함   
//
/// **SendMessage(): 메시지 핸들러 함수를 직접 호출 하고, 결과를 반환함
//  윈도우 프로시저를 즉시 호출
//	해당 메시지의 핸들러 함수가 끝나야 반홤
////////////////////////////////////////////////////////////////////
// ThreadSub.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SlaveBMS.h"
#include "ThreadSub.h"
//#include "crcprotocol.h"

// CThreadSub

//IMPLEMENT_DYNCREATE(CThreadSub, CWinThread)


CThreadSub::CThreadSub(CSlaveBMSApp *pParent)
{
	SlaveBMSApp=pParent;
   	ModAClass->vec_mv2000.resize( 16); 
}

CThreadSub::~CThreadSub()
{

}

 
  int CThreadSub::Read_RecoderData(CComm *comm,MODBUS_PACK MOD_PACK)
 {

	if(comm==NULL)
		   return COMM_NOCONNECT;

	if(!comm->IsOpen())
		return COMM_NOCONNECT;


	unsigned char RcvBuff[256];
	unsigned char SendBuff[256];

	short int szDisplay[256];
	float floatData[256];
    int mLen=0;
	int iRet=0;
   	USHORT crc=0;

	int CheckError=0;

	 memset(SendBuff,0x00, sizeof(SendBuff));
	// Copy Send Buff
	Copy2SendBuff((unsigned char*)SendBuff,   MOD_PACK,mLen);

  ///// CRC 계산

	crc = (int)(CCrcProtocol::crc16((BYTE*)SendBuff,mLen));
	
	SendBuff[mLen++] = HI_BYTE(crc);
	SendBuff[mLen++] = LO_BYTE(crc);



	memset( RcvBuff,0x00, sizeof(RcvBuff));

	if(  ModAClass->vec_mv2000.size()>0)
	{
			ModAClass->vec_mv2000.clear();
	}
	
	ModAClass->vec_mv2000.resize(16);

	iRet=comm->ExtendSendRecv((unsigned char*)SendBuff, mLen,MOD_PACK.Quantity*2+5,(unsigned char*)RcvBuff, 1000);
	
	if(iRet <0)
	{
		ControlLEDB(OFF_RECEIVE);
		return iRet;
	}
	

	memset ( szDisplay, 0x00, sizeof(short int)*256 );

	// CRC Check
	if(CCrcProtocol::CheckCRC(crc,(unsigned char*)RcvBuff,iRet) == ERROR_OTHER)
	 {
		 return ERROR_OTHER;
	 }


	for(int i=0; i<(iRet-5)/2; i++)
	 {
		 memcpy ( &szDisplay[i], &RcvBuff[3+(i*2)], sizeof(__int16) );
		 //g_dData[i]=rcvbuf[3+i];
	 }	

	 for(int i=0; i <(iRet-5)/2; i++)
	 {
			MSB2LSB((unsigned char*)&szDisplay[i],sizeof(szDisplay[i]));
			floatData[i]=  (float)szDisplay[i]/1000;
			ModAClass->vec_mv2000[i]= floatData[i];
	 }

	 return COMM_OK;
 }


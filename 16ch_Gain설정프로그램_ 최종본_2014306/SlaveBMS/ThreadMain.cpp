// ThreadMain.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SlaveBMS.h"
#include "ThreadMain.h"
//#include "CrcProtocol.h"


// CThreadMain

//IMPLEMENT_DYNCREATE(CThreadMain, CWinThread)

CThreadMain::CThreadMain(CSlaveBMSApp *pParent)
{

	pSlaveBMS = pParent;

}

CThreadMain::~CThreadMain()
{
	
}


 int CThreadMain::Read_ModuleData(CComm *comm,MODBUS_PACK MOD_PACK)
 {
  	 // 송신
	 if(comm==NULL)
		return COMM_NOCONNECT;

	if(!comm->IsOpen())
		return COMM_NOCONNECT;


	unsigned char RcvBuff[256];
	unsigned char SendBuff[256];
	short int szDisplay[256];

	int mLen=0;
	int iRet=0;
 
   	USHORT crc=0;

	 memset(SendBuff,0x00, sizeof(SendBuff));
	// Copy Send Buff


	if(ModAClass->ModAddr==0)
	 {
		ModAClass->ModAddr=40000;
		MOD_PACK.Address= ModAClass->ModAddr;
		ModAClass->Vec_Module.resize( 2,vector<int>(100 , 0) );

	 }

	Copy2SendBuff((unsigned char*)SendBuff,   MOD_PACK,mLen);

  ///// CRC 계산////

	crc = (int)(CCrcProtocol::crc16((BYTE*)SendBuff,mLen));

	SendBuff[mLen++] = HI_BYTE(crc);
	SendBuff[mLen++] = LO_BYTE(crc);

	memset( RcvBuff,0x00, sizeof(RcvBuff));


	iRet= comm->SendRecv((unsigned char*)SendBuff, mLen,MOD_PACK.Quantity*2+5,(unsigned char*)RcvBuff, 1000);

	if(iRet <0)
	{
		ControlLED(OFF_RECEIVE);
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
		 }	

		int col=0;

	  for(int i=0; i <(iRet-5)/2; i++)
	  {
		  MSB2LSB((unsigned char*)&szDisplay[i],sizeof(szDisplay[i]));
	  }

		col = (MOD_PACK.Address/100)	-400;

		ModAClass->SlaveAddr=col;
	
		for(int row=0;row<100;row++)
		{
			ModAClass->Vec_Module[col][row]=szDisplay[ row];			 
		}

		 if(ModAClass->ModAddr==40000)
		 {
			 ModAClass->ModAddr+=100;
		 }
		 else
		 {
			  ModAClass->ModAddr=40000;
		 }

	 return COMM_OK;
 }

 int CThreadMain::SetData(CComm *comm,MODULE_INFORM MOD_PACK)
 { 	 // 송신
	 if(comm==NULL)
		return COMM_NOCONNECT;

	if(!comm->IsOpen())
		return COMM_NOCONNECT;


	unsigned char RcvBuff[256];
	unsigned char SendBuff[256];

	int mLen=0;
	int iRet=0;
 
   	USHORT crc=0;

	 memset(SendBuff,0x00, sizeof(SendBuff));
	// Copy Send Buff

	Put2SendBuff((unsigned char*)SendBuff,MOD_PACK,mLen);

  ///// CRC 계산////

	crc = (int)(CCrcProtocol::crc16((BYTE*)SendBuff,mLen));

	SendBuff[mLen++] = HI_BYTE(crc);
	SendBuff[mLen++] = LO_BYTE(crc);

	memset( RcvBuff,0x00, sizeof(RcvBuff));

	iRet= comm->SendRecv((unsigned char*)SendBuff, mLen,8,(unsigned char*)RcvBuff, 500	);

	if(iRet <0)
	{ 
		
		ControlLED(RECEIVE_END);
		return iRet;
	}

	// CRC Check
	if(CCrcProtocol::CheckCRC(crc,(unsigned char*)RcvBuff,iRet) == ERROR_OTHER)
	 {
		 return ERROR_OTHER;
	 }

	 return COMM_OK;
 }




  void CThreadMain::Put2SendBuff(unsigned char *SendBuff, MODULE_INFORM ModInform,int& nLen )
 {

   	SendBuff[nLen++] = (BYTE)(ModInform.modpack.ID);
	SendBuff[nLen++] = (BYTE)(ModInform.modpack.Command); 
	SendBuff[nLen++] = (BYTE)(ModInform.modpack.Address/256);
	SendBuff[nLen++] = (BYTE)(ModInform.modpack.Address%256);
	SendBuff[nLen++] = (BYTE)(ModInform.modpack.Quantity/256);
	SendBuff[nLen++] = (BYTE)(ModInform.modpack.Quantity%256);
	SendBuff[nLen++] = (BYTE)(ModInform.modpack.Datalength);

	for(int i=0; i<3;  i++)
	{
			SendBuff[nLen++] = HI_BYTE(ModInform.Data[i]);
			SendBuff[nLen++] = LO_BYTE(ModInform.Data[i]);
	}
	
 }
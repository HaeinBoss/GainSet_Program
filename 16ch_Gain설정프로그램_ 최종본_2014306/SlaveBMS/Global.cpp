// Global.cpp : implementation file
//

#include "stdafx.h"
#include "Global.h"


CModVoltA::CModVoltA()
{
	SlaveAddr=0;
	 ModAddr=0;
}

CModVoltA::~CModVoltA()
{	

}


//
//BOOL g_bStart=FALSE;
// BOOL g_SubStart=FALSE;
INT iClear=0; 
CModVoltA  *ModAClass;



 void Copy2SendBuff(unsigned char *SendBuff,MODBUS_PACK Mod_Data,int& nLen )
 {

   	SendBuff[nLen++] = (BYTE)(Mod_Data.ID);
	SendBuff[nLen++] = (BYTE)(Mod_Data.Command); 
	SendBuff[nLen++] = (BYTE)(Mod_Data.Address/256);
	SendBuff[nLen++] = (BYTE)(Mod_Data.Address%256);
	SendBuff[nLen++] = (BYTE)(Mod_Data.Quantity/256);
	SendBuff[nLen++] = (BYTE)(Mod_Data.Quantity%256);

 }


 void MSB2LSB(unsigned char* Data,int nSize)
{
  unsigned char *Buff= new unsigned char[nSize];
  memcpy(Buff, Data,nSize);

  for( int i=0; i<nSize; i++)
  {
	Data[i]=Buff[nSize-i-1];
  }

   delete Buff;

 }


   	MODBUS_PACK PutOnModBusStructure(const UCHAR& m1, const UCHAR& m2, USHORT& m3,USHORT& m4,UCHAR& m5)
    {
		MODBUS_PACK ModPack;
    
		ModPack.ID =m1;
		ModPack.Command=m2;
		ModPack.Address=m3;
		ModPack.Quantity=m4;
		ModPack.Datalength=m5;

		return ModPack;
   }



void SetWaitMilliSecond(DWORD dwMillisecond)
{
   MSG msg;
   DWORD dwStart;
   dwStart = GetTickCount();
 
  while(GetTickCount() - dwStart < dwMillisecond)
   {
	  while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	  {
	     TranslateMessage(&msg);
	      DispatchMessage(&msg);
	  }
 }
}

void  CModVoltA::RemoveVector(  col_s &SlaveVec)
{

	
	/////////2D vector/////////////
   	col_s::iterator erase_after  = SlaveVec.begin();
	while(erase_after != SlaveVec.end())
	{
		erase_after = SlaveVec.erase(erase_after);
	}

	/////////1D vector/////////////
   	 std::vector<float>fclear;
	vec_mv2000.swap(fclear);
	fclear.clear();
	vec_mv2000.clear();

}


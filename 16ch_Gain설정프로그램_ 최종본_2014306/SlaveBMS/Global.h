#pragma once

//#include <iostream>
#include<vector>
#include <queue>	
using namespace std;

 //// MSB LSB
//#define DWORD  unsigned int
//#define WORD   unsigned short
//#define BYTE   unsigned char

#define CR_WHITE_BTN	RGB(200,200,200)
#define CR_BLUE_BTN		RGB(184,210,246)
#define CR_RED_BTN		RGB(254,110,111)
#define CR_GREEN_BTN	RGB(103,215,101)
#define CR_GRAY_BTN		RGB(192,192,192)
//::GetSysColor(COLOR_3DSHADOW)
//::GetSysColor(COLOR_BTNFACE);

#define ERROR_NONE		0
#define ERROR_NOT_OPEN	1
#define ERROR_WRITE		2
#define ERROR_TIME_OUT	3
#define ERROR_TC		4
#define ERROR_BCCHK		5
#define ERROR_OTHER		6
#define ERROR_AUTO		7

#define DATA_ORDER	    30
 const int IMAGENUM = 14;
 const int IMGNUM = 6;

// #define SCAN_RATE 1000
//#define ORDER  16

  

typedef	union	{
	unsigned char		pValue08[2];
  unsigned short	int		pValue16;
}pValue;


// 공용체 생성
  typedef struct MODBUS_PACK
{
		public :
		UCHAR	ID;     
		UCHAR	Command;			
		USHORT	Address;
		USHORT Quantity;
		unsigned char	Datalength;
		pValue	pData[256];
  }_MODBUS_PACK;

// mod id , cell num temp num 설정

typedef struct _MODULE_INFORM
{
	MODBUS_PACK   modpack;
	short int Data[3]; 

}MODULE_INFORM;

	









class CModVoltA
{
public:
  CModVoltA();
	virtual ~CModVoltA(void);

	// BMS Set  ,, Mod ID/ Cell Num/ Temp Num 설정
	queue<MODULE_INFORM>qModInform;
	
	//Slave Module 전압값	  (BMS #1, BMS #2)
	typedef std::vector <int> row_s;
	typedef std::vector <row_s> col_s;
	col_s  Vec_Module;

   vector<float> vec_mv2000;

	int SlaveAddr;
	USHORT ModAddr;

	void RemoveVector(  col_s &SlaveVec);

	MODBUS_PACK  ModulePack[2];

};

//// Compare

/// Master & Slave Packet	
// 쓰레드 제어 Flag
//extern BOOL g_bStart;
//extern BOOL g_SubStart;


extern   CModVoltA  *ModAClass;

extern void Copy2SendBuff(unsigned char *SendBuff,MODBUS_PACK Mod_Data,int& nLen );
extern void MSB2LSB(unsigned char* Data,int nSize);
extern  MODBUS_PACK PutOnModBusStructure(const UCHAR& m1, const UCHAR& m2, USHORT& m3,USHORT& m4,UCHAR& m5);


extern void ControlLED(int nKind);
extern void ControlLEDB(int nKind);
extern void SetWaitMilliSecond(DWORD dwMillisecond);

//extern MODBUS_PACK  ModulePack[2];
//extern MODBUS_PACK  ModulePack[2];

/////////////////////////////////////////////////////////////////////
  // Module Data 




	











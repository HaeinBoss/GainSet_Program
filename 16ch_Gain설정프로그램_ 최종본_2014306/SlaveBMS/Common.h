#pragma once

#define COMM_ERROR_CONNECTION   0
#define SEND_OK        1
#define SEND_END		2
#define SEND_OFF		 3

#define RECEIVE_OK			4	  
#define RECEIVE_END		5
#define OFF_RECEIVE		6
#define STOP_IMG				8


#define GET_CURR_TIME 1


////////////////////////////////////////////////////////////
/*기본 Color*/
#define WHITE_COLOR	RGB(255,255,255)
#define BLACK_COLOR	RGB(0,0,0)
#define BLUE_COLOR	RGB(0,0,255)
#define BLUE_DK_COLOR	RGB(0,0,128)
#define RED_COLOR	RGB(255,0,0)
#define RED_DK_COLOR RGB(128,0,0)
#define GREEN_COLOR	RGB(0,255,0)
#define GREEN_DK_COLOR	RGB(0,128,0)
#define GRAY_COLOR	RGB(192,192,192)
#define GRAY_DK_COLOR	RGB(128,128,128)
#define GRAY_LT_COLOR	RGB(230,230,230)			   
#define YELLOW_COLOR	RGB(255,255,0)
#define MINOR_COLOR		RGB(255,128,64)
#define  PINK_COLOR		   RGB(243,86,175)
#define  SKYBLUE_COLOR   RGB(80,179,221)
////////////////////////////////////////////////////////////



#define PDU_DATA_SIZE  252			// MODBUS 사양으로 Serial PDU 데이터는 모두 252 바이트로 규정한다.
#define DIRECTORY_MASTER		"../Master_Log/"


typedef struct _CONTROL_LED
{
		int LedCnt[3];


}CONTROL_LED;
typedef struct _CONTROL_PROCESS
{
	__time64_t timeStart;		//시작시간
	__time64_t timeAtt;			//온도도달 시간
	__time64_t timeEnd;			//종료시간(유지완료 예상시간)
	int nDelayMinute;			//유지시간
	BOOL bFlag;					//0:정지, 1:온도컨트롤, 2:목표온도도달, 3:완료
	double dSV;					//설정온도
}CONTROL_PROCESS,*PCONTROL_PROCESS;

typedef struct _COMM_INFO
{
	enum enumKind
	{
		TCP_IP=0,
		SERIAL,
	};
	int nKind;
	DCB dcb;
	int iHandShake;
	char szPorSerial[10];
	char szIPAddress[100];
	WORD nPort;
}COMM_INFO, *PCOMM_INFO;

struct DWORD_BIT
{
 //DWORD wData;
	 WORD BitH0:1;
	 WORD BitH1:1;
	 WORD BitH2:1;
	 WORD BitH3:1;
	 WORD BitH4:1;
	 WORD BitH5:1;
	 WORD BitH6:1;
	 WORD BitH7:1;
	 WORD BitH8:1;
	 WORD BitH9:1;
	 WORD BitHA:1;
	 WORD BitHB:1;
	 WORD BitHC:1;
	 WORD BitHD:1;
	 WORD BitHE:1;
	 WORD BitHF:1;

	 WORD BitL0:1;
	 WORD BitL1:1;
	 WORD BitL2:1;
	 WORD BitL3:1;
	 WORD BitL4:1;
	 WORD BitL5:1;
	 WORD BitL6:1;
	 WORD BitL7:1;
	 WORD BitL8:1;
	 WORD BitL9:1;
	 WORD BitLA:1;
	 WORD BitLB:1;
	 WORD BitLC:1;
	 WORD BitLD:1;
	 WORD BitLE:1;
	 WORD BitLF:1;

};


union BIT_DATA
{
	public :
	 bool operator[](int nBit) 
	 { return (Data>>(nBit)) & 1; }
	 DWORD Data;
	 DWORD_BIT bit_data;
};




////

#define MASTER_MODE 1


	enum
	{
		FUNCTION_CODE_OFFSET = 1,
		// RTU 헤더 길이는 Slave 주소와 Function code 로 2 바이트이다.
		HEADER_LENGTH	= 2 ,
		// RTU 프레임 길이는 헤더 길이와 2 바이트 CRC 로 구성된다.
		FRAME_LENGTH	= HEADER_LENGTH + 2,
		// RTU 예외 메시지 길이는 프레임 길이 더하기 1 바이트의 예외 코드이다.
		EXC_MSG_LENGTH	= FRAME_LENGTH + 1,
		// RTU 최대 길이는 PDU 데이터 크기 더하기 프레임 길이이다.
		MAX_FRAME_SIZE	= PDU_DATA_SIZE + FRAME_LENGTH
	};
//폰트 갯수
#define FONT_COUNT	100

//
//extern CString g_strBinDir;


extern CString g_strBinDir;
extern COMM_INFO g_Comminfo[2];
extern BOOL BrowseFolder(HWND hWnd,  char *szFolder, LPCSTR szInit=NULL);
extern BOOL BCCCheck(unsigned char *pBuf, int nCount);
extern void AddListBox(CListBox *lb, const char *format, ...);




 // Com port 정보를 전달
 extern CString GetCommString( char *comm );



// Master Status 데이터
extern BIT_DATA g_bitData[10];
extern void ShowDoneDialog(CString strMsg);
extern void ShowErrorDialog(CString strMsg);
 extern COMM_INFO g_Comminfo[2];
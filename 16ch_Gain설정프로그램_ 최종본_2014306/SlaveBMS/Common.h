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
/*�⺻ Color*/
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



#define PDU_DATA_SIZE  252			// MODBUS ������� Serial PDU �����ʹ� ��� 252 ����Ʈ�� �����Ѵ�.
#define DIRECTORY_MASTER		"../Master_Log/"


typedef struct _CONTROL_LED
{
		int LedCnt[3];


}CONTROL_LED;
typedef struct _CONTROL_PROCESS
{
	__time64_t timeStart;		//���۽ð�
	__time64_t timeAtt;			//�µ����� �ð�
	__time64_t timeEnd;			//����ð�(�����Ϸ� ����ð�)
	int nDelayMinute;			//�����ð�
	BOOL bFlag;					//0:����, 1:�µ���Ʈ��, 2:��ǥ�µ�����, 3:�Ϸ�
	double dSV;					//�����µ�
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
		// RTU ��� ���̴� Slave �ּҿ� Function code �� 2 ����Ʈ�̴�.
		HEADER_LENGTH	= 2 ,
		// RTU ������ ���̴� ��� ���̿� 2 ����Ʈ CRC �� �����ȴ�.
		FRAME_LENGTH	= HEADER_LENGTH + 2,
		// RTU ���� �޽��� ���̴� ������ ���� ���ϱ� 1 ����Ʈ�� ���� �ڵ��̴�.
		EXC_MSG_LENGTH	= FRAME_LENGTH + 1,
		// RTU �ִ� ���̴� PDU ������ ũ�� ���ϱ� ������ �����̴�.
		MAX_FRAME_SIZE	= PDU_DATA_SIZE + FRAME_LENGTH
	};
//��Ʈ ����
#define FONT_COUNT	100

//
//extern CString g_strBinDir;


extern CString g_strBinDir;
extern COMM_INFO g_Comminfo[2];
extern BOOL BrowseFolder(HWND hWnd,  char *szFolder, LPCSTR szInit=NULL);
extern BOOL BCCCheck(unsigned char *pBuf, int nCount);
extern void AddListBox(CListBox *lb, const char *format, ...);




 // Com port ������ ����
 extern CString GetCommString( char *comm );



// Master Status ������
extern BIT_DATA g_bitData[10];
extern void ShowDoneDialog(CString strMsg);
extern void ShowErrorDialog(CString strMsg);
 extern COMM_INFO g_Comminfo[2];
/* 
 * CHXLog v1.0
 * Copyright (C) 2010 by ENICS CHUNG - <enics_sky@naver.com>
 *
 * 저작권
 *  이 소스는 수정은 가능하나 재배포, 판매, 대여는 허용되지 않습니다.
 *
 */


//#pragma once

#ifndef __CHXLOG_H__
#define __CHXLOG_H__


#include <afxmt.h>




class CHXLog
{

public:
	CHXLog(void);
	~CHXLog(void);

private:
	//*-------------------------------------------------------
	long	m_lMaxLogSizeBytes;	//로그 최대 크기(byte) 1048576 = 1MB
	int		m_lMaxLogFileCount; // 로그 파일 최대 갯수 (백업 로테이션)

	//*-------------------------------------------------------	
	char _h_errormessage_[256];

	CCriticalSection m_csLog;
	CCriticalSection m_csXprint;


	char	m_errmsg[256];
	char	m_logDir[256];
	char	m_logFileName[256];

	BOOL	m_bInited;

	int		RotateLogFile();

	

public:
	//*------------------------------------------------------------------------------------
	int		InitLogFile(char *strLogDir, char * strLogFileName,bool bApply);	// 로그파일 초기화 - 파일경로(절대경로 또는 상대경로, default "app.log"), 파일명
	
	int       SetLogParamFile(char *strLogDir, char * strLogFileName);	
	int		Logging(char *logString);		// 로그 기록 - 단순 문자열

	int      DataLogging(char *StrLog);		// 로그 기록 - 실시간 문자열
	void	xfprintf(int Num,char* format, ...);	// 로그 기록 - printf 스타일
   	int		LogFileOpen();
//	void	dfprintf(char* format, ...);	// 로그 기록 - printf 스타일

	//*------------------------------------------------------------------------------------
	char *	errmsg();						// 최종 에러 메시지 얻기
	char *	errmsg(DWORD errorcode) ;		// 최종 에러 메시지 얻기
	int		GetModulePath(char *path, int buffsize); // 실행 프로그램의 현재 위치(절대경로) 얻기
	//*------------------------------------------------------------------------------------
	void SetLogFileSize(long nMaxSizeBytes);	//로그파일최대크기세팅(바이트), 최대 1GB 까지 설정 가능, 로그 라인단위로 절삭되므로 지정 크기보다 조금 작거나 클 수 있음
	void SetLogFileCount(long nMaxCount);	//로그파일 백업 갯수, 최대 100개 까지 설정 가능
   int		LogFileClose();


   	CTimeSpan m_SumT;					   // sum of previous intervals      (이전 간격의 합)
	CTimeSpan m_DTime;					   // elapsed time of this interval  (간격에 따라. 흘러간 시간)
	//long m_lCount;			       		            // countdown time in seconds      (매초 마다의 카운트다운 시간)
	CString GetHMS;
	void Display();			                             // display panels(switch m_Status)   (패널에 디스플레이함) (m_Status ,, 0,1,2,3)..
	void DisplayNormalHMS();	          // display panels(switch m_nHMS when m_status is 0 or 1)  (패널에 디스플레이함),m_status = 0,1

		
	int Time_Status;		//0: 타이머가 멈출때, 1: 타이머가 동작할때 (ON), 2: 카운트 다운이 중지 될때, 3: 카운트 다운이 동작할때.
 
	// 시, 분, 초 , 카운트
	int m_nHMS;			//0  if hh:mm:ss..
	int m_nSec;
	int m_nCnt;


	CString m_Timer;
	 void OnSwapData();
	 char *GetToken(char *parm_data, char *parm_token);

		FILE *	m_pFLogFile;
};

#endif

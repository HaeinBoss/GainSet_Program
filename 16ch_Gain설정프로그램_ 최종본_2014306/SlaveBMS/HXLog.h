/* 
 * CHXLog v1.0
 * Copyright (C) 2010 by ENICS CHUNG - <enics_sky@naver.com>
 *
 * ���۱�
 *  �� �ҽ��� ������ �����ϳ� �����, �Ǹ�, �뿩�� ������ �ʽ��ϴ�.
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
	long	m_lMaxLogSizeBytes;	//�α� �ִ� ũ��(byte) 1048576 = 1MB
	int		m_lMaxLogFileCount; // �α� ���� �ִ� ���� (��� �����̼�)

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
	int		InitLogFile(char *strLogDir, char * strLogFileName,bool bApply);	// �α����� �ʱ�ȭ - ���ϰ��(������ �Ǵ� �����, default "app.log"), ���ϸ�
	
	int       SetLogParamFile(char *strLogDir, char * strLogFileName);	
	int		Logging(char *logString);		// �α� ��� - �ܼ� ���ڿ�

	int      DataLogging(char *StrLog);		// �α� ��� - �ǽð� ���ڿ�
	void	xfprintf(int Num,char* format, ...);	// �α� ��� - printf ��Ÿ��
   	int		LogFileOpen();
//	void	dfprintf(char* format, ...);	// �α� ��� - printf ��Ÿ��

	//*------------------------------------------------------------------------------------
	char *	errmsg();						// ���� ���� �޽��� ���
	char *	errmsg(DWORD errorcode) ;		// ���� ���� �޽��� ���
	int		GetModulePath(char *path, int buffsize); // ���� ���α׷��� ���� ��ġ(������) ���
	//*------------------------------------------------------------------------------------
	void SetLogFileSize(long nMaxSizeBytes);	//�α������ִ�ũ�⼼��(����Ʈ), �ִ� 1GB ���� ���� ����, �α� ���δ����� ����ǹǷ� ���� ũ�⺸�� ���� �۰ų� Ŭ �� ����
	void SetLogFileCount(long nMaxCount);	//�α����� ��� ����, �ִ� 100�� ���� ���� ����
   int		LogFileClose();


   	CTimeSpan m_SumT;					   // sum of previous intervals      (���� ������ ��)
	CTimeSpan m_DTime;					   // elapsed time of this interval  (���ݿ� ����. �귯�� �ð�)
	//long m_lCount;			       		            // countdown time in seconds      (���� ������ ī��Ʈ�ٿ� �ð�)
	CString GetHMS;
	void Display();			                             // display panels(switch m_Status)   (�гο� ���÷�����) (m_Status ,, 0,1,2,3)..
	void DisplayNormalHMS();	          // display panels(switch m_nHMS when m_status is 0 or 1)  (�гο� ���÷�����),m_status = 0,1

		
	int Time_Status;		//0: Ÿ�̸Ӱ� ���⶧, 1: Ÿ�̸Ӱ� �����Ҷ� (ON), 2: ī��Ʈ �ٿ��� ���� �ɶ�, 3: ī��Ʈ �ٿ��� �����Ҷ�.
 
	// ��, ��, �� , ī��Ʈ
	int m_nHMS;			//0  if hh:mm:ss..
	int m_nSec;
	int m_nCnt;


	CString m_Timer;
	 void OnSwapData();
	 char *GetToken(char *parm_data, char *parm_token);

		FILE *	m_pFLogFile;
};

#endif

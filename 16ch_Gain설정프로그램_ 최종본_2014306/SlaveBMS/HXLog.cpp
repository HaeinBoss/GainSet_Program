/* 
 * CHXLog v1.0
 * Copyright (C) 2010 by ENICS CHUNG - <enics_sky@naver.com>
 *
 * 저작권
 *  이 소스는 수정은 가능하나 재배포, 판매, 대여는 허용되지 않습니다.
 *
 */

#include "stdafx.h"
#include "HXLog.h"
//
//#define	DEFAULT_LOGFILENAME	"app.csv"

CHXLog::CHXLog(void)
{
	m_pFLogFile = NULL;
	memset(m_errmsg, 0, sizeof(m_errmsg));
	memset(m_logDir, 0, sizeof(m_logDir));
	memset(m_logFileName, 0, sizeof(m_logFileName));

	//*-------------------------------------------------------
	m_lMaxLogSizeBytes = 1048576;	//1048576 = 1MB
	m_lMaxLogFileCount = 5;
	//*-------------------------------------------------------

	m_bInited = FALSE;

	m_SumT=m_DTime=CTimeSpan(0,0,0,0);	// initially elapsed time is 0
	m_nHMS=0;			// initially display format is hh:mm:ss

	m_nHMS = 0;
	m_nSec = 0;
	m_nCnt = 0;

	Time_Status=0;



}

CHXLog::~CHXLog(void)
{
	//LogFileClose();


}



int CHXLog::SetLogParamFile(char *strLogDir, char * strLogFileName)
{
	if(m_bInited)
	{

		return TRUE;
	}

	char szS5FileName[128];
	int len=0;

	// log path
	memset(m_logDir, 0, sizeof(m_logDir));
	
	if (strLogDir != NULL && strlen(strLogDir) > 1)
		sprintf(m_logDir, "%s", strLogDir);
	else
	{
		char path[MAX_PATH] = {0};
		if (GetModulePath(path, MAX_PATH) )
			strcpy(m_logDir, path);
		else
			strcpy(m_logDir, ".");
	}

	if ((len=strlen(m_logDir)) > 0  && (m_logDir[len-1] != '\\') )
	{
		strcat(m_logDir, "\\");
	}
	strcpy(szS5FileName, m_logDir);
	

	// log file name
	memset(m_logFileName, 0, sizeof(m_logFileName));

	if (strLogFileName != NULL && strlen(strLogFileName) > 1)
	{
		sprintf(m_logFileName, "%s", strLogFileName);
	}
		/*else
		strcat(m_logFileName, DEFAULT_LOGFILENAME);*/

		strcat(szS5FileName, m_logFileName);
	
	if( (m_pFLogFile = fopen(szS5FileName,"a+")) == NULL )
	{
		memset(m_errmsg, 0, sizeof(m_errmsg));
		sprintf(m_errmsg, "[ERROR] creating log file \"%s\": %s ", szS5FileName, errmsg(::GetLastError()) );
		perror(m_errmsg);

		m_bInited = FALSE;

		return 0;
	}


	fflush(m_pFLogFile);

	m_bInited = TRUE;

  return 1;

}

int CHXLog::InitLogFile(char *strLogDir, char * strLogFileName,bool bApply)
{
	if(m_bInited)
	{

		return TRUE;
	}

	char szS5FileName[128];
	int len=0;

	// log path
	memset(m_logDir, 0, sizeof(m_logDir));
	
	if (strLogDir != NULL && strlen(strLogDir) > 1)
		sprintf(m_logDir, "%s", strLogDir);
	else
	{
		char path[MAX_PATH] = {0};
		if (GetModulePath(path, MAX_PATH) )
			strcpy(m_logDir, path);
		else
			strcpy(m_logDir, ".");
	}

	if ((len=strlen(m_logDir)) > 0  && (m_logDir[len-1] != '\\') )
	{
		strcat(m_logDir, "\\");
	}
	strcpy(szS5FileName, m_logDir);
	

	// log file name
	memset(m_logFileName, 0, sizeof(m_logFileName));

	if (strLogFileName != NULL && strlen(strLogFileName) > 1)
	{
		sprintf(m_logFileName, "%s", strLogFileName);
	}
	/*else
		strcat(m_logFileName, DEFAULT_LOGFILENAME);*/

	strcat(szS5FileName, m_logFileName);
	
	if( (m_pFLogFile = fopen(szS5FileName,bApply? "a" : "w")))
	{
		memset(m_errmsg, 0, sizeof(m_errmsg));
		sprintf(m_errmsg, "[ERROR] creating log file \"%s\": %s ", szS5FileName, errmsg(::GetLastError()) );
		perror(m_errmsg);

		m_bInited = FALSE;

		return 0;
	}

	fflush(m_pFLogFile);

	m_bInited = TRUE;

  return 1;
}

void CHXLog::SetLogFileSize(long nMaxSize){ if(nMaxSize<1) return; if(nMaxSize >1073741824){ m_lMaxLogSizeBytes = 1073741824L; return;}  m_lMaxLogSizeBytes= nMaxSize; return;   }

void CHXLog::SetLogFileCount(long nMaxCount){ if(nMaxCount<0) return; if(nMaxCount >100){ m_lMaxLogFileCount = 100; return;}  m_lMaxLogFileCount= nMaxCount; return;   }


int CHXLog::Logging(char *logString)
{	
	char strTimebuf[1000];

	time_t now = time(NULL);

	CString str=_T("");

	 Time_Status =1;
	if(m_pFLogFile)
	{
		m_csLog.Lock(); 
		
		str.Format("%d",m_nCnt+1);
		//fprintf(m_pFLogFile,"[%s ",strTimebuf);		
		//printf("[%s ",strTimebuf);

	
		strcpy(strTimebuf, (const char *)str); 
		fprintf(m_pFLogFile,"%s, ",strTimebuf);		
		printf("%s, ",strTimebuf);

		_strdate_s( strTimebuf, 128 );
		fprintf(m_pFLogFile,"%s, ",strTimebuf);		
		printf("%s,",strTimebuf);

	//	_strtime_s(strTimebuf,128);
		strcpy(strTimebuf, (const char *)GetHMS); 	
		fprintf(m_pFLogFile,"%s",strTimebuf);
		printf("%s",strTimebuf);

		//printf("%s\n",logString);

		fprintf(m_pFLogFile,"%s\n",logString);
		fflush(m_pFLogFile);

	//	RotateLogFile();

		m_csLog.Unlock();
	}
	else
	{
		memset(m_errmsg, 0, sizeof(m_errmsg));
		sprintf(m_errmsg, "[ERROR] log file pointer is null.");

		return 0;
	}

  return 1;
}



int CHXLog::DataLogging(char* strLog)
{

	//char strTimebuf[128];
	  //	time_t now = time(NULL);

	if(m_pFLogFile)
	{
		m_csLog.Lock(); 

		//_strdate_s( strTimebuf, 128 );
		//fprintf(m_pFLogFile,"[%s ",strTimebuf);		
		//printf("[%s ",strTimebuf);

		//_strtime_s(strTimebuf,128);
		//fprintf(m_pFLogFile,"%s] ",strTimebuf);
		//printf("%s] ",strTimebuf);

	//	printf("%s\n",logString);

		fprintf(m_pFLogFile,"%s\n",strLog);
		fflush(m_pFLogFile);

	//	RotateLogFile();

		m_csLog.Unlock();
	}
	else
	{
		memset(m_errmsg, 0, sizeof(m_errmsg));
		sprintf(m_errmsg, "[ERROR] log file pointer is null.");

		return 0;
	}

  return 1;

}

int CHXLog::LogFileOpen()
{
	char szS5FileName[128];

	if (m_logDir != NULL && strlen(m_logDir))
			strcpy(szS5FileName, m_logDir);

	if (m_logFileName != NULL && strlen(m_logFileName))
	{
		strcat(szS5FileName, m_logFileName);
	}
	//else
	//{
	//	strcat(szS5FileName, DEFAULT_LOGFILENAME);
	//}
	
	if( (m_pFLogFile = fopen(szS5FileName,"a+")) == NULL )
	{
		memset(m_errmsg, 0, sizeof(m_errmsg));
		sprintf(m_errmsg, "[ERROR] opening log file \"%s\": %s", szS5FileName, errmsg(::GetLastError()) );
		perror(m_errmsg);

		return 0;
	}
	fflush(m_pFLogFile);

	return 1;
}

int CHXLog::LogFileClose()
{
	if( m_pFLogFile && fclose(m_pFLogFile) )
	{
		perror("[ERRO] Error closing log file$\nSystem Error: \n");

		memset(m_errmsg, 0, sizeof(m_errmsg));
		sprintf(m_errmsg, "[ERROR] closing log file: %s", errmsg(::GetLastError()) );
		perror(m_errmsg);
		
		return 0;
	}

	 Time_Status =2;
	  Display();
	 m_pFLogFile = NULL;

	return 1;
}


/**
 * function : RotateLogFile
 * parameter :
 * return :
		0 = fail
		1 = success
**/
int CHXLog::RotateLogFile()
{
	int  i;
	long	lsize;
	char *pcTmp=NULL;
	char szBaseFilename[MAX_PATH];
	char szOldFilename[MAX_PATH], szNewFilename[MAX_PATH];
	char szLogFileName[MAX_PATH];

	if (m_pFLogFile == NULL)
	{	
		memset(m_errmsg, 0, sizeof(m_errmsg));
		sprintf(m_errmsg, "[ERROR] log file pointer is null.");
		perror(m_errmsg);

		return 0;
	}
	
	if ( (lsize = ftell(m_pFLogFile)) < m_lMaxLogSizeBytes) // max file size, 1048576 = 1M byte
	{
		return 1;

	}

	// close file;
	LogFileClose(); 

	memset(szLogFileName, 0, sizeof(szLogFileName));
	memset(szBaseFilename, 0, sizeof(szBaseFilename));
	memset(szOldFilename, 0, sizeof(szOldFilename));
	memset(szNewFilename, 0, sizeof(szNewFilename));

	if (m_logDir != NULL && strlen(m_logDir))
			strcpy(szLogFileName, m_logDir);

	if (m_logFileName != NULL && strlen(m_logFileName))
	{
		strcat(szLogFileName, m_logFileName);
	}
	//else
	//{
	//	strcat(szLogFileName, DEFAULT_LOGFILENAME);
	//}	
	//
	strcpy(szBaseFilename,szLogFileName);
	pcTmp = strrchr(szBaseFilename, '.');
	if(pcTmp != NULL)
		pcTmp[1] = 0x00;

	// 마지막 파일 삭제
	sprintf(szNewFilename, "%s%02d", szBaseFilename, m_lMaxLogFileCount);
	_unlink(szNewFilename);

	// 파일 확장자 1씩 증가
	for (i = m_lMaxLogFileCount - 1; i > 0; i--)
	{
		sprintf(szOldFilename, "%s%02d", szBaseFilename, i);
		sprintf(szNewFilename, "%s%02d", szBaseFilename, i+1);
		rename(szOldFilename, szNewFilename);
	}

	if(m_lMaxLogFileCount>0)
	{
		strcpy(szOldFilename, szLogFileName);
		sprintf(szNewFilename, "%s01", szBaseFilename);
		rename(szOldFilename, szNewFilename);
	}
	else
	{	
		_unlink(szLogFileName);
	}

	// open log file;
	LogFileOpen();

	return 1;
}


char *CHXLog::errmsg() {
	return errmsg(::GetLastError());
}

char *CHXLog::errmsg(DWORD errorcode) {
		
		LPVOID lpMsgBuf=NULL;
		memset(_h_errormessage_, 0, 256);

		if (errorcode == 0)
			return NULL;
		
		if (!FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
							FORMAT_MESSAGE_FROM_SYSTEM |
							FORMAT_MESSAGE_IGNORE_INSERTS ,
						   NULL, 
						   errorcode,
						   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
						   (LPTSTR) &lpMsgBuf, 
						   0, 
						   NULL ))
		{
			//printf("Format message failed with 0x%x\n", errorcode);
			_snprintf(_h_errormessage_, 256, "unknown error. code=%u", errorcode);
			
		}
		else
		{
			LPTSTR p = (LPTSTR)strchr((char *)lpMsgBuf, (int)'\r');//_tcschr(lpMsgBuf, '\r');
			 if(p != NULL)
				{ /* lose CRLF */
				 *p = '\0';
				} /* lose CRLF */
			 
			 p = (LPTSTR)strchr((char *)lpMsgBuf, (int)'\n');//_tcschr(lpMsgBuf, '\r');
			 if(p != NULL)
				{ /* lose CRLF */
				 *p = '\0';
				} /* lose CRLF */

			_snprintf(_h_errormessage_, 256, "%s code=%u", lpMsgBuf, errorcode);
		}
		//printf("error message: %s\n", lpMsgBuf);
		//printf("file path: %s\n", szFilename);
		if (lpMsgBuf)
			LocalFree(lpMsgBuf);

		return _h_errormessage_;
}



int CHXLog::GetModulePath(char *path, int buffsize)
{
	int i;

	if (path == NULL || buffsize < 1)
		return 0;

	memset(path, 0, buffsize);

	if ( GetModuleFileName(NULL, path, buffsize) == 0)
		return 0;

	for(i= strlen(path) - 1 ; i >=0 ; --i)
	{
		if (path[i] == '\\')
		{
			path[i] = 0x00;
			return 1;
		}
	}

	return 0;
}


void CHXLog::xfprintf(int Num,char* format, ...)
{
	
	m_csXprint.Lock();
	if (1)
	{

		int ret=0;
		char logString[4000]={0};
		va_list valist;
		//time_t now = time(NULL);
		//struct tm today;
		va_start(valist, format);

		/*
		_strdate_s( strTimebuf, 128 );		
		fprintf(stream,"[%s ",strTimebuf);
		printf("[%s ",strTimebuf);		
		_strtime_s(strTimebuf,128);		
		fprintf(stream,"%s] ",strTimebuf);
		printf("%s] ",strTimebuf);
		*/

		vsprintf(logString, format, valist);	

		if(  Num==0)
		{
			DataLogging(logString);
		}
		else
		{
		   Logging(logString);

		}
		va_end(valist);
	}
	m_csXprint.Unlock();
	
	return;
}




void CHXLog::Display()
{
		CString strMsg;

		// update timer
		switch(Time_Status)
		{
			case 0:																   // When Timer Stop
			  DisplayNormalHMS();
			  GetHMS= m_Timer + strMsg;
			   break;

			case 1:										 // 타이머가 켜질때..
				m_nSec++;							// 시간이 흐르면서 바뀜
				DisplayNormalHMS();
				m_nCnt++;	
				GetHMS=m_Timer + strMsg;
				//DataWrite(	);
				break;

			case 2:
				// if countdown is paused
				m_nSec++;	// update elapsed time
				DisplayNormalHMS();

				m_nCnt++;	
				GetHMS += strMsg;
				break;

			default:
			TRACE0("Status variable is not correct");
			break;

		}

}


void CHXLog::DisplayNormalHMS()
{
	 int nHour, nMin, nSec;		// number of hours, minutes, seconds elapsed
	m_DTime = m_nSec;

	SYSTEMTIME s_time;
	GetLocalTime(&s_time);
	nHour = s_time.wHour;
	nMin = s_time.wMinute;
	nSec = s_time.wSecond;

	switch(m_nHMS)
	{
	  case 0:		//if HH:MM:SS  is selected
		  m_Timer.Format(" %02d:%02d:%02d", nHour, nMin, nSec);
	    break;

	  case 1:		//if  MMMM:SS is selected
     	  m_Timer.Format(" %7d:%2d", 60*nHour+nMin, nSec);
	    break;

	  case 2:	  // if SSSSSS is selected	
		  m_Timer.Format(" %12d", 3600*nHour + 60*nMin + nSec);
	    break;
	
	  default:
		break;

	}

}


//
//// // original       if(*parm_data == ' ' || *parm_data == ';' || *parm_data == '|' || *parm_data == '\t' || *parm_data == ',') break; 
char *CHXLog::GetToken(char *parm_data, char *parm_token)
{
	while(*parm_data != 0 && *parm_data != '\n')
	{ 

        if( *parm_data == ',' )
		{		
			break; 
		}
		else 
		{
			*parm_token =*parm_data; 
		}
        parm_data++; 
        parm_token++; 
    } 

    *parm_token = '\0'; 

    return parm_data + 1; 

}






//KThread.cpp
#include "stdafx.h"
#include "KThread.h"

namespace KSYSTEMS
{
CKThread::CKThread()
{
	m_dwTime=1000;
	m_hThread=INVALID_HANDLE_VALUE;
	m_hEvent =::CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, 0, 0);
}

CKThread::~CKThread()
{
	if(IsRun())	Stop(true);
	::CloseHandle(m_hThread);
	::CloseHandle(m_hEvent);
}

void CKThread::SetWaitTime(DWORD dwTime)
{
	m_dwTime= dwTime;
}

BOOL CKThread::SetPriority( int nPriority)
{
	return ::SetThreadPriority(m_hThread, nPriority);
}

DWORD CKThread::SuspendThread()
{
	return ::SuspendThread(m_hThread);
}

DWORD CKThread::ResumeThread()
{
	return ::ResumeThread(m_hThread);
}

//CreateThread( 
//            NULL,                   // default security attributes
//            0,                      // use default stack size  
//            MyThreadFunction,       // thread function name
//            pDataArray[i],          // argument to thread function 
//            0,                      // use default creation flags 
//            &dwThreadIdArray[i]);   // returns the thread identifier 

BOOL CKThread::Start(LPFUNC lpfunc, LPVOID lpData)
{
	if(IsRun())	return 1;

	m_lpfunc=lpfunc;
	m_lpData=lpData;

	m_hThread = ::CreateThread(NULL, 0, CKThread::FNTHREAD, (LPVOID)this, 0, NULL);

	if(m_hThread==INVALID_HANDLE_VALUE)
		return 0;
										/*THREAD_PRIORITY_ABOVE_NORMAL*/
	return SetPriority(THREAD_PRIORITY_ABOVE_NORMAL);
}

DWORD CALLBACK CKThread::FNTHREAD(LPVOID lpData)
{
	CKThread* pThread=(CKThread*)lpData;


	if(pThread->m_lpfunc)
	{
		(*pThread->m_lpfunc)(pThread, pThread->m_lpData);
	}
	else
	{
		if(!pThread->InitInstance())
		{
			pThread->OnInitError();
			return 0;
		}

		pThread->Run();
		pThread->ExitInstance();
	}
	return 0;
}

BOOL CKThread::InitInstance()
{
	return 1;
}

void CKThread::OnInitError()
{

}

void CKThread::ExitInstance()
{
}

BOOL CKThread::IsRun()
{
	DWORD dwStatus;
	if(m_hThread==INVALID_HANDLE_VALUE)
		return 0;
	::GetExitCodeThread(m_hThread, &dwStatus);

	return (dwStatus==STILL_ACTIVE);
}

BOOL CKThread::Stop(bool bSurely)
{
	if(!IsRun())	return 1;

	SetQueue(KTE_STOP,0);
	if(bSurely)
		::TerminateThread(m_hThread, DWORD(-1));

	if(!IsRun())
	{
		::CloseHandle(m_hThread);
		m_hThread=INVALID_HANDLE_VALUE;
		return 1;
	}
	return 0;
}

BOOL CKThread::SetQueue(DWORD dwEvent, DWORD dwData)
{
	return ::PostQueuedCompletionStatus(m_hEvent, dwEvent, dwData, NULL);
}

//작업지시를 얻는다.
BOOL CKThread::GetQueue(DWORD* lpEvent, DWORD* lpData)
{
	OVERLAPPED*	lpOverlapped=NULL;
	return ::GetQueuedCompletionStatus(m_hEvent, lpEvent, lpData, &lpOverlapped, m_dwTime);
}

void CKThread::Run()
{
	DWORD dwEvent=0, dwData=0;
	while(1)
	{
		if(!GetQueue(&dwEvent, &dwData))
		{
			if((dwEvent=GetLastError())!=KTE_TIMEOUT)
				break;
		}
		//쓰레드 종료 이벤트
		if(dwEvent==KTE_STOP)
			break;
		
		if(!OnEvent(dwEvent, dwData))
			break;

		dwEvent=0; 
		dwData=0;
	}
}

BOOL CKThread::OnEvent(DWORD dwEvent, DWORD dwData)
{
	return 1;
}

}//namespace KSYSTEMS


// SThread.cpp : implementation file
//

#include "stdafx.h"
#include "SThread.h"

//HANDLE CreateIoCompletionPort( HANDLE FileHandle,
//                                                               HANDLE ExistingCompletionPort,
//                                                               DWORD CompletionKey,
//                                                               DWORD NumberOfConcurrentThreads
// CSThread


// ���� ����Ʈ : http://codeoz.tistory.com/13
// 
// # NumberOfconcurrentThreads : ������ Completion Port ������Ʈ�� �Ҵ��� �������� ���� �����Ѵ�.
// ���࿡ 3�� ���޵Ǹ� Completion Port���� ������� �Ϸ�Ǿ��� ��� ������ ó���� �� �� �ִ�, 
//  ���� ���� ������ �������� ���� �� 3���� �ȴ�. 0�� �����ϴ� ���� 1�� �����ϴ� ��� ���̰� ���� ���̴�.
// - Completion Port������Ʈ�� �����ϴµ� �־ �ʿ��� ���ڴ� �̰� �ϳ���. ������ ���ڴ� ù��°���� 
//  ������� INVALID_HANDLE_VALUE, NULL, 0�� �����ϸ� �ȴ�.
//  (������ ���ڴ� CreateIoCompletionPort �Լ��� �ι�° ����� ����ϴµ� �ʿ��� �͵��̴�.
//

namespace KSYSTEMS2
{
CSThread::CSThread()
{
   s_dwTime=1000;
   s_hThread=INVALID_HANDLE_VALUE;
   s_hEvent =::CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, 0, 0);
}


CSThread::~CSThread()
{
	if(IsRun())    Stop(true);
	::CloseHandle(s_hThread);
   ::CloseHandle(s_hEvent);
}

void CSThread::SetWaitTime(DWORD dwTime)
{
	s_dwTime = dwTime;

}


BOOL CSThread::SetPriority( int nPriority)
{
	return ::SetThreadPriority(s_hThread, nPriority);
}

DWORD CSThread::SuspendThread()
{

	return ::SuspendThread(s_hThread);

}

DWORD CSThread::ResumeThread()
{
	return ::ResumeThread(s_hThread);

}

//CreateThread( 
//            NULL,                   // default security attributes
//            0,                      // use default stack size  
//            MyThreadFunction,       // thread function name
//            pDataArray[i],          // argument to thread function 
//            0,                      // use default creation flags 
//            &dwThreadIdArray[i]);   // returns the thread identifier 

BOOL CSThread::Start(LPFUNC2 lpfunc, LPVOID lpData)
{
	if(IsRun())	return 1;

	m_lpfunc=lpfunc;
	m_lpData=lpData;

	//s_hThread = ::CreateThread(NULL, 0, CSThread::FNTHREAD2, (LPVOID)this,0, NULL);
							    
	s_hThread = ::CreateThread(NULL, 0, CSThread::FNTHREAD2, (LPVOID)this,0,NULL);
	if(s_hThread==INVALID_HANDLE_VALUE)
		return 0;									

	//THREAD_PRIORITY_ABOVE_NORMAL
	return SetPriority(THREAD_PRIORITY_ABOVE_NORMAL);
}

DWORD CALLBACK CSThread::FNTHREAD2(LPVOID lpData)
{
	CSThread* sThread=(CSThread*)lpData;


	if(sThread->m_lpfunc)
	{	 
		(*sThread->m_lpfunc)(sThread, sThread->m_lpData);
		//(*pThread->m_lpfunc)(pThread, pThread->m_lpData);
	}
	else
	{
		if(!sThread->InitInstance())
		{
			sThread->OnInitError();
			return 0;
		}

		sThread->Run();
		sThread->ExitInstance();
	}
	return 0;
}

BOOL CSThread::InitInstance()
{
	return 1;
}

void CSThread::OnInitError()
{

}

void CSThread::ExitInstance()
{
}

BOOL CSThread::IsRun()
{
	DWORD dwStatus;
	if(s_hThread==INVALID_HANDLE_VALUE)
		return 0;
	::GetExitCodeThread(s_hThread, &dwStatus);

	return (dwStatus==STILL_ACTIVE);
}

BOOL CSThread::Stop(bool bSurely)
{
	if(!IsRun())	return 1;

	SetQueue(STE_STOP,0);
	if(bSurely)
		::TerminateThread(s_hThread, DWORD(-1));

	if(!IsRun())
	{
		::CloseHandle(s_hThread);
		s_hThread=INVALID_HANDLE_VALUE;
		return 1;
	}
	return 0;
}

BOOL CSThread::SetQueue(DWORD dwEvent, DWORD dwData)
{
	return ::PostQueuedCompletionStatus(s_hEvent, dwEvent, dwData, NULL);
}

//�۾����ø� ��´�.
BOOL CSThread::GetQueue(DWORD* lpEvent, DWORD* lpData)
{
	OVERLAPPED*	lpOverlapped=NULL;
	return ::GetQueuedCompletionStatus(s_hEvent, lpEvent, lpData, &lpOverlapped, s_dwTime);
}

void CSThread::Run()
{
	DWORD dwEvent=0, dwData=0;
	while(1)
	{
		if(!GetQueue(&dwEvent, &dwData))
		{
			if((dwEvent=GetLastError())!=STE_TIMEOUT)
				break;
		}
		//������ ���� �̺�Ʈ
		if(dwEvent==STE_STOP)
			break;
		
		if(!OnEvent(dwEvent, dwData))
			break;

		dwEvent=0; 
		dwData=0;
	}
}

BOOL CSThread::OnEvent(DWORD dwEvent, DWORD dwData)
{
	return 1;
}

}//namespace KSYSTEMS2



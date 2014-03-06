// SThread.cpp : implementation file
//

#include "stdafx.h"
#include "SThread.h"

//HANDLE CreateIoCompletionPort( HANDLE FileHandle,
//                                                               HANDLE ExistingCompletionPort,
//                                                               DWORD CompletionKey,
//                                                               DWORD NumberOfConcurrentThreads
// CSThread


// 참고 사이트 : http://codeoz.tistory.com/13
// 
// # NumberOfconcurrentThreads : 생성된 Completion Port 오브젝트에 할당할 쓰레드의 수를 결정한다.
// 만약에 3이 전달되면 Completion Port에서 입출력이 완료되었을 경우 적절한 처리를 할 수 있는, 
//  동시 실행 가능한 쓰레드의 수는 총 3개가 된다. 0이 전달하는 경우와 1을 전달하는 경우 차이가 없을 것이다.
// - Completion Port오브젝트를 생성하는데 있어서 필요한 인자는 이것 하나다. 나머지 인자는 첫번째부터 
//  순서대로 INVALID_HANDLE_VALUE, NULL, 0을 전달하면 된다.
//  (나머지 인자는 CreateIoCompletionPort 함수의 두번째 기능을 사용하는데 필요한 것들이다.
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

//작업지시를 얻는다.
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
		//쓰레드 종료 이벤트
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



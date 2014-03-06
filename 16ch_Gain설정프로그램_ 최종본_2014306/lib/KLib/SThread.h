
/*/////////////////////////////////////////////////////////////
   생성일  2013-05-29
   수정일 :  미정
/*/////////////////////////////////////////////////////////////


// CSThread.h
#ifndef _STHREAD_H_
#define _STHREAD_H_

/*/////////////////////////////////////////////////////////////
//namespace
/*/////////////////////////////////////////////////////////////
namespace KSYSTEMS2
{
	//STHREAD EVENT
#define   STE_TIMEOUT		WAIT_TIMEOUT
#define	STE_EVENT		((DWORD)0xF0000000L)
#define   STE_STOP		 STE_EVENT+1
#define   STE_UID		STE_EVENT+1000
#define   STE_UID1		STE_UID+1
#define   STE_UID2		STE_UID+2
#define   STE_UID3		STE_UID+3
#define   STE_UID4		STE_UID+4
#define   STE_UID5		STE_UID+5

class CSThread;
typedef BOOL	 (WINAPI *LPFUNC2)(CSThread* pSThread, LPVOID pData2);

//typedef void (CALLBACK *LPUSRFUNC)(CKThread* pThread, LPVOID lpData);

/*/////////////////////////////////////////////////////////////
//	클래스:CSThread
/*/////////////////////////////////////////////////////////////



class CSThread 
{
	//DECLARE_DYNAMIC(CSThread)

public:
	CSThread();
	~CSThread();

	// 현재 쓰레드가 생성되어 있는지 여부
	BOOL IsRun();

	//쓰레드 기동
	BOOL Start(LPFUNC2 lpfunc=NULL, LPVOID lpData=NULL);

	//쓰레드 중지 (함수 인자는 확실히 중지 시키려면 true로 설정)
	BOOL Stop(bool bSurely=false);

    // 쓰레드 대기 시간 (milisecond)
	void SetWaitTime(DWORD dwTime);

	// 쓰레드의 중요도를 설정하는 것이며 일반적으로 THREAD_PRIORITY_ABOVE_NORMAL을 설정한다.
	BOOL SetPriority(int nPriority);

	//쓰레드 일시정지
	DWORD SuspendThread();

	//일시 정지된 쓰레드를 기동
	DWORD ResumeThread();

	//작업을 지시한다.
	BOOL SetQueue(DWORD dwEvent, DWORD dwData);

	//작업을 대기한다.
	BOOL GetQueue(DWORD* lpEvent, DWORD* lpData);

	LPFUNC2 m_lpfunc;
	LPVOID m_lpData;

protected:
	// 쓰레드 함수
	static DWORD CALLBACK FNTHREAD2(LPVOID lpData);

	// Thread Ready	인스턴스 초기화
	virtual BOOL InitInstance();

	//InitInstance Error Call Function
	virtual void OnInitError();

	// Thread Exit
	virtual void ExitInstance();

	//FNTHREAD2 -> Run()
	virtual void Run();

	// 이벤트 발생시 호출
 	virtual BOOL OnEvent(DWORD dwEvent,DWORD dwData);

protected:
	HANDLE s_hThread;
	HANDLE s_hEvent;
	DWORD s_dwTime;
};

template <class CParent>
class CSThreadT : public CSThread
{
  public:
    BOOL Start(CParent* pParent)
	{
		  m_sParent = pParent;
		  return CSThread::Start();
	}

protected:
	  // 주기적으로 호출되는 함수
	 //OnCallThread()의 리턴값이 FALSE 이면 쓰레드가 종료된다.
	virtual BOOL OnEvent(DWORD dwEvent, DWORD dwData)
	{
		return m_sParent->OnCallThread(dwEvent, dwEvent);
	}

   protected:
	CParent* m_sParent;

    };

}//namespace KSYSTEMS2

#endif //_STHREAD_H_
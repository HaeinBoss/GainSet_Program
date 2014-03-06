/*/////////////////////////////////////////////////////////////
생성일  2002-12
수정일	2004-03-30
/*/////////////////////////////////////////////////////////////


//KThread.h
#ifndef _KTHREAD_H_
#define _KTHREAD_H_

/*/////////////////////////////////////////////////////////////
//namespace
/*/////////////////////////////////////////////////////////////
namespace KSYSTEMS
{
//KTHREAD EVENT
#define KTE_TIMEOUT		WAIT_TIMEOUT
#define	KTE_EVENT		((DWORD)0xF0000000L)
#define KTE_STOP		KTE_EVENT+1
#define KTE_UID			KTE_EVENT+1000
#define KTE_UID1		KTE_UID+1
#define KTE_UID2		KTE_UID+2
#define KTE_UID3		KTE_UID+3
#define KTE_UID4		KTE_UID+4
#define KTE_UID5		KTE_UID+5

class CKThread;
typedef BOOL (WINAPI *LPFUNC)(CKThread* pKThread, LPVOID pData);

//typedef void (CALLBACK *LPUSRFUNC)(CKThread* pThread, LPVOID lpData);

/*/////////////////////////////////////////////////////////////
//	클래스:CKThread
/*/////////////////////////////////////////////////////////////
class CKThread
{
public:

	CKThread();
	~CKThread();

	//현재 쓰레드가 생성되어 있는지 여부
	BOOL IsRun();

	//쓰레드 기동
	BOOL Start(LPFUNC lpfunc=NULL, LPVOID lpData=NULL);

	//쓰레드 중지 (함수 인자는 확실히 중지 시키려면 true로 설정)
	BOOL Stop(bool bSurely=false);

	//쓰레드 대기 시간(milisecond)
	void SetWaitTime(DWORD dwTime);

	//쓰레드의 중요도를 설정하는 것이며 일반적으로 THREAD_PRIORITY_ABOVE_NORMAL을 설정한다.
	BOOL SetPriority(int nPriority);

	//쓰레드 일시정지
	DWORD SuspendThread();

	//일시 정지된 쓰레드를 기동
	DWORD ResumeThread();

	//작업을 지시한다.
	BOOL SetQueue(DWORD dwEvent, DWORD dwData);

	//작업을 대기한다.
	BOOL GetQueue(DWORD* lpEvent, DWORD* lpData);

	LPFUNC m_lpfunc;
	LPVOID m_lpData;
protected:
	//쓰레드 함수
	static DWORD CALLBACK FNTHREAD(LPVOID lpData);

	//Thread Ready
	virtual BOOL InitInstance();

	//InitInstance Error Call Function
	virtual void OnInitError();

	//Thread Exit
	virtual void ExitInstance();

	//FNTHREAD() -> Run()
	virtual void Run();

	//이벤트 발생시 호출된다.
	virtual BOOL OnEvent(DWORD dwEvent, DWORD dwData);

protected:
	HANDLE m_hThread;
	HANDLE m_hEvent;
	DWORD  m_dwTime;
};

template <class CParent>
class CKThreadT : public CKThread
{
public:
	BOOL Start(CParent* pParent)
	{
		m_pParent=pParent;
		return CKThread::Start();
	}
protected:
	//주기적으로 호출되는 함수
	//OnCallThread()의 리턴값이 FALSE이면 쓰레드가 종료한다.
	virtual BOOL OnEvent(DWORD dwEvent, DWORD dwData)
	{
		return m_pParent->OnCallThread(dwEvent, dwEvent);
	}

protected:
	CParent* m_pParent;
};

}//namespace KSYSTEMS

#endif //_KTHREAD_H_
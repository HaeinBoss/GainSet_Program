/*/////////////////////////////////////////////////////////////
������  2002-12
������	2004-03-30
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
//	Ŭ����:CKThread
/*/////////////////////////////////////////////////////////////
class CKThread
{
public:

	CKThread();
	~CKThread();

	//���� �����尡 �����Ǿ� �ִ��� ����
	BOOL IsRun();

	//������ �⵿
	BOOL Start(LPFUNC lpfunc=NULL, LPVOID lpData=NULL);

	//������ ���� (�Լ� ���ڴ� Ȯ���� ���� ��Ű���� true�� ����)
	BOOL Stop(bool bSurely=false);

	//������ ��� �ð�(milisecond)
	void SetWaitTime(DWORD dwTime);

	//�������� �߿䵵�� �����ϴ� ���̸� �Ϲ������� THREAD_PRIORITY_ABOVE_NORMAL�� �����Ѵ�.
	BOOL SetPriority(int nPriority);

	//������ �Ͻ�����
	DWORD SuspendThread();

	//�Ͻ� ������ �����带 �⵿
	DWORD ResumeThread();

	//�۾��� �����Ѵ�.
	BOOL SetQueue(DWORD dwEvent, DWORD dwData);

	//�۾��� ����Ѵ�.
	BOOL GetQueue(DWORD* lpEvent, DWORD* lpData);

	LPFUNC m_lpfunc;
	LPVOID m_lpData;
protected:
	//������ �Լ�
	static DWORD CALLBACK FNTHREAD(LPVOID lpData);

	//Thread Ready
	virtual BOOL InitInstance();

	//InitInstance Error Call Function
	virtual void OnInitError();

	//Thread Exit
	virtual void ExitInstance();

	//FNTHREAD() -> Run()
	virtual void Run();

	//�̺�Ʈ �߻��� ȣ��ȴ�.
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
	//�ֱ������� ȣ��Ǵ� �Լ�
	//OnCallThread()�� ���ϰ��� FALSE�̸� �����尡 �����Ѵ�.
	virtual BOOL OnEvent(DWORD dwEvent, DWORD dwData)
	{
		return m_pParent->OnCallThread(dwEvent, dwEvent);
	}

protected:
	CParent* m_pParent;
};

}//namespace KSYSTEMS

#endif //_KTHREAD_H_
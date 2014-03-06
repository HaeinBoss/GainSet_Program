
/*/////////////////////////////////////////////////////////////
   ������  2013-05-29
   ������ :  ����
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
//	Ŭ����:CSThread
/*/////////////////////////////////////////////////////////////



class CSThread 
{
	//DECLARE_DYNAMIC(CSThread)

public:
	CSThread();
	~CSThread();

	// ���� �����尡 �����Ǿ� �ִ��� ����
	BOOL IsRun();

	//������ �⵿
	BOOL Start(LPFUNC2 lpfunc=NULL, LPVOID lpData=NULL);

	//������ ���� (�Լ� ���ڴ� Ȯ���� ���� ��Ű���� true�� ����)
	BOOL Stop(bool bSurely=false);

    // ������ ��� �ð� (milisecond)
	void SetWaitTime(DWORD dwTime);

	// �������� �߿䵵�� �����ϴ� ���̸� �Ϲ������� THREAD_PRIORITY_ABOVE_NORMAL�� �����Ѵ�.
	BOOL SetPriority(int nPriority);

	//������ �Ͻ�����
	DWORD SuspendThread();

	//�Ͻ� ������ �����带 �⵿
	DWORD ResumeThread();

	//�۾��� �����Ѵ�.
	BOOL SetQueue(DWORD dwEvent, DWORD dwData);

	//�۾��� ����Ѵ�.
	BOOL GetQueue(DWORD* lpEvent, DWORD* lpData);

	LPFUNC2 m_lpfunc;
	LPVOID m_lpData;

protected:
	// ������ �Լ�
	static DWORD CALLBACK FNTHREAD2(LPVOID lpData);

	// Thread Ready	�ν��Ͻ� �ʱ�ȭ
	virtual BOOL InitInstance();

	//InitInstance Error Call Function
	virtual void OnInitError();

	// Thread Exit
	virtual void ExitInstance();

	//FNTHREAD2 -> Run()
	virtual void Run();

	// �̺�Ʈ �߻��� ȣ��
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
	  // �ֱ������� ȣ��Ǵ� �Լ�
	 //OnCallThread()�� ���ϰ��� FALSE �̸� �����尡 ����ȴ�.
	virtual BOOL OnEvent(DWORD dwEvent, DWORD dwData)
	{
		return m_sParent->OnCallThread(dwEvent, dwEvent);
	}

   protected:
	CParent* m_sParent;

    };

}//namespace KSYSTEMS2

#endif //_STHREAD_H_
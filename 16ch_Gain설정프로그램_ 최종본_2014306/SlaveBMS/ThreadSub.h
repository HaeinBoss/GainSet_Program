#pragma once

 //  위 클래스는 MV2000 용입니다.

// CThreadSub

class CThreadSub 
{
	//DECLARE_DYNCREATE(CThreadSub)

protected:
	//CThreadSub();           // 동적 만들기에 사용되는 protected 생성자입니다.


public:

	HANDLE Sub_handler;
	 CSlaveBMSApp *SlaveBMSApp;  
	 CThreadSub(CSlaveBMSApp *pParent);
	virtual ~CThreadSub();
	int Read_RecoderData(CComm *comm,MODBUS_PACK MOD_PACK);
	
public: 
   void CopyOnSendBuff();

};



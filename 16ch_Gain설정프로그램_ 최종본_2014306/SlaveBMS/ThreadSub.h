#pragma once

 //  �� Ŭ������ MV2000 ���Դϴ�.

// CThreadSub

class CThreadSub 
{
	//DECLARE_DYNCREATE(CThreadSub)

protected:
	//CThreadSub();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.


public:

	HANDLE Sub_handler;
	 CSlaveBMSApp *SlaveBMSApp;  
	 CThreadSub(CSlaveBMSApp *pParent);
	virtual ~CThreadSub();
	int Read_RecoderData(CComm *comm,MODBUS_PACK MOD_PACK);
	
public: 
   void CopyOnSendBuff();

};



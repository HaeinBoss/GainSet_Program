#pragma once


class CSlaveBMSApp;

// CThreadMain

class CThreadMain
{
	//DECLARE_DYNCREATE(CThreadMain)

protected:
	//CThreadMain();           // 동적 만들기에 사용되는 protected 생성자입니다.



public:

	HANDLE m_hKill;
	CSlaveBMSApp *pSlaveBMS;
	CThreadMain(CSlaveBMSApp *pParent);
	virtual ~CThreadMain();


public:

	int Read_ModuleData(CComm *comm,MODBUS_PACK MOD_PACK);
	int SetData(CComm *comm,MODULE_INFORM MOD_PACK);
	void Put2SendBuff(unsigned char *SendBuff,MODULE_INFORM ModInform,int& nLen );

};



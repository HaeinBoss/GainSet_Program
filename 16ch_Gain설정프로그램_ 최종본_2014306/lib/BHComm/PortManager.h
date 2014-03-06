#if !defined(AFX_PORTMANAGER_H__827BE97D_4DF6_46EA_9608_300801B11D85__INCLUDED_)
#define AFX_PORTMANAGER_H__827BE97D_4DF6_46EA_9608_300801B11D85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PortManager.h : header file
//
#define UNKNOWN_DEVICE	-1
#define MODEM_DEVICE	0
#define USB_DEVICE		1
#define PORT_DEVICE		2

/////////////////////////////////////////////////////////////////////////////
// CPortManager window

class  SerialInfo
{
public:
	SerialInfo()
	{	
		Open = FALSE;
		BaudRate = 19200;
		Parity = 0;
		DataBits = 8;
		StopBits = 0;/* 0,1,2 = 1, 1.5, 2               */
		ComPort = -1;
		bPortInit = FALSE;
	}
	
	BOOL	Open;
	CString strComPort;
	int     ComPort;
	int     BaudRate;
	int     Parity;
	int     DataBits;
	int     StopBits;
	BOOL	bPortInit;

};

class CPortInfo : public CObject {
public:
	UINT iDeviceType;
	CString strDeviceType;
	CString strPName;
	CString strFName;
	CString strMName;
	CString strHWid;
	CString strLocInfo;
	BOOL	bBusy;
}; 

class  CPortManager : public CWnd
{
// Construction
public:
	CPortManager();
	
// Attributes
public:
	CObList m_PortList;
// Operations
public:
	CString GetVendorID(CPortInfo *pInfo);
	CString GetProductID(CPortInfo *pInfo);
	void RefreshInfo();
	BOOL EnumPortsWdm();
	BOOL EnumPortsWNt4();
	BOOL EnumPortsW9x();
	void SearchPnpKeyW9x(HKEY hkPnp, BOOL bUsbDevice);
	BOOL EnumDevices();
	void ReleaseListInfo();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPortManager)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPortManager();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPortManager)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTMANAGER_H__827BE97D_4DF6_46EA_9608_300801B11D85__INCLUDED_)

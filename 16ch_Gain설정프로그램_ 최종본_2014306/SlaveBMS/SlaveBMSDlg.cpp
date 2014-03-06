// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// SlaveBMSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SlaveBMS.h"
#include <crtdbg.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//extern CSlaveBMSApp theApp;

// BMS Set

#include "BMSSetDlg.h"

// CAboutDlg dialog used for App About
  void ControlLED(int nKind)
  {
		CSlaveBMSDlg *pMainDlg=NULL;
		pMainDlg=(CSlaveBMSDlg*)theApp.GetMainWnd();
		DWORD dwControlColor = ::GetSysColor(CTLCOLOR_DLG);

		if( nKind==SEND_OK )
		{
			BlinkTxControl(&pMainDlg->Tx_Led_A,SEND_OK);
			pMainDlg->m_charTX_A.SetFontStatic("Arial",15,GREEN_COLOR,FS_BOLD | FS_LEFT);
			pMainDlg->m_charTX_A.SetTextString("TX");
			// pMainDlg->m_charTX_A.SetBackground(dwControlColor);

		}
		else if(nKind==SEND_END)
		{
			BlinkTxControl(&pMainDlg->Tx_Led_A,SEND_END);
			pMainDlg->m_charTX_A.SetFontStatic("Arial",15,GREEN_DK_COLOR,FS_BOLD | FS_LEFT);
			pMainDlg->m_charTX_A.SetTextString("TX");
			// pMainDlg->m_charTX_A.SetBackground(RGB(228,228,228));

		}
		else if(nKind==SEND_OFF)
		{
		  	BlinkTxControl(&pMainDlg->Tx_Led_A,SEND_OFF);
			pMainDlg->m_charTX_A.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
			pMainDlg->m_charTX_A.SetTextString("TX");
			// pMainDlg->m_charTX_A.SetBackground(dwControlColor);

		}
	  	if(nKind==RECEIVE_OK)
	{
			BlinkRxControl(&pMainDlg->Rx_Led_A,RECEIVE_OK);
		  pMainDlg->m_charRX_A.SetFontStatic("Arial",15,RED_COLOR,FS_BOLD | FS_LEFT);
		  pMainDlg->m_charRX_A.SetTextString("RX");
		//  pMainDlg->m_charRX_A.SetBackground(dwControlColor);
	
	}

   	if(nKind==RECEIVE_END)
	{
		BlinkRxControl(&pMainDlg->Rx_Led_A,RECEIVE_END);
		 pMainDlg->m_charRX_A.SetFontStatic("Arial",15,RED_DK_COLOR,FS_BOLD | FS_LEFT);
		 pMainDlg->m_charRX_A.SetTextString("RX");
		// pMainDlg->m_charRX_A.SetBackground(dwControlColor);
	
	}


	if(nKind==OFF_RECEIVE)
	{
		BlinkRxControl(&pMainDlg->Rx_Led_A,OFF_RECEIVE);
		 pMainDlg->m_charRX_A.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
		 pMainDlg->m_charRX_A.SetTextString("RX");
		// pMainDlg->m_charRX_A.SetBackground(RGB(228,228,228));

	}
  }


    void ControlLEDB(int nKind)
  {
		CSlaveBMSDlg *pMainDlg=NULL;
		pMainDlg=(CSlaveBMSDlg*)theApp.GetMainWnd();
		DWORD dwControlColor = ::GetSysColor(CTLCOLOR_DLG);

		if( nKind==SEND_OK )
		{
			BlinkTxControl(&pMainDlg->Tx_Led_B,SEND_OK);
			pMainDlg->m_charTX_B.SetFontStatic("Arial",15,GREEN_COLOR,FS_BOLD | FS_LEFT);
			pMainDlg->m_charTX_B.SetTextString("TX");
			// pMainDlg->m_charTX_B.SetBackground(dwControlColor);

		}
		else if(nKind==SEND_END)
		{
			BlinkTxControl(&pMainDlg->Tx_Led_B,SEND_END);
			pMainDlg->m_charTX_B.SetFontStatic("Arial",15,GREEN_DK_COLOR,FS_BOLD | FS_LEFT);
			pMainDlg->m_charTX_B.SetTextString("TX");
			// pMainDlg->m_charTX_B.SetBackground(RGB(228,228,228));

		}
		else if(nKind==SEND_OFF)
		{
		  	BlinkTxControl(&pMainDlg->Tx_Led_B,SEND_OFF);
			pMainDlg->m_charTX_B.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
			pMainDlg->m_charTX_B.SetTextString("TX");
			// pMainDlg->m_charTX_B.SetBackground(dwControlColor);

		}
	  	if(nKind==RECEIVE_OK)
	{
			BlinkRxControl(&pMainDlg->Rx_Led_B,RECEIVE_OK);
		  pMainDlg->m_charRX_B.SetFontStatic("Arial",15,RED_COLOR,FS_BOLD | FS_LEFT);
		  pMainDlg->m_charRX_B.SetTextString("RX");
		//  pMainDlg->m_charRX_B.SetBackground(dwControlColor);
	
	}

   	if(nKind==RECEIVE_END)
	{
		BlinkRxControl(&pMainDlg->Rx_Led_B,RECEIVE_END);
		 pMainDlg->m_charRX_B.SetFontStatic("Arial",15,RED_DK_COLOR,FS_BOLD | FS_LEFT);
		 pMainDlg->m_charRX_B.SetTextString("RX");
		// pMainDlg->m_charRX_B.SetBackground(dwControlColor);
	
	}


	if(nKind==OFF_RECEIVE)
	{
		BlinkRxControl(&pMainDlg->Rx_Led_B,OFF_RECEIVE);
		 pMainDlg->m_charRX_B.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
		 pMainDlg->m_charRX_B.SetTextString("RX");
		 //pMainDlg->m_charRX_B.SetBackground(RGB(228,228,228));

	}
  }

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSlaveBMSDlg dialog




CSlaveBMSDlg::CSlaveBMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSlaveBMSDlg::IDD, pParent)
	,m_pCOMA (&m_COMM_INFO[0])
	,m_pCOMB (&m_COMM_INFO[1])
	, m_lSizeKB(10)
{
	ComPortA  ="";
	ComPortB  ="";
	ModNum=0;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_GAIN_PROGRAM_ICO);
}

void CSlaveBMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMMA, m_cbComPortA);	 
	DDX_Control(pDX, IDC_COMBO_COMMB, m_cbComPortB);
	DDX_Control(pDX, IDC_BTN_COMMOPEN_A, m_BtnPortOpenA);
	DDX_Control(pDX, IDC_BTN_COMMOPEN_B, m_BtnPortOpenB);
	DDX_Control(pDX, IDC_GAINLIST_A, GainList_A);
	DDX_Control(pDX, IDC_BTN_SET, Btn_Set);
	DDX_Control(pDX, IDC_STATIC_TXA, m_charTX_A);
	DDX_Control(pDX, IDC_STATIC_RXA, m_charRX_A);
	DDX_Control(pDX, IDC_STATIC_TXB, m_charTX_B);
	DDX_Control(pDX, IDC_STATIC_RXB, m_charRX_B);
	DDX_Control(pDX, IDC_STATIC_TXLED_A, Tx_Led_A);
	DDX_Control(pDX, IDC_STATIC_RXLED_A, Rx_Led_A);
	DDX_Control(pDX, IDC_STATIC_TXLED_B, Tx_Led_B);
	DDX_Control(pDX, IDC_STATIC_RXLED_B, Rx_Led_B);
	DDX_Control(pDX, IDC_LABEL_BMS, LabelBMS);
	DDX_Control(pDX, IDC_LABEL_MV2000, Label_MV2000);
	DDX_Control(pDX, IDC_BTN_SAVECSV_FILE, Btn_SaveFile);


	DDX_Control(pDX, IDC_CHECK_BALANCING, Balancing_Test);
}

BEGIN_MESSAGE_MAP(CSlaveBMSDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COMMOPEN_A, &CSlaveBMSDlg::OnBtnCommOpenA)
	ON_BN_CLICKED(IDC_BTN_COMMOPEN_B, &CSlaveBMSDlg::OnBtnCommOpenB)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_COMMA, &CSlaveBMSDlg::OnSelchangeComboCommA)
	ON_CBN_SELCHANGE(IDC_COMBO_COMMB, &CSlaveBMSDlg::OnSelchangeComboCommB)
	ON_MESSAGE(WM_BMSMOD_INFO,&CSlaveBMSDlg::OnBMSModuleData )
	ON_MESSAGE(WM_MV2000_INFO,&CSlaveBMSDlg::OnMV2000Data )
	ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, OnModuleDataItem)
	ON_WM_CLOSE()
	ON_NOTIFY(HDN_ITEMCHANGING, 0, &CSlaveBMSDlg::OnHdnItemchangingGainlistA)
	ON_BN_CLICKED(IDC_BTN_SET, &CSlaveBMSDlg::OnButtonBMSSet)	  	
	ON_MESSAGE(0x031A, OnThemeChanged)
	ON_BN_CLICKED(IDC_BTN_SAVECSV_FILE, &CSlaveBMSDlg::OnBtnSavecsvFile)
	ON_BN_CLICKED(IDC_CHECK_BALANCING, &CSlaveBMSDlg::OnCheckBalancingTest)	
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_MOD14, IDC_RADIO_MOD16, &CSlaveBMSDlg::OnButtonRadio)
END_MESSAGE_MAP()


// CSlaveBMSDlg message handlers
			  

LRESULT CSlaveBMSDlg::OnThemeChanged(WPARAM, LPARAM)
{

	ThemeSlaveBMS.ThemeChanged(m_hWnd);
	return 1;
}


BOOL CSlaveBMSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, "About Gain Set");
		}
	}

	((CSlaveBMSApp*)AfxGetApp())->DlgSlaveBMS = this;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

		///////Port Open Button
	m_BtnPortOpenA.SetShade(SHHS_SOFTBUMP);
	m_BtnPortOpenA.SetFont("Tahoma",13,600);

	m_BtnPortOpenB.SetShade(SHHS_SOFTBUMP);
	m_BtnPortOpenB.SetFont("Tahoma",13,600);

    Btn_Set.SetShade(SHHS_SOFTBUMP,8,10,50,CR_GREEN_BTN);
	Btn_Set.SetFont("Tahoma",13,600);

	Btn_SaveFile.SetShade(SHHS_SOFTBUMP,8,10,50,CR_BLUE_BTN);
	Btn_SaveFile.SetFont("Tahoma",13,700);


	InitializePort();
	SetStaticControl();
	CreateSlaveBMSTable();
   	ThemeSlaveBMS.Init(m_hWnd);
	GainList_A.SetThemeManager(&ThemeSlaveBMS);

	ModAClass = new CModVoltA();
	

	theApp.CreatClass("Main");
	theApp.CreatClass("Sub");

	vMatrix.resize( 2  ,VoltData(32 , 0)); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSlaveBMSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSlaveBMSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSlaveBMSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSlaveBMSDlg::InitializePort()
{
  CWinApp* pApp = AfxGetApp();

	 CString strItem="COMPORT";
	CString strItemB="COMPORT";

	m_SerialInfo[0].strComPort = pApp->GetProfileString("COM PORT", strItem, "COM1");
	m_SerialInfo[0].ComPort = atoi(m_SerialInfo[0].strComPort.Mid(3)) - 1;
	strcpy(m_COMM_INFO[0].szPorSerial,strItem);

	strItem = "BAUDRATE";
	m_SerialInfo[0].BaudRate = pApp->GetProfileInt("COM PORT", strItem, CBR_115200);		
	m_COMM_INFO[0].dcb.BaudRate=CBR_115200;

	strItem = "DATA";
	m_SerialInfo[0].DataBits = pApp->GetProfileInt("COM PORT", strItem,8 );
   	m_COMM_INFO[0].dcb.ByteSize=8;

	strItem = "PARITY";
	m_SerialInfo[0].Parity = pApp->GetProfileInt("COM PORT", strItem, 0);
	m_COMM_INFO[0].dcb.Parity=m_SerialInfo[0].Parity;

	strItem = "STOP";
	m_SerialInfo[0].StopBits = pApp->GetProfileInt("COM PORT", strItem,ONESTOPBIT );
	m_COMM_INFO[0].dcb.StopBits=	m_SerialInfo[0].StopBits;

	m_SerialInfo[1].strComPort = pApp->GetProfileString("COM PORT", strItemB, "COM1");
	m_SerialInfo[1].ComPort = atoi(m_SerialInfo[1].strComPort.Mid(3)) - 1;
   	strcpy(m_COMM_INFO[1].szPorSerial,strItem);

	strItemB = "BAUDRATE";
	m_SerialInfo[1].BaudRate = pApp->GetProfileInt("COM PORT", strItemB, CBR_19200);
	m_COMM_INFO[1].dcb.BaudRate=CBR_19200;

	strItemB = "DATA";
	m_SerialInfo[1].DataBits = pApp->GetProfileInt("COM PORT", strItemB,8 );
	m_COMM_INFO[1].dcb.ByteSize=8;
		
	strItemB = "PARITY";
	m_SerialInfo[1].Parity = pApp->GetProfileInt("COM PORT", strItemB, 0);
	m_COMM_INFO[1].dcb.Parity=m_SerialInfo[1].Parity;
	
	strItemB = "STOP";
	m_SerialInfo[1].StopBits = pApp->GetProfileInt("COM PORT", strItemB,ONESTOPBIT );
	m_COMM_INFO[1].dcb.StopBits=	m_SerialInfo[1].StopBits;
	m_COMM_INFO[1].dcb.StopBits=	m_SerialInfo[1].StopBits;


	SettingsA();
	 SettingsB();

	MakeComboPortA();
	MakeComboPortB();




}

void CSlaveBMSDlg::SettingsA()
{

	// Port 1
	m_SerialInfo[0].BaudRate =CBR_115200;

	 CString m_strA;
	m_PortManager[0].RefreshInfo();

	POSITION posA =  m_PortManager[0].m_PortList.GetHeadPosition();
	while(posA)
	{
		CPortInfo *portinfoA = (CPortInfo*)m_PortManager[0].m_PortList.GetNext(posA);
		m_strA.Format("[%s] %s",portinfoA->strPName, portinfoA->strFName);

	}


}
void CSlaveBMSDlg::SettingsB()
{
	CString  m_strB;
	//Port 2
	m_SerialInfo[1].BaudRate =CBR_19200;
    m_PortManager[1].RefreshInfo();

	POSITION posB =  m_PortManager[1].m_PortList.GetHeadPosition();
	while(posB)
	{
		CPortInfo *portinfoB = (CPortInfo*)m_PortManager[1].m_PortList.GetNext(posB);
		m_strB.Format("[%s] %s",portinfoB->strPName, portinfoB->strFName);
	}

}


void CSlaveBMSDlg::MakeComboPortA()
{
	int cb_idx = 0, sel_idx = -1;			// index
	CString m_str;
	POSITION posA = m_PortManager[0].m_PortList.GetHeadPosition();    // Com Port 가져오기
	
	int nCount = m_cbComPortA.GetCount();			// Combo box 카운트

	for(int iter = 0 ; iter < nCount ; iter ++)
	{
		m_cbComPortA.DeleteString(0);					//0으로		
	}


	while(posA)
	{

	CPortInfo *portinfoA = (CPortInfo*)m_PortManager[0].m_PortList.GetNext(posA);	//Port manager
		m_str.Format("[%s] %s",portinfoA->strPName, portinfoA->strFName);

		if(  cb_idx==0)
		{

		ComPortA=portinfoA->strPName;
		m_cbComPortA.InsertString(cb_idx, portinfoA->strPName);
		m_cbComPortA.SetItemData(cb_idx, (DWORD)portinfoA);
		if(!m_SerialInfo[0].strComPort.CompareNoCase(portinfoA->strPName))
		{
			sel_idx = cb_idx;//저장된 COMPORT 가 있으면
		}
		cb_idx++;

		}

	}
	m_cbComPortA.InsertString(cb_idx, "Refresh");
		
	if(m_cbComPortA.GetCount())
	{
		if(sel_idx < 0 )
		{
			m_cbComPortA.SetCurSel(0);
		}
		else
		{
			m_cbComPortA.SetCurSel(sel_idx);
		}
	}

	if(!m_PortManager[0].m_PortList.GetCount())
	{
		m_BtnPortOpenA.EnableWindow(FALSE);

	}
	else
	{
		m_BtnPortOpenA.EnableWindow(TRUE);
	//	m_BtnPortOpenA.SetIcon(IDI_ICON_DISCONNECT_PORT,BS_LEFT);
	}



}

void CSlaveBMSDlg::MakeComboPortB()
{

	int cb_idx = 0, sel_idx = -1;			// index
	CString m_str;
	POSITION posB = m_PortManager[1].m_PortList.GetHeadPosition();    // Com Port 가져오기
	
	int nCount = m_cbComPortB.GetCount();			// Combo box 카운트

	for(int iter = 0 ; iter < nCount ; iter ++)
	{
		m_cbComPortB.DeleteString(0);					//0으로		
	}

		while(posB)
	{
		CPortInfo *portinfoB = (CPortInfo*)m_PortManager[1].m_PortList.GetNext(posB);	//Port manager
		m_str.Format("[%s] %s",portinfoB->strPName, portinfoB->strFName);
		
		if(portinfoB->strPName!=ComPortA)
		{
			m_cbComPortB.InsertString(cb_idx, portinfoB->strPName);
			m_cbComPortB.SetItemData(cb_idx, (DWORD)portinfoB);
		 
			ComPortB= portinfoB->strPName;
			if(!m_SerialInfo[1].strComPort.CompareNoCase(portinfoB->strPName))
			{
				sel_idx = cb_idx;//저장된 COMPORT 가 있으면
			}
	     		cb_idx++;	

			}
		}

	m_cbComPortB.InsertString(cb_idx, "Refresh");
		
	if(m_cbComPortB.GetCount())
	{
		if(sel_idx < 0 )
		{
			m_cbComPortB.SetCurSel(0);
		}
		else
		{
			m_cbComPortB.SetCurSel(sel_idx);
		}
	}


		if(!m_PortManager[1].m_PortList.GetCount())
	{
		m_BtnPortOpenB.EnableWindow(FALSE);
	}
	else
	{
		m_BtnPortOpenB.EnableWindow(TRUE);
	}

}

void CSlaveBMSDlg::WriteProfileA()
{
	CWinApp* pApp = AfxGetApp();
	CString strItem = "COMPORT";

	m_COMM_INFO[0].nKind=COMM_INFO::SERIAL;


	pApp->WriteProfileString("COM PORT", strItem, m_SerialInfo[0].strComPort);
	m_SerialInfo[0].ComPort = atoi(m_SerialInfo[0].strComPort.Mid(3)) - 1;
	strcpy(m_COMM_INFO[0].szPorSerial,m_SerialInfo[0].strComPort);

	strItem = "BAUDRATE";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[0].BaudRate);
	 m_COMM_INFO[0].dcb.BaudRate= m_SerialInfo[0].BaudRate;

	strItem = "DATA";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[0].DataBits);
	m_COMM_INFO[0].dcb.ByteSize =  m_SerialInfo[0].DataBits;

	strItem = "PARITY";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[0].Parity);
	m_COMM_INFO[0].dcb.Parity =m_SerialInfo[0].Parity;

	strItem = "STOP";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[0].StopBits);
   	m_COMM_INFO[0].dcb.StopBits =  m_SerialInfo[0].StopBits;

}

void CSlaveBMSDlg::WriteProfileB()
{
     CWinApp* pApp = AfxGetApp();
	CString strItem = "COMPORT";

	m_COMM_INFO[1].nKind=COMM_INFO::SERIAL;
	pApp->WriteProfileString("COM PORT", strItem, m_SerialInfo[1].strComPort);
	m_SerialInfo[1].ComPort = atoi(m_SerialInfo[1].strComPort.Mid(3)) - 1;
	strcpy(m_COMM_INFO[1].szPorSerial,m_SerialInfo[1].strComPort);

	strItem = "BAUDRATE";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[1].BaudRate);
   m_COMM_INFO[1].dcb.BaudRate= m_SerialInfo[1].BaudRate;

	strItem = "DATA";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[1].DataBits);
	m_COMM_INFO[1].dcb.ByteSize =  m_SerialInfo[1].DataBits;
	
	strItem = "PARITY";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[1].Parity);
	m_COMM_INFO[1].dcb.Parity =m_SerialInfo[1].Parity;

	strItem = "STOP";
	pApp->WriteProfileInt("COM PORT", strItem, m_SerialInfo[1].StopBits);
   m_COMM_INFO[1].dcb.StopBits =  m_SerialInfo[1].StopBits;

}

//Connnect 버튼 설정
void CSlaveBMSDlg::OnBtnCommOpenA()
{
	CString m_str;
	CString Port;
	CString Alarm_Port;
		
	BOOL retVal = true;		
	
	// 버튼의 글자를 가져오자!
	m_BtnPortOpenA.GetWindowTextA(m_str);

	if(m_str.Find("Open")>=0)
	{
	 	CPortInfo *m_pinfo;
		m_pinfo = (CPortInfo*)m_cbComPortA.GetItemData(m_cbComPortA.GetCurSel());
	  	if(m_pinfo)
		{
			m_SerialInfo[0].strComPort = m_pinfo->strPName;	 
	//		g_bStart= TRUE;
			WriteProfileA();
			COMPortOpenA();
		   // 쓰레드 제어

			//theApp.CreatClass("Main");
			k_ThreadRead.SetWaitTime(250);
			k_ThreadRead.Start(ThreadRead,this);

		}

	}
	else
	{	 
		// Port 가 Open 되었다면..
		k_ThreadRead.Stop();

		 if(COMPortCloseA())
		{
			 m_BtnPortOpenA.SetWindowText("Open");
			 m_cbComPortA.EnableWindow(TRUE);
			 Alarm_Port.Format("통신접속이 끊어졌습니다.");
			//this->SetWindowTextA(Alarm_Port);
			 MessageBox(Alarm_Port,"BMS",MB_ICONINFORMATION);
			// theApp.ControlComm("Main");
		}


		 }
}

////////////Serial Com Port 설정////////

void CSlaveBMSDlg::ReleaseSerialA()
{
  // 	m_commTICA->Close();  

	m_SerialInfo[0].bPortInit = FALSE;
	m_SerialInfo[0].Open = FALSE;

}

void CSlaveBMSDlg::ReleaseSerialB()
{
  	m_SerialInfo[1].bPortInit = FALSE;
	m_SerialInfo[1].Open = FALSE;

}




void CSlaveBMSDlg::OnBtnCommOpenB()
{
   CString m_str;
	CString Port;
	CString Alarm_Port;
	
	// 버튼의 글자를 가져오자!
	m_BtnPortOpenB.GetWindowTextA(m_str);

		if(m_str.Find("Open")>=0)
		{
			CPortInfo *m_pinfo;
			m_pinfo = (CPortInfo*)m_cbComPortB.GetItemData(m_cbComPortB.GetCurSel());
	  		if(m_pinfo)
			{
				m_SerialInfo[1].strComPort = m_pinfo->strPName;	
				//g_SubStart=TRUE;			
				WriteProfileB();
				COMPortOpenB();

				s_ThreadRead.SetWaitTime(500);
				s_ThreadRead.Start(ThreadReadB,this);

			}

		}
		else
		{  
			s_ThreadRead.Stop();

 			if(COMPortCloseB())
			{	
				m_BtnPortOpenB.SetWindowText("Open");
				m_cbComPortB.EnableWindow(TRUE);

				Alarm_Port.Format("통신접속이 끊어졌습니다");
				// this->SetWindowTextA(Alarm_Port);
				MessageBox(Alarm_Port,"MV2000",MB_ICONINFORMATION);
			
				//theApp.ControlComm("Sub");
			}

			
		}

}

#include "SlaveBMSDlg.h"
void CSlaveBMSDlg::OnDestroy()
{
	//  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	  
   //SAFE_DELETE(SlaveItem);

  	std::vector<CString>iclear;
	VecItem.swap(iclear);
	iclear.clear();
	VecItem.clear();

	delete m_PortManager[0];
	delete m_PortManager[1];

	ModAClass->RemoveVector(	ModAClass->Vec_Module);   
	ReleaseVoltMemory(vMatrix);

	delete ModAClass;
	ModAClass = NULL;		 


	CDialog::OnDestroy();

}

void CSlaveBMSDlg::OnSelchangeComboCommA()
{

	CString m_str;
	m_BtnPortOpenA.GetWindowText(m_str);

	CString m_com_str;
	m_cbComPortA.GetWindowText(m_com_str);
	if(m_com_str.Find("Refresh") >= 0)
	{
		ComPortA="";
		SettingsA();//컴포트 Refresh
		MakeComboPortA();
	


	}

}

void CSlaveBMSDlg::OnSelchangeComboCommB()
{
	CString m_str;
	m_BtnPortOpenB.GetWindowText(m_str);

	CString m_com_str;
	m_cbComPortB.GetWindowText(m_com_str);
	if(m_com_str.Find("Refresh") >= 0)
	{
		ComPortB="";
		SettingsB();//컴포트 Refresh
		MakeComboPortB();

	}
	
}

void CSlaveBMSDlg::OnClose()
{
   	static BOOL bFirst=TRUE;
  	int nFaild=0;
	
	if ( !k_ThreadRead.Stop() )
   {   
		nFaild++;
   }

	if ( !s_ThreadRead.Stop() )
   {   
		nFaild++;
   }

	if ( bFirst )
	{   
		if(theApp.m_pThreadMain!=NULL)
		{
			theApp.ControlComm("Main");
		}

		if(theApp.m_pThreadSub!=NULL)
		{
			theApp.ControlComm("Sub");
		}
	}
        if ( MessageBox("종료하시겠습니까?","Gain Set",MB_YESNO )==IDYES )
		{	
			bFirst=FALSE;
		}
		else
		{
			  return;
		}

	  if(nFaild)
	  {
		PostMessage(WM_CLOSE);
      }

	
   	OnOK();

}

void CSlaveBMSDlg::OnButtonGainset()
{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다..		

	//GAIN_SETTING GainSettings;
	////memset(&GainSettings,0x00,sizeof(GainSettings));

	CString m_str;
	bool  blCheck;
	blCheck = true;	

	//USHORT fGainCalc=0;

 


//	bmsset.qGainSetting.push(Make_Gain(0x01,0x10,0,15,15,fGainCalc,(USHORT*)GainSettings.RefVolt));
}


void CSlaveBMSDlg::CreateSlaveBMSTable()
{
	// 리스트 컨트롤 Format 설정
	ListView_SetExtendedListViewStyleEx(GainList_A.m_hWnd, LVS_EX_FULLROWSELECT, 0);
	ListView_SetExtendedListViewStyleEx(GainList_A.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	ListView_SetExtendedListViewStyleEx(GainList_A.m_hWnd,LVS_EX_GRIDLINES,LVS_EX_GRIDLINES);
	ListView_SetExtendedListViewStyleEx(GainList_A.m_hWnd,LVS_EX_DOUBLEBUFFER,LVS_EX_DOUBLEBUFFER);

   	// 리스트 컨트롤 헤더 설정
	GainHeaderCtrl.SubclassWindow(GainList_A.GetHeaderCtrl()->m_hWnd);
	CFont Dfont;
    Dfont.CreateFontA(16, 0, 0, 0, 750, 0, 0, 0, 	DEFAULT_CHARSET,						//	문자셋종류 (iCharSet)
																									OUT_STRING_PRECIS,			//	 출력정밀도( iOutPrecision)
																									CLIP_CHARACTER_PRECIS,			//  클리핑정밀도 (iClipPrecision)
																									DEFAULT_QUALITY,						//  출력문자품질  (iQuality)
																									 DEFAULT_PITCH |FF_MODERN,   //	글꼴   (PitchiPitchAndFamily)
																									"Arial");			
	GainList_A.SetFont(&Dfont);
	GainHeaderCtrl.SetFont(&Dfont);    //헤더 영역에 폰트 설정
    GainHeaderCtrl.SetHeight(28);      //헤더 영역의 크기 설정 => 두줄이 가능하도록 넉넉하게 설정
   Dfont.Detach();
	
	GainHeaderCtrl.SetBkColor(RGB(56,64,103));   //배경색 설정
	GainHeaderCtrl.SetTextColor(RGB(230,235,231)); //문자색 설정

	DrawSlaveHeader();


	//
	CFont bFont;			
	bFont.CreateFont(16,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,
		                                    OUT_DEFAULT_PRECIS,   // 출력정밀도
											CLIP_DEFAULT_PRECIS,	// 클리핑정밀도
											DEFAULT_QUALITY,
											DEFAULT_PITCH,"Arial");

	//lancing_Test.SetTextColor(RGB(0,0,0));
	Balancing_Test.SetFont(&bFont);
  	bFont.Detach();
	//
}


void CSlaveBMSDlg::DrawSlaveHeader()
{
   CString SlaveTitle[]= { "","CH 1","CH 2",								 
												 "CH 3","CH 4",
											 	 "CH 5","CH 6",
												 "CH 7","CH 8",
												 "CH 9","CH 10",				
												 "CH 11","CH 12",
												 "CH 13","CH 14" ,
											     "CH 15","CH 16"
   
											};

	SetSlaveListTitle(SlaveTitle);
	GainList_A.SetItemHeight(27);

  GainList_A.SetItemCount(9);

	SetSlaveListItem();
}

void CSlaveBMSDlg::SetSlaveListTitle(CString *STitle)
{
	for(int col=0; col<17; col++)
	{
		if(col==0)
		{
		  	GainList_A.InsertColumn(col,STitle[col],	LVCFMT_CENTER, 175);       
		}
		else
		{
			GainList_A.InsertColumn(col,STitle[col],	LVCFMT_CENTER, 56);       
			
		}
	}

}


////////////////// 리스트 컨트롤 아이템//////////////////

void CSlaveBMSDlg::SetSlaveListItem()
{
		char *strItem[]={"BMS #1   Volt","BMS #1   Temp",
										 "MV2000", "Volt Difference",
										 "BMS #2   Volt","BMS #2   Temp"};

		   CSlaveVoltA SlaveItem[6];
	  //    SlaveItem = new CSlaveVoltA[6];
	 for (int i=0; i<6;i++)
	 {
		 // 지역 변수
		 SlaveItem[i].textdata = strItem[i];
		 //전역 변수
		 VecItem.push_back(SlaveItem[i].textdata);
	 }
	  

}

//////////// 리스트 컨트롤 메시지 컨트롤 //////////////////

LRESULT CSlaveBMSDlg::OnModuleDataItem(WPARAM wParam, LPARAM lParam)
{

    if( (HWND) wParam ==GainList_A.GetSafeHwnd() )
   {
	   //lParam is a pointer to the data that is needed for the element
		CQuickList::CListItemData* SlaveBMSData = ( CQuickList::CListItemData*)lParam;
		// Get which item and subitem that is asked for.
		int item = SlaveBMSData->GetItem();	 
		int subItem =SlaveBMSData->GetSubItem();

		float Difference=0.0;

		//CSlaveVoltA *slaveitem = VecItem[item];
	
		#ifndef QUICKLIST_NOEDIT
			if(   SlaveBMSData->GetSubItem() <16)
			{
				SlaveBMSData->m_allowEdit = FALSE;
			}
	#endif

#ifndef QUICKlIST_NOCOLORS

		if( SlaveBMSData->GetItem() %2==0  )
		{
		   SlaveBMSData->m_colors.m_textColor =	RGB(25,25,25);
		   SlaveBMSData->m_colors.m_backColor =RGB(228,229,231);

		}						
		else
		{
			SlaveBMSData->m_colors.m_textColor =	RGB(25,25,25);
			SlaveBMSData->m_colors.m_backColor =	RGB(233,234,236);
	
		}
#endif

 #ifndef QUICKLIST_NOTEXTSTYLE 

#endif

	 //if( 아이템 개수< logCnt )


		if(SlaveBMSData->GetSubItem()==0)
		{

			if(SlaveBMSData->GetItem()<6)
			{
				SlaveBMSData->m_text.Format(_T("   %s      "),  VecItem[SlaveBMSData->GetItem()]);
			}
		}
		else  if(SlaveBMSData->GetSubItem()<=16)
		{

			if( (SlaveBMSData->GetItem() <6))
			{
				 if(ModNum>0)
			     { 
						  if( SlaveBMSData->GetItem()==0)
						  {
  							 SlaveBMSData->m_text.Format(_T("  %1.3f"), vMatrix[0][SlaveBMSData->GetSubItem()-1]);
						  }
						  else if( SlaveBMSData->GetItem()==1)
						  {
  							 SlaveBMSData->m_text.Format(_T("  %2.1f"), vMatrix[0][SlaveBMSData->GetSubItem()+15]);
						  }
						  else if( SlaveBMSData->GetItem()==4)
						  {
							 SlaveBMSData->m_text.Format(_T("  %1.3f"), vMatrix[1][SlaveBMSData->GetSubItem()-1]);
						  }
						  else if( SlaveBMSData->GetItem()==5)
						  {
							 SlaveBMSData->m_text.Format(_T("  %2.1f"), vMatrix[1][SlaveBMSData->GetSubItem()+15]);   
						  }  
			        }  
			}
		
		     if(ModAClass->vec_mv2000.size()>0)
		     {
					if( SlaveBMSData->GetItem()==2)
				   {
					  if(ModNum>0)
						SlaveBMSData->m_text.Format(_T("  %1.3f"), ModAClass->vec_mv2000[SlaveBMSData->GetSubItem()-1]);	
					}
					else if( SlaveBMSData->GetItem()==3)
					{

						 if(ModNum>0)
						 {
							Difference=   vMatrix[0][SlaveBMSData->GetSubItem()-1]- ModAClass->vec_mv2000[SlaveBMSData->GetSubItem()-1];
						
							 SlaveBMSData->m_text.Format(_T("  %1.3f"), 	Difference);
							 if((-0.005 < Difference) && (Difference<0.005))
							 {
								 // 글자색: 검은색
								SlaveBMSData->m_colors.m_textColor =	RGB(25,25,25);
								}
							 else
							 {	  	// 글자색: 빨간색
									SlaveBMSData->m_colors.m_textColor =	RGB(255,11,11);
							 } 
						 
						 }
					}
			}
		
		} 

    }   //리스트 핸들러

   return FALSE;
}











void CSlaveBMSDlg::OnHdnItemchangingGainlistA(NMHDR *pNMHDR, LRESULT *pResult)
{
	 HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	if (phdn && (phdn->pitem->mask & HDI_WIDTH) != 0)
	{
		*pResult = TRUE;
	}
}

void CSlaveBMSDlg::COMPortOpenA()
{
   	CString temp;
	
	char szBuffer[MAX_PATH] = {0,};
	CString strPort[2];
	 
	// CString --> char* 형으로 변환
	int nLength = (MAX_PATH > strlen(ComPortA)) ? strlen(ComPortA) : MAX_PATH;
	strncpy(szBuffer, (LPSTR)(LPCSTR)ComPortA, nLength); 

	CString strGetPort=GetCommString(szBuffer);
	strPort[0].Format("\\\\.\\COM%s",strGetPort);		

	if(m_pCOMA.Open())
		{
			m_BtnPortOpenA.SetWindowText("Close");			
			temp.Format("포트가 열렸습니다 - %s, %dbps.",m_COMM_INFO[0].szPorSerial,m_COMM_INFO[0].dcb.BaudRate);

			m_cbComPortA.EnableWindow(FALSE);
			//this->SetWindowTextA(temp);
			this->SetWindowTextA("Gain Set");
			//if ( pView )
			//	::AddListBox(&pView->m_LBstatusCOM1, temp);
		}
		else
		{

			m_pCOMA.Close();
			
			temp.Format( "포트를 열수가 없습니다 !!");
		   m_cbComPortA.EnableWindow(TRUE);
		}


}
void CSlaveBMSDlg::COMPortOpenB()
{
	CString temp;
	char szBuffer2[MAX_PATH] = {0,};
	CString strPort[2];

		// CString --> char* 형으로 변환
		int nLength = (MAX_PATH > strlen(ComPortB)) ? strlen(ComPortB) : MAX_PATH;
		strncpy(szBuffer2, (LPSTR)(LPCSTR)ComPortB, nLength); 

	    CString strGetPortB=GetCommString(szBuffer2);
	  strPort[1].Format("\\\\.\\COM%s",strGetPortB);	

	  if(m_pCOMB.Open() )
		{
			temp.Format("포트가 열렸습니다 - %s, %dbps.", m_COMM_INFO[1].szPorSerial, m_COMM_INFO[1].dcb.BaudRate);
		   	//this->SetWindowTextA(temp);
			this->SetWindowTextA("Gain Set");
			m_BtnPortOpenB.SetWindowText("Close");	
			m_cbComPortB.EnableWindow(FALSE);
		}
		else
		{
			temp.Format("포트를 열수가 없습니다 !!");
		   m_cbComPortB.EnableWindow(TRUE);
		}		
}


//// COM Port CLOSE
BOOL CSlaveBMSDlg::COMPortCloseA()
 {
	 
	WINTRACE("COM1 Port CLOSE 시도!!");
	 m_pCOMA.Close();
	return TRUE;

}

BOOL CSlaveBMSDlg::COMPortCloseB()
{
	
	 WINTRACE("PORT 2 : %s CLOSE 시도!\n");

	m_pCOMB.Close();
	return TRUE;
}


////////////////Static Control	  ////////////////

void CSlaveBMSDlg::SetStaticControl()
{  	
	DWORD dwControlColor = ::GetSysColor(CTLCOLOR_DLG);

	//// 라벨 설정
	m_charTX_A.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
	m_charTX_A.SetTextString("TX");
	//m_charTX_A.SetBackground(dwControlColor);

	m_charRX_A.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
	m_charRX_A.SetTextString("RX");
	//m_charRX_A.SetBackground(dwControlColor);

   	m_charTX_B.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
	m_charTX_B.SetTextString("TX");
	//m_charTX_B.SetBackground(dwControlColor);

	m_charRX_B.SetFontStatic("Arial",15,GRAY_DK_COLOR,FS_BOLD | FS_LEFT);
	m_charRX_B.SetTextString("RX");
	//m_charRX_B.SetBackground(dwControlColor);

	Tx_Led_A.SetBitmap(IDB_GRAYL_LED, CxStatic::FitControl);
	Tx_Led_A.SetBkColor( dwControlColor);

	Rx_Led_A.SetBitmap(IDB_GRAYL_LED, CxStatic::FitControl);
	Rx_Led_A.SetBkColor( dwControlColor);

	Tx_Led_B.SetBitmap(IDB_GRAYL_LED, CxStatic::FitControl);
	Tx_Led_B.SetBkColor( dwControlColor);

	Rx_Led_B.SetBitmap(IDB_GRAYL_LED, CxStatic::FitControl);
	Rx_Led_B.SetBkColor( dwControlColor);

	LabelBMS.SetFontStatic("Arial",16,RGB(0,0,0),FS_BOLD | FS_RIGHT);
	LabelBMS.SetTextString("BMS");
	//LabelBMS.SetBackground(dwControlColor);

	Label_MV2000.SetFontStatic("Arial",16,RGB(0,0,0),FS_BOLD | FS_RIGHT);
	Label_MV2000.SetTextString("MV2000");
	//Label_MV2000.SetBackground(dwControlColor);


	CFont bFont;			
	bFont.CreateFont(16,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,
		                                    OUT_DEFAULT_PRECIS,   // 출력정밀도
											CLIP_DEFAULT_PRECIS,	// 클리핑정밀도
											DEFAULT_QUALITY,
											DEFAULT_PITCH,"Arial");

	//Balancing_Test.SetTextColor(RGB(0,0,0));
	//Balancing_Test.SetBkColor(RGB(190,218,245));
	Balancing_Test.SetFont(&bFont);
   	bFont.Detach();

}


void CSlaveBMSDlg::OnButtonBMSSet()
{
		if(trackBMSSet.IsAlreadyPopped())
		{
			trackBMSSet.ShowDialog();
		}
		else
		{
		// Param Dlg
			CBMSSetDlg* BMSSetDlg = new CBMSSetDlg(trackBMSSet);  // note the passing of the tracker;
			BMSSetDlg->Create(BMSSetDlg->IDD,NULL);
			BMSSetDlg->ShowWindow(SW_SHOW);
		}
}


//// WM_MESSAGE////

LRESULT CSlaveBMSDlg:: OnBMSModuleData(WPARAM wParam, LPARAM lParam)
{

	ModNum=(int)(wParam);
	ModNum++;

	  ReleaseVoltMemory(vMatrix);
   	   vMatrix.resize( 2  ,VoltData(32 , 0)); 


  	for(int  col=0; col<2; col++)
	{
		for ( int row = 0;  row < 16; ++row)
		{
			vMatrix[col][row]=(float)(ModAClass->Vec_Module[col][row+1])/1000 ;
			vMatrix[col][row+16]=(float)(ModAClass->Vec_Module[col][row+50])/10 ;
		}
	}

	//GainList_A.Invalidate();
	GainList_A.RedrawItems(	GainList_A.GetTopIndex(),
	GainList_A.GetTopIndex()+GainList_A.GetCountPerPage());	
	return FALSE;

}
LRESULT CSlaveBMSDlg::OnMV2000Data(WPARAM wParam, LPARAM lParam)
{


	GainList_A.Invalidate();

	return FALSE;
}

// 쓰레드 Run
BOOL WINAPI CSlaveBMSDlg::ThreadRead(KSYSTEMS::CKThread *pThread, LPVOID lpData)
{
	CSlaveBMSDlg *pParent =(CSlaveBMSDlg*)lpData;
	DWORD dwEvent=0, dwData=0;

	int Address = 0;
	USHORT Cnt =100;
	UCHAR length=0;
   	CString strAlam="";
	   
	while(1)
	{
		if(!pThread->GetQueue(&dwEvent,&dwData))	// 작업을 대기함
		{
		//	SetWaitMilliSecond(50);
			if((dwEvent=GetLastError()) != KTE_TIMEOUT)
			{
				break;
			}

		}
		// 쓰레드 종료 이벤트
		if(dwEvent == KTE_STOP)
		{  	
			if(pParent->m_pCOMA.IsOpen())
			{
			  	 ControlLED(SEND_OFF);
				ControlLED(OFF_RECEIVE);
			}
			break;
		}

		if(pParent !=NULL )
		{	
		   ModAClass->ModulePack[0] =   PutOnModBusStructure(0x01,0x03,ModAClass->ModAddr,Cnt,length);

		    // BMS Set & Balancing Test
		  if(ModAClass->qModInform.size()>0)
			{
			    MODULE_INFORM  module_control;

				memset(&module_control,0x00,sizeof(module_control));
				module_control= ModAClass->qModInform.front();

				if(theApp.m_pThreadMain->SetData(&pParent->m_pCOMA,module_control) != COMM_OK)
				{

				}

				ModAClass->qModInform.pop();
			}
			else
			{
				if(theApp.m_pThreadMain->Read_ModuleData(&pParent->m_pCOMA,ModAClass->ModulePack[0] ) != COMM_OK)
				{
					pParent->Balancing_Test.EnableWindow(FALSE);
				}
				else
				{
					pParent->Balancing_Test.EnableWindow(TRUE);
					::PostMessage(pParent->m_hWnd,WM_BMSMOD_INFO,(WPARAM)ModAClass->SlaveAddr,(LPARAM)NULL); 
				}
			}
		}		

	}

	return 0;

}



 // 2번째 쓰레드
 BOOL WINAPI CSlaveBMSDlg::ThreadReadB(CSThread *pThread2, LPVOID lpData2)
 {
  	CSlaveBMSDlg *pParentB = (CSlaveBMSDlg*)lpData2;

	DWORD dwEvent=0, dwData=0;
	static BOOL mFirst=TRUE;

	
	while(1)
	{
		 if(!pThread2->GetQueue(&dwEvent,&dwData))	// 작업을 대기함
		 {
	//		SetWaitMilliSecond(50);
		    if((dwEvent=GetLastError()) != STE_TIMEOUT)
			{
				break;
			}

			}
		// 쓰레드 종료 이벤트
		if(dwEvent == STE_STOP)
		{  	
			ControlLEDB(SEND_OFF);
			ControlLEDB(OFF_RECEIVE);
			break;
		}


		if( !pParentB->m_pCOMB.IsOpen() )
		{
			if( !pParentB->m_pCOMB.Open() )
				continue;
		
		}

		if(pParentB !=NULL )
		{	
							
			USHORT AddressB=0;
			USHORT CntB =16;
			UCHAR length=0;
	
			
		     ModAClass->ModulePack[1] =   PutOnModBusStructure(0x01,0x04,AddressB,CntB,length);
	 		//SetWaitMilliSecond(20);
			if(theApp.m_pThreadSub->Read_RecoderData(&pParentB->m_pCOMB,ModAClass->ModulePack[1] )!= COMM_OK)
			{
			}
			else
			{
					::PostMessage(pParentB->m_hWnd,WM_MV2000_INFO,(WPARAM)NULL,(LPARAM)NULL); 
			}
	
		} // Main Dialog 가 열려져 있다면,.
	
	}// while 구문 핸들러

 
	return 0;
 }


 void CSlaveBMSDlg::ReleaseVoltMemory(Mat_Volt &VoltM)
 {
	Mat_Volt::iterator erase_vec  = VoltM.begin();
	while(erase_vec != VoltM.end())
	{
			erase_vec = VoltM.erase(erase_vec);
	}

 }

 // save 버튼
 void CSlaveBMSDlg::OnBtnSavecsvFile()
 {
	 SetFilePath();
 }

 
 BOOL CSlaveBMSDlg::BrowseFileDlg()
 {
	SYSTEMTIME _t;
	GetLocalTime(&_t);
	
	CString sExcelFileName;
	CString m_sExcelFileSavePath;

	sExcelFileName.Format(TEXT("\\LogTable_%04d%02d%02d_%02d'%02d'%02d.csv"), _t.wYear, _t.wMonth, _t.wDay, _t.wHour, _t.wMinute, _t.wSecond);

	CString sFilter = TEXT("CSV Files(*.csv)|*.csv||");
	CFileDialog fileDialog(FALSE, TEXT(""), sExcelFileName, OFN_HIDEREADONLY, sFilter);

	fileDialog.m_ofn.lpstrTitle = "파일을 저장하세요";
	fileDialog.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12;

//   fileDialog.m_ofn.lpstrInitialDir = sf_GetComputerDir();

	if(IDOK == fileDialog.DoModal())
	{
			
		m_sExcelFileName = fileDialog.GetPathName();
		
		int n = m_sExcelFileName.ReverseFind( '\\' );
		strFolder = m_sExcelFileName.Left(  n  ); 
		
		m_sExcelFileName = fileDialog.GetFileName();
        
		return TRUE;
	}
	else
	{
	   return FALSE;

	}
 
   return FALSE;

 }

 void CSlaveBMSDlg::SetFilePath()
 {

	UpdateData();
	CString strFileName="";


	// 로그 기록할 경로 정의하기
	char path[MAX_PATH]={0,};
	char FilePath[260]={0,};

	if(BrowseFileDlg())
	{

	int nLength = (MAX_PATH > strlen(strFolder)) ? strlen(strFolder) : MAX_PATH;
	strncpy(path, (LPSTR)(LPCSTR)strFolder, nLength); 


	int rLength = (MAX_PATH > strlen(m_sExcelFileName)) ? strlen(m_sExcelFileName) : MAX_PATH;
	strncpy(FilePath, (LPSTR)(LPCSTR)m_sExcelFileName, rLength); 


	//-------------------------------------------------------------------------
	// CHXLog 객체 초기화 하기 InitLogFile()
	//   파라미터
	//     1. path = 로그가 저장될 절대경로 또는 상대경로 (default 현재실행디렉토리)
	//     2. 로그 파일명 (default "app.log")
	TableLog.InitLogFile(path, FilePath,TRUE);	

	//-------------------------------------------------------------------------
	// 로그파일 백업 갯수 1개로 설정
	//Paramlogger.SetLogFileCount(1);	

	//-------------------------------------------------------------------------
	// 로그파일 최대 크기 설정	
	// 로그 라인 단위로 저장되지 때문에 로그파일 크기는 조금 크거나 작을 수 있음	

	if( m_lSizeKB<= 1,1073741824)
	{
		TableLog.SetLogFileSize(1024*m_lSizeKB);  // m_lSizeKB= 10K Byte로 설정
	}

		RecordTableData();
	}

 }


 void CSlaveBMSDlg::RecordTableData()
 {
	 
	int row=0;
	SYSTEMTIME _t;
	GetLocalTime(&_t);
	TableLog.xfprintf(0,"[LOG TABLE]");
	TableLog.xfprintf(0,"%4d.%02d.%02d \t %02d:%02d:%02d ",_t.wYear, _t.wMonth, _t.wDay, _t.wHour, _t.wMinute, _t.wSecond);

	CString GetTime;
	float fDiff[16];

	memset(fDiff,0,sizeof(float)*16);
	TableLog.xfprintf(0,",CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16");

	if(ModNum>0)
	{
     //BMS Mod #1 Volt., Temp.
	  TableLog.xfprintf(0,"%s,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f","BMS#1 Volt.", vMatrix[0][0],vMatrix[0][1],vMatrix[0][2],vMatrix[0][3],vMatrix[0][4],vMatrix[0][5],
						                               vMatrix[0][6],vMatrix[0][7],vMatrix[0][8],vMatrix[0][9],vMatrix[0][10],
						                               vMatrix[0][11],vMatrix[0][12],vMatrix[0][13],vMatrix[0][14],vMatrix[0][15]);  	
	   
	 TableLog.xfprintf(0,"%s,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f","BMS#1 Temp.", vMatrix[0][16],vMatrix[0][17],vMatrix[0][18],vMatrix[0][19],vMatrix[0][20],vMatrix[0][21],
						                               vMatrix[0][22],vMatrix[0][23],vMatrix[0][24],vMatrix[0][25],vMatrix[0][26],
						                               vMatrix[0][27],vMatrix[0][28],vMatrix[0][29],vMatrix[0][30],vMatrix[0][31]);  	
	
	//BMS Mod #2 Volt., Temp.
	 TableLog.xfprintf(0,"%s,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f","BMS#2 Volt.", vMatrix[1][0],vMatrix[1][1],vMatrix[1][2],vMatrix[1][3],vMatrix[1][4],vMatrix[1][5],
						                               vMatrix[1][6],vMatrix[1][7],vMatrix[1][8],vMatrix[1][9],vMatrix[1][10],
						                               vMatrix[1][11],vMatrix[1][12],vMatrix[1][13],vMatrix[1][14],vMatrix[1][15]);  	
	   
	 TableLog.xfprintf(0,"%s,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f,%2.1f","BMS#2 Temp.", vMatrix[1][16],vMatrix[1][17],vMatrix[1][18],vMatrix[1][19],vMatrix[1][20],vMatrix[1][21],
						                               vMatrix[1][22],vMatrix[1][23],vMatrix[1][24],vMatrix[1][25],vMatrix[1][26],
						                               vMatrix[1][27],vMatrix[1][28],vMatrix[1][29],vMatrix[1][30],vMatrix[1][31]);  	
	 
	 //MV2000
	 TableLog.xfprintf(0,"%s,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f","MV2000", ModAClass->vec_mv2000[0], ModAClass->vec_mv2000[1], ModAClass->vec_mv2000[2], ModAClass->vec_mv2000[3], ModAClass->vec_mv2000[4], ModAClass->vec_mv2000[5],
						                           ModAClass->vec_mv2000[6], ModAClass->vec_mv2000[7], ModAClass->vec_mv2000[8], ModAClass->vec_mv2000[9], ModAClass->vec_mv2000[10],
						                           ModAClass->vec_mv2000[11],ModAClass->vec_mv2000[12],ModAClass->vec_mv2000[13],ModAClass->vec_mv2000[14],ModAClass->vec_mv2000[15]);  	

	 //Volt. Difference
	 TableLog.xfprintf(0,"%s,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f","Volt. Difference",vMatrix[0][0]- ModAClass->vec_mv2000[0],vMatrix[0][1]-ModAClass->vec_mv2000[1], 
														   vMatrix[0][2]- ModAClass->vec_mv2000[2],vMatrix[0][3]-ModAClass->vec_mv2000[3],
														   vMatrix[0][4]-ModAClass->vec_mv2000[4], vMatrix[0][5]-ModAClass->vec_mv2000[5],
														   vMatrix[0][6]- ModAClass->vec_mv2000[6],vMatrix[0][7]-ModAClass->vec_mv2000[7],  
														   vMatrix[0][8]- ModAClass->vec_mv2000[8],vMatrix[0][9]-ModAClass->vec_mv2000[9],  
														   vMatrix[0][10]- ModAClass->vec_mv2000[10],vMatrix[0][11]-ModAClass->vec_mv2000[11],
														   vMatrix[0][12]-ModAClass->vec_mv2000[12],vMatrix[0][13]- ModAClass->vec_mv2000[13],
														   vMatrix[0][14]-ModAClass->vec_mv2000[14],vMatrix[0][15]-ModAClass->vec_mv2000[15]); 
														   
	}
	GetTime.Format(" %02d:%02d:%02d ",_t.wHour, _t.wMinute, _t.wSecond);
   	TableLog.xfprintf(0,"==========Finish Loging : %s==========",GetTime);
	TableLog.LogFileClose(); 


 }
 void CSlaveBMSDlg::OnCheckBalancingTest()
 {

	MODULE_INFORM  BalancingPack;
	CString strAlam="";
	memset( BalancingPack.Data,0,sizeof(short int)*3  );
	BalancingPack.Data[0]=100;   //fix value

	// On 할때..1

	if(Balancing_Test.GetCheck())
	{
		BalancingPack.Data[1]=1;
	}
	else	// Off 할때.0
	{
		BalancingPack.Data[1]=0;
	}

	BalancingPack.modpack.ID = 0x01;
	BalancingPack.modpack.Command = 0x10;
	BalancingPack.modpack.Address =52100;
	BalancingPack.modpack.Quantity =3;
	BalancingPack.modpack.Datalength =6;

	ModAClass->qModInform.push( BalancingPack);

 }

 BOOL CSlaveBMSDlg::PreTranslateMessage(MSG* pMsg)
{
		if( pMsg->message == WM_KEYDOWN ) 
	{ 
		if( pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN ) 
				return TRUE; 
	} 

	return __super::PreTranslateMessage(pMsg);
}




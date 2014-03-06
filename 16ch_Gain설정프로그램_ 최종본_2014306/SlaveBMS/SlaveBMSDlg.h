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

// SlaveBMSDlg.h : header file
//

#pragma once
#include "afxwin.h"


 #include<vector>
using namespace std;

 #define WM_BMSMOD_INFO		(WM_USER+200)
#define WM_MV2000_INFO			(WM_USER+201)
#define WM_THREADMAIN_STOP		(WM_USER+202)
 

// Lib Files from ControlLib  & ButtonLib
#include "..\SlaveBMS\ButtonControl\xshadebutton.h"

#include "..\SlaveBMS\control\fontstatic.h"
#include  "..\SlaveBMS\control\RgbColor.h"
#include "..\SlaveBMS\Control\cxstatic.h"
#include "ModelessDialogTracker.h"
// List Control  
#include "..\ControlLib\quicklist.h"
#include "..\ControlLib\headerctrlex.h"
#include "..\ControlLib\theme.h"
#include "SkinRadio.h"
// Tab Dialog


// Log Lib
#include "HXLog.h"

#include <vector>
using namespace std;

// CSlaveBMSDlg dialog



class CSlaveVoltA
{
public:
	CString textdata;

};

class CSlaveBMSDlg : public CDialog
{
// Construction
public:
	CSlaveBMSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SLAVEBMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
		// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   	
   	// 통신 쓰레드
	CKThread k_ThreadRead;  
	static BOOL WINAPI ThreadRead(CKThread* pThread,LPVOID lpData);

	CSThread s_ThreadRead;  
	static BOOL WINAPI ThreadReadB(CSThread* pThread2, LPVOID lpData2);

	afx_msg LRESULT OnThemeChanged(WPARAM, LPARAM);		  
	afx_msg void OnHdnItemchangingGainlistA(NMHDR *pNMHDR, LRESULT *pResult);   

	DECLARE_MESSAGE_MAP()

public:
		// 자동 포트 설정 (2013-11-26,화)
	CPortManager m_PortManager[2];
	SerialInfo  m_SerialInfo[2];


   // void OnButtonRadio(UINT id); 

	CxShadeButton m_BtnPortOpenA;
	CxShadeButton m_BtnPortOpenB;
	CTheme ThemeSlaveBMS;
	vector< CString>VecItem; 
     	// 벡터 생성
	typedef std::vector <float> VoltData;
	typedef std::vector <VoltData> Mat_Volt;
	Mat_Volt vMatrix;
	void ReleaseVoltMemory(Mat_Volt &VoltM); 	
public:	 

	CComboBox m_cbComPortA;
	CComboBox m_cbComPortB;

  


	int ModNum;
	void InitializePort();
	void SettingsA();
	void SettingsB();

	void MakeComboPortA();
	void MakeComboPortB();

	void WriteProfileA();
	void ReleaseSerialA();

	void WriteProfileB();
	void ReleaseSerialB();

	afx_msg void OnBtnCommOpenA();		   
	afx_msg void OnBtnCommOpenB();		    
	
	/////////////2013-11-27 수/////////////
	// Com Port 정보

  CString ComPortA;
  CString ComPortB;
  afx_msg void OnDestroy();
  afx_msg void OnSelchangeComboCommA();
  afx_msg void OnSelchangeComboCommB();

  afx_msg void OnClose();
  afx_msg void OnButtonGainset();

  CQuickList GainList_A;

  CHeaderCtrlEx  GainHeaderCtrl;
  void CreateSlaveBMSTable();
  void DrawSlaveHeader();
  void SetSlaveListTitle(CString *STitle);		
  // 아이템 삽입
  void SetSlaveListItem();
 

public:
    //////////2013-12-04  금//////////////
 	 //CCOM *m_pCOM[2];
	void COMPortOpenA();
	void COMPortOpenB();

	BOOL COMPortCloseA();
   	BOOL COMPortCloseB();

	CxShadeButton Btn_Set;
	CxShadeButton Btn_SaveFile;	
 	void SetStaticControl();
	
public:
	CFontStatic m_charTX_A;
	CFontStatic m_charRX_A;
	CFontStatic m_charTX_B;
	CFontStatic m_charRX_B;

	CxStatic Tx_Led_A;
	CxStatic Rx_Led_A;
	CxStatic Tx_Led_B;
	CxStatic Rx_Led_B;


 //  모달리스 다이얼로그
	ModelessDialogTracker trackBMSSet;
	// AFX_MSG
	afx_msg void OnButtonBMSSet();

	// com port가 열었는지, 닫혔는지 확인 기능
	CComm m_pCOMA;
	CComm m_pCOMB;
	COMM_INFO  m_COMM_INFO[2];

	// Connect Button 
	CFontStatic LabelBMS;
	CFontStatic Label_MV2000;  

	afx_msg void OnBtnSavecsvFile();
	afx_msg void OnCheckBalancingTest();
	virtual void RecordTableData();

// 사용자 파일 경로와 이름 설정
	CString strFolder;																	
	BOOL BrowseFileDlg(); 
	void SetFilePath();
//	void CreateTabControl();
//
//// 탭 컨트롤 
	afx_msg LRESULT OnBMSModuleData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMV2000Data(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnModuleDataItem(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

 private:
	CHXLog  TableLog;
	long m_lSizeKB;			// 로그 파일 초기 사이즈
	CString m_sExcelFileName;
	//CSkinRadio Mod_Radio[2];
public:
	CButton Balancing_Test;
};

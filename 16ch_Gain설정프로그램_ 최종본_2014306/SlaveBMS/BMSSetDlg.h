#pragma once
#include "ModelessDialogTracker.h"
#include "colorctrl.h"
#include "fontctrl.h"
#include "..\SlaveBMS\ButtonControl\xshadebutton.h"



// CBMSSetDlg 대화 상자입니다.

class CBMSSetDlg :  public CDialog,ModelessDialogHelper
{
	//DECLARE_DYNAMIC(CBMSSetDlg)

public:

	///////////////////////////////////////////
	// stuff specific to the modeless dialog.
	CBMSSetDlg(ModelessDialogTracker& tracker);   
	BOOL Create(UINT nID, CWnd* pWnd)           	
	{ return CDialog::Create(nID,pWnd);	}
	BOOL ShowWindow(int nCmdShow)
	{ return CDialog::ShowWindow(nCmdShow); }
	void PostNcDestroy()
	{ delete this;
	}
	//void OnCancel()								// make sure dialog is only closed with DestroyWindow.. not CDialog::OnOK or CDialog::OnCancel
	//{ DestroyWindow(); }

	///////////////////////////////////////////
	virtual ~CBMSSetDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BMSSET_DLG };

protected:	
	
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()


public:		
	
   	afx_msg void OnEnChangeEditId();
	afx_msg void OnEnChangeEditCellNum();
	afx_msg void OnEnChangeEditTempnum();
	void CreateControls();
	// Mod ID : 1 ~ 32 // Cell No. : 1 ~ 16// Temp No. : 1 ~ 16
	void CheckModNumber();			
	afx_msg void OnButtonSet();
	
 	CColorCtrl<CFontCtrlEx < CEdit > > m_ID;
	CColorCtrl<CFontCtrlEx < CEdit > > m_CellNum;
	CColorCtrl<CFontCtrlEx < CEdit > > m_TempNum;

	CFontStatic Label_ID;
	CFontStatic Label_CellNum;
	CFontStatic Label_TempNum;
	CxShadeButton Btn_ModSet;

	void RequestData(MODULE_INFORM &ModInfo);
	void DisplayMessage(int Mod,MODULE_INFORM &ModPack,CString strWarn);
};


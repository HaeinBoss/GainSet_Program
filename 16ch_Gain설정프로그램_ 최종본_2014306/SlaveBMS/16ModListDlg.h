#pragma once


// C16ModListDlg 대화 상자입니다.

class C16ModListDlg : public CDialog
{
	DECLARE_DYNAMIC(C16ModListDlg)

public:
	C16ModListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~C16ModListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CESGAIN_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

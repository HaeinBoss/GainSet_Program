#pragma once


// C16ModListDlg ��ȭ �����Դϴ�.

class C16ModListDlg : public CDialog
{
	DECLARE_DYNAMIC(C16ModListDlg)

public:
	C16ModListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~C16ModListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CESGAIN_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

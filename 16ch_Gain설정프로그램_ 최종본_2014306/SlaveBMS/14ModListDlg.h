#pragma once
// List Control  
#include "..\ControlLib\quicklist.h"
#include "..\ControlLib\headerctrlex.h"
#include "..\ControlLib\theme.h"  


#include <vector>
using namespace std;

// C14ModListDlg ��ȭ �����Դϴ�.

class C14ModListDlg : public CDialog
{
	DECLARE_DYNAMIC(C14ModListDlg)

public:
	C14ModListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~C14ModListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SUNVERGEGAIN_FORM };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnThemeSet(WPARAM, LPARAM);		  
   	afx_msg LRESULT OnModADataItem(WPARAM wParam, LPARAM lParam);	 


	afx_msg LRESULT OnBMSModuleData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMV2000Data(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	
public:
	// ǥ�׸���
	void CreateMod14Table(); 
	void DrawSlaveHeader();
	void SetSlaveListTitle(CString *STitle);
    void SetSlaveListItem();

	CHeaderCtrlEx  HeaderCtrlA;
	CQuickList Mod14_List;
	CTheme themeModA;
	vector< CString>VecModA;   	
	int ModANum;


	// ���� ����
	typedef std::vector <float> ModVoltA;
	typedef std::vector <ModVoltA> Mat_VoltA;
	Mat_VoltA vMatrixA;
	void ReleaseVoltMemory(Mat_VoltA &VoltA); 	
	
};

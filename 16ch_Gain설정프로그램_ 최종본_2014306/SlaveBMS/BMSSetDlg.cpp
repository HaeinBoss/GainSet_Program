// BMSSetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SlaveBMS.h"
#include "BMSSetDlg.h"


// CBMSSetDlg ��ȭ �����Դϴ�.

//IMPLEMENT_DYNAMIC(CBMSSetDlg, CDialog)


BOOL CheckModAData(MODULE_INFORM &MOD_PACK,USHORT& m1, USHORT& m2)
{
   BOOL bRet = TRUE;


   if(MOD_PACK.Data[0] >=1 && MOD_PACK.Data[0] <=m1)
  {
  	if(MOD_PACK.Data[1] >=1 && MOD_PACK.Data[1] <=m2)
  	{
  		if(MOD_PACK.Data[2] >=1 && MOD_PACK.Data[2] <=m2)
  		{
			bRet=TRUE;
  		}
  
  	}
  
  }
   else  if (   (( MOD_PACK.Data[0] <1) &&  (MOD_PACK.Data[0] <0)    ||  (MOD_PACK.Data[0] >m1)  )  ||
  			  (  ( MOD_PACK.Data[1] <1) &&  (MOD_PACK.Data[1] <0)    ||  (MOD_PACK.Data[1] >m2)  ) ||
  			( ( MOD_PACK.Data[2] <1) &&  (MOD_PACK.Data[2] <0)       ||  (MOD_PACK.Data[2] >m2)  )	  )
   {
	 bRet=FALSE;
   }

   	
	return bRet;
}

CBMSSetDlg::CBMSSetDlg(ModelessDialogTracker& tracker)
: ModelessDialogHelper(tracker, *this)
{

   
}

CBMSSetDlg::~CBMSSetDlg()
{

}

void CBMSSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_ID);
	DDX_Control(pDX, IDC_EDIT_CELLNUM, m_CellNum);
	DDX_Control(pDX, IDC_EDIT_TEMPNUM, m_TempNum);
	DDX_Control(pDX, IDC_STATIC_MODLABEL, Label_ID);
	DDX_Control(pDX, IDC_STATIC_CELLNUM_LABEL, Label_CellNum);
	DDX_Control(pDX, IDC_STATIC_TEMPNUM_LABEL, Label_TempNum);
	DDX_Control(pDX, IDC_BTN_SET, Btn_ModSet);
}


BEGIN_MESSAGE_MAP(CBMSSetDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT_ID, &CBMSSetDlg::OnEnChangeEditId)
	ON_EN_CHANGE(IDC_EDIT_CELLNUM, &CBMSSetDlg::OnEnChangeEditCellNum)
	ON_EN_CHANGE(IDC_EDIT_TEMPNUM, &CBMSSetDlg::OnEnChangeEditTempnum)
	ON_BN_CLICKED(IDC_BTN_SET, &CBMSSetDlg::OnButtonSet)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CBMSSetDlg �޽��� ó�����Դϴ�.

  BOOL CBMSSetDlg::OnInitDialog()
{
	__super::OnInitDialog();


	CreateControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CBMSSetDlg::CreateControls()
{
	CFont sFont;			
	DWORD dwControlColor = ::GetSysColor(CTLCOLOR_DLG);

	sFont.CreateFont(16,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,
		                                    OUT_DEFAULT_PRECIS,   // ������е�
											CLIP_DEFAULT_PRECIS,	// Ŭ�������е�
											DEFAULT_QUALITY,
											DEFAULT_PITCH,"Arial");

	m_ID.SetTextColor(RGB(0,0,0));
	m_ID.SetBkColor(RGB(190,218,245));
	m_ID.SetFont(&sFont);
  
	m_CellNum.SetTextColor(RGB(0,0,0));
	m_CellNum.SetBkColor(RGB(190,218,245));
	m_CellNum.SetFont(&sFont);
	
	m_TempNum.SetTextColor(RGB(0,0,0));
	m_TempNum.SetBkColor(RGB(190,218,245));
	m_TempNum.SetFont(&sFont);

	sFont.Detach();

	Label_ID.SetFontStatic("Arial",16,RGB(0,0,0),FS_BOLD | FS_LEFT);
	Label_ID.SetTextString("Mod ID");
	Label_ID.SetBackground(RGB(190,218,245));
	
	Label_CellNum.SetFontStatic("Arial",16,RGB(0,0,0),FS_BOLD | FS_LEFT);
	Label_CellNum.SetTextString("Cell Num");
	Label_CellNum.SetBackground(RGB(190,218,245));

	Label_TempNum.SetFontStatic("Arial",16,RGB(0,0,0),FS_BOLD | FS_LEFT);
	Label_TempNum.SetTextString("Temp Num");
	Label_TempNum.SetBackground(RGB(190,218,245));

	Btn_ModSet.SetShade(SHHS_SOFTBUMP,8,10,50,CR_RED_BTN);
	Btn_ModSet.SetFont("Tahoma",13,600);


}

////////////////Edit Box ���ڼ� ���͸�/////////////////////////
void CBMSSetDlg::OnEnChangeEditId()
{
	  CString strLen;
	  m_ID.GetWindowTextA(strLen);

    if(strLen.GetLength() >3)     // 3���ڷ� ������ ���  
    {  
         // �ʰ� �Ǿ��� ������ �������� �Է��� ���ڸ� �����ؾ� �Ѵ�.  
		CString strOutText = strLen.Left(strLen.GetLength() - 1);  
		m_ID.SetWindowText(strOutText);  
		m_ID.SetSel(strOutText.GetLength(), strOutText.GetLength());  

    }  

}

void CBMSSetDlg::OnEnChangeEditCellNum()
{
   CString strLen;
	m_CellNum.GetWindowTextA(strLen);
		
    if(strLen.GetLength() > 2) // 2���ڷ� ������ ���  
    {  
         // �ʰ� �Ǿ��� ������ �������� �Է��� ���ڸ� �����ؾ� �Ѵ�.  
        CString strOutText = strLen.Left(strLen.GetLength() - 1);   
       	m_CellNum.SetWindowText(strOutText);  
		// ��ü���� (������ġ , ����ġ)       
        m_CellNum.SetSel(strOutText.GetLength(), strOutText.GetLength());  

    }  
	
}

void CBMSSetDlg::OnEnChangeEditTempnum()
{
  	CString strLen;
	m_TempNum.GetWindowTextA(strLen);
		
    if(strLen.GetLength() > 2) // 2���ڷ� ������ ���  
    {  
         // �ʰ� �Ǿ��� ������ �������� �Է��� ���ڸ� �����ؾ� �Ѵ�.  
        CString strOutText = strLen.Left(strLen.GetLength() - 1);   
       	m_TempNum.SetWindowText(strOutText);  
		// ��ü���� (������ġ , ����ġ)       
        m_TempNum.SetSel(strOutText.GetLength(), strOutText.GetLength());  
    }  
}


///////// Mod ID , Cell Num, Temp Num //////////
 // Mod ID : 1 ~ 32  / Cell No. : 1 ~ 16 
// Temp No. : 1~16

void CBMSSetDlg::CheckModNumber()
{
	MODULE_INFORM  ModData;

	CString strText[3];
	CString strAlam="";
	memset( ModData.Data,0,sizeof(short int)*3  );

		   // ����� ���� �Է¹ޱ�
	m_ID.GetWindowText( strText[0]);
	m_TempNum.GetWindowText( strText[2]);
	m_CellNum.GetWindowText( strText[1]);


	ModData.Data[0] =	_ttoi(strText[0]);
	ModData.Data[1] =	_ttoi(	strText[1]);
	ModData.Data[2] =	_ttoi(	strText[2]);

 
	USHORT m3=32;
	USHORT m4=16;

	// ���� ���͸�

   if(ModData.Data[0] ==255)
   {
		ModData.Data[1] =0; 
		ModData.Data[2] =0;

		::Sleep(5);
		SetTimer(1,410, NULL);	
		strAlam.Format("�ʱ�ȭ�� �Ͽ����ϴ�!");	

		
		if(MessageBox(strAlam,"BMS �ʱ�ȭ",MB_ICONINFORMATION)==IDOK)
		{
		  RequestData(ModData);
		}


	 }
   else
   { 
		   if( CheckModAData(ModData,m3,m4))
		   {
			 strAlam.Format(" Module ID , Cell Temp �� �����Ǿ����ϴ�");
			 DisplayMessage(1,ModData,strAlam);

		   }
		   else
		   {
			 strAlam.Format(" ������ ����ϴ�.\n\nMod id :1 ~ 32  (�ʱ�ȭ:255) \n\nCell Num : 1 ~ 16\n\nTemp Num : 1 ~ 16");
			 DisplayMessage(0,ModData,strAlam);
		   }

   }
}
void CBMSSetDlg::OnButtonSet()
{
	CheckModNumber();
}


void CBMSSetDlg::RequestData(MODULE_INFORM &ModInfo)
{
	ModInfo.modpack.ID = 0x01;
	ModInfo.modpack.Command = 0x10;
	ModInfo.modpack.Address =52100;
	ModInfo.modpack.Quantity =3;
	ModInfo.modpack.Datalength =6;

	ModAClass->qModInform.push( ModInfo);

}



void CBMSSetDlg::DisplayMessage(int Mod,MODULE_INFORM &ModPack,CString strWarn)
{
	switch(Mod)
	{
	case 0:

	::Sleep(5);
	SetTimer(1, 410, NULL);
	//strAlam.Format(" ������ ����ϴ�.\n\nMod id :1 ~ 32  (�ʱ�ȭ:255) \n\nCell Num : 1 ~ 16\n\nTemp Num : 1 ~ 16");
	if(MessageBox(strWarn,"�����ʰ�",MB_ICONERROR)==IDOK)
	{
	   	// return;
	}

	 break;

   	case 1:

	::Sleep(5);
	SetTimer(1, 410, NULL);	
	if(MessageBox(strWarn,"BMS SET",MB_ICONINFORMATION)==IDOK)
	{
	  RequestData(ModPack);
	}
  
	break;

	}


}

void CBMSSetDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strCaption; // ������ ĸ�� 
	CWnd* pWnd=AfxGetMainWnd()->GetWindow(GW_HWNDFIRST); 

	while(pWnd)
	{ 
		if(pWnd->IsWindowVisible() && pWnd->GetWindowTextLength() && pWnd->GetOwner() != NULL) 
		{ 
	    	pWnd->GetWindowText(strCaption); 
		    if(strstr(strCaption,"�����ʰ�") != NULL) break; 
			else  if(strstr(strCaption,"BMS SET") != NULL) break; 
			else if(strstr(strCaption,"BMS �ʱ�ȭ") != NULL) break; 
		} 
	    pWnd = pWnd->GetWindow(GW_HWNDNEXT); 
	} 

	if(pWnd) 
	{ 
		pWnd->SendMessage(WM_CLOSE, 0, 0L); 
		KillTimer(1); 
	} 

__super::OnTimer(nIDEvent);
}

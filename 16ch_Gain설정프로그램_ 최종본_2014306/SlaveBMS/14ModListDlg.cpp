// 14ModListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SlaveBMS.h"
#include "14ModListDlg.h"


// C14ModListDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(C14ModListDlg, CDialog)

C14ModListDlg::C14ModListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C14ModListDlg::IDD, pParent)
	,ModANum(0)
{

}

C14ModListDlg::~C14ModListDlg()
{
}

void C14ModListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_14MOD_LIST, Mod14_List);
}


BEGIN_MESSAGE_MAP(C14ModListDlg, CDialog)
 ON_MESSAGE(0x031A, OnThemeSet)
 ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, OnModADataItem)
END_MESSAGE_MAP()


// C14ModListDlg �޽��� ó�����Դϴ�.

LRESULT C14ModListDlg::OnThemeSet(WPARAM, LPARAM)
{
	themeModA.ThemeChanged(m_hWnd);
	return 1;
}


BOOL C14ModListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	CreateMod14Table();
    themeModA.Init(m_hWnd);
	Mod14_List.SetThemeManager(&themeModA);


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void C14ModListDlg::CreateMod14Table()
{
  // ����Ʈ ��Ʈ�� Format ����
	Mod14_List.MoveWindow(0,0,1078,285);
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd, LVS_EX_FULLROWSELECT, 0);
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd,LVS_EX_GRIDLINES,LVS_EX_GRIDLINES);
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd,LVS_EX_DOUBLEBUFFER,LVS_EX_DOUBLEBUFFER);
   
   	// ����Ʈ ��Ʈ�� ��� ����
	HeaderCtrlA.SubclassWindow(Mod14_List.GetHeaderCtrl()->m_hWnd);
	CFont Dfont;
    Dfont.CreateFontA(16, 0, 0, 0, 750, 0, 0, 0, 	DEFAULT_CHARSET,						//	���ڼ����� (iCharSet)
													OUT_STRING_PRECIS,			//	 ������е�( iOutPrecision)
													CLIP_CHARACTER_PRECIS,			//  Ŭ�������е� (iClipPrecision)
													DEFAULT_QUALITY,						//  ��¹���ǰ��  (iQuality)
													 DEFAULT_PITCH |FF_MODERN,   //	�۲�   (PitchiPitchAndFamily)
													"Arial");			
	Mod14_List.SetFont(&Dfont);
	HeaderCtrlA.SetFont(&Dfont);    //��� ������ ��Ʈ ����
    HeaderCtrlA.SetHeight(28);      //��� ������ ũ�� ���� => ������ �����ϵ��� �˳��ϰ� ����
	Dfont.Detach();
	
	HeaderCtrlA.SetBkColor(RGB(56,64,103));   //���� ����
	HeaderCtrlA.SetTextColor(RGB(230,235,231)); //���ڻ� ����

	DrawSlaveHeader();
  

}
void C14ModListDlg::DrawSlaveHeader()
{
   CString SlaveTitle[]= { "","CH 1","CH 2",								 
							 "CH 3","CH 4",
			 				 "CH 5","CH 6",
							 "CH 7","CH 8",
							 "CH 9","CH 10",				
							 "CH 11","CH 12",
							 "CH 13","CH 14"};

	SetSlaveListTitle(SlaveTitle);
	Mod14_List.SetItemHeight(27);
	Mod14_List.SetItemCount(9);

	SetSlaveListItem();
}

void C14ModListDlg::SetSlaveListTitle(CString *STitle)
{
	for(int col=0; col<15; col++)
	{
		if(col==0)
		{
		  	Mod14_List.InsertColumn(col,STitle[col],	LVCFMT_CENTER, 176);       
		}
		else
		{
			Mod14_List.InsertColumn(col,STitle[col],	LVCFMT_CENTER, 64);       
			
		}
	}

}


////////////////// ����Ʈ ��Ʈ�� ������//////////////////

void C14ModListDlg::SetSlaveListItem()
{
	char *strItem[]={"BMS #1   Volt","BMS #1   Temp",
					 "MV2000", "Volt Difference",
					 "BMS #2   Volt","BMS #2   Temp"};

	 CSlaveVoltA SlaveItem[6];
	  //    SlaveItem = new CSlaveVoltA[6];
	 for (int i=0; i<6;i++)
	 {
		// ���� ����
		SlaveItem[i].textdata = strItem[i];
     	 //���� ����
	    VecModA.push_back(SlaveItem[i].textdata);
	 }
	  

}

//////////// ����Ʈ ��Ʈ�� �޽��� ��Ʈ�� //////////////////

LRESULT C14ModListDlg::OnModADataItem(WPARAM wParam, LPARAM lParam)
{

    if( (HWND) wParam ==Mod14_List.GetSafeHwnd() )
   {
	   //lParam is a pointer to the data that is needed for the element
		CQuickList::CListItemData* SlaveBMSData = ( CQuickList::CListItemData*)lParam;
		// Get which item and subitem that is asked for.
		int item = SlaveBMSData->GetItem();	 
		int subItem =SlaveBMSData->GetSubItem();

		float Difference=0.0;

		//CSlaveVoltA *slaveitem = VecItem[item];
	
		#ifndef QUICKLIST_NOEDIT
			if(   SlaveBMSData->GetSubItem() <15)
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

	 //if( ������ ����< logCnt )


		if(SlaveBMSData->GetSubItem()==0)
		{

			if(SlaveBMSData->GetItem()<6)
			{
				SlaveBMSData->m_text.Format(_T("   %s      "),  VecModA[SlaveBMSData->GetItem()]);
			}
		}
		else  if(SlaveBMSData->GetSubItem()<=14)
		{

			if( (SlaveBMSData->GetItem() <6))
			{
				 if(ModANum!=0)
			     { 
/*						  if( SlaveBMSData->GetItem()==0)
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
						  }*/  
			        }  
			}
		
		 //    if(ModAClass->vec_mv2000.size()>0)
		 //    {
			//		if( SlaveBMSData->GetItem()==2)
			//	   {
			//			 SlaveBMSData->m_text.Format(_T("  %1.3f"), ModAClass->vec_mv2000[SlaveBMSData->GetSubItem()-1]);
			//		}
			//		else if( SlaveBMSData->GetItem()==3)
			//		{

			//			 if(ModANum!=0)
			//			 {
			//				Difference=   vMatrix[0][SlaveBMSData->GetSubItem()-1]- ModAClass->vec_mv2000[SlaveBMSData->GetSubItem()-1];
			//			 }
			//				 SlaveBMSData->m_text.Format(_T("  %1.3f"), 	Difference);
			//				 if((-0.005 < Difference) && (Difference<0.005))
			//				 {
			//					 // ���ڻ�: ������
			//					SlaveBMSData->m_colors.m_textColor =	RGB(25,25,25);
			//				 }
			//				 else
			//				 {	  	// ���ڻ�: ������
			//						SlaveBMSData->m_colors.m_textColor =	RGB(255,11,11);
			//				 }
			//		}
			//}
		
		} 

    }   //����Ʈ �ڵ鷯

   return FALSE;
}


 void C14ModListDlg::ReleaseVoltMemory(Mat_VoltA &VoltA)
 {
	Mat_VoltA::iterator erase_vec  = VoltA.begin();
	while(erase_vec != VoltA.end())
	{
			erase_vec = VoltA.erase(erase_vec);
	}

 }


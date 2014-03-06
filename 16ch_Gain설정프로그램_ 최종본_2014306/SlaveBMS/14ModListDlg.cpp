// 14ModListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SlaveBMS.h"
#include "14ModListDlg.h"


// C14ModListDlg 대화 상자입니다.

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


// C14ModListDlg 메시지 처리기입니다.

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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void C14ModListDlg::CreateMod14Table()
{
  // 리스트 컨트롤 Format 설정
	Mod14_List.MoveWindow(0,0,1078,285);
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd, LVS_EX_FULLROWSELECT, 0);
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd,LVS_EX_GRIDLINES,LVS_EX_GRIDLINES);
	ListView_SetExtendedListViewStyleEx(Mod14_List.m_hWnd,LVS_EX_DOUBLEBUFFER,LVS_EX_DOUBLEBUFFER);
   
   	// 리스트 컨트롤 헤더 설정
	HeaderCtrlA.SubclassWindow(Mod14_List.GetHeaderCtrl()->m_hWnd);
	CFont Dfont;
    Dfont.CreateFontA(16, 0, 0, 0, 750, 0, 0, 0, 	DEFAULT_CHARSET,						//	문자셋종류 (iCharSet)
													OUT_STRING_PRECIS,			//	 출력정밀도( iOutPrecision)
													CLIP_CHARACTER_PRECIS,			//  클리핑정밀도 (iClipPrecision)
													DEFAULT_QUALITY,						//  출력문자품질  (iQuality)
													 DEFAULT_PITCH |FF_MODERN,   //	글꼴   (PitchiPitchAndFamily)
													"Arial");			
	Mod14_List.SetFont(&Dfont);
	HeaderCtrlA.SetFont(&Dfont);    //헤더 영역에 폰트 설정
    HeaderCtrlA.SetHeight(28);      //헤더 영역의 크기 설정 => 두줄이 가능하도록 넉넉하게 설정
	Dfont.Detach();
	
	HeaderCtrlA.SetBkColor(RGB(56,64,103));   //배경색 설정
	HeaderCtrlA.SetTextColor(RGB(230,235,231)); //문자색 설정

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


////////////////// 리스트 컨트롤 아이템//////////////////

void C14ModListDlg::SetSlaveListItem()
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
	    VecModA.push_back(SlaveItem[i].textdata);
	 }
	  

}

//////////// 리스트 컨트롤 메시지 컨트롤 //////////////////

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

	 //if( 아이템 개수< logCnt )


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
			//					 // 글자색: 검은색
			//					SlaveBMSData->m_colors.m_textColor =	RGB(25,25,25);
			//				 }
			//				 else
			//				 {	  	// 글자색: 빨간색
			//						SlaveBMSData->m_colors.m_textColor =	RGB(255,11,11);
			//				 }
			//		}
			//}
		
		} 

    }   //리스트 핸들러

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


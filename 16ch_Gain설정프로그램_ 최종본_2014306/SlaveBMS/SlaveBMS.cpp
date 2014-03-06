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

// SlaveBMS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SlaveBMS.h"
#include "SlaveBMSDlg.h"
#include "crcprotocol.h"
#include <crtdbg.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSlaveBMSApp

BEGIN_MESSAGE_MAP(CSlaveBMSApp, CWinApp)
//	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
//	ON_MESSAGE(WM_THREAD_STOP, OnThreadStop)
END_MESSAGE_MAP()


// CSlaveBMSApp construction

CSlaveBMSApp::CSlaveBMSApp()
{
	m_pThreadMain=NULL;
	 m_pThreadSub=NULL;
	//DlgSlaveBMS->m_pCOM[0]=NULL;
	//DlgSlaveBMS->m_pCOM[1]=NULL;
}


// The one and only CSlaveBMSApp object

CSlaveBMSApp theApp;


// CSlaveBMSApp initialization

BOOL CSlaveBMSApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	g_strBinDir=GetModulePath();
	CSlaveBMSDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK													  2
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


//// 쓰레드 돌리기/////



  void CSlaveBMSApp::SendStopMessage(int nCase)
  {

	    CSlaveBMSDlg *pSlaveDlg=NULL;
	  if(nCase==THREAD_MODULE_STOP)
	  {
		  ::SendMessage(pSlaveDlg->m_hWnd,WM_THREADMAIN_STOP,(WPARAM)THREAD_MODULE_STOP,(LPARAM)NULL);
	  }
	  else if(nCase==THREAD_MV2000_STOP)
	  {
		  ::SendMessage(pSlaveDlg->m_hWnd,WM_THREADMAIN_STOP,(WPARAM)THREAD_MV2000_STOP,(LPARAM)NULL);
	  }

  }


  void CSlaveBMSApp::CreatClass(CString nOrder)
  {
	  if(nOrder=="Main")
	  {
			m_pThreadMain = new CThreadMain( this );
		  	//ModAClass = new CModVoltA();
	  }
	  else if(nOrder=="Sub")
	  {
		  m_pThreadSub = new CThreadSub(this);
	  }
  }

  // 쓰레드, CCOM 변수를 삭제하는 함수
  void CSlaveBMSApp::ControlComm(CString nCase)
  {
	if(nCase=="Main")
	{
		  delete m_pThreadMain;
           m_pThreadMain = NULL;

	}
	else if(nCase=="Sub")
	{
		delete m_pThreadSub;
	     m_pThreadSub=NULL; 
	
	   }

  }



  int CSlaveBMSApp::ExitInstance()
 {

   
	 return CWinApp::ExitInstance();

 }



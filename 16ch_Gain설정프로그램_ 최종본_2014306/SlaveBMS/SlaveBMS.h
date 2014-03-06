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

// SlaveBMS.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "SlaveBMSDlg.h"
//#include "..\lib\Serial\CCOM.h"
#include "threadmain.h"
#include "threadsub.h"

#define THREAD_MODULE_STOP			0
#define THREAD_MV2000_STOP				1

// CSlaveBMSApp:
// See SlaveBMS.cpp for the implementation of this class
//

class CSlaveBMSApp : public CWinApp
{
public:
	CSlaveBMSApp();

// Overrides
	public:
	virtual BOOL InitInstance();

	 //CCOM *m_pCOM[2];
	 	virtual int ExitInstance();
	// Implementation

	CThreadMain *m_pThreadMain;
	CThreadSub   *m_pThreadSub;
   	CSlaveBMSDlg  *DlgSlaveBMS;

	void CreatClass(CString nOrder);
	void ControlComm(CString nCase);			
	
	void SendStopMessage(int nCase);
	
	   //////////2013-12-04  ±Ý//////////////
	DECLARE_MESSAGE_MAP()
};

extern CSlaveBMSApp theApp;
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

// stdafx.cpp : source file that includes just the standard includes
// SlaveBMS.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
 #include "resource.h"


CString GetModulePath()
{
	char szPath[MAX_PATH];
	memset(szPath, 0x00, MAX_PATH);

	::GetModuleFileName(NULL, szPath, MAX_PATH);

	CString sTempPath = szPath;
	int iLength = sTempPath.GetLength();
	int iPos = sTempPath.ReverseFind(TCHAR('\\'));

	CString sModulePath = sTempPath.Left(iPos);
	sModulePath += "\\";

	return sModulePath;

}


void BlinkTxControl(CxStatic *PicA, int nKind)
{
 	if(nKind==SEND_OK)
	{ 
		PicA->SetBitmap(IDB_GREEN_LED, CxStatic::FitControl);
		//PicB->LoadFromFile(strImgTxOn);
	}
	else if(nKind==SEND_END)
	{	
		PicA->SetBitmap(IDB_DKGREEN_LED, CxStatic::FitControl);
		//PicB->LoadFromFile(strImgTxOff );
	}
	else  if(nKind==SEND_OFF)
	{
	 PicA->SetBitmap(IDB_GRAYL_LED, CxStatic::FitControl);
	}

}


void BlinkRxControl(CxStatic *PicB, int nKind)
{
	if(nKind==RECEIVE_OK)
	{ 
		PicB->SetBitmap(IDB_RED_LED, CxStatic::FitControl);
		//PicB->LoadFromFile(strImgTxOn);
	}
	else if(nKind==RECEIVE_END)
	{	
		PicB->SetBitmap(IDB_DKRED_LED, CxStatic::FitControl);
		//PicB->LoadFromFile(strImgTxOff );
	}
	else  if(nKind==OFF_RECEIVE)
	{
	 PicB->SetBitmap(IDB_GRAYL_LED, CxStatic::FitControl);
	}
}
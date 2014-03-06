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

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#pragma warning(disable: 4312)
#pragma warning(disable: 4244)
#pragma warning(disable: 4005)
#pragma warning(disable : 4996)
#pragma warning(disable : 4482)
#pragma warning(disable : 4018)
#pragma warning(disable : 4311)
#pragma warning(disable : 4267)
#pragma warning(disable : 4819)

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars
#include <afx.h>
	//User header 
#include <afxdisp.h>        // MFC 자동화 클래스입니다.
#include <afxmt.h>

#include <direct.h>

#include "WinTrace.h"	   
#include "..\lib\BHComm\PortManager.h"
 
#include "..\lib\KLib\KThread.h"
using namespace KSYSTEMS;
 
#include "..\lib\KLib\SThread.h"
using namespace KSYSTEMS2;
		  
#include "Common.h"	
#include "comm.h"
#include "global.h"	
#include "locale.h"

#include "..\SlaveBMS\Control\cxstatic.h"
#include "CrcProtocol.h"


#define SAFE_DELETE(p)	   { delete [] p;	p = NULL;  }

#define HI_BYTE(x)	((unsigned char)((x)>>8))
#define LO_BYTE(x)	((unsigned char)(x))

extern CString GetModulePath();
extern void BlinkTxControl(CxStatic *PicA,int nKind);
extern void BlinkRxControl(CxStatic *PicB,int nKind);

#pragma comment(linker,"/manifestdependency:\" type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"") 












#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



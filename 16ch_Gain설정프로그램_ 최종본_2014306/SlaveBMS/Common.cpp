#include "stdafx.h"
#include "Common.h"

CString g_strBinDir;
COMM_INFO g_Comminfo[2];




BIT_DATA g_bitData[10];		//bit data

 
  CString GetCommString( char *comm )
{

	CString StrComm=_T("");
	 char delimit_string[] = "COM";
	 char *p_token = NULL;

	 p_token = strtok(comm, delimit_string);

	 //strtok(comm, delimit_string );
	 // delimit_string  스트링에 있는 구분자(delimiter)로 comm 스트링을	token 단위로 나누어 준다

	 //COM 글자를 제하고 자르기 때문에 '19' 만남음 
	 
	 StrComm.Format("%s",p_token);

	 return StrComm;
}





















////////Limit Data/////////

void CloseLogFile();
void CreateLogFile();


CString GetCurDir();


void AddListBox(CListBox *lb, const char *format, ...)
{
	char szBuf[1024];
    va_list arglist;
    va_start(arglist, format);
	vsprintf(szBuf, format, arglist);
	va_end(arglist);

	if(lb && lb->GetSafeHwnd() )
	{
		while(lb->GetCount()>0)
		{
			lb->DeleteString(0);
		};

		DWORD_PTR dwpData;
		dwpData=lb->GetItemData(0);
		lb->InsertString(0,szBuf);

		CClientDC dc(lb);
		CFont * f = lb->GetFont();
		dc.SelectObject(f);
		CSize sz = dc.GetTextExtent(szBuf, (int)_tcslen(szBuf));
		sz.cx += 3 * ::GetSystemMetrics(SM_CXBORDER);

		if ( (int)dwpData < (int)sz.cx )
		{
			lb->SetItemData(0, (DWORD_PTR)sz.cx);
			lb->SetHorizontalExtent(sz.cx);
		}
		else
		{
			lb->SetItemData(0, (DWORD_PTR)dwpData);
			lb->SetHorizontalExtent((DWORD_PTR)dwpData);
		}
	}
}



int CALLBACK BrowseCallBackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch ( uMsg )
	{
	case BFFM_INITIALIZED:
		{
			SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
		}
		break;
	case BFFM_SELCHANGED:
		{
			TCHAR szText[MAX_PATH]={0};
			SHGetPathFromIDList( (LPCITEMIDLIST)lParam, szText);
			SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szText);
		}
		break;
	}

	return 0;
}

BOOL BrowseFolder(HWND hWnd,  char *szFolder, LPCSTR szInit/*=NULL*/)
{
	LPMALLOC	pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	CString strInit=szInit;

	bi.hwndOwner=hWnd;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=NULL;
	bi.lpszTitle=NULL;
	bi.ulFlags=BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT | BIF_VALIDATE;
	if ( !strInit.IsEmpty() )
	{
		bi.lpfn=BrowseCallBackProc;
		bi.lParam=(LPARAM)strInit.GetBuffer(strInit.GetLength());
	}
	else
	{
		bi.lpfn=NULL;
		bi.lParam=0;
	}

	pidl=::SHBrowseForFolder(&bi);

	if (pidl==NULL)
	{
		return FALSE;
	}

	::SHGetPathFromIDList(pidl,szFolder);

	if ( ::SHGetMalloc(&pMalloc) !=NOERROR)
		return FALSE;

	pMalloc->Free(pidl);
	pMalloc->Release();

	return TRUE;
}

int dir_remove(CString dir_path )
{
	int count = 0 ;

	CFileFind       ff ;
	CString         fn  , fp ;
	CFileStatus     fs ;
	CString         strPath ;
	strPath.Format("%s\\*.*" , dir_path) ;

	if (!ff.FindFile((LPCTSTR)strPath)) {
		//AfxMessageBox("FindFile Error") ;
		return 0;
	}
	BOOL    bEnd = FALSE ;
	while (!bEnd) {
		if (!ff.FindNextFile())
			bEnd = TRUE ;
		fn = ff.GetFileName() ;
		fp = ff.GetFilePath() ;
		if(ff.IsDots())
			continue ;
		else {
			count ++ ;
			if (!CFile::GetStatus((LPCTSTR)fp , fs)) {
				TRACE( "Error\n" ) ;
				ff.Close() ;
				exit( 1 ) ;
			}
			if (fs.m_attribute & 0x01) { // read only
				fs.m_attribute ^= 0x01 ;
				CFile::SetStatus((LPCTSTR)fp , fs) ;
			}
			if( ff.IsDirectory() ) {
				TRACE("%s       dir\n", fn ) ;
				dir_remove( fp ) ;
				TRACE("\n" ) ;
			}
			else {
				TRACE("%s       file\n", fn ) ;
				remove((LPCTSTR) fp) ;
			}
		}
	}
	ff.Close();
	TRACE( "dirpath = %s\n", dir_path ) ;
	::RemoveDirectory( dir_path ) ;
	return 1 ;
}


//int RemoveForOverDay_RawData(LPCSTR szLotNo)
//{
//	CString strRmdir;
//	strRmdir.Format("%s%s",g_strBinDir+(CString)"../GraphData/", szLotNo );
//	dir_remove(strRmdir);
//	return 0;
//}

BOOL BCCCheck(unsigned char *pBuf, int nCount)
{
	char check[100];

	unsigned int sum = 0;

	for (int i = 1 ; i < nCount-2; i++) // STX는 빠짐 
		sum  += pBuf[i];

	sum = sum & 0x000000FF;

	sprintf(check, "%.2X", sum);

	if(strncmp(check, (char*)&pBuf[nCount-2], 2)== 0)
	{
		return TRUE;
	}
	else
	{
		char str[2048];
		memset ( str, 0x00, sizeof(str) );
		strncpy ( str, (char*)pBuf, nCount );
		TRACE ( "\nBcc [%s], [%-2.2s], [%-2.2s]\n", str, check, &pBuf[nCount-2] );
		return FALSE;
	}
}


  
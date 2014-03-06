// SkinRadio.cpp : 구현 파일입니다.
//

#include "stdafx.h"
//#include "TestSkinRadio.h"
#include "SkinRadio.h"


// CSkinRadio

IMPLEMENT_DYNAMIC(CSkinRadio, CButton)

CSkinRadio::CSkinRadio()
{
	m_stSkinInfo.bCheck = FALSE;
	m_stSkinInfo.nMarkWidth = 0;
	m_stSkinInfo.nMarkHeight = 0;
	m_stSkinInfo.nFontSize = 12;
	m_stSkinInfo.bFontBold = FALSE;
	m_stSkinInfo.crFont = RGB(8,3,69);
	m_stSkinInfo.nAlignFormat = DT_CENTER|DT_VCENTER;
	m_stSkinInfo.crBack = RGB(236,233,213);
}

CSkinRadio::~CSkinRadio()
{
}


BEGIN_MESSAGE_MAP(CSkinRadio, CButton)
	ON_MESSAGE(WM_CXSHADE_RADIO , OnRadioInfo)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CSkinRadio 메시지 처리기입니다.


BOOL CSkinRadio::SetMarkImage(UINT nImageID)
{
	if( m_stSkinInfo.bmpMark.GetSafeHandle() )
		m_stSkinInfo.bmpMark.DeleteObject();

	if( !m_stSkinInfo.bmpMark.LoadBitmap(nImageID) )
		return FALSE;

	BITMAP bm;
	m_stSkinInfo.bmpMark.GetBitmap(&bm);

	m_stSkinInfo.nMarkWidth = bm.bmWidth / 2;
	m_stSkinInfo.nMarkHeight = bm.bmHeight;

	Invalidate(TRUE);
	return TRUE;
}

void CSkinRadio::DrawImageMark(CPaintDC *pdc, CBitmap *pBitmap, CRect rScreen, BOOL bCheck)
{
	if( !m_stSkinInfo.bmpMark.GetSafeHandle() )
		return;

	BITMAP bm;
	pBitmap->GetBitmap(&bm);
	CDC dcMem;
	dcMem.CreateCompatibleDC(pdc);
	dcMem.SelectObject(pBitmap);

	int nStateWidth=0;

	nStateWidth = bm.bmWidth / 2;

	if( m_stSkinInfo.nAlignFormat & DT_BOTTOM )
		rScreen.top = rScreen.bottom - bm.bmHeight;
	else if( m_stSkinInfo.nAlignFormat & DT_VCENTER )
		rScreen.top = rScreen.CenterPoint().y - (bm.bmHeight / 2);

	if( bCheck )
		pdc->BitBlt(rScreen.left, rScreen.top, nStateWidth, bm.bmHeight, &dcMem, nStateWidth, 0, SRCCOPY);
	else
		pdc->BitBlt(rScreen.left, rScreen.top, nStateWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);
}


void CSkinRadio::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CRect rScreen;
	GetClientRect(&rScreen);

	pDC->FillRect(&rScreen, &CBrush(m_stSkinInfo.crBack));

	DrawImageMark((CPaintDC*)pDC, &m_stSkinInfo.bmpMark, rScreen, m_stSkinInfo.bCheck);

	CString strCaption;
	GetWindowText(strCaption);

	rScreen.left += (m_stSkinInfo.nMarkWidth+2);
	DrawText((CPaintDC*)pDC, strCaption, m_stSkinInfo.nFontSize, 
		m_stSkinInfo.crFont, rScreen, 
		m_stSkinInfo.nAlignFormat, m_stSkinInfo.bFontBold);
}

void CSkinRadio::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW | BS_AUTORADIOBUTTON);

	CButton::PreSubclassWindow();
}

void CSkinRadio::SetCheck(BOOL bCheck)
{
	//CButton::SetCheck(bCheck);
	m_stSkinInfo.bCheck = bCheck;
	Invalidate(FALSE);

	OnBMSetCheck(bCheck);
}

BOOL CSkinRadio::GetCheck()
{
	return m_stSkinInfo.bCheck;
}

void CSkinRadio::OnLButtonUp(UINT nFlags, CPoint point)
{
	SetCheck(TRUE);

	CButton::OnLButtonUp(nFlags, point);
}

void CSkinRadio::OnBMSetCheck(BOOL bCheck)
{
	if(bCheck)
	{
		HWND hthis,hwnd2,hpwnd;
		hpwnd=GetParent()->GetSafeHwnd();
		hwnd2=hthis=GetSafeHwnd();
		if (hthis && hpwnd)
		{
			while(1)
			{
				hwnd2=::GetNextDlgGroupItem(hpwnd,hwnd2,0);
				if ((hwnd2==hthis)||(hwnd2==NULL)) break;
				if( hwnd2 != this->GetSafeHwnd() )
					::PostMessage(hwnd2, WM_CXSHADE_RADIO, 0, 0);					
			}
		}
	}
}

LRESULT CSkinRadio::OnRadioInfo(WPARAM wparam, LPARAM)
{
	if (m_stSkinInfo.bCheck)
		SetCheck(FALSE);

	return 0;
}

void CSkinRadio::DrawText(CPaintDC *pdc, CString strText, int nFontSize, COLORREF crFontColor, CRect rArea, UINT nFormat, BOOL bFontBold)
{
	CFont *pftOld, FontInfo;
	int nFontHeavy=0;

	nFontHeavy = ( bFontBold ) ? FW_BOLD : FW_NORMAL;
	FontInfo.CreateFont(nFontSize, 0,0,0, nFontHeavy, 0,0,0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "돋움");

	pftOld = pdc->SelectObject(&FontInfo);
	pdc->SetBkMode(TRANSPARENT);
	pdc->SetTextColor(crFontColor);

	pdc->DrawText(strText, &rArea, nFormat|DT_SINGLELINE);

	pdc->SelectObject(pftOld);
	FontInfo.DeleteObject();
}

void CSkinRadio::SetWindowText(CString strText)
{
	CWnd::SetWindowText(strText);

	Invalidate(FALSE);
}

void CSkinRadio::SetAlignFormat(UINT nAlignFormat)
{
	m_stSkinInfo.nAlignFormat = nAlignFormat;

	Invalidate(FALSE);
}

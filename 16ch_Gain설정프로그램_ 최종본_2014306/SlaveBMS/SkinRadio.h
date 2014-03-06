#pragma once


#define WM_CXSHADE_RADIO WM_USER+0x100

// CSkinRadio

class CSkinRadio : public CButton
{
	DECLARE_DYNAMIC(CSkinRadio)

public:
	static struct ST_SKIN_RADIO_INFO
	{
		CBitmap		bmpMark;
		BOOL		bCheck;
		int			nMarkWidth;
		int			nMarkHeight;
		UINT		nAlignFormat;
		int			nFontSize;
		BOOL		bFontBold;
		COLORREF	crFont;
		COLORREF	crBack;
	};

	CSkinRadio();
	virtual ~CSkinRadio();

protected:
	DECLARE_MESSAGE_MAP()
public:
	ST_SKIN_RADIO_INFO m_stSkinInfo;
	BOOL SetMarkImage(UINT nImageID);
	void DrawImageMark(CPaintDC *pdc, CBitmap *pBitmap, CRect rScreen, BOOL bCheck);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetCheck(BOOL bCheck);
	BOOL GetCheck();
	void OnBMSetCheck(BOOL bCheck);
	LRESULT OnRadioInfo(WPARAM wparam, LPARAM);
	void DrawText(CPaintDC *pdc, CString strText, int nFontSize, COLORREF crFontColor, CRect rArea, UINT nFormat, BOOL bFontBold);
	void SetWindowText(CString strText);
	void SetAlignFormat(UINT nAlignFormat);
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

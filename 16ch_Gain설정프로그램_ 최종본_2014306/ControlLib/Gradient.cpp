#include "stdafx.h"
#include "Gradient.h"
#pragma comment( lib, "msimg32.lib")

#define VECT(x,y)  (x*3 + y)
CGradient::CGradient()
{
	m_nType=CGradient::Cent;

	m_clrLT=RGB(255,255,255);
	m_clrRT=RGB(180,210,180);
	m_clrLB=RGB(120,150,120);
	m_clrRB=RGB(120,150,120);
//	m_clrLT=RGB(255,255,255);
//	m_clrRT=RGB(255,255,255);
//	m_clrLB=RGB(120,150,120);
//	m_clrRB=RGB(120,150,120);

	m_clrCT		= RGB(255,255,255);

	memset(m_triVert, NULL, sizeof(m_triVert));
}

CGradient::~CGradient()
{
}

COLORREF CGradient::GetColor(COLORREF clr1, COLORREF clr2)
{
	int red=(GetRValue(clr1) + GetRValue(clr2))/2;
	int grn=(GetGValue(clr1) + GetGValue(clr2))/2;
	int blu=(GetBValue(clr1) + GetBValue(clr2))/2;
	return RGB(red,grn,blu);
}

void CGradient::ChangeRect(const CRect& rect)
{
	int i=0;
	for( i=0; i<ROW_MAX; i++)
	{
		m_triVert[i][0].x	  =  rect.left;
		m_triVert[i][1].x	  =  rect.left+rect.Width()/2;
		m_triVert[i][2].x	   =  rect.right;
	}

	for( i=0; i<COL_MAX; i++)
	{
		m_triVert[0][i].y     =  rect.top;
		m_triVert[1][i].y     =  rect.top + rect.Height()/2;
		m_triVert[2][i].y     =  rect.bottom;
	}

	COLORREF clrTC = GetColor(m_clrLT, m_clrRT);
	COLORREF clrBC = GetColor(m_clrLB, m_clrRB);
	COLORREF clrLC = GetColor(m_clrLT, m_clrLB);
	COLORREF clrRC = GetColor(m_clrRT, m_clrRB);

	m_triVert[0][0].Red   =  GetRValue(m_clrLT)<<8;
	m_triVert[0][0].Green =  GetGValue(m_clrLT)<<8;
	m_triVert[0][0].Blue  =  GetBValue(m_clrLT)<<8;
				 
	m_triVert[0][1].Red   =  GetRValue(clrTC)<<8;
	m_triVert[0][1].Green =  GetGValue(clrTC)<<8;
	m_triVert[0][1].Blue  =  GetBValue(clrTC)<<8;
				  
	m_triVert[0][2].Red   =  GetRValue(m_clrRT)<<8;
	m_triVert[0][2].Green =  GetGValue(m_clrRT)<<8;
	m_triVert[0][2].Blue  =  GetBValue(m_clrRT)<<8;

	//SECOND ROW
	m_triVert[1][0].Red   =  GetRValue(clrLC)<<8;
	m_triVert[1][0].Green =  GetGValue(clrLC)<<8;
	m_triVert[1][0].Blue  =  GetBValue(clrLC)<<8;
				  
	m_triVert[1][1].Red   =  GetRValue(m_clrCT)<<8;
	m_triVert[1][1].Green =  GetGValue(m_clrCT)<<8;
	m_triVert[1][1].Blue  =  GetBValue(m_clrCT)<<8;
				  
	m_triVert[1][2].Red   =  GetRValue(clrRC)<<8;
	m_triVert[1][2].Green =  GetGValue(clrRC)<<8;
	m_triVert[1][2].Blue  =  GetBValue(clrRC)<<8;

	//LAST ROW
	m_triVert[2][0].Red   =  GetRValue(m_clrLB)<<8;
	m_triVert[2][0].Green =  GetGValue(m_clrLB)<<8;
	m_triVert[2][0].Blue  =  GetBValue(m_clrLB)<<8;
				  
	m_triVert[2][1].Red   =  GetRValue(clrBC)<<8;
	m_triVert[2][1].Green =  GetGValue(clrBC)<<8;
	m_triVert[2][1].Blue  =  GetBValue(clrBC)<<8;
				  
	m_triVert[2][2].Red   =  GetRValue(m_clrRB)<<8;
	m_triVert[2][2].Green =  GetGValue(m_clrRB)<<8;
	m_triVert[2][2].Blue  =  GetBValue(m_clrRB)<<8;
}

void CGradient::Draw(const CDC& dc)
{
	GRADIENT_RECT		grRC[4];
	GRADIENT_TRIANGLE	grTR[8];
	switch(m_nType)
	{
		//º¸Åë
	case CGradient::Normal:
		grRC[0].UpperLeft =0;
		grRC[0].LowerRight=8;
		::GradientFill(dc.m_hDC, m_triVert[0],9,grRC,1,GRADIENT_FILL_RECT_H);
		break;
		//
	case CGradient::Horz:
		grRC[0].UpperLeft =0;
		grRC[0].LowerRight=7;
		grRC[1].UpperLeft =1;
		grRC[1].LowerRight=8;
		::GradientFill(dc.m_hDC,m_triVert[0],9,grRC,2,GRADIENT_FILL_RECT_H);
		break;
	case CGradient::Vert:
		grRC[0].UpperLeft =0;
		grRC[0].LowerRight=5;
		grRC[1].UpperLeft =3;
		grRC[1].LowerRight=8;
		::GradientFill(dc.m_hDC,m_triVert[0],9,grRC,2,GRADIENT_FILL_RECT_V);
		break;
	case CGradient::Cent:
		grTR[0].Vertex1=VECT(1,1);	grTR[0].Vertex2=VECT(0,0);	grTR[0].Vertex3=VECT(0,2);
		grTR[1].Vertex1=VECT(1,1);	grTR[1].Vertex2=VECT(0,2);	grTR[1].Vertex3=VECT(2,2);
		grTR[2].Vertex1=VECT(1,1);	grTR[2].Vertex2=VECT(2,2);	grTR[2].Vertex3=VECT(2,0);
		grTR[3].Vertex1=VECT(1,1);	grTR[3].Vertex2=VECT(2,0);	grTR[3].Vertex3=VECT(0,0);

//		grTR[0].Vertex1=VECT(1,0);	grTR[0].Vertex2=VECT(0,1);	grTR[0].Vertex3=VECT(0,0);
//		grTR[1].Vertex1=VECT(1,0);	grTR[1].Vertex2=VECT(0,1);	grTR[1].Vertex3=VECT(1,1);
//		grTR[2].Vertex1=VECT(1,0);	grTR[2].Vertex2=VECT(2,1);	grTR[2].Vertex3=VECT(1,1);
//		grTR[3].Vertex1=VECT(1,0);	grTR[3].Vertex2=VECT(2,1);	grTR[3].Vertex3=VECT(2,0);
//		grTR[4].Vertex1=VECT(1,2);	grTR[4].Vertex2=VECT(0,1);	grTR[4].Vertex3=VECT(0,2);
//		grTR[5].Vertex1=VECT(1,2);	grTR[5].Vertex2=VECT(0,1);	grTR[5].Vertex3=VECT(1,1);
//		grTR[6].Vertex1=VECT(1,2);	grTR[6].Vertex2=VECT(2,1);	grTR[6].Vertex3=VECT(1,1);
//		grTR[7].Vertex1=VECT(1,2);	grTR[7].Vertex2=VECT(2,1);	grTR[7].Vertex3=VECT(2,2);
		::GradientFill(dc.m_hDC, m_triVert[0],9,grTR,4,GRADIENT_FILL_TRIANGLE);
		break;
	default:	
		return;
	}
}

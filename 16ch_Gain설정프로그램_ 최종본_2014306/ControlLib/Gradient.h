//Gradient.h
#ifndef _GRADIENT_H_
#define _GRADIENT_H_


class CGradient
{
public:
	enum TYPE 
	{
		Normal=0, 
		Cent, 
		Horz, 
		Vert
	};

	enum { COL_MAX=3 };
	enum { ROW_MAX=3 };

	CGradient();
	~CGradient();

	void ChangeRect(const CRect& rect);
	void Draw(const CDC& dc);
	int  GetGradient () const;
	void SetGradient (int nType=CGradient::Cent);
	static COLORREF GetColor(COLORREF clr1, COLORREF clr2);
public:
	int 		m_nType;
	COLORREF  	m_clrLT;
	COLORREF  	m_clrRT;
	COLORREF  	m_clrRB;
	COLORREF  	m_clrLB;
	COLORREF  	m_clrCT;

protected:
	TRIVERTEX	m_triVert[ROW_MAX][COL_MAX];
};


#endif //_GRADIENT_H_
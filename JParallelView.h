// JParallelView.h : interface of the CJParallelView class
//


#pragma once
#include "afxwin.h"
# define MAXDATOS 10000

class CJParallelView : public CFormView
{
protected: // create from serialization only
	CJParallelView();
	DECLARE_DYNCREATE(CJParallelView)

public:
	enum{ IDD = IDD_JPARALLEL_FORM };

// Attributes
public:
	CJParallelDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CJParallelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	FILE *f;
	int m_nDesde, m_nHasta, m_nActual;
	int array;
	int datos[MAXDATOS];
	CButton m_hPin0;
	CButton m_hPin1;
	CButton m_hPin2;
	CButton m_hPin3;
	CButton m_hPin4;
	CButton m_hPin5;
	CButton m_hPin6;
	CButton m_hPin7;
	CEdit m_hPuerto;
	CButton m_hAutorefrescar;
	CEdit m_hTiempo;
	afx_msg void OnTimer(UINT nIDEvent);
	CButton m_hLeer;
	CStatic m_hResult;
	afx_msg void OnFileOpen();
	afx_msg void OnBnClickedCheck8();
	CEdit m_hEDesde;
	CEdit m_hHasta;
	CButton m_hBRetroceder;
	CButton m_hBContador;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	void Actualizar( int dato);
};

#ifndef _DEBUG  // debug version in JParallelView.cpp
inline CJParallelDoc* CJParallelView::GetDocument() const
   { return reinterpret_cast<CJParallelDoc*>(m_pDocument); }
#endif


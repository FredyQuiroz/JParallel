// JParallelView.cpp : implementation of the CJParallelView class
//

#include "stdafx.h"
#include "JParallel.h"

#include "JParallelDoc.h"
#include "JParallelView.h"

# include <math.h>

short _stdcall Inp32(short PortAddress);
void _stdcall Out32(short PortAddress, short data);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJParallelView

IMPLEMENT_DYNCREATE(CJParallelView, CFormView)

BEGIN_MESSAGE_MAP(CJParallelView, CFormView)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_CHECK8, OnBnClickedCheck8)
	ON_EN_CHANGE(IDC_EDIT3, OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnEnChangeEdit4)
END_MESSAGE_MAP()

// CJParallelView construction/destruction

CJParallelView::CJParallelView()
	: CFormView(CJParallelView::IDD)
{
	// TODO: add construction code here
	f= NULL;
	array= 0;
	datos[0]=-1;
	m_nHasta= m_nDesde= -1;
}

CJParallelView::~CJParallelView()
{
}

void CJParallelView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK0, m_hPin0);
	DDX_Control(pDX, IDC_CHECK1, m_hPin1);
	DDX_Control(pDX, IDC_CHECK2, m_hPin2);
	DDX_Control(pDX, IDC_CHECK3, m_hPin3);
	DDX_Control(pDX, IDC_CHECK4, m_hPin4);
	DDX_Control(pDX, IDC_CHECK5, m_hPin5);
	DDX_Control(pDX, IDC_CHECK6, m_hPin6);
	DDX_Control(pDX, IDC_CHECK7, m_hPin7);
	DDX_Control(pDX, IDC_EDIT1, m_hPuerto);
	DDX_Control(pDX, IDC_CHECK9, m_hAutorefrescar);
	DDX_Control(pDX, IDC_EDIT2, m_hTiempo);
	DDX_Control(pDX, IDC_CHECK10, m_hLeer);
	DDX_Control(pDX, IDC_RESULTADO, m_hResult);
	DDX_Control(pDX, IDC_EDIT3, m_hEDesde);
	DDX_Control(pDX, IDC_EDIT4, m_hHasta);
	DDX_Control(pDX, IDC_CHECK11, m_hBRetroceder);
	DDX_Control(pDX, IDC_CHECK8, m_hBContador);
}

BOOL CJParallelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CJParallelView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_hPin0.SetCheck(0);
	m_hPin1.SetCheck(0);
	m_hPin2.SetCheck(0);
	m_hPin3.SetCheck(0);
	m_hPin4.SetCheck(0);
	m_hPin5.SetCheck(0);
	m_hPin6.SetCheck(0);
	m_hPin7.SetCheck(0);
	m_hLeer.SetCheck(1);
	m_hPuerto.SetWindowText("888");
	m_hTiempo.SetWindowText("100");
	m_hBContador.SetCheck(false);
	OnBnClickedCheck8();
	SetTimer(1, 100, NULL);
}

// CJParallelView diagnostics

#ifdef _DEBUG
void CJParallelView::AssertValid() const
{
	CFormView::AssertValid();
}

void CJParallelView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CJParallelDoc* CJParallelView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJParallelDoc)));
	return (CJParallelDoc*)m_pDocument;
}
#endif //_DEBUG


// CJParallelView message handlers

void CJParallelView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString temp;
	int port, dato=0;
	m_hPuerto.GetWindowText(temp);
	port= atoi( temp);
	if( m_hBContador.GetCheck()) {

		if( m_hAutorefrescar.GetCheck()) {

			if( m_nDesde!=-1) {

				if( m_nHasta!=-1) {

					if( m_nActual== m_nHasta) {

						if( m_hBRetroceder.GetCheck()) {
                        
							dato= m_nHasta;
							m_nHasta= m_nDesde;
							m_nActual= m_nDesde= dato;
							if( m_nDesde<m_nHasta)
								m_nActual--;
							else if( m_nDesde>m_nHasta) m_nActual++;
						} else {
							if( m_nDesde<m_nHasta) 
								m_nActual=m_nDesde-1;
							else if( m_nDesde>m_nHasta)
								m_nActual=m_nHasta-1;
						}
					}
					if( m_nDesde<m_nHasta) 
                    
						m_nActual++;
					else if( m_nDesde>m_nHasta) m_nActual--;
				} else m_nActual++;
				int nLow, nHi;
				nHi= (int) floor(m_nActual/10);
				nHi= nHi<<4;
				nLow= m_nActual%10;
				dato= nHi;
				dato|= nLow;
				Out32(port, dato);
				Actualizar(dato);
				temp.Format("Escrito :%d", m_nActual);
				m_hResult.SetWindowText(temp);
			}
		}
	} else if( ! m_hLeer.GetCheck()) {
	
		if( !m_hAutorefrescar.GetCheck()) {

			if( m_hPin0.GetCheck())

				dato|= 1;
			if( m_hPin1.GetCheck())

				dato|= 2;
			if( m_hPin2.GetCheck())

				dato|= 4;
			if( m_hPin3.GetCheck())

				dato|= 8;
			if( m_hPin4.GetCheck())

				dato|= 16;
			if( m_hPin5.GetCheck())

				dato|= 32;
			if( m_hPin6.GetCheck())

				dato|= 64;
			if( m_hPin7.GetCheck())

				dato|= 128;
		} else {

			if( datos[array]==-1)

				array=0;
			dato= datos[array];
			array++;
			Actualizar(dato);
		}
		Out32(port, dato);
		temp.Format("Escrito :%d", dato);
		m_hResult.SetWindowText(temp);

	} else {

		dato= Inp32( port);
		temp.Format("Leido :%d", dato);
		m_hResult.SetWindowText(temp);
		Actualizar(dato);	
	}
	KillTimer(1);
	m_hTiempo.GetWindowText(temp);
	port= atoi(temp);
	SetTimer(1, port, NULL);
	CFormView::OnTimer(nIDEvent);
}

void CJParallelView::Actualizar( int dato) {

		m_hPin0.SetCheck(dato&1);
		m_hPin1.SetCheck(dato&2);
		m_hPin2.SetCheck(dato&4);
		m_hPin3.SetCheck(dato&8);
		m_hPin4.SetCheck(dato&16);
		m_hPin5.SetCheck(dato&32);		
		m_hPin6.SetCheck(dato&64);		
		m_hPin7.SetCheck(dato&128);	
}

void CJParallelView::OnFileOpen()
{
	int temp;
	CFileDialog dlgFile( true, "txt", NULL, OFN_HIDEREADONLY, "Todos los archivos de texto(*.txt)|*.txt||",this);
	if( dlgFile.DoModal()==IDOK) {

		CWaitCursor wait;
		if((f=fopen(dlgFile.GetPathName(), "r"))==NULL) {

			MessageBox("No se puede abrir el archivo");
			return;
		}
		KillTimer(1);
		array=0;
		m_hAutorefrescar.SetCheck(1);
		m_hLeer.SetCheck(0);
		fscanf(f, "%d", &temp);
		CString h;
		h.Format("%d", temp);
		m_hTiempo.SetWindowText(h);
		for( int i=0; !feof(f); i++) {

			fscanf(f, "%d", &temp);
			datos[i]= temp;
		}
		datos[i]=-1;
		SetTimer( 1, atoi(h), NULL);
		fclose(f);
	}
}

// oncontador
void CJParallelView::OnBnClickedCheck8()
{
	if( m_hBContador.GetCheck()) {

        m_hEDesde.EnableWindow();
		m_hHasta.EnableWindow();
		m_hBRetroceder.EnableWindow();
		m_hLeer.EnableWindow(false);
	} else {
		m_hEDesde.EnableWindow(false);
		m_hHasta.EnableWindow(false);
		m_hBRetroceder.EnableWindow(false);
	}
}
// incicio del contador
void CJParallelView::OnEnChangeEdit3()
{
	CString szTemp;
	m_hEDesde.GetWindowText(szTemp);
	if( !szTemp.IsEmpty()) {

		m_nActual= m_nDesde= atoi(szTemp);
		m_hHasta.GetWindowText(szTemp);
		if( !szTemp.IsEmpty()) 

			m_nHasta= atoi(szTemp);
	}
	else m_nDesde=-1;
}

// fin del contador
void CJParallelView::OnEnChangeEdit4()
{
	CString szTemp;
	m_hHasta.GetWindowText(szTemp);
	if( !szTemp.IsEmpty()) {

		m_nHasta= atoi(szTemp);
		m_hEDesde.GetWindowText(szTemp);
		if( !szTemp.IsEmpty()) 

			m_nActual= m_nDesde= atoi(szTemp);
	}
	else m_nHasta=-1;
}

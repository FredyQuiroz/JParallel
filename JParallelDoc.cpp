// JParallelDoc.cpp : implementation of the CJParallelDoc class
//

#include "stdafx.h"
#include "JParallel.h"

#include "JParallelDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJParallelDoc

IMPLEMENT_DYNCREATE(CJParallelDoc, CDocument)

BEGIN_MESSAGE_MAP(CJParallelDoc, CDocument)
END_MESSAGE_MAP()


// CJParallelDoc construction/destruction

CJParallelDoc::CJParallelDoc()
{
	// TODO: add one-time construction code here

}

CJParallelDoc::~CJParallelDoc()
{
}

BOOL CJParallelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CJParallelDoc serialization

void CJParallelDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CJParallelDoc diagnostics

#ifdef _DEBUG
void CJParallelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJParallelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CJParallelDoc commands

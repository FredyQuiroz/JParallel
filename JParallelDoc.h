// JParallelDoc.h : interface of the CJParallelDoc class
//


#pragma once

class CJParallelDoc : public CDocument
{
protected: // create from serialization only
	CJParallelDoc();
	DECLARE_DYNCREATE(CJParallelDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CJParallelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};



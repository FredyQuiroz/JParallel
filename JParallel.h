// JParallel.h : main header file for the JParallel application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CJParallelApp:
// See JParallel.cpp for the implementation of this class
//

class CJParallelApp : public CWinApp
{
public:
	CJParallelApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
};

extern CJParallelApp theApp;
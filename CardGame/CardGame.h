
// CardGame.h : CardGame ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CCardGameApp:
// �� Ŭ������ ������ ���ؼ��� CardGame.cpp�� �����Ͻʽÿ�.
//

class CCardGameApp : public CWinAppEx
{
public:
	CCardGameApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCardGameApp theApp;

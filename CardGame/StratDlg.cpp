// StratDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CardGame.h"
#include "StratDlg.h"
#include "afxdialogex.h"


// CStratDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStratDlg, CDialogEx)

CStratDlg::CStratDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStratDlg::IDD, pParent)
{

}

CStratDlg::~CStratDlg()
{
}

void CStratDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStratDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL1, &CStratDlg::OnBnClickedButtonLevel1)
END_MESSAGE_MAP()


// CStratDlg 메시지 처리기입니다.


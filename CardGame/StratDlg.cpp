// StratDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CardGame.h"
#include "StratDlg.h"
#include "afxdialogex.h"


// CStratDlg ��ȭ �����Դϴ�.

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


// CStratDlg �޽��� ó�����Դϴ�.


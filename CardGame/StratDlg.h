#pragma once


// CStratDlg ��ȭ �����Դϴ�.

class CStratDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStratDlg)

public:
	CStratDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStratDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLevel1();
};

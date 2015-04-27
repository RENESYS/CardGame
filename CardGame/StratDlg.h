#pragma once


// CStratDlg 대화 상자입니다.

class CStratDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStratDlg)

public:
	CStratDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStratDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLevel1();
};

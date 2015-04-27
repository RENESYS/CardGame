
// CardGameView.h : CCardGameView Ŭ������ �������̽�
//

#pragma once


class CCardGameView : public CView
{
protected: // serialization������ ��������ϴ�.
	CCardGameView();
	DECLARE_DYNCREATE(CCardGameView)

// Ư���Դϴ�.
public:
	CCardGameDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CCardGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	UINT m_nRowTempIndex;
	UINT m_nColTempIndex;
	int nMatchCount;

	bool bComboCheck;
	bool bInitCheck;
	bool bNewRecord;

	//�ǹ� ���� ������
	bool bFeverMode;
	bool bFeverEffect;
	bool bFeverStartOffset;
	int nFeverCount;
	int nFeverRowIndex;
	int nFeverColIndex;
	int nFeverXpos;
	double dFeverStartOffset;

	int nTimeLeft;

private:
	int nComboWidth;
	int nComboHeight;
	int nComboPosWidth;
	int nComboPosHeight;

	int nFeverOffset;

	CBitmap m_Backbmp;
	CRect m_TimeBar;
	

	

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
private:
	void OnMatching();
	void startFever();
	void endFever();
	int calcOffset(double x);


	
};

#ifndef _DEBUG  // CardGameView.cpp�� ����� ����
inline CCardGameDoc* CCardGameView::GetDocument() const
   { return reinterpret_cast<CCardGameDoc*>(m_pDocument); }
#endif


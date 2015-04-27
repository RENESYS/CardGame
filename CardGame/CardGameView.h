
// CardGameView.h : CCardGameView 클래스의 인터페이스
//

#pragma once


class CCardGameView : public CView
{
protected: // serialization에서만 만들어집니다.
	CCardGameView();
	DECLARE_DYNCREATE(CCardGameView)

// 특성입니다.
public:
	CCardGameDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CCardGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	UINT m_nRowTempIndex;
	UINT m_nColTempIndex;
	int nMatchCount;

	bool bComboCheck;
	bool bInitCheck;
	bool bNewRecord;

	//피버 관련 변수들
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

#ifndef _DEBUG  // CardGameView.cpp의 디버그 버전
inline CCardGameDoc* CCardGameView::GetDocument() const
   { return reinterpret_cast<CCardGameDoc*>(m_pDocument); }
#endif


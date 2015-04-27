
// CardGameDoc.h : CCardGameDoc 클래스의 인터페이스
//


#pragma once

class CCardGameDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CCardGameDoc();
	DECLARE_DYNCREATE(CCardGameDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CCardGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CBitmap m_bmp[6][6];
	CSize m_bmCell;
	int m_nRow;
	int m_nCol;

	int m_nRnd[36];
	UINT m_nBmpID[6][6];
	bool m_bShow[6][6];

	int m_nRowIndex;
	int m_nColIndex;
	UINT m_nBmpFirstID;
	UINT m_nBmpSecondID;
	bool m_bMouse;

	bool m_bStart;
	int m_nScore;
	int m_nCombo;
	int m_nRecord;

	int m_nFever;
	UINT m_nFeverID;


private:
	int m_nFeverRow;
	int m_nFeverCol;

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnEasy();
	afx_msg void OnNormal();
	afx_msg void OnHard();
	afx_msg void OnExtreme();

	void ResizeWindow();
	void OnRandom();
	void setFeverCard();
	void gameInitial(int row, int col, int time);
	void playMusic(const char* name);
	void OnSuccess();
	void gameOver();
	void setRecord();
};

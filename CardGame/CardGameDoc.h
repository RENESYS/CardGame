
// CardGameDoc.h : CCardGameDoc Ŭ������ �������̽�
//


#pragma once

class CCardGameDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CCardGameDoc();
	DECLARE_DYNCREATE(CCardGameDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CCardGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
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


// CardGameDoc.cpp : CCardGameDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "CardGame.h"
#endif

#include "CardGameDoc.h"

#include <propkey.h>
#include<stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCardGameDoc

IMPLEMENT_DYNCREATE(CCardGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CCardGameDoc, CDocument)
	ON_COMMAND(ID_EASY, &CCardGameDoc::OnEasy)
	ON_COMMAND(ID_NORMAL, &CCardGameDoc::OnNormal)
	ON_COMMAND(ID_HARD, &CCardGameDoc::OnHard)
	ON_COMMAND(ID_EXTREME, &CCardGameDoc::OnExtreme)
END_MESSAGE_MAP()


// CCardGameDoc ����/�Ҹ�

CCardGameDoc::CCardGameDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_bmCell = CSize(79, 81);
	m_bStart = true;
	m_nRow = 3;
	m_nCol = 4;
	m_nScore = 0;
	m_nRecord = 0;
	m_nFeverID = m_nFeverRow = m_nFeverCol = 0;

	for (int i = 0; i < m_nRow; i++){
		for (int j = 0; j < m_nCol; j++){
			m_bShow[i][j] = true;
		}
	}

	m_nBmpFirstID = m_nBmpSecondID = 0;
	m_bMouse = false;

}

CCardGameDoc::~CCardGameDoc()
{
}

BOOL CCardGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CCardGameDoc serialization

void CCardGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CCardGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CCardGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCardGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCardGameDoc ����

#ifdef _DEBUG
void CCardGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCardGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCardGameDoc ���

#include "CardGameView.h"
#include "MainFrm.h"
void CCardGameDoc::ResizeWindow()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	CREATESTRUCT st;
	CREATESTRUCT& rst = st;

	pMain->PreCreateWindow(rst);

	rst.lpszName = _T("Game");
	
	if (m_nRow == 6){
		rst.cx = (m_nRow + 1) * m_bmCell.cx + 100;
		rst.cy = (m_nCol + 2) * m_bmCell.cy + 100;
	}
	else{
		rst.cx = (m_nRow + 1) * m_bmCell.cx + 180;
		rst.cy = (m_nCol + 1) * m_bmCell.cy + 100;
	}

	CRect rect;
	pMain->GetClientRect(rect);
	pMain->MoveWindow(rect.left, rect.top, rst.cx, rst.cy);
}


void CCardGameDoc::OnRandom()
{
	srand((unsigned)time(NULL));
	BOOL bInsert = TRUE;
	int nGrating = m_nRow * m_nCol;

	// ������ ����ŭ ���鼭 ���� �߻�
	for (int n = 0; n < nGrating; n++){
		m_nRnd[n] = (rand() % (nGrating / 2)) + 1;
		for (int m = 0; m < n; m++){
			if (m_nRnd[n] == m_nRnd[m]){
				if (bInsert == FALSE){
					n--;
					bInsert = TRUE; 
				}
				else
					bInsert = FALSE;
			}
		}
	}
	int nCount = 0;
	for (int n = 0; n < m_nRow; n++){
		for (int m = 0; m < m_nCol; m++){
			m_nBmpID[n][m] = m_nRnd[nCount++];
		}
	}
}

void CCardGameDoc::setFeverCard(){
	m_nFeverCol = (rand() % m_nCol);
	m_nFeverRow = (rand() % m_nRow);
	m_nFeverID = m_nBmpID[m_nFeverRow][m_nFeverCol];
	//m_nFeverID = m_nBmpID[1][1];
}

void CCardGameDoc::gameInitial(int row, int col, int time)
{
	CCardGameView* pView = (CCardGameView*)m_viewList.GetHead();

	// �ְ� ���� �ҷ�����
	CFile File;
	char tempbuff[10];
	File.Open(_T("score.txt"), CFile::modeRead);
	File.Read(tempbuff, 10);
	sscanf(tempbuff, "%d", &m_nRecord);
	File.Close();

	if (pView->bFeverMode)
		pView->KillTimer(FEVER);

	//pView->SetTimer(TIME, 1000, NULL);
	pView->KillTimer(TIME);

	BASS_Free();
	playMusic("bgm.mp3");

	m_nRow = row;
	m_nCol = col;

	OnRandom();

	//ȭ�� ���� ����
	m_nBmpFirstID = m_nBmpSecondID = 0;
	pView->m_nRowTempIndex = pView->m_nColTempIndex = 0;
	for (int n = 0; n < m_nRow; n++)
		for (int m = 0; m < m_nCol; m++)
			m_bShow[n][m] = true;

	m_bStart = true;
	pView->nMatchCount = 0;
	pView->nTimeLeft = time;
	m_nCombo = 0;

	//�ǹ� ���� ����
	pView->bFeverMode = false;
	pView->nFeverCount = m_nFeverRow = m_nFeverCol = 0;
	pView->bFeverEffect = false;
	m_nFever = 1;
	pView->dFeverStartOffset = -4.5;
	pView->nFeverXpos = -300;

	pView->Invalidate();
}

void CCardGameDoc::playMusic(const char* name){
	BASS_Init(-1, 44100, 0, 0, NULL);
	HSTREAM sample = BASS_StreamCreateFile(FALSE, name, 0, 0, 0);
	BASS_ChannelPlay(sample, FALSE);
}

void CCardGameDoc::OnSuccess(){
	if (m_nRow != 6){
		int res = AfxMessageBox(_T("CLEAR! ���� �ܰ�� �Ѿ�ðڽ��ϱ�?"), MB_YESNO);
		if (res == IDYES){
			if (m_nRow == 5)
				gameInitial(6, 6, 240);
			else
				gameInitial(m_nRow + 1, m_nCol + 1, 60 * (m_nRow - 1));
			//�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�.
			m_nBmpFirstID = m_nBmpSecondID = 0;
			m_bMouse = false;
		}
	}
	else{
		AfxMessageBox(_T("ALL CLEAR!!!"));
		if (m_nScore > m_nRecord)
			setRecord();
	}
}


void CCardGameDoc::setRecord(){
	CFile File;
	char* str = new char[10];
	_itoa(m_nScore, str, 10);
	File.Open(_T("score.txt"), CFile::modeWrite);
	File.Write(str, strlen(str));
	File.Close();
	delete str;
}

void CCardGameDoc::gameOver(){
	int res = AfxMessageBox(_T("GAME OVER! �ٽ� �Ͻðڽ��ϱ�?"), MB_YESNO);
	if (res == IDYES){
		gameInitial(m_nRow, m_nCol, 60 * (m_nRow - 2));
		//�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�.
		m_nScore = 0;
		m_nBmpFirstID = m_nBmpSecondID = 0;
		m_bMouse = false;
	}
	else{
		if (m_nScore > m_nRecord)
			setRecord();
	}
}

void CCardGameDoc::OnEasy(){
	gameInitial(3, 4, 60);
	m_nScore = 0;
}
void CCardGameDoc::OnNormal(){
	gameInitial(4, 5, 120);
	m_nScore = 0;
}
void CCardGameDoc::OnHard(){
	gameInitial(5, 6, 180);
	m_nScore = 0;
}
void CCardGameDoc::OnExtreme(){
	gameInitial(6, 6, 240);
	m_nScore = 0;
}



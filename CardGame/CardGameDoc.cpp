
// CardGameDoc.cpp : CCardGameDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CCardGameDoc 생성/소멸

CCardGameDoc::CCardGameDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CCardGameDoc serialization

void CCardGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CCardGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CCardGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CCardGameDoc 진단

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


// CCardGameDoc 명령

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

	// 격자의 수만큼 돌면서 난수 발생
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

	// 최고 점수 불러오기
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

	//화면 관련 변수
	m_nBmpFirstID = m_nBmpSecondID = 0;
	pView->m_nRowTempIndex = pView->m_nColTempIndex = 0;
	for (int n = 0; n < m_nRow; n++)
		for (int m = 0; m < m_nCol; m++)
			m_bShow[n][m] = true;

	m_bStart = true;
	pView->nMatchCount = 0;
	pView->nTimeLeft = time;
	m_nCombo = 0;

	//피버 관련 변수
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
		int res = AfxMessageBox(_T("CLEAR! 다음 단계로 넘어가시겠습니까?"), MB_YESNO);
		if (res == IDYES){
			if (m_nRow == 5)
				gameInitial(6, 6, 240);
			else
				gameInitial(m_nRow + 1, m_nCol + 1, 60 * (m_nRow - 1));
			//아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다.
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
	int res = AfxMessageBox(_T("GAME OVER! 다시 하시겠습니까?"), MB_YESNO);
	if (res == IDYES){
		gameInitial(m_nRow, m_nCol, 60 * (m_nRow - 2));
		//아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다.
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



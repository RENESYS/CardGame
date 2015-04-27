
// CardGameView.cpp : CCardGameView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CardGame.h"
#endif

#include "CardGameDoc.h"
#include "CardGameView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif





// CCardGameView

IMPLEMENT_DYNCREATE(CCardGameView, CView)

BEGIN_MESSAGE_MAP(CCardGameView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()

	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CCardGameView 생성/소멸

CCardGameView::CCardGameView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	bComboCheck = false;
	bInitCheck = false;
	bNewRecord = false;

	bFeverMode = false;
	bFeverEffect = false;
	bFeverStartOffset = false;
	nFeverCount = 0;
	nFeverOffset = 0;
	
	
	nComboHeight = nComboWidth = 0;
	nComboPosHeight = 50;
	nComboPosWidth = 130;

	nFeverRowIndex = nFeverColIndex = 0;

	nTimeLeft = 180;
}

CCardGameView::~CCardGameView()
{
}

BOOL CCardGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCardGameView 그리기

void CCardGameView::OnDraw(CDC* pDC)
{
	CCardGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int nCount = 0;
	CDC memDC;
	CBitmap* pOldBmp = NULL;
	CString str;
	CBitmap bmp;

	CRect rect;
	GetClientRect(&rect);

	memDC.CreateCompatibleDC(pDC);

	bmp.LoadBitmap(IDB_BITMAP_BG);
	pOldBmp = memDC.SelectObject(&bmp);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 600, 375, SRCCOPY);
	bmp.DeleteObject();

	str.Format(_T("최고점수 : %d"), pDoc->m_nRecord);
	pDC->TextOutW(50, 30, str);
	str.Format(_T("현재점수 : %d"), pDoc->m_nScore);
	pDC->TextOutW(50, 50, str);

	CBrush brush, *pOld;
	brush.CreateSolidBrush(RGB(255, 100, 0));
	pOld = pDC->SelectObject(&brush);
	m_TimeBar = CRect(80, rect.Height() - 50, 80 + (nTimeLeft * 2), rect.Height() - 30);
	pDC->Rectangle(m_TimeBar);
	pDC->SelectObject(pOld);
	brush.DeleteObject();

	for (int n = 0; n < pDoc->m_nRow; n++){
		for (int m = 0; m < pDoc->m_nCol; m++){
			//그림 출력
			if (pDoc->m_bShow[n][m] == true){
				pDoc->m_bmp[n][m].LoadBitmap(IDB_BITMAP1 + pDoc->m_nRnd[nCount]);
				pOldBmp = memDC.SelectObject(&pDoc->m_bmp[n][m]);

				pDC->BitBlt(pDoc->m_bmCell.cx*(m + 1), pDoc->m_bmCell.cy*(n + 1),
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy, &memDC, 0, 0, SRCCOPY);
				pDoc->m_bmp[n][m].DeleteObject();
			}
			nCount++;
			//덮개 출력
			if (pDoc->m_bShow[n][m] == false){
				bmp.LoadBitmap(IDB_BITMAP1);
				pOldBmp = memDC.SelectObject(&bmp);
				pDC->BitBlt(pDoc->m_bmCell.cx*(m + 1), pDoc->m_bmCell.cy*(n + 1), 
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy, &memDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}
			//피버모드 특수 덮개
			if (bFeverMode){
				bmp.LoadBitmap(IDB_BITMAP_FEVERCOVER);
				pOldBmp = memDC.SelectObject(&bmp);
				pDC->BitBlt(pDoc->m_bmCell.cx*(nFeverColIndex + 1), pDoc->m_bmCell.cy*(nFeverRowIndex + 1),
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy, &memDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();

				bFeverEffect = true;
				SetTimer(FEVER_EFFECT, 100, NULL);
			}
		}
	}
	memDC.SelectObject(pOldBmp);

	if (pDoc->m_bStart == true){
		pDoc->ResizeWindow();
		bInitCheck = true;
		pDoc->setFeverCard();
		SetTimer(INIT_SHOW, 1500, NULL);
	}

	if (pDoc->m_nScore > pDoc->m_nRecord){
		if (!bNewRecord){
			pDoc->playMusic("newRecord.wav");
			bNewRecord = true;
		}
		bmp.LoadBitmap(IDB_BITMAP_RECORD);
		pOldBmp = memDC.SelectObject(&bmp);
		pDC->TransparentBlt(150, 40, 160, 50, &memDC, 0, 0, 160, 50, RGB(255, 0, 255));
		bmp.DeleteObject();
	}
}


// CCardGameView 인쇄

BOOL CCardGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCardGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCardGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCardGameView 진단

#ifdef _DEBUG
void CCardGameView::AssertValid() const
{
	CView::AssertValid();
}

void CCardGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCardGameDoc* CCardGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCardGameDoc)));
	return (CCardGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CCardGameView 메시지 처리기


void CCardGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCardGameDoc* pDoc = GetDocument();
	pDoc->m_nRowIndex = point.y / pDoc->m_bmCell.cy - 1;
	pDoc->m_nColIndex = point.x / pDoc->m_bmCell.cx - 1;

	// 이전 클릭한 곳에 다시 클릭, 두번 이상 클릭, 격자 밖에 클릭했다면 리턴
	if (pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] == true
		|| pDoc->m_nBmpSecondID != 0 || pDoc->m_nRowIndex > pDoc->m_nRow - 1
		|| pDoc->m_nColIndex > pDoc->m_nCol - 1 || pDoc->m_nRowIndex < 0 || pDoc->m_nColIndex < 0)
		return;

	//클릭 사운드 효과
	BASS_Init(-1, 44100, 0, 0, NULL);
	HSTREAM sample = BASS_StreamCreateFile(FALSE, "click.wav", 0, 0, 0);
	BASS_ChannelPlay(sample, FALSE);

	// 마우스가 가지고 있는 인덱스 값에 그림을 보여줌
	pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = true;

	// 마우스가 클릭한 곳의 인덱스 및 그림 아이디 저장
	// 첫번째 마우스 클릭
	if (!pDoc->m_bMouse){
		//피버모드 발동
		if (pDoc->m_nFeverID == pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex]){
			startFever();
			return;
		}
		pDoc->m_bMouse = true;
		pDoc->m_nBmpFirstID = pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];
		m_nRowTempIndex = pDoc->m_nRowIndex;
		m_nColTempIndex = pDoc->m_nColIndex;
	}
	// 두번째 마우스 클릭
	else{
		//피버모드 발동
		if (pDoc->m_nFeverID == pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex]){
			startFever();
			return;
		}
		pDoc->m_bMouse = false;
		pDoc->m_nBmpSecondID = pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];
	}
	// 같은 그림인지 판단한다
	OnMatching();

	CView::OnLButtonDown(nFlags, point);
}


void CCardGameView::OnMatching()
{
	CCardGameDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	CDC memDC;
	CBitmap bmp;
	memDC.CreateCompatibleDC(pDC);

	// 그림이 같다면
	if (pDoc->m_nBmpFirstID == pDoc->m_nBmpSecondID && pDoc->m_bMouse == false){
		// 클릭 이벤트 초기화
		pDoc->m_bShow[m_nRowTempIndex][m_nColTempIndex] = true;
		pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = true;
		pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;

		nMatchCount++;
		pDoc->m_nCombo++;
		
		//콤보 효과 표시
		if (pDoc->m_nCombo > 1){
			pDoc->playMusic("combo.wav");
			bComboCheck = true;
			SetTimer(COMBO_TIME, 10, NULL);
		}
		pDoc->m_nScore += 100 * pDoc->m_nCombo * pDoc->m_nFever;
	}
	else if (pDoc->m_nBmpFirstID != pDoc->m_nBmpSecondID && pDoc->m_bMouse == false){
		// 다른 그림이라면 잠시 보여줌
		bmp.LoadBitmap(IDB_BITMAP1 + pDoc->m_nBmpSecondID);
		CBitmap*  pOldBmp = memDC.SelectObject(&bmp);
		pDC->BitBlt(pDoc->m_bmCell.cx*(pDoc->m_nColIndex + 1), pDoc->m_bmCell.cy * (pDoc->m_nRowIndex + 1),
			pDoc->m_bmCell.cx, pDoc->m_bmCell.cy, &memDC, 0, 0, SRCCOPY);
		bmp.DeleteObject();
		memDC.SelectObject(pOldBmp);
		Sleep(400);

		//클릭 이벤트 초기화
		pDoc->m_bShow[m_nRowTempIndex][m_nColTempIndex] = false;
		pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = false;
		pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
		pDoc->m_nCombo = 0;
	}
	Invalidate();
	if (nMatchCount == (pDoc->m_nRow * pDoc->m_nCol) / 2)
		pDoc->OnSuccess();
}


void CCardGameView::OnTimer(UINT_PTR nIDEvent)
{
	CCardGameDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	CDC memDC;
	CBitmap bmp;
	CBitmap* pOldBmp;

	CRect rect;
	GetClientRect(&rect);

	switch (nIDEvent){
	case COMBO_TIME:
		bmp.LoadBitmap(IDB_BITMAP_COMBO);
		memDC.CreateCompatibleDC(pDC);
		pOldBmp = memDC.SelectObject(&bmp);
		pDC->TransparentBlt(nComboPosWidth, nComboPosHeight, nComboWidth, nComboHeight, &memDC, 0, 0, 160, 100, RGB(255, 0, 255));
		bmp.DeleteObject();
		memDC.SelectObject(pOldBmp);

		//콤보 마크가 점점 커지는 효과
		nComboWidth += 10;
		nComboHeight += 5;
		nComboPosWidth -= 5;
		nComboPosHeight -= 2;

		if (nComboWidth > 160){
			//초기화 부분
			Sleep(500);
			nComboHeight = nComboWidth = 0;
			nComboPosWidth = 130;
			nComboPosHeight = 50;
			KillTimer(COMBO_TIME);
			Invalidate();
		}
		return;

	case INIT_SHOW:
		if (bInitCheck){
			bInitCheck = false;
			pDoc->m_bStart = false;
		}
		else{
			for (int n = 0; n < pDoc->m_nRow; n++)
				for (int m = 0; m < pDoc->m_nCol; m++)
					pDoc->m_bShow[n][m] = false;
			Invalidate();
			KillTimer(INIT_SHOW);
			SetTimer(TIME, 1000, NULL);
		}
		return;

	case FEVER:
		endFever();
		pDoc->playMusic("bgm.mp3");
		bFeverEffect = false;
		KillTimer(FEVER);
		return;

	case FEVER_EFFECT:
		if (bFeverEffect){
			bmp.LoadBitmap(IDB_BITMAP_FEVER1 + (nFeverOffset%3));
			memDC.CreateCompatibleDC(pDC);
			pOldBmp = memDC.SelectObject(&bmp);
			pDC->TransparentBlt(rect.Width() - 300 , 0, 250, 100, &memDC, 0, 0, 250, 100, RGB(255, 0, 255));
			bmp.DeleteObject();
			memDC.SelectObject(pOldBmp);
			nFeverOffset++;
		}
		else{
			nFeverOffset = 0;
			KillTimer(FEVER_EFFECT);
		}
		return;

	case FEVER_START:
		memDC.CreateCompatibleDC(pDC);
		//memDC.SelectObject(&m_Backbmp);
		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		
		m_Backbmp.LoadBitmap(IDB_BITMAP_FEVERSTART);
		pOldBmp = memDC.SelectObject(&m_Backbmp);
		pDC->TransparentBlt(nFeverXpos, rect.Height() / 2 - 100, rect.Width() / 2, rect.Height() / 2,
			&memDC, 0, 0, 470, 300, RGB(255, 0, 255));
		Invalidate(FALSE);
		Sleep(25);
		m_Backbmp.DeleteObject();
		memDC.SelectObject(pOldBmp);

		dFeverStartOffset += 0.2;
		nFeverXpos += calcOffset(dFeverStartOffset);

		if (nFeverXpos > rect.Width() + 50){
			nFeverXpos = -300;
			dFeverStartOffset = -4.5;
			bFeverStartOffset = false;
			KillTimer(FEVER_START);
			Invalidate();
		}
		return;

	case TIME:
		nTimeLeft--;
		InvalidateRect(m_TimeBar, false);
		if (nTimeLeft < 0){
			KillTimer(TIME);
			pDoc->gameOver();
		}
		return;
	}
	CView::OnTimer(nIDEvent);
}


void CCardGameView::startFever(){
	CCardGameDoc* pDoc = GetDocument();

	//피버 중 피버가 다시 발동하면 이전 피버를 제거
	if (bFeverMode)
		endFever();

	//두번째 카드에서 피버가 발생했을 때
	if (pDoc->m_bMouse){
		pDoc->m_bMouse = false;
		pDoc->m_bShow[m_nRowTempIndex][m_nColTempIndex] = false;
	}

	BASS_Free();
	SetTimer(FEVER, 13000, NULL);
	pDoc->playMusic("fever.mp3");
	pDoc->m_nFever = 5;
	bFeverMode = true;
	nFeverCount++;
	SetTimer(FEVER_START, 25, NULL);

	//피버 발생 위치 파악
	nFeverColIndex = pDoc->m_nColIndex;
	nFeverRowIndex = pDoc->m_nRowIndex;
	
	//2개의 피버카드 모두 소진 시 카운트 증가
	if (nFeverCount == 2)
		nMatchCount++;

	if (nMatchCount == (pDoc->m_nRow * pDoc->m_nCol) / 2)
		pDoc->OnSuccess();
}

void CCardGameView::endFever(){
	CCardGameDoc* pDoc = GetDocument();
	
	pDoc->m_nFever = 1;
	bFeverMode = false;

	BASS_Free();
	pDoc->m_bShow[nFeverRowIndex][nFeverColIndex] = true;
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	Invalidate();
}

#include<cmath>
int CCardGameView::calcOffset(double x){ return (int)(exp(x) + exp(-x)); }

int CCardGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	GetDocument()->gameInitial(3, 4, 60);
	return 0;
}

void CCardGameView::OnDestroy()
{
	CView::OnDestroy();
	CCardGameDoc* pDoc = GetDocument();
	if (pDoc->m_nScore > pDoc->m_nRecord)
		pDoc->setRecord();
	BASS_Free();
}

// EditProgramView.cpp: CEditProgramView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "EditProgram.h"
#endif

#include "EditProgramDoc.h"
#include "EditProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditProgramView

IMPLEMENT_DYNCREATE(CEditProgramView, CView)

BEGIN_MESSAGE_MAP(CEditProgramView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CEditProgramView 생성/소멸

CEditProgramView::CEditProgramView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	pntCur.x = 0;
	pntCur.y = 0;
}

CEditProgramView::~CEditProgramView()
{
}

BOOL CEditProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CEditProgramView 그리기

void CEditProgramView::OnDraw(CDC* /*pDC*/)
{
	CEditProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CEditProgramView 인쇄

BOOL CEditProgramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CEditProgramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CEditProgramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CEditProgramView 진단

#ifdef _DEBUG
void CEditProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CEditProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditProgramDoc* CEditProgramView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditProgramDoc)));
	return (CEditProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditProgramView 메시지 처리기


int CEditProgramView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	pDoc = GetDocument();

	TEXTMETRIC txtKey;

	CClientDC dc(this);

	dc.GetTextMetrics(&txtKey);

	CreateSolidCaret(txtKey.tmAveCharWidth / 2, txtKey.tmHeight);

	CPoint pntTmp(0, 0);

	SetCaretPos(pntTmp);

	ShowCaret();

	return 0;
}


void CEditProgramView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);

	TEXTMETRIC txtKey;

	dc.GetTextMetrics(&txtKey);

	HideCaret();

	if (nChar == VK_BACK)
	{
		if (!pDoc->strDB[pDoc->pline].IsEmpty())
		{
			pDoc->strDB[pDoc->pline] = pDoc->strDB[pDoc->pline].Left(pDoc->strDB[pDoc->pline].GetLength() - 1);
			dc.TextOut(0, pntCur.y, pDoc->strDB[pDoc->pline] + _T("  "));
		}
	}
	else if (nChar == VK_RETURN)
	{
		pDoc->pline++;
	}
	else if (nChar == VK_UP)
	{
		pDoc->pline--;
	}
	else
	{
		pDoc->strDB[pDoc->pline] += (TCHAR)nChar;
		dc.TextOut(0, (int)pDoc->pline * txtKey.tmHeight, pDoc->strDB[pDoc->pline]);
	}

	CSize strSize;
	strSize = dc.GetTextExtent(pDoc->strDB[pDoc->pline]);

	pntCur.x = strSize.cx;
	pntCur.y = int(pDoc->pline) * txtKey.tmHeight;
	SetCaretPos(pntCur);
	ShowCaret();

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CEditProgramView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pDoc->pline == 0)
		return;
	if (nChar == VK_UP)
		OnChar(nChar, nRepCnt, nFlags);

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CEditProgramView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	TEXTMETRIC txtKey;

	dc.GetTextMetrics(&txtKey);

	for (int i = 0; i <= pDoc->pline; i++)
	{
		dc.TextOut(0, (int)i*txtKey.tmHeight, pDoc->strDB[i]);
	}
}

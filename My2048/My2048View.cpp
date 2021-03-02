
// My2048View.cpp : CMy2048View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "My2048.h"
#endif

#include "My2048Doc.h"
#include "My2048View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2048View

IMPLEMENT_DYNCREATE(CMy2048View, CView)

BEGIN_MESSAGE_MAP(CMy2048View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2048View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMy2048View 构造/析构

CMy2048View::CMy2048View()
{
	// TODO:  在此处添加构造代码
	status = MAINMENU;
}

CMy2048View::~CMy2048View()
{
}

BOOL CMy2048View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2048View 绘制

void CMy2048View::OnDraw(CDC* pDC)
{
	CMy2048Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	SetBackground(pDC);
	switch (status)
	{
	case MAINMENU:
	{
		SetTitle(pDC);
		DrawMainMenu(pDC);
		break;
	}
	case INGAME:
	{
		DrawFrame(pDC);
		DrawCurrentData(pDC);
		DrawButtons(pDC);
		RefreshScore(pDC);
		break;
	}
	default:
		break;
	}
}


// CMy2048View 打印


void CMy2048View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy2048View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2048View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy2048View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CMy2048View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy2048View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy2048View 诊断

#ifdef _DEBUG
void CMy2048View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2048View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2048Doc* CMy2048View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2048Doc)));
	return (CMy2048Doc*)m_pDocument;
}
#endif //_DEBUG


void CMy2048View::SetBackground(CDC *pDC)
{
	CBitmap cbmp;
	cbmp.LoadBitmapW(IDB_BACKGROUND);
	BITMAP bmp;
	cbmp.GetBitmap(&bmp);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&cbmp);
	pDC->StretchBlt(0, 0, gui.rect_2048wnd.Width(), gui.rect_2048wnd.Height(), &dc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
}


void CMy2048View::SetTitle(CDC *pDC)
{
	CBrush brush(gui.color_title_background);
	pDC->FillRect(gui.rect_title, &brush);

	pDC->SelectObject(gui.font_title);
	pDC->SetTextColor(gui.color_title_text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(_T("2 0 4 8"), gui.rect_title, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


void CMy2048View::DrawMainMenu(CDC *pDC)
{
	pDC->SelectObject(gui.font_menuitem);
	pDC->SetTextColor(gui.color_menuitem);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(_T("开 始 游 戏"), gui.rect_menuitem_newgame, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->DrawText(_T("载 入 游 戏"), gui.rect_menuitem_loadgame, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->DrawText(_T("退 出 游 戏"), gui.rect_menuitem_exitgame, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


void CMy2048View::HighlightMenuitem(CDC *pDC, int flag)
{
	pDC->SelectObject(gui.font_menuitem);
	pDC->SetTextColor(gui.color_menuitem_highlighted);
	pDC->SetBkMode(TRANSPARENT);

	switch (flag)
	{
	case 1:
	{
		pDC->DrawText(_T("开 始 游 戏"), gui.rect_menuitem_newgame, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		break;
	}
	case 2:
	{
		pDC->DrawText(_T("载 入 游 戏"), gui.rect_menuitem_loadgame, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		break;
	}
	case 3:
	{
		pDC->DrawText(_T("退 出 游 戏"), gui.rect_menuitem_exitgame, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		break;
	}
	default:
		break;
	}
}


void CMy2048View::DrawButtons(CDC *pDC)
{
	CBrush brush(gui.color_button_background);
	pDC->FillRect(gui.rect_button_restart, &brush);
	pDC->SelectObject(gui.font_button);
	pDC->SetTextColor(gui.color_button_text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(_T("Restart"), gui.rect_button_restart, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	pDC->FillRect(gui.rect_button_menu, &brush);
	pDC->DrawText(_T("Menu"), gui.rect_button_menu, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


void CMy2048View::HighlightButton(CDC *pDC, int flag)
{
	pDC->SelectObject(gui.font_button);
	pDC->SetTextColor(gui.color_button_text_highlighted);
	pDC->SetBkMode(TRANSPARENT);

	switch (flag)
	{
	case 1:
	{
		pDC->DrawText(_T("Restart"), gui.rect_button_restart, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		break;
	}
	case 2:
	{
		pDC->DrawText(_T("Menu"), gui.rect_button_menu, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		break;
	}
	default:
		break;
	}
}


void CMy2048View::DrawFrame(CDC *pDC)
{
	CBrush brush(gui.color_lattice);
	pDC->FillRect(CRect(gui.nodes[0][0], gui.nodes[4][4]), &brush);

	CPen *poldpen;
	poldpen = pDC->SelectObject(&gui.pen_frame);
	for (int i = 0; i < 5; i++)
	{
		pDC->MoveTo(gui.nodes[i][0]);
		pDC->LineTo(gui.nodes[i][4]);
	}
	for (int j = 0; j < 5; j++)
	{
		pDC->MoveTo(gui.nodes[0][j]);
		pDC->LineTo(gui.nodes[4][j]);
	}
	pDC->SelectObject(poldpen);
}


void CMy2048View::DrawSingleLattice(CDC *pDC, int x, int y, int value)
{
	int i = y, j = x;
	switch (value)
	{
	case 0:
	{
		CBrush brush(gui.color_lattice);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 2:
	{
		CBrush brush(gui.color_2_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_2_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("2"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 4:
	{
		CBrush brush(gui.color_4_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_4_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("4"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 8:
	{
		CBrush brush(gui.color_8_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_8_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("8"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 16:
	{
		CBrush brush(gui.color_16_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_16_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("16"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 32:
	{
		CBrush brush(gui.color_32_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_32_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("32"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 64:
	{
		CBrush brush(gui.color_64_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_64_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("64"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 128:
	{
		CBrush brush(gui.color_128_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_128_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("128"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 256:
	{
		CBrush brush(gui.color_256_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_256_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("256"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 512:
	{
		CBrush brush(gui.color_512_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_512_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("512"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 1024:
	{
		CBrush brush(gui.color_1024_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_1024_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("1024"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	case 2048:
	{
		CBrush brush(gui.color_2048_background);
		pDC->FillRect(CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), &brush);

		pDC->SelectObject(gui.font_lattice);
		pDC->SetTextColor(gui.color_2048_text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(_T("2048"), CRect(gui.nodes[i][j], gui.nodes[i + 1][j + 1]), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		CPen *poldpen;
		poldpen = pDC->SelectObject(&gui.pen_frame);
		pDC->MoveTo(gui.nodes[i][j]);
		pDC->LineTo(gui.nodes[i + 1][j]);
		pDC->LineTo(gui.nodes[i + 1][j + 1]);
		pDC->LineTo(gui.nodes[i][j + 1]);
		pDC->LineTo(gui.nodes[i][j]);
		pDC->SelectObject(poldpen);

		break;
	}
	default:
		break;
	}
}


void CMy2048View::DrawCurrentData(CDC *pDC)
{
	CMy2048Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			DrawSingleLattice(pDC, i, j, pDoc->data[i][j]);
		}
	}
}


void CMy2048View::RefreshScore(CDC *pDC)
{
	CMy2048Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CBrush brush(gui.color_score_background);
	pDC->FillRect(gui.rect_score, &brush);

	CString str;
	str.Format(_T("SCORE: %d"), pDoc->score);
	pDC->SelectObject(gui.font_score);
	pDC->SetTextColor(gui.color_score_text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(str, gui.rect_score, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


// CMy2048View 消息处理程序


void CMy2048View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()
	OnPrepareDC(&dc);
	OnDraw(&dc);
}


void CMy2048View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	switch (status)
	{
	case MAINMENU:
	{
		DrawMainMenu(pDC);
		if (!((point.x >= gui.rect_menuitem_newgame.left&&point.x <= gui.rect_menuitem_newgame.right&&point.y >= gui.rect_menuitem_newgame.top&&point.y <= gui.rect_menuitem_newgame.bottom) || \
			(point.x >= gui.rect_menuitem_loadgame.left&&point.x <= gui.rect_menuitem_loadgame.right&&point.y >= gui.rect_menuitem_loadgame.top&&point.y <= gui.rect_menuitem_loadgame.bottom) || \
			(point.x >= gui.rect_menuitem_exitgame.left&&point.x <= gui.rect_menuitem_exitgame.right&&point.y >= gui.rect_menuitem_exitgame.top&&point.y <= gui.rect_menuitem_exitgame.bottom)))
		{
			ReleaseDC(pDC);
			return;
		}
		if (point.x >= gui.rect_menuitem_newgame.left&&point.x <= gui.rect_menuitem_newgame.right&&point.y >= gui.rect_menuitem_newgame.top&&point.y <= gui.rect_menuitem_newgame.bottom)
		{
			HighlightMenuitem(pDC, 1);
		}
		if (point.x >= gui.rect_menuitem_loadgame.left&&point.x <= gui.rect_menuitem_loadgame.right&&point.y >= gui.rect_menuitem_loadgame.top&&point.y <= gui.rect_menuitem_loadgame.bottom)
		{
			HighlightMenuitem(pDC, 2);
		}
		if (point.x >= gui.rect_menuitem_exitgame.left&&point.x <= gui.rect_menuitem_exitgame.right&&point.y >= gui.rect_menuitem_exitgame.top&&point.y <= gui.rect_menuitem_exitgame.bottom)
		{
			HighlightMenuitem(pDC, 3);
		}
		ReleaseDC(pDC);
		break;
	}
	case INGAME:
	{
		DrawButtons(pDC);
		if (!((point.x >= gui.rect_button_restart.left&&point.x <= gui.rect_button_restart.right&&point.y >= gui.rect_button_restart.top&&point.y <= gui.rect_button_restart.bottom) || \
			(point.x >= gui.rect_button_menu.left&&point.x <= gui.rect_button_menu.right&&point.y >= gui.rect_button_menu.top&&point.y <= gui.rect_button_menu.bottom)))
		{
			ReleaseDC(pDC);
			return;
		}
		if (point.x >= gui.rect_button_restart.left&&point.x <= gui.rect_button_restart.right&&point.y >= gui.rect_button_restart.top&&point.y <= gui.rect_button_restart.bottom)
		{
			HighlightButton(pDC, 1);
		}
		if (point.x >= gui.rect_button_menu.left&&point.x <= gui.rect_button_menu.right&&point.y >= gui.rect_button_menu.top&&point.y <= gui.rect_button_menu.bottom)
		{
			HighlightButton(pDC, 2);
		}
		ReleaseDC(pDC);
		break;
	}
	default:
		break;
	}
	CView::OnMouseMove(nFlags, point);
}


void CMy2048View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	switch (status)
	{
	case MAINMENU:
	{
		if (!((point.x >= gui.rect_menuitem_newgame.left&&point.x <= gui.rect_menuitem_newgame.right&&point.y >= gui.rect_menuitem_newgame.top&&point.y <= gui.rect_menuitem_newgame.bottom) || \
			(point.x >= gui.rect_menuitem_loadgame.left&&point.x <= gui.rect_menuitem_loadgame.right&&point.y >= gui.rect_menuitem_loadgame.top&&point.y <= gui.rect_menuitem_loadgame.bottom) || \
			(point.x >= gui.rect_menuitem_exitgame.left&&point.x <= gui.rect_menuitem_exitgame.right&&point.y >= gui.rect_menuitem_exitgame.top&&point.y <= gui.rect_menuitem_exitgame.bottom)))
		{
			ReleaseDC(pDC);
			return;
		}
		if (point.x >= gui.rect_menuitem_newgame.left&&point.x <= gui.rect_menuitem_newgame.right&&point.y >= gui.rect_menuitem_newgame.top&&point.y <= gui.rect_menuitem_newgame.bottom)
		{
			status = INGAME;
			CMy2048Doc *pDoc = GetDocument();
			fopen_s(&pDoc->fp, "C:\\Users\\thinkpad\\Documents\\My Games\\2048\\TempData.txt", "w");
			pDoc->GenerateNewGame();
			Invalidate();
		}
		if (point.x >= gui.rect_menuitem_loadgame.left&&point.x <= gui.rect_menuitem_loadgame.right&&point.y >= gui.rect_menuitem_loadgame.top&&point.y <= gui.rect_menuitem_loadgame.bottom)
		{
			CMy2048Doc *pDoc = GetDocument();
			if (GetFileAttributes(_T("C:\\Users\\thinkpad\\Documents\\My Games\\2048\\TempData.txt")) == -1)
			{
				MessageBox(_T("No save games!"), _T("Warnings"), MB_OK);
			}
			else
			{
				fopen_s(&pDoc->fp, "C:\\Users\\thinkpad\\Documents\\My Games\\2048\\TempData.txt", "r");
				char c = fgetc(pDoc->fp);
				if (c == EOF)
				{
					fclose(pDoc->fp);
					MessageBox(_T("No save games!"), _T("Warnings"), MB_OK);
				}
				else
				{
					rewind(pDoc->fp);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							fscanf_s(pDoc->fp, "%d ", &(pDoc->data[i][j]), sizeof(int));
						}
					}
					fscanf_s(pDoc->fp, "%d", &(pDoc->score), sizeof(int));
					fclose(pDoc->fp);
					fopen_s(&pDoc->fp, "C:\\Users\\thinkpad\\Documents\\My Games\\2048\\TempData.txt", "w");
					status = INGAME;
					Invalidate();
				}
			}
		}
		if (point.x >= gui.rect_menuitem_exitgame.left&&point.x <= gui.rect_menuitem_exitgame.right&&point.y >= gui.rect_menuitem_exitgame.top&&point.y <= gui.rect_menuitem_exitgame.bottom)
		{
			exit(0);
		}
		ReleaseDC(pDC);
		break;
	}
	case INGAME:
	{
		if (!((point.x >= gui.rect_button_restart.left&&point.x <= gui.rect_button_restart.right&&point.y >= gui.rect_button_restart.top&&point.y <= gui.rect_button_restart.bottom) || \
			(point.x >= gui.rect_button_menu.left&&point.x <= gui.rect_button_menu.right&&point.y >= gui.rect_button_menu.top&&point.y <= gui.rect_button_menu.bottom)))
		{
			ReleaseDC(pDC);
			return;
		}
		if (point.x >= gui.rect_button_restart.left&&point.x <= gui.rect_button_restart.right&&point.y >= gui.rect_button_restart.top&&point.y <= gui.rect_button_restart.bottom)
		{
			CMy2048Doc *pDoc = GetDocument();
			fclose(pDoc->fp);
			fopen_s(&pDoc->fp, "C:\\Users\\thinkpad\\Documents\\My Games\\2048\\TempData.txt", "w");
			pDoc->GenerateNewGame();
			Invalidate();
		}
		if (point.x >= gui.rect_button_menu.left&&point.x <= gui.rect_button_menu.right&&point.y >= gui.rect_button_menu.top&&point.y <= gui.rect_button_menu.bottom)
		{
			CMy2048Doc *pDoc = GetDocument();
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					fprintf_s(pDoc->fp, "%d ", pDoc->data[i][j], sizeof(int));
				}
			}
			fprintf_s(pDoc->fp, "%d", pDoc->score, sizeof(int));
			fclose(pDoc->fp);
			status = MAINMENU;
			Invalidate();
		}
		ReleaseDC(pDC);
		break;
	}
	default:
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy2048View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (status == MAINMENU)
	{
		return;
	}
	CMy2048Doc *pDoc = GetDocument();
	bool flag_GenerateNewLattice = FALSE;
	switch (nChar)
	{
	case VK_UP:
	{
		//MessageBox(_T("The key up is pressed."), _T("Info"), MB_OK);
		flag_GenerateNewLattice = pDoc->MoveUp();
		break;
	}
	case VK_DOWN:
	{
		//MessageBox(_T("The key down is pressed."), _T("Info"), MB_OK);
		flag_GenerateNewLattice = pDoc->MoveDown();
		break;
	}
	case VK_LEFT:
	{
		//MessageBox(_T("The key left is pressed."), _T("Info"), MB_OK);
		flag_GenerateNewLattice = pDoc->MoveLeft();
		break;
	}
	case VK_RIGHT:
	{
		//MessageBox(_T("The key right is pressed."), _T("Info"), MB_OK);
		flag_GenerateNewLattice = pDoc->MoveRight();
		break;
	}
	default:
		break;
	}
	if (flag_GenerateNewLattice == TRUE)
	{
		pDoc->GenerateNewLattice();
	}
	Invalidate();
	int flag_CurrentStatus = pDoc->JudgeCurrentStatus();
	switch (flag_CurrentStatus)
	{
	case 0:
	{
		break;
	}
	case 1:
	{
		MessageBox(_T("You win!"), _T("Congratulations!"), MB_OK);
		pDoc->GenerateNewGame();
		Invalidate();
		break;
	}
	case -1:
	{
		MessageBox(_T("You lose!"), _T("Oops!"), MB_OK);
		pDoc->GenerateNewGame();
		Invalidate();
		break;
	}
	default:
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

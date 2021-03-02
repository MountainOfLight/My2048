
// My2048Doc.cpp : CMy2048Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "My2048.h"
#endif

#include "My2048Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2048Doc

IMPLEMENT_DYNCREATE(CMy2048Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy2048Doc, CDocument)
END_MESSAGE_MAP()


// CMy2048Doc 构造/析构

CMy2048Doc::CMy2048Doc()
{
	// TODO:  在此添加一次性构造代码
	isWin = FALSE;
	isLose = FALSE;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = 0;
		}
	}
	score = 0;
	ratio_2to4 = 5;
}

CMy2048Doc::~CMy2048Doc()
{
}

BOOL CMy2048Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMy2048Doc 序列化

void CMy2048Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy2048Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CMy2048Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy2048Doc::SetSearchContent(const CString& value)
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

// CMy2048Doc 诊断

#ifdef _DEBUG
void CMy2048Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2048Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2048Doc 命令
int CMy2048Doc::random(int max)
{
	int random_seed = rand();
	srand(((int)time(0) + random_seed) % 65536);
	return rand() % (max + 1);
}


void CMy2048Doc::GenerateNewLattice()
{
	int count_empty = 0;
	CPoint index_empty[16];
	for (int k = 0; k < 16; k++)
	{
		index_empty[k] = CPoint(-1, -1);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (data[i][j] == 0)
			{
				index_empty[count_empty] = CPoint(i, j);
				count_empty++;
			}
		}
	}
	int lattice_index = random(count_empty - 1);
	int temp_x = index_empty[lattice_index].x, temp_y = index_empty[lattice_index].y;
	int lattice_value = random(ratio_2to4);
	if (lattice_value != ratio_2to4)
	{
		data[temp_x][temp_y] = 2;
	}
	else
	{
		data[temp_x][temp_y] = 4;
	}
}


void CMy2048Doc::GenerateNewGame()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = 0;
		}
	}
	score = 0;
	GenerateNewLattice();
	GenerateNewLattice();
}


int CMy2048Doc::JudgeCurrentStatus()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (data[i][j] == 2048)
			{
				return 1;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (data[i][j] == 0)
			{
				return 0;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (data[i][j] == data[i][j + 1])
			{
				return 0;
			}
		}
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (data[i][j] == data[i + 1][j])
			{
				return 0;
			}
		}
	}

	return -1;
}


bool CMy2048Doc::MoveUp()
{
	bool flag = FALSE;
	int sum = 0;
	double temp_data[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp_data[i][j] = (double)data[i][j];
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int t = 1; t <= 3; t++) // Is 3 times enough?
		{
			for (int x = 1; x < 4; x++)
			{
				if (temp_data[x][y] != 0 && temp_data[x - 1][y] == 0)
				{
					//MoveLattice(x - 1, y, x, y, (int)temp_data[x][y]);
					temp_data[x - 1][y] = temp_data[x][y];
					temp_data[x][y] = 0;
					flag = TRUE;
				}
				if (temp_data[x][y] != 0 && temp_data[x - 1][y] != 0 && temp_data[x][y] == temp_data[x - 1][y])
				{
					//MoveLattice(x - 1, y, x, y, (int)temp_data[x][y]);
					sum = (int)(sum + temp_data[x - 1][y] + temp_data[x][y]);
					score = (int)(score + temp_data[x - 1][y] + temp_data[x][y]);
					temp_data[x - 1][y] = temp_data[x - 1][y] + temp_data[x][y] + x / 100.0 + y / 100.0;
					temp_data[x][y] = 0;
					flag = TRUE;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = (int)temp_data[i][j];
		}
	}
	if (sum != 0)
	{
		AddScore(sum);
	}
	return flag;
}


bool CMy2048Doc::MoveDown()
{
	bool flag = FALSE;
	int sum = 0;
	double temp_data[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp_data[i][j] = (double)data[i][j];
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int t = 1; t <= 3; t++) // Is 3 times enough?
		{
			for (int x = 2; x > -1; x--)
			{
				if (temp_data[x][y] != 0 && temp_data[x + 1][y] == 0)
				{
					//MoveLattice(x, y, x + 1, y, (int)temp_data[x][y]);
					temp_data[x + 1][y] = temp_data[x][y];
					temp_data[x][y] = 0;
					flag = TRUE;
				}
				if (temp_data[x][y] != 0 && temp_data[x + 1][y] != 0 && temp_data[x][y] == temp_data[x + 1][y])
				{
					//MoveLattice(x, y, x + 1, y, (int)temp_data[x][y]);
					sum = (int)(sum + temp_data[x + 1][y] + temp_data[x][y]);
					score = (int)(score + temp_data[x + 1][y] + temp_data[x][y]);
					temp_data[x + 1][y] = temp_data[x + 1][y] + temp_data[x][y] + x / 100.0 + y / 100.0;
					temp_data[x][y] = 0;
					flag = TRUE;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = (int)temp_data[i][j];
		}
	}
	if (sum != 0)
	{
		AddScore(sum);
	}
	return flag;
}


bool CMy2048Doc::MoveLeft()
{
	bool flag = FALSE;
	int sum = 0;
	double temp_data[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp_data[i][j] = (double)data[i][j];
		}
	}

	for (int x = 0; x < 4; x++)
	{
		for (int t = 1; t <= 3; t++) // Is 3 times enough?
		{
			for (int y = 1; y < 4; y++)
			{
				if (temp_data[x][y] != 0 && temp_data[x][y - 1] == 0)
				{
					//MoveLattice(x, y - 1, x, y, (int)temp_data[x][y]);
					temp_data[x][y - 1] = temp_data[x][y];
					temp_data[x][y] = 0;
					flag = TRUE;
				}
				if (temp_data[x][y] != 0 && temp_data[x][y - 1] != 0 && temp_data[x][y] == temp_data[x][y - 1])
				{
					//MoveLattice(x, y - 1, x, y, (int)temp_data[x][y]);
					sum = (int)(sum + temp_data[x][y - 1] + temp_data[x][y]);
					score = (int)(score + temp_data[x][y - 1] + temp_data[x][y]);
					temp_data[x][y - 1] = temp_data[x][y - 1] + temp_data[x][y] + x / 100.0 + y / 100.0;
					temp_data[x][y] = 0;
					flag = TRUE;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = (int)temp_data[i][j];
		}
	}
	if (sum != 0)
	{
		AddScore(sum);
	}
	return flag;
}


bool CMy2048Doc::MoveRight()
{
	bool flag = FALSE;
	int sum = 0;
	double temp_data[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp_data[i][j] = (double)data[i][j];
		}
	}

	for (int x = 0; x < 4; x++)
	{
		for (int t = 1; t <= 3; t++) // Is 3 times enough?
		{
			for (int y = 2; y > -1; y--)
			{
				if (temp_data[x][y] != 0 && temp_data[x][y + 1] == 0)
				{
					//MoveLattice(x, y, x, y + 1, (int)temp_data[x][y]);
					temp_data[x][y + 1] = temp_data[x][y];
					temp_data[x][y] = 0;
					flag = TRUE;
				}
				if (temp_data[x][y] != 0 && temp_data[x][y + 1] != 0 && temp_data[x][y] == temp_data[x][y + 1])
				{
					//MoveLattice(x, y, x, y + 1, (int)temp_data[x][y]);
					sum = (int)(sum + temp_data[x][y + 1] + temp_data[x][y]);
					score = (int)(score + temp_data[x][y + 1] + temp_data[x][y]);
					temp_data[x][y + 1] = temp_data[x][y + 1] + temp_data[x][y] + x / 100.0 + y / 100.0;
					temp_data[x][y] = 0;
					flag = TRUE;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = (int)temp_data[i][j];
		}
	}
	if (sum != 0)
	{
		//AddScore(sum);
	}
	return flag;
}


void CMy2048Doc::MoveLattice(int x1, int y1, int x2, int y2, int value)
{
	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->GetSafeHwnd();
	HDC hDC = GetDC(hWnd);

	int i1 = y1, j1 = x1, i2 = y2, j2 = x2;
	int p1x = (int)(0.5*(gui.nodes[i1][j1].x + gui.nodes[i2][j2].x + 5));
	int p1y = (int)(0.5*(gui.nodes[i1][j1].y + gui.nodes[i2][j2].y + 5));
	int p2x = (int)(0.5*(gui.nodes[i1 + 1][j1 + 1].x + gui.nodes[i2 + 1][j2 + 1].x + 5));
	int p2y = (int)(0.5*(gui.nodes[i1 + 1][j1 + 1].y + gui.nodes[i2 + 1][j2 + 1].y + 5));
	
	Sleep(5);

	HBRUSH brush;
	brush=CreateSolidBrush(RGB(255, 255, 255));
	switch (value)
	{
	case 0:
		brush = CreateSolidBrush(gui.color_lattice);
		break;
	case 2:
		brush = CreateSolidBrush(gui.color_2_background);
		break;
	case 4:
		brush = CreateSolidBrush(gui.color_4_background);
		break;
	case 8:
		brush = CreateSolidBrush(gui.color_8_background);
		break;
	case 16:
		brush = CreateSolidBrush(gui.color_16_background);
		break;
	case 32:
		brush = CreateSolidBrush(gui.color_32_background);
		break;
	case 64:
		brush = CreateSolidBrush(gui.color_64_background);
		break;
	case 128:
		brush = CreateSolidBrush(gui.color_128_background);
		break;
	case 256:
		brush = CreateSolidBrush(gui.color_256_background);
		break;
	case 512:
		brush = CreateSolidBrush(gui.color_512_background);
		break;
	case 1024:
		brush = CreateSolidBrush(gui.color_1024_background);
		break;
	case 2048:
		brush = CreateSolidBrush(gui.color_2048_background);
		break;
	default:
		break;
	}
	SelectObject(hDC, brush);
	Rectangle(hDC, p1x, p1y, p2x, p2y);

	HPEN pen;
	pen = CreatePen(PS_SOLID, 5, gui.color_frame);
	SelectObject(hDC, pen);
	MoveToEx(hDC, p1x, p1y, NULL);
	LineTo(hDC, p2x, p1y);
	LineTo(hDC, p2x, p2y);
	LineTo(hDC, p1x, p2y);
	LineTo(hDC, p1x, p1y);
	
	Sleep(5);

	ReleaseDC(hWnd, hDC);
}


void CMy2048Doc::AddScore(int score)
{
	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->GetSafeHwnd();
	HDC hDC = GetDC(hWnd);

	RECT rect;
	rect.top = 35;
	rect.bottom = 45;
	rect.left = 270;
	rect.right = 300;
	HBRUSH brush;
	brush = CreateSolidBrush(gui.color_score_background);
	FillRect(hDC, &rect, brush);

	CString str;
	str.Format(_T("+%d"), score);

	HFONT font;
	font = CreateFont(10, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));
	SelectObject(hDC, font);
	SetTextColor(hDC, gui.color_score_text);
	SetBkMode(hDC, TRANSPARENT);

	DrawText(hDC, str, str.GetLength() + 1, CRect(270, 35, 300, 45), DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	Sleep(10);

	ReleaseDC(hWnd, hDC);
}

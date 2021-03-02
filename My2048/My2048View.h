
// My2048View.h : CMy2048View ��Ľӿ�
//

#pragma once
#include <Windows.h>
#include "My2048Doc.h"
#include "GUIsettings.h"

enum STATUS{ MAINMENU, INGAME };

class CMy2048View : public CView
{
protected: // �������л�����
	CMy2048View();
	DECLARE_DYNCREATE(CMy2048View)
	STATUS status;
	GUIsettings gui;

// ����
public:
	CMy2048Doc* GetDocument() const;

// ����
public:
	void SetBackground(CDC *pDC);
	void SetTitle(CDC *pDC);
	void DrawMainMenu(CDC *pDC);
	void HighlightMenuitem(CDC *pDC, int flag);
	void DrawButtons(CDC *pDC);
	void HighlightButton(CDC *pDC, int flag);
	void DrawFrame(CDC *pDC);
	void DrawSingleLattice(CDC *pDC, int x, int y, int value);
	void DrawCurrentData(CDC *pDC);
	void RefreshScore(CDC *pDC);

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy2048View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // My2048View.cpp �еĵ��԰汾
inline CMy2048Doc* CMy2048View::GetDocument() const
   { return reinterpret_cast<CMy2048Doc*>(m_pDocument); }
#endif


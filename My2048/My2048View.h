
// My2048View.h : CMy2048View 类的接口
//

#pragma once
#include <Windows.h>
#include "My2048Doc.h"
#include "GUIsettings.h"

enum STATUS{ MAINMENU, INGAME };

class CMy2048View : public CView
{
protected: // 仅从序列化创建
	CMy2048View();
	DECLARE_DYNCREATE(CMy2048View)
	STATUS status;
	GUIsettings gui;

// 特性
public:
	CMy2048Doc* GetDocument() const;

// 操作
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

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy2048View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // My2048View.cpp 中的调试版本
inline CMy2048Doc* CMy2048View::GetDocument() const
   { return reinterpret_cast<CMy2048Doc*>(m_pDocument); }
#endif


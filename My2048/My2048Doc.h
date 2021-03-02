
// My2048Doc.h : CMy2048Doc 类的接口
//


#pragma once
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "GUIsettings.h"


class CMy2048Doc : public CDocument
{
protected: // 仅从序列化创建
	CMy2048Doc();
	DECLARE_DYNCREATE(CMy2048Doc)
	bool isWin;
	bool isLose;
	int data[4][4];
	int score;
	int ratio_2to4;
	FILE *fp;
	GUIsettings gui;

// 特性
public:
	int random(int max);
	void GenerateNewLattice();
	void GenerateNewGame();
	int JudgeCurrentStatus();
	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();
	void MoveLattice(int x1, int y1, int x2, int y2, int value);
	void AddScore(int score);

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMy2048Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
